package com.example.assignment2;

import android.app.Activity;
import android.content.Intent;

import androidx.annotation.NonNull;

import com.google.android.material.bottomnavigation.BottomNavigationView;

/**
 * Helper to wire the BottomNavigationView across Activities.
 * Keeps tab switching consistent and avoids code duplication.
 */
public class BaseNav {

    /**
     * Connects a BottomNavigationView to launch the correct Activity per tab.
     * @param activity   the current screen hosting the nav
     * @param nav        the BottomNavigationView instance
     * @param selectedId the menu id that should appear selected for this screen
     */
    public static void setup(@NonNull Activity activity,
                             @NonNull BottomNavigationView nav,
                             int selectedId) {

        // Making the current tab visually selected.
        nav.setSelectedItemId(selectedId);

        // No operation on re selects
        nav.setOnItemReselectedListener(item -> {
            // empty to prevent relaunching the same Activity.
        });

        nav.setOnItemSelectedListener(item -> {
            final int id = item.getItemId();

            // if it's already on the tab do nothing.
            if (id == selectedId) return true;

            Class<?> target = null;
            if (id == R.id.nav_home) {
                target = HomeActivity.class;
            } else if (id == R.id.nav_search) {
                target = SearchActivity.class;
            } else if (id == R.id.nav_post) {
                target = PostActivity.class;
            } else if (id == R.id.nav_profile) {
                target = ProfileActivity.class;
            }

            if (target == null) return false;

            // if already on the target, stop
            if (activity.getClass() == target) return true;

            // Reusing existing instances if possible and avoiding stacking duplicates.
            Intent i = new Intent(activity, target);
            i.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP           // don't recreate if it's top
                    | Intent.FLAG_ACTIVITY_CLEAR_TOP             // pop intermediates if any
                    | Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);    // bring existing instance to front

            activity.startActivity(i);

            // No transition when switching tabs
            activity.overridePendingTransition(0, 0);
            return true;
        });
    }
}
