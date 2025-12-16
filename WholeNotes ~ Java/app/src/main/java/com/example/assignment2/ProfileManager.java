package com.example.assignment2;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.firestore.DocumentSnapshot;
import com.google.firebase.firestore.FirebaseFirestore;
import com.google.firebase.firestore.SetOptions; // <-- 1. IMPORT THIS

import java.util.HashMap;
import java.util.Map;

/**
 * Manages saving and loading user profile data (name, bio, public status)
 * from the 'users' collection in Firestore.
 */
public class ProfileManager {

    private final FirebaseAuth auth = FirebaseAuth.getInstance();
    private final FirebaseFirestore db = FirebaseFirestore.getInstance();

    /**
     * A simple data class to hold profile information.
     */
    public static class UserProfile {
        public String name = "";
        public String bio = "";
        public boolean isPublic = true; // Default value

        // Default constructor needed for Firestore mapping (though we map manually here)
        public UserProfile() {}
    }

    public interface ProfileLoadCallback {
        void onSuccess(UserProfile profile);
        void onFailure(Exception e);
    }

    public interface ProfileSaveCallback {
        void onSuccess();
        void onFailure(Exception e);
    }

    /**
     * Gets the current user's UID from FirebaseAuth.
     * @return User ID string or null if not logged in.
     */
    private String getUserId() {
        FirebaseUser user = auth.getCurrentUser();
        return (user != null) ? user.getUid() : null;
    }

    /**
     * Saves the user's profile data to their document in Firestore.
     */
    public void saveProfile(String name, String bio, boolean isPublic, ProfileSaveCallback callback) {
        String userId = getUserId();
        if (userId == null) {
            callback.onFailure(new Exception("No user logged in"));
            return;
        }

        // Create a map of the data to update
        Map<String, Object> profileData = new HashMap<>();
        profileData.put("name", name);
        profileData.put("bio", bio);
        profileData.put("isPublic", isPublic);

        // Use .set() with SetOptions.merge() to create the document if it doesn't exist,
        // or update it if it does. This is much safer than .update().
        db.collection("users").document(userId)
                .set(profileData, SetOptions.merge()) // <-- 2. THIS LINE IS THE FIX
                .addOnSuccessListener(aVoid -> callback.onSuccess())
                .addOnFailureListener(callback::onFailure);
    }

    /**
     * Loads the user's profile data from their document in Firestore.
     */
    public void loadProfile(ProfileLoadCallback callback) {
        String userId = getUserId();
        if (userId == null) {
            callback.onFailure(new Exception("No user logged in"));
            return;
        }

        db.collection("users").document(userId)
                .get()
                .addOnCompleteListener(task -> {
                    if (task.isSuccessful()) {
                        DocumentSnapshot document = task.getResult();
                        if (document != null && document.exists()) {

                            // Manually map the fields to our UserProfile object
                            UserProfile profile = new UserProfile();
                            profile.name = document.getString("name");
                            profile.bio = document.getString("bio");

                            // Handle boolean which might be null
                            Boolean isPublic = document.getBoolean("isPublic");
                            profile.isPublic = (isPublic != null) ? isPublic : true;

                            callback.onSuccess(profile);

                        } else {
                            callback.onFailure(new Exception("User document not found"));
                        }
                    } else {
                        callback.onFailure(task.getException());
                    }
                });
    }
}