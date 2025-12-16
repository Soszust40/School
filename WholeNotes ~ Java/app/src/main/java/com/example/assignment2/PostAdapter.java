package com.example.assignment2;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

/**
 * RecyclerView adapter for showing Post objects in a scrolling list.
 * Each Post is displayed in an "item_post.xml" card layout.
 */
public class PostAdapter extends RecyclerView.Adapter<PostAdapter.VH> {

    public interface OnDeleteClickListener {
        void onDeleteClick(Post post);
    }
    
    public interface OnLikeClickListener {
        void onLikeClick(Post post);
    }

    private List<Post> data;
    private OnDeleteClickListener deleteListener;
    private OnLikeClickListener likeListener;
    private String currentUserEmail;
    private String currentUserId;

    // Constructor takes the list of posts I want to show
    public PostAdapter(List<Post> data) {
        this.data = data;
    }

    /** Set the delete click listener and current user email for showing delete buttons */
    public void setDeleteListener(OnDeleteClickListener listener, String currentUserEmail) {
        this.deleteListener = listener;
        this.currentUserEmail = currentUserEmail;
    }
    
    /** Set the like click listener and current user info */
    public void setLikeListener(OnLikeClickListener listener, String currentUserEmail, String currentUserId) {
        this.likeListener = listener;
        this.currentUserEmail = currentUserEmail;
        this.currentUserId = currentUserId;
    }

    /** Replace data and refresh UI when posts change. */
    public void setData(List<Post> newData) {
        this.data = newData;
        notifyDataSetChanged(); // refresh
    }

    @NonNull
    @Override
    public VH onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        // Inflate one card layout for each Post
        View v = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.item_post, parent, false);
        return new VH(v);
    }

    @Override
    public void onBindViewHolder(@NonNull VH holder, int position) {
        Post p = data.get(position);

        // Required fields
        holder.tvTitle.setText(p.title);
        holder.tvSubtitle.setText(p.subtitle);
        holder.tvText.setText(p.text);

        // Show lyrics only if the post has them
        if (p.lyrics != null && !p.lyrics.isEmpty()) {
            holder.tvLyrics.setVisibility(View.VISIBLE);
            holder.tvLyrics.setText(p.lyrics);
        } else {
            holder.tvLyrics.setVisibility(View.GONE);
        }

        // Show clip label only if provided
        if (p.clip != null && !p.clip.isEmpty()) {
            holder.tvClip.setVisibility(View.VISIBLE);
            holder.tvClip.setText(p.clip);
        } else {
            holder.tvClip.setVisibility(View.GONE);
        }

        // Likes and comments
        holder.tvLikes.setText(
                holder.itemView.getContext().getString(R.string.likes_count, p.likes)
        );

        holder.tvComments.setText(
                holder.itemView.getContext().getString(R.string.comments_count, p.comments)
        );

        // Optional song reference
        if (p.song != null && !p.song.isEmpty()) {
            holder.tvSong.setVisibility(View.VISIBLE);
            holder.tvSong.setText(
                    holder.itemView.getContext().getString(R.string.song_reference, p.song)
            );
        } else {
            holder.tvSong.setVisibility(View.GONE);
        }

        // NEW: Show location name (City, State) if available
        if (holder.tvDistance != null) {
            // DEBUG: Log to see if location data exists
            android.util.Log.d("PostAdapter", "Post: " + p.title +
                    ", locationName: " + p.locationName +
                    ", lat: " + p.latitude +
                    ", lon: " + p.longitude);

            if (p.locationName != null && !p.locationName.isEmpty()) {
                holder.tvDistance.setVisibility(View.VISIBLE);
                holder.tvDistance.setText(String.format("📍 %s", p.locationName));
            } else {
                holder.tvDistance.setVisibility(View.GONE);
            }
        }

        // Show delete button only for posts by the current user
        if (holder.btnDelete != null) {
            boolean canDelete = currentUserEmail != null && 
                               currentUserEmail.equalsIgnoreCase(p.authorEmail);
            if (canDelete) {
                holder.btnDelete.setVisibility(View.VISIBLE);
                holder.btnDelete.setOnClickListener(v -> {
                    if (deleteListener != null) {
                        deleteListener.onDeleteClick(p);
                    }
                });
            } else {
                holder.btnDelete.setVisibility(View.GONE);
                holder.btnDelete.setOnClickListener(null);
            }
        }
        
        // Handle like button
        if (holder.btnLike != null) {
            boolean isLiked = p.isLikedByUser(currentUserId);
            holder.btnLike.setText(isLiked ? "♥ " + p.likes : "♡ " + p.likes);
            holder.btnLike.setOnClickListener(v -> {
                if (likeListener != null) {
                    likeListener.onLikeClick(p);
                }
            });
        }
    }

    @Override
    public int getItemCount() {
        return data == null ? 0 : data.size();
    }

    /** ViewHolder holds references to views inside one post card. */
    static class VH extends RecyclerView.ViewHolder {
        TextView tvTitle, tvSubtitle, tvText, tvLyrics, tvClip, tvLikes, tvComments, tvSong;
        TextView tvDistance, btnDelete, btnLike;

        VH(View itemView) {
            super(itemView);
            tvTitle    = itemView.findViewById(R.id.tvTitle);
            tvSubtitle = itemView.findViewById(R.id.tvSubtitle);
            tvText     = itemView.findViewById(R.id.tvText);
            tvLyrics   = itemView.findViewById(R.id.tvLyrics);
            tvClip     = itemView.findViewById(R.id.tvClip);
            tvLikes    = itemView.findViewById(R.id.tvLikes);
            tvComments = itemView.findViewById(R.id.tvComments);
            tvSong     = itemView.findViewById(R.id.tvSong);
            tvDistance = itemView.findViewById(R.id.tvDistance);
            btnDelete  = itemView.findViewById(R.id.btnDelete);
            btnLike    = itemView.findViewById(R.id.btnLike);
        }
    }
}