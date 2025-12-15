package com.example.fitnesslogger;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import java.io.InputStream;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class AddActivity extends AppCompatActivity {

    private Spinner spinner;
    private SeekBar sbDuration;
    private TextView tvDurationLabel;
    private ImageView ivPreview;
    private Button btnFetch;
    private String currentImageUrl = "";

    private final ExecutorService executor = Executors.newSingleThreadExecutor();
    private final Handler handler = new Handler(Looper.getMainLooper());

    // List of possible image URLs
    private final String[] imageUrls = {
            "https://images.unsplash.com/photo-1517836357463-d25dfeac3438?w=400",
            "https://images.unsplash.com/photo-1502904550040-7534597429ae?w=400",
            "https://images.unsplash.com/photo-1571019614242-c5c5dee9f50b?w=400",
            "https://images.unsplash.com/photo-1541534741688-6078c6bfb5c5?w=400",
            "https://images.unsplash.com/photo-1486739985386-d4fae04ca6f7?w=400"
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add);

        // Initialize UI components
        spinner = findViewById(R.id.spinnerActivityType);
        sbDuration = findViewById(R.id.sbDuration);
        tvDurationLabel = findViewById(R.id.tvDurationLabel);
        ivPreview = findViewById(R.id.ivPreview);
        btnFetch = findViewById(R.id.btnFetchImage);
        Button btnSave = findViewById(R.id.btnSave);

        // Populate spinner using array resource
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(
                this, R.array.activity_types, android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);

        // Restore image after rotation / config change
        if (savedInstanceState != null) {
            currentImageUrl = savedInstanceState.getString("url_key", "");
            if (!currentImageUrl.isEmpty()) {
                if (currentImageUrl.equals("LOCAL_PLACEHOLDER")) {
                    ivPreview.setImageResource(R.drawable.offline_placeholder);
                } else {
                    loadImage(currentImageUrl);
                }
            }
        }

        updateDurationLabel(sbDuration.getProgress());

        // SeekBar listener for duration
        sbDuration.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if(progress < 1) {
                    seekBar.setProgress(1);
                    return;
                }
                updateDurationLabel(progress);
            }
            @Override public void onStartTrackingTouch(SeekBar seekBar) {}
            @Override public void onStopTrackingTouch(SeekBar seekBar) {}
        });

        // Button that fetches a random image
        btnFetch.setOnClickListener(v -> {
            fetchRandomFromList();
            startCooldown();
        });

        // Save activity button
        btnSave.setOnClickListener(v -> saveActivity());
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);
        outState.putString("url_key", currentImageUrl);
    }

    // Cooldown to prevent button spam
    private void startCooldown() {
        // Disable button
        btnFetch.setEnabled(false);

        // 1-second cooldown
        new Handler(Looper.getMainLooper()).postDelayed(() -> {
            btnFetch.setEnabled(true);
        }, 1000);
    }

    // Updates label showing selected duration
    private void updateDurationLabel(int minutes) {
        tvDurationLabel.setText(getString(R.string.lbl_duration_format, minutes));
    }

    // Get a random image URL and load it
    private void fetchRandomFromList() {
        int randomIndex = new Random().nextInt(imageUrls.length);
        String selectedUrl = imageUrls[randomIndex];
        loadImage(selectedUrl);
    }

    // Load image from URL in background
    private void loadImage(String url) {
        executor.execute(() -> {
            try {
                InputStream in = new java.net.URL(url).openStream(); // Download image data
                Bitmap bmp = BitmapFactory.decodeStream(in); // Decode bitmap


                handler.post(() -> {
                    ivPreview.setImageBitmap(bmp); // Set downloaded image
                    currentImageUrl = url; // Save URL
                });
            } catch (Exception e) {
                handler.post(() -> { // On failure, show placeholder
                    ivPreview.setImageResource(R.drawable.offline_placeholder);
                    currentImageUrl = "LOCAL_PLACEHOLDER";
                    Toast.makeText(AddActivity.this, getString(R.string.err_network_msg), Toast.LENGTH_SHORT).show();
                });
            }
        });
    }

    // Saves the workout to the database
    private void saveActivity() {
        String type = spinner.getSelectedItem().toString(); // Selected activity type
        String duration = String.valueOf(sbDuration.getProgress()); // Duration

        if(currentImageUrl.isEmpty()) {
            currentImageUrl = "LOCAL_PLACEHOLDER";
        }

        FitnessDatabaseHelper db = new FitnessDatabaseHelper(this);
        boolean success = db.addWorkout(type, duration, currentImageUrl);

        if(success) {
            Toast.makeText(this, getString(R.string.msg_saved), Toast.LENGTH_SHORT).show();
            finish();
        } else {
            Toast.makeText(this, getString(R.string.msg_save_error), Toast.LENGTH_SHORT).show();
        }
    }
}