package com.example.assignment2;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.Address;
import android.location.Geocoder;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;

import com.google.android.gms.location.FusedLocationProviderClient;
import com.google.android.gms.location.LocationServices;
import com.google.android.material.bottomnavigation.BottomNavigationView;

import java.io.IOException;
import java.util.List;
import java.util.Locale;
import com.google.android.gms.location.Priority;

public class PostActivity extends AppCompatActivity {

    private static final String K_TITLE = "k_title", K_BODY = "k_body", K_SONG = "k_song", K_LYR = "k_lyr", K_CLIP = "k_clip";

    private EditText etTitle, etBody, etSong, etLyrics, etClip;
    private TextView locationDisplay;
    private Button btnSubmit;

    private FusedLocationProviderClient fusedLocationClient;
    private Double postLatitude = null;
    private Double postLongitude = null;
    private String postLocationName = null;

    private final ActivityResultLauncher<String> requestPermissionLauncher =
            registerForActivityResult(new ActivityResultContracts.RequestPermission(), isGranted -> {
                if (isGranted) {
                    getLocation();
                } else {
                    locationDisplay.setText(R.string.location_permission_denied);
                    Toast.makeText(this, "Location permission is needed to tag your post", Toast.LENGTH_LONG).show();
                }
            });

    @Override
    protected void onCreate(Bundle s) {
        super.onCreate(s);
        setContentView(R.layout.activity_post);

        // Initialize UI elements
        etTitle = findViewById(R.id.etTitle);
        etBody = findViewById(R.id.etBody);
        etSong = findViewById(R.id.etSong);
        etLyrics = findViewById(R.id.etLyrics);
        etClip = findViewById(R.id.etClip);
        locationDisplay = findViewById(R.id.text_location_display);
        btnSubmit = findViewById(R.id.btnSubmit);

        // Restore saved state if any
        if (s != null) {
            etTitle.setText(s.getString(K_TITLE, ""));
            etBody.setText(s.getString(K_BODY, ""));
            etSong.setText(s.getString(K_SONG, ""));
            etLyrics.setText(s.getString(K_LYR, ""));
            etClip.setText(s.getString(K_CLIP, ""));
        }

        // Setup location services
        fusedLocationClient = LocationServices.getFusedLocationProviderClient(this);

        // Request location permission and fetch location
        checkLocationPermissionAndGetLocation();

        // Setup bottom navigation
        BottomNavigationView nav = findViewById(R.id.bottom_navigation);
        BaseNav.setup(this, nav, R.id.nav_post);

        // Submit button
        btnSubmit.setOnClickListener(v -> submitPost());
    }

    // New submit post using firebase
    private void submitPost() {
        String title = etTitle.getText().toString().trim();
        String body  = etBody.getText().toString().trim();
        String song  = etSong.getText().toString().trim();
        String lyr   = etLyrics.getText().toString().trim();
        String clip  = etClip.getText().toString().trim();

        if (title.isEmpty() && body.isEmpty()) {
            Toast.makeText(this, "Add at least a title or body", Toast.LENGTH_SHORT).show();
            return;
        }

        // Build your existing data model
        Post p = new Post(
                title,
                /* subtitle */ "",
                body,
                emptyToNull(lyr),
                emptyToNull(clip),
                0, 0,
                emptyToNull(song),
                /* authorEmail filled by PostManager */ "",
                postLatitude,
                postLongitude,
                postLocationName
        );

        PostManager repo = new PostManager();
        btnSubmit.setEnabled(false);

        repo.addPost(p, newId -> {
            Toast.makeText(this, getString(R.string.posted_to_profile), Toast.LENGTH_SHORT).show();

            // Navigate
            Intent i = new Intent(this, ProfileActivity.class);
            i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);
            startActivity(i);
            overridePendingTransition(0, 0);
            finish();

        }, err -> {
            btnSubmit.setEnabled(true);
            Toast.makeText(this, "Post failed: " + err.getMessage(), Toast.LENGTH_LONG).show();
        });
    }

    private String emptyToNull(String s) {
        return (s == null || s.trim().isEmpty()) ? null : s.trim();
    }


    // Checks for location permission and requests location if granted
    private void checkLocationPermissionAndGetLocation() {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION)
                == PackageManager.PERMISSION_GRANTED) {
            getLocation();
        } else {
            requestPermissionLauncher.launch(Manifest.permission.ACCESS_FINE_LOCATION);
        }
    }

    private void getLocation() {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION)
                != PackageManager.PERMISSION_GRANTED) {
            return;
        }

        // This is the new line to force a fresh location check
        fusedLocationClient.getCurrentLocation(Priority.PRIORITY_HIGH_ACCURACY, null)
                .addOnSuccessListener(this, location -> {
                    if (location != null) {
                        postLatitude = location.getLatitude();
                        postLongitude = location.getLongitude();
                        fetchAddressFromCoordinates(postLatitude, postLongitude);
                    } else {
                        locationDisplay.setText(R.string.location_not_retrieved);
                        Toast.makeText(this, "Make sure location services are enabled", Toast.LENGTH_LONG).show();
                    }
                });
    }

    private void fetchAddressFromCoordinates(double lat, double lon) {
        new Thread(() -> {
            try {
                Geocoder geocoder = new Geocoder(this, Locale.getDefault());

                // Check if Geocoder is available
                if (!Geocoder.isPresent()) {
                    // Fallback to coordinates
                    postLocationName = String.format(Locale.US, "%.4f°, %.4f°", lat, lon);
                    runOnUiThread(() -> {
                        locationDisplay.setText("📍 " + postLocationName);
                        Toast.makeText(this, "Using coordinates (Geocoder unavailable)", Toast.LENGTH_SHORT).show();
                    });
                    return;
                }

                List<Address> addresses = geocoder.getFromLocation(lat, lon, 1);

                if (addresses != null && !addresses.isEmpty()) {
                    Address address = addresses.get(0);
                    postLocationName = formatLocationName(address);

                    if (postLocationName == null || postLocationName.isEmpty()) {
                        // Fallback to coordinates
                        postLocationName = String.format(Locale.US, "%.4f°, %.4f°", lat, lon);
                    }

                    final String displayText = "📍 " + postLocationName;
                    runOnUiThread(() -> {
                        locationDisplay.setText(displayText);
                        Log.d("PostActivity", "Location name: " + postLocationName);
                    });

                } else {
                    // No addresses returned, use coordinates
                    postLocationName = String.format(Locale.US, "%.4f°, %.4f°", lat, lon);
                    runOnUiThread(() -> {
                        locationDisplay.setText("📍 " + postLocationName);
                    });
                }
            } catch (IOException e) {
                Log.e("PostActivity", "Geocoder failed", e);
                // Fallback to coordinates
                postLocationName = String.format(Locale.US, "%.4f°, %.4f°", lat, lon);
                runOnUiThread(() -> {
                    locationDisplay.setText("📍 " + postLocationName);
                    Toast.makeText(this, "Network error - using coordinates", Toast.LENGTH_SHORT).show();
                });
            }
        }).start();
    }

    /**
     * Format location name intelligently based on available address components
     * Works worldwide by adapting to different address formats
     */
    private String formatLocationName(Address address) {
        String city = address.getLocality();              // City name
        String state = address.getAdminArea();            // State/Province/Region
        String country = address.getCountryName();        // Country name
        String countryCode = address.getCountryCode();    // ISO country code (e.g., "US", "FR", "JP")

        Log.d("PostActivity", "Geocoded - City: " + city + ", State: " + state + ", Country: " + country + ", Code: " + countryCode);

        // For US, Canada, Australia, Brazil, India - use "City, State/Province"
        if (countryCode != null && isCountryWithStates(countryCode)) {
            if (city != null && state != null) {
                return city + ", " + state;
            } else if (city != null) {
                return city + ", " + country;
            } else if (state != null) {
                return state + ", " + country;
            }
        }

        // For other countries - use "City, Country"
        if (city != null && country != null) {
            return city + ", " + country;
        }

        // Fallback options
        if (city != null) {
            return city;
        }
        if (state != null && country != null) {
            return state + ", " + country;
        }
        if (state != null) {
            return state;
        }
        return country;
    }

    /**
     * Check if country typically uses state/province divisions in addresses
     */
    private boolean isCountryWithStates(String countryCode) {
        switch (countryCode.toUpperCase()) {
            case "US":  // United States
            case "CA":  // Canada
            case "AU":  // Australia
            case "BR":  // Brazil
            case "IN":  // India
            case "MX":  // Mexico
            case "AR":  // Argentina
            case "DE":  // Germany
            case "MY":  // Malaysia
            case "NG":  // Nigeria
                return true;
            default:
                return false;
        }
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle out) {
        super.onSaveInstanceState(out);
        out.putString(K_TITLE, etTitle.getText().toString());
        out.putString(K_BODY, etBody.getText().toString());
        out.putString(K_SONG, etSong.getText().toString());
        out.putString(K_LYR, etLyrics.getText().toString());
        out.putString(K_CLIP, etClip.getText().toString());
    }

    // Refreshes location when activity resumes
    @Override
    protected void onResume() {
        super.onResume();
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION)
                == PackageManager.PERMISSION_GRANTED) {
            getLocation();
        }
    }
}