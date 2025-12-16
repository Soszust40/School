package com.example.assignment2;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.*;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.gms.location.FusedLocationProviderClient;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.location.Priority;
import com.google.android.gms.tasks.CancellationTokenSource;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

/**
 * Fragment that shows the feed.
 * SENSOR INTEGRATION (For "for_you" tab only):
 * - Uses GPS/GNSS location sensor via FusedLocationProviderClient
 * - Filters posts within radius of user location (radius comes from AppPrefs)
 * - Sorts by distance (nearest first)
 * SENSOR LIMITATIONS:
 * - GPS doesn't work well indoors (needs clear sky view)
 * - Accuracy: 5-50 meters typical, worse in urban areas
 * - Cold start can take 30+ seconds to get first fix
 * - Battery drain with continuous use
 * ERROR HANDLING:
 * 1. Permission denied - Falls back to showing all posts
 * 2. Location services disabled/unavailable - Shows all posts with message
 */
public class FeedFragment extends Fragment implements DataStore.OnChangeListener {
    private static final String TAG = "FeedFragment";
    private static final String ARG_KIND = "k";
    private static final int LOCATION_PERMISSION_CODE = 100;
    // Keep a default radius as a fallback; actual value is read from AppPrefs.
    private static final double DEFAULT_RADIUS_MILES = 50.0;

    private PostAdapter adapter;
    private TextView tvStatus;
    private String feedKind; // "following" or "for_you"

    // Location services (only used for "for_you" tab)
    private FusedLocationProviderClient fusedLocationClient;
    private CancellationTokenSource cancellationTokenSource;
    private Double userLatitude = null;
    private Double userLongitude = null;
    private boolean locationPermissionGranted = false;

    public static FeedFragment newInstance(String kind) {
        Bundle b = new Bundle();
        b.putString(ARG_KIND, kind);
        FeedFragment f = new FeedFragment();
        f.setArguments(b);
        return f;
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inf, @Nullable ViewGroup c, @Nullable Bundle s) {
        return inf.inflate(R.layout.fragment_feed, c, false);
    }

    @Override
    public void onViewCreated(@NonNull View v, @Nullable Bundle s) {
        RecyclerView rv = v.findViewById(R.id.recycler);
        tvStatus = v.findViewById(R.id.tvStatus);

        rv.setLayoutManager(new LinearLayoutManager(requireContext()));
        adapter = new PostAdapter(new ArrayList<>());
        
        // Set up delete functionality
        String currentUser = AuthManager.currentUser(requireContext());
        adapter.setDeleteListener(this::deletePost, currentUser);
        
        // Set up like functionality
        String currentUserId = getCurrentUserId();
        adapter.setLikeListener(this::likePost, currentUser, currentUserId);
        
        rv.setAdapter(adapter);

        // Get the feed type
        if (getArguments() != null) {
            feedKind = getArguments().getString(ARG_KIND, "following");
        }

        Log.d(TAG, "Feed type: " + feedKind);

        // Only use location for "for_you" tab
        if (isForYouFeed()) {
            fusedLocationClient = LocationServices.getFusedLocationProviderClient(requireActivity());
            cancellationTokenSource = new CancellationTokenSource();
            checkLocationPermission();
        } else {
            // "following" tab - just show all posts
            adapter.setData(DataStore.getAllPosts());
        }
    }

    // When we come back (e.g., after changing Settings), re-apply preferences.
    @Override
    public void onResume() {
        super.onResume();

        if (!isForYouFeed()) return;

        boolean nearbyEnabled = AppPrefs.isNearbyEnabled(requireContext());
        if (!nearbyEnabled) {
            // If user turned nearby off, show everything with a hint.
            showAllPosts("Location-based filtering is off in Settings.");
            return;
        }

        if (userLatitude != null && userLongitude != null) {
            // Already have a location; just re-filter with the latest radius.
            filterAndDisplayPosts();
        } else if (locationPermissionGranted) {
            // Try again to get a fix if we never got one.
            getUserLocation();
        }
        // If no permission, checkLocationPermission() already handled fallback in onViewCreated.
    }

    private boolean isForYouFeed() {
        return "for_you".equals(feedKind) || "foryou".equals(feedKind);
    }

    /**
     * ERROR HANDLING TYPE 1: Permission Denial
     */
    private void checkLocationPermission() {
        if (ContextCompat.checkSelfPermission(requireContext(),
                Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED) {
            locationPermissionGranted = true;
            Log.d(TAG, "Location permission already granted");
            getUserLocation();
        } else {
            Log.d(TAG, "Requesting location permission");
            if (shouldShowRequestPermissionRationale(Manifest.permission.ACCESS_FINE_LOCATION)) {
                new AlertDialog.Builder(requireContext())
                        .setTitle("Location Needed")
                        .setMessage("Location is needed to show nearby ratings. Without it, you'll see all posts.")
                        .setPositiveButton("OK", (d, w) -> requestPermissions(
                                new String[]{Manifest.permission.ACCESS_FINE_LOCATION},
                                LOCATION_PERMISSION_CODE))
                        .setNegativeButton("Skip", (d, w) -> showAllPosts("Location permission needed"))
                        .show();
            } else {
                requestPermissions(
                        new String[]{Manifest.permission.ACCESS_FINE_LOCATION},
                        LOCATION_PERMISSION_CODE);
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
                                           @NonNull int[] grantResults) {
        if (requestCode == LOCATION_PERMISSION_CODE) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                locationPermissionGranted = true;
                Log.d(TAG, "Location permission granted by user");
                getUserLocation();
            } else {
                // ERROR HANDLING: Permission denied
                Log.d(TAG, "Location permission denied by user");
                showAllPosts("Location permission denied. Showing all posts.");
                Toast.makeText(requireContext(),
                        "Enable location in settings for nearby ratings",
                        Toast.LENGTH_SHORT).show();
            }
        }
    }

    /**
     * ERROR HANDLING TYPE 2: Location Unavailable
     * Gets user location using GPS sensor
     */
    private void getUserLocation() {
        if (!locationPermissionGranted) {
            showAllPosts(null);
            return;
        }

        if (tvStatus != null) {
            tvStatus.setText(R.string.status_getting_location);
            tvStatus.setVisibility(View.VISIBLE);
        }

        Log.d(TAG, "Requesting current location...");

        try {
            fusedLocationClient.getCurrentLocation(
                    Priority.PRIORITY_HIGH_ACCURACY,
                    cancellationTokenSource.getToken()
            ).addOnSuccessListener(requireActivity(), location -> {
                if (location != null) {
                    // Got location from GPS sensor
                    userLatitude = location.getLatitude();
                    userLongitude = location.getLongitude();

                    Log.d(TAG, "Location received: " + userLatitude + ", " + userLongitude);

                    filterAndDisplayPosts();
                } else {
                    // ERROR HANDLING TYPE 2: Location null (GPS can't get fix)
                    Log.e(TAG, "Location is null");
                    handleLocationUnavailable();
                }
            }).addOnFailureListener(requireActivity(), e -> {
                // ERROR HANDLING TYPE 2: Location failed
                Log.e(TAG, "Failed to get location", e);
                showAllPosts("Location unavailable. Showing all posts.");
            });
        } catch (SecurityException e) {
            Log.e(TAG, "Security exception getting location", e);
            showAllPosts("Location error. Showing all posts.");
        }
    }

    /**
     * ERROR HANDLING TYPE 2: GPS unable to determine position
     * Common causes: indoors, GPS disabled, poor satellite visibility
     */
    private void handleLocationUnavailable() {
        new AlertDialog.Builder(requireContext())
                .setTitle("Location Unavailable")
                .setMessage("Can't get your location. This may be because:\n\n" +
                        "• GPS is off\n• You're indoors\n• Poor GPS signal\n\nShow all posts instead?")
                .setPositiveButton("Show All", (d, w) -> showAllPosts("Location unavailable. Showing all posts."))
                .setNegativeButton("Retry", (d, w) -> {
                    cancellationTokenSource = new CancellationTokenSource();
                    getUserLocation();
                })
                .show();
    }

    /**
     * CORE FUNCTIONALITY: Filter posts by location.
     * Uses AppPrefs for radius, and each Post's getDistanceFrom.
     */
    private void filterAndDisplayPosts() {
        if (userLatitude == null || userLongitude == null) {
            Log.w(TAG, "User location is null, showing all posts");
            showAllPosts(null);
            return;
        }

        // Read current settings
        boolean nearbyEnabled = AppPrefs.isNearbyEnabled(requireContext());
        double radiusMiles = AppPrefs.getNearbyRadiusMiles(requireContext());
        if (radiusMiles <= 0) {
            radiusMiles = DEFAULT_RADIUS_MILES;
        }

        if (!nearbyEnabled) {
            Log.d(TAG, "Nearby filtering disabled in prefs; showing all posts.");
            showAllPosts("Location-based filtering is off in Settings.");
            return;
        }

        Log.d(TAG, "Filtering posts for user location: " + userLatitude + ", " + userLongitude +
                " within " + radiusMiles + " miles");

        List<Post> allPosts = DataStore.getAllPosts();
        List<Post> nearbyPosts = new ArrayList<>();

        Log.d(TAG, "Total posts: " + allPosts.size());

        // Filter: keep only posts within radius
        for (Post post : allPosts) {
            double distance = post.getDistanceFrom(userLatitude, userLongitude);

            Log.d(TAG, "Post: " + post.title +
                    ", Location: " + post.latitude + ", " + post.longitude +
                    ", Distance: " + String.format("%.2f", distance) + " miles");

            if (distance <= radiusMiles) {
                nearbyPosts.add(post);
                Log.d(TAG, "  -> INCLUDED (within radius)");
            } else {
                Log.d(TAG, "  -> EXCLUDED (" + String.format("%.2f", distance) + " miles away)");
            }
        }

        Log.d(TAG, "Nearby posts found: " + nearbyPosts.size());

        // Sort by distance (nearest first)
        nearbyPosts.sort(new Comparator<>() {
            @Override
            public int compare(Post p1, Post p2) {
                double d1 = p1.getDistanceFrom(userLatitude, userLongitude);
                double d2 = p2.getDistanceFrom(userLatitude, userLongitude);
                return Double.compare(d1, d2);
            }
        });

        if (tvStatus != null) {
            tvStatus.setText(String.format("Showing ratings within %.0f miles", radiusMiles));
            tvStatus.setVisibility(View.VISIBLE);
        }

        adapter.setData(nearbyPosts);
    }

    /**
     * Fallback: show all posts when location not available
     */
    private void showAllPosts(String statusMessage) {
        Log.d(TAG, "Showing all posts" + (statusMessage != null ? ": " + statusMessage : ""));
        if (tvStatus != null) {
            if (statusMessage != null) {
                tvStatus.setText(statusMessage);
                tvStatus.setVisibility(View.VISIBLE);
            } else {
                tvStatus.setVisibility(View.GONE);
            }
        }
        adapter.setData(DataStore.getAllPosts());
    }

    @Override
    public void onStart() {
        super.onStart();
        DataStore.addListener(this);
    }

    @Override
    public void onStop() {
        DataStore.removeListener(this);
        super.onStop();
    }

    @Override
    public void onDataChanged() {
        if (adapter == null) return;

        if (isForYouFeed() && userLatitude != null && userLongitude != null) {
            // Re-apply nearby filter when posts change
            filterAndDisplayPosts();
        } else {
            adapter.setData(DataStore.getAllPosts());
        }
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        if (cancellationTokenSource != null) {
            cancellationTokenSource.cancel();
        }
    }

    /** Handle post deletion with confirmation dialog */
    private void deletePost(Post post) {
        new AlertDialog.Builder(requireContext())
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
                        Toast.makeText(requireContext(), "Network error, but deleted locally", Toast.LENGTH_SHORT).show();
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
        boolean deleted = DataStore.deletePost(requireContext(), post);
        if (deleted) {
            Toast.makeText(requireContext(), "Post deleted", Toast.LENGTH_SHORT).show();
            // UI will refresh automatically via DataStore listener pattern
        } else {
            Toast.makeText(requireContext(), "Could not delete post", Toast.LENGTH_SHORT).show();
        }
    }
    
    /** Handle like button clicks */
    private void likePost(Post post) {
        DataStore.toggleLike(requireContext(), post, (isLiked, error) -> {
            if (error != null) {
                Toast.makeText(requireContext(), error, Toast.LENGTH_SHORT).show();
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
