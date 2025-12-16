package com.example.assignment2;

import android.content.Context;
import android.content.SharedPreferences;

/**
 * Stores/retrieves profile info per user.
 * Uses SharedPreferences with keys that include the username,
 * so each account can have its own saved name, bio, and public/private status.
 */
public class ProfilePrefs {
    private static final String PREF = "profile_prefs"; // file name for SharedPreferences

    // Building a unique key
    private static String key(String username, String field) {
        return username + "_" + field;
    }

    // Saving user's profile fields into SharedPreferences
    public static void save(Context c, String username, String name, String bio, boolean isPublic) {
        SharedPreferences sp = c.getSharedPreferences(PREF, Context.MODE_PRIVATE);
        sp.edit()
                .putString(key(username, "name"), name)
                .putString(key(username, "bio"), bio)
                .putBoolean(key(username, "is_public"), isPublic)
                .apply();
    }

    // Getting the saved display name for user
    public static String name(Context c, String username) {
        return c.getSharedPreferences(PREF, Context.MODE_PRIVATE)
                .getString(key(username, "name"), "");
    }

    // Getting the saved bio for user
    public static String bio(Context c, String username) {
        return c.getSharedPreferences(PREF, Context.MODE_PRIVATE)
                .getString(key(username, "bio"), "");
    }

    // Checking if the profile is marked public, default = true
    public static boolean isPublic(Context c, String username) {
        return c.getSharedPreferences(PREF, Context.MODE_PRIVATE)
                .getBoolean(key(username, "is_public"), true);
    }
}
