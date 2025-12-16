package com.example.assignment2;

import android.content.Intent;
import android.os.Bundle;
import android.text.InputType;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

public class LoginActivity extends AppCompatActivity {

    // Keys for saving typed text when phone rotates
    private static final String K_USERNAME = "k_username";
    private static final String K_PASS = "k_pass";

    private EditText etUsername, etPass;
    private CheckBox cbRemember;

    @Override
    protected void onCreate(Bundle s) {
        super.onCreate(s);

        // Skip login screen if user remembered
        if (AuthManager.isRemembered(this)) {
            startActivity(new Intent(this, HomeActivity.class));
            finish();
            return;
        }

        setContentView(R.layout.activity_login);

        // Hook up views
        etUsername = findViewById(R.id.etUsername);
        etPass = findViewById(R.id.etPassword);
        cbRemember = findViewById(R.id.cbRemember);
        Button btnLogin = findViewById(R.id.btnLogin);
        TextView tvRegister = findViewById(R.id.tvRegister);

        // Restore text after rotation
        if (s != null) {
            etUsername.setText(s.getString(K_USERNAME, ""));
            etPass.setText(s.getString(K_PASS, ""));
        }

        // Input types
        etUsername.setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS);
        etPass.setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD);

        btnLogin.setOnClickListener(v -> handleLogin());
        tvRegister.setOnClickListener(v -> handleRegister());
    }

    // Login Method
    private void handleLogin() {
        String email = etUsername.getText().toString().trim();
        String pass = etPass.getText().toString();

        if (email.isEmpty() || pass.isEmpty()) {
            Toast.makeText(this, getString(R.string.login_fill_both), Toast.LENGTH_SHORT).show();
            return;
        }

        AuthManager.loginUser(this, email, pass, cbRemember.isChecked(), result -> runOnUiThread(() -> {
            switch (result) {
                case SUCCESS:
                    Toast.makeText(this, getString(R.string.login_success), Toast.LENGTH_SHORT).show();
                    goHome();
                    break;
                case FAIL_NO_NETWORK:
                    Toast.makeText(this, getString(R.string.login_no_network), Toast.LENGTH_LONG).show();
                    break;
                case FAIL_INVALID_CREDENTIALS:
                    Toast.makeText(this, getString(R.string.login_invalid_credentials), Toast.LENGTH_SHORT).show();
                    break;
                case FAIL_INVALID_EMAIL:
                    Toast.makeText(this, getString(R.string.login_invalid_email), Toast.LENGTH_SHORT).show();
                    break;
                case FAIL_USER_DISABLED:
                    Toast.makeText(this, getString(R.string.login_user_disabled), Toast.LENGTH_SHORT).show();
                    break;
                case FAIL_OTHER:
                    Toast.makeText(this, getString(R.string.login_error_other), Toast.LENGTH_SHORT).show();
                    break;
            }
        }));
    }

    // Register Method
    private void handleRegister() {
        String email = etUsername.getText().toString().trim();
        String pass = etPass.getText().toString();

        if (email.isEmpty() || pass.isEmpty()) {
            Toast.makeText(this, getString(R.string.login_fill_both), Toast.LENGTH_SHORT).show();
            return;
        }

        AuthManager.registerUser(this, email, pass, cbRemember.isChecked(), result -> runOnUiThread(() -> {
            switch (result) {
                case SUCCESS:
                    Toast.makeText(this, getString(R.string.login_account_created), Toast.LENGTH_SHORT).show();
                    goHome();
                    break;
                case FAIL_NO_NETWORK:
                    Toast.makeText(this, getString(R.string.login_no_network), Toast.LENGTH_LONG).show();
                    break;
                case FAIL_EMAIL_ALREADY_IN_USE:
                    Toast.makeText(this, getString(R.string.login_email_in_use), Toast.LENGTH_SHORT).show();
                    break;
                case FAIL_WEAK_PASSWORD:
                    Toast.makeText(this, getString(R.string.login_weak_password), Toast.LENGTH_SHORT).show();
                    break;
                case FAIL_INVALID_EMAIL:
                    Toast.makeText(this, getString(R.string.login_invalid_email), Toast.LENGTH_SHORT).show();
                    break;
                case FAIL_OTHER:
                    Toast.makeText(this, getString(R.string.login_error_other), Toast.LENGTH_SHORT).show();
                    break;
            }
        }));
    }

    private void goHome() {
        Intent i = new Intent(this, HomeActivity.class);
        i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(i);
        finish();
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle out) {
        super.onSaveInstanceState(out);
        out.putString(K_USERNAME, etUsername.getText().toString());
        out.putString(K_PASS, etPass.getText().toString());
    }
}