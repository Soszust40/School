package com.example.assignment2;

import android.content.Context;
import android.content.SharedPreferences;

import org.json.JSONArray;
import org.json.JSONException;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Locale;
import java.util.Set;

/**
 * Single source of truth for posts.
 * - In-memory list (fast UI)
 * - JSON persistence in SharedPreferences (survives app restarts)
 * - Simple observer pattern so screens refresh live on changes
 */
public class DataStore {

    // --- Observer pattern (UI refresh hooks) ---
    public interface OnChangeListener { void onDataChanged(); }
    private static final Set<OnChangeListener> LISTENERS = new HashSet<>();
    public static void addListener(OnChangeListener l) { if (l != null) LISTENERS.add(l); }
    public static void removeListener(OnChangeListener l) { LISTENERS.remove(l); }
    private static com.google.firebase.firestore.ListenerRegistration realtimeListener;
    private static void notifyChanged() {
        // Copy to avoid ConcurrentModification if a listener removes themselves while iterating.
        for (OnChangeListener l : new ArrayList<>(LISTENERS)) l.onDataChanged();
    }

    // For persistence:
    private static final String PREF = "data_store";
    private static final String KEY_POSTS = "posts_json";

    private static SharedPreferences sp(Context c) {
        return c.getSharedPreferences(PREF, Context.MODE_PRIVATE);
    }

    private static void save(Context c) {
        JSONArray arr = new JSONArray();
        for (Post p : ALL) {
            try { arr.put(p.toJson()); } catch (JSONException ignored) {}
        }
        sp(c).edit().putString(KEY_POSTS, arr.toString()).apply();
    }

    private static void load(Context c) {
        ALL.clear();
        String raw = sp(c).getString(KEY_POSTS, null);
        if (raw == null || raw.isEmpty()) {
            seedSamples();
            // Persist seed so the first run looks the same after relaunch even if the user hasn't posted yet.
            save(c);
            return;
        }
        try {
            JSONArray arr = new JSONArray(raw);
            for (int i = 0; i < arr.length(); i++) {
                Post p = Post.fromJson(arr.getJSONObject(i));
                ALL.add(p);
            }
        } catch (Exception e) {
            // if the cache is corrupted start over with samples
            seedSamples();
            save(c);
        }
    }

    // Data in memory:
    private static final List<Post> ALL = new ArrayList<>();
    private static boolean initialized = false;

    // used AI to generate these samples:
    private static void seedSamples() {
        ALL.clear();

        // East Lansing, Michigan
        ALL.add(new Post(
                "Album Review — Aurora",
                "by sophiedemo  •  Album",
                "A luminous debut that blends ambient textures with clever lyricism. Standout tracks include 'Drift' and 'Solaris'. Production leans warm—perfect with our terracotta vibe.",
                "I found a light where the night had been",
                "0:18 — 0:30",
                120, 24,
                "Aurora",
                "sophiedemo",
                42.7325, -84.5555,
                "East Lansing, MI"
        ));

        // Los Angeles, California
        ALL.add(new Post(
                "Song Review — Skyline",
                "by evademo  •  Single",
                "Punchy drums, glossy synths, and a chorus that sticks. Could be mixed louder, but the dynamics are refreshing for pop.",
                null,
                "0:42 — 0:56",
                89, 15,
                "Skyline",
                "evademo",
                34.0522, -118.2437,
                "Los Angeles, CA"
        ));

        // New York, New York
        ALL.add(new Post(
                "Concert Review — MUNA",
                "by catiedemo  •  Live",
                "High-energy set with flawless harmonies. Crowd interaction 10/10. If you go, don't miss the encore—pure serotonin.",
                null,
                "1:10 — 1:28",
                143, 31,
                "Number One Fan",
                "catiedemo",
                40.7128, -74.0060,
                "New York, NY"
        ));
    }

    /** Call once (e.g., in HomeActivity.onCreate) to load persisted posts. */
    public static synchronized void init(Context c) {
        if (initialized) return;
        load(c.getApplicationContext());
        initialized = true;

        // Start realtime listening
        startRealtimeSync(c.getApplicationContext());
    }

    /** Add a post for the current user, persist, and notify observers. */
    public static void addUserPost(Context c, String title, String body, String song, String lyrics, String clip, Double lat, Double lon, String locationName) {
        String username = AuthManager.currentUser(c);
        if (username == null || username.isEmpty()) username = "guest";
        String subtitle = "by " + username + "  •  Post";
        Post p = new Post(
                (title == null || title.isEmpty()) ? "Untitled Post" : title,
                subtitle,
                body == null ? "" : body,
                (lyrics == null || lyrics.isEmpty()) ? null : lyrics,
                (clip == null || clip.isEmpty()) ? null : clip,
                0, 0,
                (song == null || song.isEmpty()) ? null : song,
                username,
                lat,
                lon,
                locationName
        );
        ALL.add(0, p); // newest first
        save(c);
        notifyChanged();
    }

    /** All posts (copy) for feeds/search. */
    public static List<Post> getAllPosts() {
        return new ArrayList<>(ALL);
    }

    /** Only the logged-in user's posts (copy) for Profile. */
    public static List<Post> getUserPosts(Context c) {
        String email = AuthManager.currentUser(c);
        List<Post> out = new ArrayList<>();
        if (email == null) return out;
        for (Post p : ALL) {
            if (email.equalsIgnoreCase(p.authorEmail)) out.add(p);
        }
        return out;
    }

    /** Simple search across song/title/body/lyrics (case-insensitive). */
    public static List<Post> search(String query) {
        if (query == null || query.trim().isEmpty()) return getAllPosts();
        String q = query.toLowerCase(Locale.US);
        List<Post> out = new ArrayList<>();
        for (Post p : ALL) {
            boolean match = (p.song != null && p.song.toLowerCase(Locale.US).contains(q))
                    || p.title.toLowerCase(Locale.US).contains(q)
                    || p.text.toLowerCase(Locale.US).contains(q)
                    || (p.lyrics != null && p.lyrics.toLowerCase(Locale.US).contains(q));
            if (match) out.add(p);
        }
        return out;
    }

    /** Delete a post by matching object, persist, and notify observers. */
    public static boolean deletePost(Context c, Post postToDelete) {
        if (postToDelete == null) return false;
        boolean removed = ALL.remove(postToDelete);
        if (removed) {
            save(c);
            notifyChanged();
        }
        return removed;
    }

    /** Sync posts from Firestore and merge with local data. */
    private static void startRealtimeSync(Context c) {
        if (realtimeListener != null) return; // prevent duplicates

        com.google.firebase.firestore.FirebaseFirestore db =
                com.google.firebase.firestore.FirebaseFirestore.getInstance();

        realtimeListener = db.collection("posts")
                .orderBy("createdAt", com.google.firebase.firestore.Query.Direction.DESCENDING)
                .addSnapshotListener((snap, error) -> {
                    if (error != null || snap == null) return;

                    List<Post> remote = new ArrayList<>();
                    for (com.google.firebase.firestore.DocumentSnapshot doc : snap.getDocuments()) {
                        try {
                            remote.add(PostManager.fromDoc(doc));
                        } catch (Exception ignored) {}
                    }

                    mergeRemotePosts(c, remote);
                });
    }


    /** Manual refresh with callback for UI feedback. */
    public static void refreshFromFirestore(Context c, Runnable onComplete) {
        PostManager manager = new PostManager();
        manager.readPosts(remotePosts -> {
            // Merge remote posts with local posts
            mergeRemotePosts(c, remotePosts);
            if (onComplete != null) onComplete.run();
        }, error -> {
            // Log error but still call onComplete
            android.util.Log.w("DataStore", "Failed to refresh from Firestore", error);
            if (onComplete != null) onComplete.run();
        });
    }

    /** Toggle like on a post and sync with Firestore */
    public static void toggleLike(Context c, Post post, LikeCallback callback) {
        if (post == null || post.id == null || post.id.isEmpty()) {
            // Post has no Firestore id yet. Try to upload it first, then like.
            PostManager uploader = new PostManager();
            uploader.addPost(post, newId -> {
                if (post != null) {
                    post.id = newId;
                }
                // Persist the new id locally so merge logic and future ops work
                save(c);
                notifyChanged();
                // Now attempt the like operation
                PostManager liker = new PostManager();
                String currentUserId = getCurrentUserId();
                if (post != null){
                    boolean currentlyLiked = post.isLikedByUser(currentUserId);
                    liker.toggleLike(post.id, currentlyLiked, newLikeStatus -> {
                        updateLocalPostLike(post, currentUserId, newLikeStatus);
                        save(c);
                        notifyChanged();
                        if (callback != null) callback.onResult(newLikeStatus, null);
                    }, error -> {
                        String msg = error == null ? "" : (error.getMessage() == null ? error.toString() : error.getMessage());
                        if (callback != null) callback.onResult(false, "Failed to sync like: " + msg);
                    });
                }
            }, err -> {
                String msg = err == null ? "" : (err.getMessage() == null ? err.toString() : err.getMessage());
                if (callback != null) callback.onResult(false, "Failed to upload post before liking: " + msg);
            });
            return;
        }
        
        String currentUserId = getCurrentUserId();
        if (currentUserId == null) {
            if (callback != null) callback.onResult(false, "Not signed in");
            return;
        }
        
        boolean currentlyLiked = post.isLikedByUser(currentUserId);
        
        PostManager manager = new PostManager();
        manager.toggleLike(post.id, currentlyLiked, newLikeStatus -> {
            // Update local post immediately
            updateLocalPostLike(post, currentUserId, newLikeStatus);
            save(c);
            notifyChanged();
            if (callback != null) callback.onResult(newLikeStatus, null);
        }, error -> {
            String msg = error == null ? "" : (error.getMessage() == null ? error.toString() : error.getMessage());
            if (callback != null) callback.onResult(currentlyLiked, "Failed to sync like: " + msg);
        });
    }
    
    /** Update local post like status */
    private static void updateLocalPostLike(Post post, String userId, boolean liked) {
        if (post.likedBy == null) {
            post.likedBy = new java.util.HashSet<>();
        }
        
        if (liked) {
            if (!post.likedBy.contains(userId)) {
                post.likedBy.add(userId);
                post.likes++;
            }
        } else {
            if (post.likedBy.contains(userId)) {
                post.likedBy.remove(userId);
                post.likes = Math.max(0, post.likes - 1);
            }
        }
    }
    
    /** Get current user ID for like tracking */
    private static String getCurrentUserId() {
        // Use Firebase Auth to get user ID
        com.google.firebase.auth.FirebaseUser user = com.google.firebase.auth.FirebaseAuth.getInstance().getCurrentUser();
        return user != null ? user.getUid() : null;
    }
    
    /** Callback for like operations */
    public interface LikeCallback {
        void onResult(boolean isLiked, String error);
    }

    /** Merge remote posts with local posts, avoiding duplicates. */
    private static void mergeRemotePosts(Context c, java.util.List<Post> remotePosts) {
        boolean dataChanged = false;
        
        // Create a set of existing post IDs for quick lookup
        java.util.Set<String> existingIds = new java.util.HashSet<>();
        for (Post localPost : ALL) {
            if (localPost.id != null) {
                existingIds.add(localPost.id);
            }
        }
        
        // Add remote posts that don't exist locally
        for (Post remotePost : remotePosts) {
            if (remotePost.id != null && !existingIds.contains(remotePost.id)) {
                ALL.add(remotePost);
                dataChanged = true;
            }
        }
        
        if (dataChanged) {
            save(c);
            notifyChanged();
        }
    }

}