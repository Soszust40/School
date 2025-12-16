package com.example.assignment2;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.viewpager2.widget.ViewPager2;

import com.google.android.material.tabs.TabLayout;
import com.google.android.material.tabs.TabLayoutMediator;

/**
 * Fragment that lives inside HomeActivity.
 * Hosts the two-tab layout: "Following" and "For you".
 * Uses ViewPager2 + TabLayout to switch between feeds.
 */
public class HomeFragment extends Fragment {

    private static final String ARG_TAB = "tab"; // bundle key for which tab to open
    private int currentTab = 0; // remembers the tab the user is currently on

    // Factory method to pass the tab index when creating this fragment
    public static HomeFragment newInstance(int tabIndex) {
        Bundle b = new Bundle();
        b.putInt(ARG_TAB, tabIndex);
        HomeFragment f = new HomeFragment();
        f.setArguments(b);
        return f;
    }

    // Letting the parent Activity ask which tab is active (for state saving)
    public int getCurrentTabIndex() {
        return currentTab;
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        // Inflating the fragment_home.xml layout which has TabLayout + ViewPager2
        return inflater.inflate(R.layout.fragment_home, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View v, @Nullable Bundle s) {
        // Getting the TabLayout and ViewPager2 from the layout
        TabLayout tabs = v.findViewById(R.id.tab_layout);
        ViewPager2 pager = v.findViewById(R.id.view_pager);

        // Hooking up a PagerAdapter that will give the content for each tab
        pager.setAdapter(new HomePagerAdapter(this));

        // Restoring the tab user was on last time that was passed in from the Activity
        if (getArguments() != null) {
            currentTab = getArguments().getInt(ARG_TAB, 0);
        }
        pager.setCurrentItem(currentTab, false);

        new TabLayoutMediator(tabs, pager, (tab, pos) -> {
            int title = (pos == 0) ? R.string.tab_following : R.string.tab_for_you;
            tab.setText(title);
            tab.setContentDescription(title); // reads the tab label
        }).attach();

        // Looking for page changes so it can remember the current tab
        pager.registerOnPageChangeCallback(new ViewPager2.OnPageChangeCallback() {
            @Override
            public void onPageSelected(int position) {
                currentTab = position;
            }
        });
    }
}