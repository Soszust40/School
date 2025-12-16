package com.example.assignment2;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.viewpager2.adapter.FragmentStateAdapter;

/**
 * Adapter that supplies the two feed fragments to the ViewPager2 in HomeFragment.
 * Tab 0 = Following
 * Tab 1 = For you
 */
public class HomePagerAdapter extends FragmentStateAdapter {
    public HomePagerAdapter(@NonNull Fragment parent) {
        super(parent);
    } // parent is the HomeFragment

    @NonNull
    @Override
    public Fragment createFragment(int position) {
        // Position 0 = Following feed
        // Position 1 = For you feed
        return FeedFragment.newInstance(position == 0 ? "following" : "foryou");
    }

    @Override
    public int getItemCount() {
        return 2;
    } //only 2 tabs total
}
