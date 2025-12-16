package com.example.assignment2;

import androidx.annotation.Nullable;

import com.google.firebase.Timestamp;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.firestore.DocumentSnapshot;
import com.google.firebase.firestore.FirebaseFirestore;

import java.util.HashMap;
import java.util.Map;

/** Controls posts using firebase */
public class PostManager {

    private static final String COL = "posts";

    private final FirebaseFirestore db = FirebaseFirestore.getInstance();
    private final FirebaseAuth auth = FirebaseAuth.getInstance();

    /** Callback types (avoids needing Java 8 Consumer). */
    public interface SuccessString { void call(String value); }
    public interface SuccessBool { void call(boolean ok); }
    public interface SuccessPostList { void call(java.util.List<Post> posts); }
    public interface Failure { void call(Throwable t); }

    /** Create a post document. Returns the new document id on success. */
    public void addPost(Post p,
                        SuccessString onSuccess,
                        @Nullable Failure onFailure) {

        FirebaseUser user = auth.getCurrentUser();
        if (user == null) {
            if (onFailure != null) onFailure.call(new IllegalStateException("Not signed in"));
            return;
        }

        // Ensure author fields present
        String authorUid = user.getUid();
        String authorEmail = user.getEmail() != null ? user.getEmail() : "unknown@user";

        // Build Firestore map
        Map<String, Object> m = new HashMap<>();
        m.put("title", nz(p.title));
        m.put("subtitle", nz(p.subtitle));
        m.put("text", nz(p.text));
        m.put("lyrics", nullable(p.lyrics));
        m.put("clip", nullable(p.clip));
        m.put("likes", p.likes);
        m.put("comments", p.comments);
        m.put("song", nullable(p.song));
        m.put("likedBy", new java.util.ArrayList<String>()); // Initialize empty likes array
        m.put("authorEmail", authorEmail);
        m.put("authorUid", authorUid);
        if (p.latitude != null)  m.put("latitude", p.latitude);
        if (p.longitude != null) m.put("longitude", p.longitude);
        if (p.locationName != null) m.put("locationName", p.locationName);
        m.put("createdAt", Timestamp.now()); // server time for ordering

        db.collection(COL)
                .add(m)
                .addOnSuccessListener(ref -> {
                    p.id = ref.getId();
                    if (onSuccess != null) onSuccess.call(ref.getId());
                })
                .addOnFailureListener(e -> {
                    if (onFailure != null) onFailure.call(e);
                });
    }

    /** Delete a post by its Firestore document id. */
    public void deletePostById(String postId,
                               SuccessBool onDone,
                               @Nullable Failure onFailure) {
        db.collection(COL)
                .document(postId)
                .delete()
                .addOnSuccessListener(aVoid -> onDone.call(true))
                .addOnFailureListener(e -> {
                    if (onFailure != null) onFailure.call(e);
                    onDone.call(false);
                });
    }

    /** Like or unlike a post. Updates both like count and user's like status. */
    public void toggleLike(String postId, boolean currentlyLiked,
                          SuccessBool onSuccess,
                          @Nullable Failure onFailure) {
        
        FirebaseUser user = auth.getCurrentUser();
        if (user == null) {
            if (onFailure != null) onFailure.call(new IllegalStateException("Not signed in"));
            return;
        }
        
        String userId = user.getUid();
        
        // Use a transaction to ensure consistency
        db.runTransaction(transaction -> {
            // Read current post state
            DocumentSnapshot postDoc = transaction.get(db.collection(COL).document(postId));
            if (!postDoc.exists()) {
                throw new IllegalStateException("Post not found");
            }
            
            // Get current likes count and likedBy array
            Long currentLikes = postDoc.getLong("likes");
            if (currentLikes == null) currentLikes = 0L;
            
            java.util.List<String> likedBy = (java.util.List<String>) postDoc.get("likedBy");
            if (likedBy == null) likedBy = new java.util.ArrayList<>();
            
            // Toggle like status
            boolean isLiked = likedBy.contains(userId);
            // Use a local variable to avoid mutating the method parameter inside the lambda
            boolean clientLiked = currentlyLiked;
            if (clientLiked != isLiked) {
                // Client state is out of sync, use server state as truth
                clientLiked = isLiked;
            }

            if (clientLiked) {
                // Unlike: remove user from likedBy and decrement count
                likedBy.remove(userId);
                currentLikes = Math.max(0, currentLikes - 1);
            } else {
                // Like: add user to likedBy and increment count
                if (!likedBy.contains(userId)) {
                    likedBy.add(userId);
                }
                currentLikes++;
            }

            // Update the document
            transaction.update(db.collection(COL).document(postId), 
                "likes", currentLikes,
                "likedBy", likedBy);

            return !clientLiked; // Return new like status
        }).addOnSuccessListener(onSuccess::call).addOnFailureListener(e -> {
            if (onFailure != null) onFailure.call(e);
        });
    }

    /** Read all posts from Firestore, ordered by creation time (newest first). */
    public void readPosts(SuccessPostList onSuccess,
                         @Nullable Failure onFailure) {
        db.collection(COL)
                .orderBy("createdAt", com.google.firebase.firestore.Query.Direction.DESCENDING)
                .get()
                .addOnSuccessListener(querySnapshot -> {
                    java.util.List<Post> posts = new java.util.ArrayList<>();
                    for (DocumentSnapshot doc : querySnapshot.getDocuments()) {
                        try {
                            Post post = fromDoc(doc);
                            posts.add(post);
                        } catch (Exception e) {
                            // Skip malformed documents, continue processing others
                            android.util.Log.w("PostManager", "Skipping malformed post: " + doc.getId(), e);
                        }
                    }
                    onSuccess.call(posts);
                })
                .addOnFailureListener(e -> {
                    if (onFailure != null) onFailure.call(e);
                });
    }

    /** Optional: turn a Firestore doc into a Post (useful when you add reading). */
    public static Post fromDoc(DocumentSnapshot d) {
        Post p = new Post(
                nz(d.getString("title")),
                nz(d.getString("subtitle")),
                nz(d.getString("text")),
                d.getString("lyrics"),
                d.getString("clip"),
                toInt(d.getLong("likes")),
                toInt(d.getLong("comments")),
                d.getString("song"),
                nz(d.getString("authorEmail")),
                d.getDouble("latitude"),
                d.getDouble("longitude"),
                d.getString("locationName")
        );
        p.id = d.getId();
        
        // Set likedBy list for tracking user likes
        java.util.List<String> likedBy = (java.util.List<String>) d.get("likedBy");
        if (likedBy != null) {
            p.likedBy = new java.util.HashSet<>(likedBy);
        }
        
        return p;
    }

    private static String nz(String s) { return s == null ? "" : s; }
    private static String nullable(String s) { return (s == null || s.isEmpty()) ? null : s; }
    private static int toInt(Long v) { return v == null ? 0 : v.intValue(); }
}
