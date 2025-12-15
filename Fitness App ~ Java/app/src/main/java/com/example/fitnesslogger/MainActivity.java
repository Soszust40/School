package com.example.fitnesslogger;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainActivity extends AppCompatActivity implements SensorEventListener {

    private SensorManager sensorManager;
    private Sensor stepSensor;
    private TextView tvStepCount;
    private ListView listView;
    private FitnessDatabaseHelper dbHelper;

    private ArrayList<String> displayList;
    private ArrayList<String> urlList;

    private static final int PERMISSION_CODE = 100;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tvStepCount = findViewById(R.id.tvStepCount);
        listView = findViewById(R.id.listViewWorkouts);
        Button btnAdd = findViewById(R.id.btnAddActivity);
        dbHelper = new FitnessDatabaseHelper(this);

        // Permission Check
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACTIVITY_RECOGNITION)
                != PackageManager.PERMISSION_GRANTED) {

            tvStepCount.setText(R.string.step_count_no_permission);

            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.ACTIVITY_RECOGNITION}, PERMISSION_CODE);
        } else {
            setupSensor();
        }

        // Button to open AddActivity
        btnAdd.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, AddActivity.class);
            startActivity(intent);
        });

        // Clicking a workout entry shows saved image
        listView.setOnItemClickListener((parent, view, position, id) -> {
            String savedUrl = urlList.get(position);
            showImageDialog(savedUrl);
        });
    }

    private void setupSensor() {
        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        if (sensorManager != null) {
            stepSensor = sensorManager.getDefaultSensor(Sensor.TYPE_STEP_COUNTER);
            if (stepSensor == null) {
                tvStepCount.setText(getString(R.string.no_sensor));
            }
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (sensorManager != null && stepSensor != null) {
            sensorManager.registerListener(this, stepSensor, SensorManager.SENSOR_DELAY_UI);
        }
        loadRecentActivities();
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (sensorManager != null) {
            sensorManager.unregisterListener(this);
        }
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == Sensor.TYPE_STEP_COUNTER) {
            tvStepCount.setText(getString(R.string.step_count_format, (int) event.values[0]));
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) { }

    private void loadRecentActivities() {
        displayList = new ArrayList<>();
        urlList = new ArrayList<>();

        Cursor cursor = dbHelper.getRecentWorkouts(); // Query last 5 workouts

        if (cursor.moveToFirst()) {
            do {
                String type = cursor.getString(1); // Activity type
                String duration = cursor.getString(2); // Duration in mins
                String url = cursor.getString(3); // Image URL

                displayList.add(type + " - " + duration + " mins");
                urlList.add(url);
            } while (cursor.moveToNext());
        }
        cursor.close();

        ArrayAdapter<String> adapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, displayList);
        listView.setAdapter(adapter);
    }

    private void showImageDialog(String urlToLoad) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        ImageView imageView = new ImageView(this);

        imageView.setMinimumHeight(600);
        imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);

        builder.setView(imageView);
        builder.setTitle(getString(R.string.dialog_title));
        builder.setPositiveButton(getString(R.string.dialog_close), null);

        // Check if URL is placeholder
        if (urlToLoad.equals("LOCAL_PLACEHOLDER")) {
            imageView.setImageResource(R.drawable.offline_placeholder);
        }
        else {
            // URL is real — attempt to download
            ExecutorService executor = Executors.newSingleThreadExecutor();
            Handler handler = new Handler(Looper.getMainLooper());

            executor.execute(() -> {
                try {
                    // Show image
                    InputStream in = new java.net.URL(urlToLoad).openStream();
                    Bitmap bmp = BitmapFactory.decodeStream(in);

                    handler.post(() -> imageView.setImageBitmap(bmp));

                } catch (Exception e) {
                    // Backup image
                    handler.post(() -> {
                        imageView.setImageResource(R.drawable.offline_placeholder);

                        Toast.makeText(MainActivity.this,
                                getString(R.string.err_network_msg),
                                Toast.LENGTH_SHORT).show();
                    });
                }
            });
        }

        // Finally display dialog
        AlertDialog dialog = builder.create();
        dialog.show();
    }

    // Permission Result Handling
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if (requestCode == PERMISSION_CODE) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                // Permission Granted: Start counting
                setupSensor();
            } else {
                // User denied — update UI accordingly
                tvStepCount.setText(R.string.step_count_no_permission);

                Toast.makeText(this, getString(R.string.permission_denied), Toast.LENGTH_SHORT).show();
            }
        }
    }
}