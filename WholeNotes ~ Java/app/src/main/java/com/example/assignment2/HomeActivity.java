package com.example.assignment2;

import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import com.google.android.material.bottomnavigation.BottomNavigationView;

/**
 * Main screen after login.
 * Hosts HomeFragment and the bottom navigation.
 * Also owns the overflow "Settings" menu (⋮).
 */
public class HomeActivity extends AppCompatActivity {

    private static final String KEY_TAB = "tabIndex";
    private int savedTab = 0;

    @Override
    protected void onCreate(Bundle s) {
        // Load posts on app startup
        DataStore.init(getApplicationContext());

        super.onCreate(s);
        setContentView(R.layout.activity_home);

        // Set up the top app bar (Toolbar) so we have a place for the ⋮ menu
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        // Restore which tab was active last time
        if (s != null) {
            savedTab = s.getInt(KEY_TAB, 0);
        }

        // Only attach HomeFragment once
        if (getSupportFragmentManager().findFragmentById(R.id.home_content) == null) {
            getSupportFragmentManager().beginTransaction()
                    .replace(R.id.home_content, HomeFragment.newInstance(savedTab))
                    .commit();
        }

        // Bottom nav -> Home, Search, Post, Activity, Profile
        BottomNavigationView nav = findViewById(R.id.bottom_navigation);
        BaseNav.setup(this, nav, R.id.nav_home);
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle out) {
        super.onSaveInstanceState(out);
        HomeFragment f = (HomeFragment) getSupportFragmentManager()
                .findFragmentById(R.id.home_content);
        if (f != null) {
            out.putInt(KEY_TAB, f.getCurrentTabIndex());
        }
    }

    // Inflate the overflow menu
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_home, menu);
        return true; // <- must be true or nothing shows
    }

    // Handle clicks on overflow menu items
    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        if (item.getItemId() == R.id.action_settings) {
            startActivity(new Intent(this, SettingsActivity.class));
            return true;
        } else if (item.getItemId() == R.id.action_refresh) {
            refreshPosts(item);
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    /** Refresh posts from Firestore with visual feedback */
    private void refreshPosts(MenuItem refreshItem) {
        // Disable the refresh button and show loading state
        refreshItem.setEnabled(false);
        refreshItem.setTitle("Refreshing...");
        
        DataStore.refreshFromFirestore(getApplicationContext(), () -> {
            // Re-enable the refresh button on UI thread
            runOnUiThread(() -> {
                refreshItem.setEnabled(true);
                refreshItem.setTitle("Refresh Posts");
                // Show a brief confirmation
                android.widget.Toast.makeText(this, "Posts refreshed", android.widget.Toast.LENGTH_SHORT).show();
            });
        });
    }
}
