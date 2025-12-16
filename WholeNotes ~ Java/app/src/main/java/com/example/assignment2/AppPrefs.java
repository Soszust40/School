package com.example.assignment2;

import android.content.Context;
import android.content.SharedPreferences;

/**
 * Central place for app-level preferences.
 */
public class AppPrefs {

    private static final String PREF = "app_prefs";

    private static final String KEY_NEARBY_ENABLED = "nearby_enabled";
    private static final String KEY_NEARBY_RADIUS_MILES = "nearby_radius_miles";

    private static SharedPreferences sp(Context c) {
        return c.getSharedPreferences(PREF, Context.MODE_PRIVATE);
    }

    // --- Near you toggle ---
    public static boolean isNearbyEnabled(Context c) {
        // default true so feature works "out of the box"
        return sp(c).getBoolean(KEY_NEARBY_ENABLED, true);
    }

    public static void setNearbyEnabled(Context c, boolean enabled) {
        sp(c).edit().putBoolean(KEY_NEARBY_ENABLED, enabled).apply();
    }

    // --- Radius preference ---

    // Distance (in miles) for which posts count as near you.
    public static double getNearbyRadiusMiles(Context c) {
        // default to 50 if user never changed it
        return Double.longBitsToDouble(
                sp(c).getLong(KEY_NEARBY_RADIUS_MILES,
                        Double.doubleToLongBits(50.0))
        );
    }

    public static void setNearbyRadiusMiles(Context c, double miles) {
        sp(c).edit()
                .putLong(KEY_NEARBY_RADIUS_MILES, Double.doubleToLongBits(miles))
                .apply();
    }
}
