package com.example.assignment2;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import androidx.appcompat.widget.SwitchCompat;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.bottomnavigation.BottomNavigationView;

import java.util.List;

/**
 * Profile screen:
 * - Shows who is logged in (username/email)
 * - Lets the user edit display name, bio, and public/private toggle (from Firestore)
 * - Lists ONLY this user's posts
 * - Supports logout back to LoginActivity
 */
public class ProfileActivity extends AppCompatActivity implements DataStore.OnChangeListener {

    // Header/profile widgets
    private EditText etName, etBio;
    private SwitchCompat swPublic;
    private Button btnSave;

    private View empty;
    private PostAdapter profileAdapter;

    private ProfileManager profileManager;

    @Override
    protected void onCreate(Bundle s) {
        super.onCreate(s);
        setContentView(R.layout.activity_profile);

        profileManager = new ProfileManager();

        // Header widgets
        TextView tvUsername = findViewById(R.id.tvUsername);
        etName   = findViewById(R.id.etName);
        etBio    = findViewById(R.id.etBio);
        swPublic = findViewById(R.id.swPublic);
        btnSave   = findViewById(R.id.btnSave);
        Button btnLogout = findViewById(R.id.btnLogout);

        // Determines which user is logged in
        String username = AuthManager.currentUser(this);
        if (username == null) username = "guest";
        tvUsername.setText(username);

        loadProfileData();

        btnSave.setOnClickListener(v -> saveProfileData());

        // Logout
        btnLogout.setOnClickListener(v -> {
            AuthManager.logout(this);
            Intent i = new Intent(this, LoginActivity.class);
            i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
            startActivity(i);
            finish();
        });

        // Posts list (per-user)
        // Posts list widgets
        RecyclerView rv = findViewById(R.id.rvProfile);
        empty = findViewById(R.id.tvEmptyProfile);
        rv.setLayoutManager(new LinearLayoutManager(this));

        // Initializing adapter with this user's posts
        List<Post> mine = DataStore.getUserPosts(this);
        profileAdapter = new PostAdapter(mine);

        // Set up delete functionality for user's own posts
        profileAdapter.setDeleteListener(this::deletePost, username);
        
        // Set up like functionality
        String currentUserId = getCurrentUserId();
        profileAdapter.setLikeListener(this::likePost, username, currentUserId);

        rv.setAdapter(profileAdapter);
        empty.setVisibility(profileAdapter.getItemCount() == 0 ? View.VISIBLE : View.GONE);

        // Bottom navigation
        BottomNavigationView nav = findViewById(R.id.bottom_navigation);
        BaseNav.setup(this, nav, R.id.nav_profile);
    }

    /**
     * Loads profile data from Firestore asynchronously.
     */
    private void loadProfileData() {
        // Disable editing while loading
        etName.setEnabled(false);
        etBio.setEnabled(false);
        swPublic.setEnabled(false);

        profileManager.loadProfile(new ProfileManager.ProfileLoadCallback() {
            @Override
            public void onSuccess(ProfileManager.UserProfile profile) {
                runOnUiThread(() -> {
                    // Populate UI with data from Firestore
                    etName.setText(profile.name);
                    etBio.setText(profile.bio);
                    swPublic.setChecked(profile.isPublic);

                    // Re-enable editing
                    etName.setEnabled(true);
                    etBio.setEnabled(true);
                    swPublic.setEnabled(true);
                });
            }

            @Override
            public void onFailure(Exception e) {
                runOnUiThread(() -> {
                    Toast.makeText(ProfileActivity.this, "Failed to load profile", Toast.LENGTH_SHORT).show();
                    // Re-enable editing even on failure
                    etName.setEnabled(true);
                    etBio.setEnabled(true);
                    swPublic.setEnabled(true);
                });
            }
        });
    }

    /**
     * Saves profile data to Firestore asynchronously.
     */
    private void saveProfileData() {
        String name = etName.getText().toString().trim();
        String bio = etBio.getText().toString().trim();
        boolean isPublic = swPublic.isChecked();

        // Disable button while saving
        btnSave.setEnabled(false);
        Toast.makeText(this, "Saving...", Toast.LENGTH_SHORT).show();

        profileManager.saveProfile(name, bio, isPublic, new ProfileManager.ProfileSaveCallback() {
            @Override
            public void onSuccess() {
                runOnUiThread(() -> {
                    Toast.makeText(ProfileActivity.this, getString(R.string.profile_saved), Toast.LENGTH_SHORT).show();
                    btnSave.setEnabled(true);
                });
            }

            @Override
            public void onFailure(Exception e) {
                runOnUiThread(() -> {
                    Toast.makeText(ProfileActivity.this, "Failed to save profile", Toast.LENGTH_SHORT).show();
                    btnSave.setEnabled(true);
                });
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        // Register for DataStore changes
        DataStore.addListener(this);
        // Refreshing list in case user just posted or account changed
        if (profileAdapter != null) {
            profileAdapter.setData(DataStore.getUserPosts(this));
            empty.setVisibility(profileAdapter.getItemCount() == 0 ? View.VISIBLE : View.GONE);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        // Unregister to avoid memory leaks
        DataStore.removeListener(this);
    }

    @Override
    public void onDataChanged() {
        // Refresh the profile list when data changes
        if (profileAdapter != null) {
            profileAdapter.setData(DataStore.getUserPosts(this));
            empty.setVisibility(profileAdapter.getItemCount() == 0 ? View.VISIBLE : View.GONE);
        }
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
    }    /** Delete post from local DataStore and refresh UI */
    private void deleteFromLocalStore(Post post) {
        boolean deleted = DataStore.deletePost(this, post);
        if (deleted) {
            Toast.makeText(this, "Post deleted", Toast.LENGTH_SHORT).show();
            // UI will refresh automatically via DataStore listener pattern
        } else {
            Toast.makeText(this, "Could not delete post", Toast.LENGTH_SHORT).show();
        }
    }
}