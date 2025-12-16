package com.example.assignment2;

import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.SearchView;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.bottomnavigation.BottomNavigationView;

import java.util.List;

/**
 * Search screen:
 * - Full-width SearchView at the top
 * - Live filtering of posts as the user types
 * - Remembers the last query across rotation
 * - Updates if new posts are added while open (DataStore listener)
 */
public class SearchActivity extends AppCompatActivity implements DataStore.OnChangeListener {

    private static final String K_QUERY = "k_query"; // key to save/restore query text

    private RecyclerView recyclerView;
    private View emptyView;
    private PostAdapter adapter;
    private String currentQuery = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search);

        // Make layout resize when keyboard opens so the list isn't covered
        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_ADJUST_RESIZE);

        // Grab views
        SearchView searchView = findViewById(R.id.searchView);
        recyclerView = findViewById(R.id.recycler);
        emptyView    = findViewById(R.id.tvEmpty);

        // Basic list setup
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        adapter = new PostAdapter(DataStore.getAllPosts());
        
        // Set up delete functionality
        String currentUser = AuthManager.currentUser(this);
        adapter.setDeleteListener(this::deletePost, currentUser);
        
        // Set up like functionality
        String currentUserId = getCurrentUserId();
        adapter.setLikeListener(this::likePost, currentUser, currentUserId);
        
        recyclerView.setAdapter(adapter);

        // Expand search by default so typing is immediate
        searchView.setIconifiedByDefault(false);
        searchView.setIconified(false);
        searchView.onActionViewExpanded();

        // Live filtering: run search on submit AND on each keystroke
        searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener() {
            @Override public boolean onQueryTextSubmit(String q) { applyQuery(q); return true; }
            @Override public boolean onQueryTextChange(String q) { applyQuery(q); return true; }
        });

        // Restore query text after rotation (and re-apply it)
        if (savedInstanceState != null) {
            currentQuery = savedInstanceState.getString(K_QUERY, "");
            if (!currentQuery.isEmpty()) {
                searchView.setQuery(currentQuery, false);
                applyQuery(currentQuery);
            }
        }

        // Bottom nav wiring (highlight Search tab)
        BottomNavigationView nav = findViewById(R.id.bottom_navigation);
        BaseNav.setup(this, nav, R.id.nav_search);
    }

    // Runs the actual search and toggles empty/list states
    private void applyQuery(String q) {
        currentQuery = (q == null) ? "" : q.trim();
        List<Post> results = DataStore.search(currentQuery);

        adapter.setData(results); // refresh list

        boolean empty = results.isEmpty();
        emptyView.setVisibility(empty ? View.VISIBLE : View.GONE);
        recyclerView.setVisibility(empty ? View.GONE : View.VISIBLE);
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle out) {
        super.onSaveInstanceState(out);
        // Remember whatever the user typed so far
        out.putString(K_QUERY, currentQuery);
    }

    // Keep results fresh if someone posts while this screen is visible
    @Override protected void onStart() {
        super.onStart();
        DataStore.addListener(this);
    }

    @Override protected void onStop() {
        DataStore.removeListener(this); // avoid leaks
        super.onStop();
    }

    // Data changed somewhere else, re-run the same query
    @Override public void onDataChanged() {
        applyQuery(currentQuery);
    }

    /** Handle post deletion with confirmation dialog */
    private void deletePost(Post post) {
        new AlertDialog.Builder(this)
            .setTitle("Delete Post")
            .setMessage("Are you sure you want to delete this post? This action cannot be undone.")
            .setPositiveButton("Delete", (dialog, which) -> {
                // Delete from Firestore if post has an ID
                if (post.id != null && !post.id.isEmpty()) {
                    PostManager manager = new PostManager();
                    manager.deletePostById(post.id, success -> {
                        // Always delete from local store regardless of Firestore success
                        deleteFromLocalStore(post);
                    }, error -> {
                        // Still delete from local store even if Firestore fails
                        Toast.makeText(this, "Network error, but deleted locally", Toast.LENGTH_SHORT).show();
                        deleteFromLocalStore(post);
                    });
                } else {
                    // No Firestore ID, just delete locally
                    deleteFromLocalStore(post);
                }
            })
            .setNegativeButton("Cancel", null)
            .show();
    }

    /** Delete post from local DataStore and refresh UI */
    private void deleteFromLocalStore(Post post) {
        boolean deleted = DataStore.deletePost(this, post);
        if (deleted) {
            Toast.makeText(this, "Post deleted", Toast.LENGTH_SHORT).show();
            // UI will refresh automatically via DataStore listener pattern
        } else {
            Toast.makeText(this, "Could not delete post", Toast.LENGTH_SHORT).show();
        }
    }
    
    /** Handle like button clicks */
    private void likePost(Post post) {
        DataStore.toggleLike(this, post, (isLiked, error) -> {
            if (error != null) {
                Toast.makeText(this, error, Toast.LENGTH_SHORT).show();
            }
            // UI will refresh automatically via DataStore listener pattern
        });
    }
    
    /** Get current user ID for like tracking */
    private String getCurrentUserId() {
        com.google.firebase.auth.FirebaseUser user = com.google.firebase.auth.FirebaseAuth.getInstance().getCurrentUser();
        return user != null ? user.getUid() : null;
    }
}
