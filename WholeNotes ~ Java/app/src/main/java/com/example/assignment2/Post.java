package com.example.assignment2;

import android.location.Location;
import org.json.JSONException;
import org.json.JSONObject;

public class Post {
    public String id; //id for firebase storage

    public String title, subtitle, text, lyrics, clip, song, authorEmail;
    public int likes, comments;
    public Double latitude;
    public Double longitude;
    public String locationName; // "City, State" format
    public java.util.Set<String> likedBy; // Set of user IDs who liked this post

    public Post(String title, String subtitle, String text, String lyrics,
                String clip, int likes, int comments, String song, String authorEmail,
                Double latitude, Double longitude, String locationName) {
        this.title = title;
        this.subtitle = subtitle;
        this.text = text;
        this.lyrics = lyrics;
        this.clip = clip;
        this.likes = likes;
        this.comments = comments;
        this.song = song;
        this.authorEmail = authorEmail;
        this.latitude = latitude;
        this.longitude = longitude;
        this.locationName = locationName;
        this.likedBy = new java.util.HashSet<>();
    }
    
    /** Check if a specific user has liked this post */
    public boolean isLikedByUser(String userId) {
        return likedBy != null && userId != null && likedBy.contains(userId);
    }

    /**
     * Calculate distance from user location in miles.
     * Returns Double.MAX_VALUE if the post has no location.
     */
    public double getDistanceFrom(double userLat, double userLon) {
        if (latitude == null || longitude == null) {
            return Double.MAX_VALUE;
        }
        float[] results = new float[1];
        Location.distanceBetween(userLat, userLon, latitude, longitude, results);
        return results[0] * 0.000621371; // Convert meters to miles
    }

    /**
     * Convert Post object to JSON including location info.
     */
    public JSONObject toJson() throws JSONException {
        JSONObject o = new JSONObject();
        if (id != null && !id.isEmpty()) o.put("id", id);
        o.put("title", n(title));
        o.put("subtitle", n(subtitle));
        o.put("text", n(text));
        o.put("lyrics", n(lyrics));
        o.put("clip", n(clip));
        o.put("likes", likes);
        o.put("comments", comments);
        o.put("song", n(song));
        o.put("authorEmail", n(authorEmail));
        if (latitude != null) o.put("latitude", latitude);
        if (longitude != null) o.put("longitude", longitude);
        if (locationName != null) o.put("locationName", locationName); // Include city/state
        if (likedBy != null && !likedBy.isEmpty()) {
            org.json.JSONArray likedByArray = new org.json.JSONArray();
            for (String userId : likedBy) {
                likedByArray.put(userId);
            }
            o.put("likedBy", likedByArray);
        }
        return o;
    }

    /**
     * Create a Post object from JSON, including location info.
     */
    public static Post fromJson(JSONObject o) throws JSONException {
        Double lat = o.has("latitude") ? o.getDouble("latitude") : null;
        Double lon = o.has("longitude") ? o.getDouble("longitude") : null;
        String locName = o.optString("locationName", null); // City, State
        String docId = o.optString("id", null);

        Post p = new Post(
            s(o, "title"),
            s(o, "subtitle"),
            s(o, "text"),
            ns(o, "lyrics"),
            ns(o, "clip"),
            o.optInt("likes", 0),
            o.optInt("comments", 0),
            ns(o, "song"),
            s(o, "authorEmail"),
            lat,
            lon,
            locName
        );
        if (!docId.isEmpty()) p.id = docId;
        
        // Restore likedBy set
        org.json.JSONArray likedByArray = o.optJSONArray("likedBy");
        if (likedByArray != null) {
            p.likedBy = new java.util.HashSet<>();
            for (int i = 0; i < likedByArray.length(); i++) {
                String userId = likedByArray.optString(i);
                if (userId != null && !userId.isEmpty()) {
                    p.likedBy.add(userId);
                }
            }
        }
        
        return p;
    }

    // Helper: convert null to empty string
    private static String n(String v) { return v == null ? "" : v; }

    // Helper: get string from JSON with default ""
    private static String s(JSONObject o, String k) { return o.optString(k, ""); }

    // Helper: get nullable string from JSON
    private static String ns(JSONObject o, String k) {
        String v = o.optString(k, null);
        return v.isEmpty() ? null : v;
    }
}
