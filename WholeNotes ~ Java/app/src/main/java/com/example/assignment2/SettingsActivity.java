package com.example.assignment2;

import android.os.Bundle;
import android.widget.SeekBar;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.appbar.MaterialToolbar;
import com.google.android.material.switchmaterial.SwitchMaterial;

/**
 * Simple settings screen backed by AppPrefs.
 * Lets user:
 *  - turn the location-based "For You" feed on/off
 *  - choose the nearby radius in miles
 */
public class SettingsActivity extends AppCompatActivity {

    private TextView tvRadiusLabel;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        // Top app bar with back arrow
        MaterialToolbar toolbar = findViewById(R.id.topAppBar);
        if (toolbar != null) {
            setSupportActionBar(toolbar);
            if (getSupportActionBar() != null) {
                getSupportActionBar().setTitle("Settings");
                getSupportActionBar().setDisplayHomeAsUpEnabled(true);
            }
            toolbar.setNavigationOnClickListener(v -> finish());
        }

        SwitchMaterial switchNearby = findViewById(R.id.switchNearby);
        SeekBar seekRadius = findViewById(R.id.seekRadius);
        tvRadiusLabel = findViewById(R.id.tvRadiusLabel);

        // Load current prefs
        boolean nearbyEnabled = AppPrefs.isNearbyEnabled(this);
        double radiusMiles = AppPrefs.getNearbyRadiusMiles(this);

        switchNearby.setChecked(nearbyEnabled);
        seekRadius.setProgress((int) Math.round(radiusMiles));
        updateRadiusLabel(radiusMiles);

        // When toggle changes, save it
        switchNearby.setOnCheckedChangeListener((buttonView, isChecked) ->
                AppPrefs.setNearbyEnabled(this, isChecked));

        // When slider moves, save + update text
        seekRadius.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                // Avoid 0: minimum 5 miles so it’s not weird
                int miles = Math.max(progress, 5);
                AppPrefs.setNearbyRadiusMiles(SettingsActivity.this, miles);
                updateRadiusLabel(miles);
            }
            @Override public void onStartTrackingTouch(SeekBar seekBar) { }
            @Override public void onStopTrackingTouch(SeekBar seekBar) { }
        });
    }

    private void updateRadiusLabel(double miles) {
        tvRadiusLabel.setText(getString(R.string.radius_label, (int) miles));
    }

    @Override
    public boolean onSupportNavigateUp() {
        finish();
        return true;
    }
}
