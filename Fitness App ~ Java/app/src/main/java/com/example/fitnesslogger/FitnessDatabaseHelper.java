package com.example.fitnesslogger;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class FitnessDatabaseHelper extends SQLiteOpenHelper {

    private static final String DATABASE_NAME = "fitness.db";
    private static final int DATABASE_VERSION = 1;
    private static final String TABLE_NAME = "workouts";

    private static final String COL_ID = "id";
    private static final String COL_TYPE = "type";
    private static final String COL_DURATION = "duration";
    private static final String COL_IMAGE_URL = "image_url";

    // Initialize Database helper
    public FitnessDatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    // Create workouts table when database is first created
    @Override
    public void onCreate(SQLiteDatabase db) {
        String createTable = "CREATE TABLE " + TABLE_NAME + " (" +
                COL_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " + // ID
                COL_TYPE + " TEXT, " +                            // Type
                COL_DURATION + " TEXT, " +                        // DURATION
                COL_IMAGE_URL + " TEXT)";                         // Image
        db.execSQL(createTable);
    }

    // Drop old table if needed and recreate
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        onCreate(db);
    }

    // Insert new workout entry into the database
    public boolean addWorkout(String type, String duration, String imageUrl) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put(COL_TYPE, type);
        cv.put(COL_DURATION, duration);
        cv.put(COL_IMAGE_URL, imageUrl);
        long result = db.insert(TABLE_NAME, null, cv);
        return result != -1;
    }

    // Retrieve 5 most recent workouts
    public Cursor getRecentWorkouts() {
        SQLiteDatabase db = this.getReadableDatabase();
        return db.rawQuery("SELECT * FROM " + TABLE_NAME + " ORDER BY " + COL_ID + " DESC LIMIT 5", null);
    }
}