package com.example.assignment2;

import android.content.Context;
import android.content.SharedPreferences;
import android.net.ConnectivityManager;
import android.net.NetworkCapabilities;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseAuthException;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.firestore.FieldValue;
import com.google.firebase.firestore.FirebaseFirestore;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class AuthManager {

    private static final String PREFS_NAME = "auth_prefs";
    private static final String KEY_EMAIL = "email";
    private static final String KEY_REMEMBER = "remember_me";

    private static final FirebaseAuth auth = FirebaseAuth.getInstance();

    public enum AuthResult {
        SUCCESS,
        FAIL_INVALID_CREDENTIALS,
        FAIL_EMAIL_ALREADY_IN_USE,
        FAIL_WEAK_PASSWORD,
        FAIL_INVALID_EMAIL,
        FAIL_USER_DISABLED,
        FAIL_NO_NETWORK,
        FAIL_OTHER
    }


    public interface AuthCallback {
        void onResult(AuthResult result);
    }

    // Check for available network
    private static boolean isNetworkAvailable(Context ctx) {
        ConnectivityManager cm = (ConnectivityManager) ctx.getSystemService(Context.CONNECTIVITY_SERVICE);
        if (cm == null) return true;

        NetworkCapabilities capabilities = cm.getNetworkCapabilities(cm.getActiveNetwork());
        return capabilities == null ||
                (!capabilities.hasTransport(NetworkCapabilities.TRANSPORT_WIFI)
                        && !capabilities.hasTransport(NetworkCapabilities.TRANSPORT_CELLULAR)
                        && !capabilities.hasTransport(NetworkCapabilities.TRANSPORT_ETHERNET));
    }

    // Remember User
    public static boolean isRemembered(Context ctx) {
        SharedPreferences prefs = ctx.getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE);
        boolean remember = prefs.getBoolean(KEY_REMEMBER, false);
        String email = prefs.getString(KEY_EMAIL, null);
        FirebaseUser user = auth.getCurrentUser();
        return remember && user != null && email != null;
    }

    // Login Method
    public static void loginUser(Context ctx, String email, String pass, boolean remember, AuthCallback callback) {
        if (isNetworkAvailable(ctx)) {
            callback.onResult(AuthResult.FAIL_NO_NETWORK);
            return;
        }

        auth.signInWithEmailAndPassword(email, pass)
                .addOnCompleteListener(task -> {
                    if (task.isSuccessful()) {
                        saveRememberPreference(ctx, email, remember);

                        // Update Last Login Time
                        updateLastLoginAndNotify(callback);

                    } else {
                        try {
                            throw Objects.requireNonNull(task.getException());
                        } catch (FirebaseAuthException e) {
                            String errorCode = e.getErrorCode();

                            switch (errorCode) {
                                case "ERROR_USER_NOT_FOUND":
                                case "ERROR_WRONG_PASSWORD":
                                case "ERROR_INVALID_CREDENTIAL":
                                    callback.onResult(AuthResult.FAIL_INVALID_CREDENTIALS);
                                    break;
                                case "ERROR_INVALID_EMAIL":
                                    callback.onResult(AuthResult.FAIL_INVALID_EMAIL);
                                    break;
                                case "ERROR_USER_DISABLED":
                                    callback.onResult(AuthResult.FAIL_USER_DISABLED);
                                    break;
                                default:
                                    callback.onResult(AuthResult.FAIL_OTHER);
                                    break;
                            }
                        } catch (Exception e) {
                            callback.onResult(AuthResult.FAIL_OTHER);
                        }
                    }
                });
    }

    // Register Method
    public static void registerUser(Context ctx, String email, String pass, boolean remember, AuthCallback callback) {
        if (isNetworkAvailable(ctx)) {
            callback.onResult(AuthResult.FAIL_NO_NETWORK);
            return;
        }

        auth.createUserWithEmailAndPassword(email, pass)
                .addOnCompleteListener(task -> {
                    if (task.isSuccessful()) {

                        FirebaseUser firebaseUser = task.getResult().getUser();
                        if (firebaseUser == null) {
                            callback.onResult(AuthResult.FAIL_OTHER);
                            return;
                        }
                        String userId = firebaseUser.getUid();
                        FirebaseFirestore db = FirebaseFirestore.getInstance();
                        String nameFromEmail = email.split("@")[0];

                        Map<String, Object> user = new HashMap<>();
                        user.put("username", nameFromEmail);
                        user.put("email", email);
                        user.put("createdAt", FieldValue.serverTimestamp());
                        user.put("lastLogin", FieldValue.serverTimestamp());
                        user.put("name", nameFromEmail);
                        user.put("bio", "");
                        user.put("isPublic", true);

                        // Create the new document in the "users" collection
                        db.collection("users")
                                .document(userId)
                                .set(user)
                                .addOnCompleteListener(dbTask -> {
                                    saveRememberPreference(ctx, email, remember);
                                    callback.onResult(AuthResult.SUCCESS);
                                });
                    } else {
                        try {
                            throw Objects.requireNonNull(task.getException());
                        } catch (FirebaseAuthException e) {
                            String errorCode = e.getErrorCode();
                            switch (errorCode) {
                                case "ERROR_EMAIL_ALREADY_IN_USE":
                                    callback.onResult(AuthResult.FAIL_EMAIL_ALREADY_IN_USE);
                                    break;
                                case "ERROR_WEAK_PASSWORD":
                                    callback.onResult(AuthResult.FAIL_WEAK_PASSWORD);
                                    break;
                                case "ERROR_INVALID_EMAIL":
                                    callback.onResult(AuthResult.FAIL_INVALID_EMAIL);
                                    break;
                                default:
                                    callback.onResult(AuthResult.FAIL_OTHER);
                                    break;
                            }
                        } catch (Exception e) {
                            callback.onResult(AuthResult.FAIL_OTHER);
                        }
                    }
                });
    }

    // Update Last Login on Firebase
    private static void updateLastLoginAndNotify(AuthCallback callback) {
        FirebaseUser user = auth.getCurrentUser();
        if (user == null) {
            callback.onResult(AuthResult.FAIL_OTHER);
            return;
        }

        String userId = user.getUid();
        FirebaseFirestore db = FirebaseFirestore.getInstance();
        Map<String, Object> updates = new HashMap<>();
        updates.put("lastLogin", FieldValue.serverTimestamp());

        db.collection("users").document(userId)
                .update(updates)
                .addOnCompleteListener(task -> {
                    callback.onResult(AuthResult.SUCCESS);
                });
    }

    private static void saveRememberPreference(Context ctx, String email, boolean remember) {
        SharedPreferences prefs = ctx.getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE);
        prefs.edit()
                .putBoolean(KEY_REMEMBER, remember)
                .putString(KEY_EMAIL, email)
                .apply();
    }

    public static void logout(Context ctx) {
        auth.signOut();
        SharedPreferences prefs = ctx.getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE);
        prefs.edit().clear().apply();
    }

    public static String currentUser(Context ctx) {
        if (auth.getCurrentUser() != null) {
            return auth.getCurrentUser().getEmail();
        }
        SharedPreferences prefs = ctx.getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE);
        return prefs.getString(KEY_EMAIL, null);
    }
}