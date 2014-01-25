package com.spdalpha.data;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.SortedSet;
import java.util.TreeSet;

import android.content.Context;
import android.content.SharedPreferences;

/**
 * Created by Daniel on 1/25/14.
 */
public class DataSource {

    private static final String PREFKEY = "userInfo";
    private SharedPreferences userPrefs;

    public DataSource(Context context) {
        userPrefs = context.getSharedPreferences(PREFKEY, Context.MODE_PRIVATE);
    }

    public boolean update(DataItem item) {

        if (item.getText().length() > 0) {
            SharedPreferences.Editor editor = userPrefs.edit();
            editor.putString( item.getKey(), item.getText());
            editor.commit();
            return true;
        } else {
            return remove(item);
        }
    }

    public boolean remove(DataItem item) {
        if (userPrefs.contains(item.getKey())) {
            SharedPreferences.Editor editor = userPrefs.edit();
            editor.remove(item.getKey());
            editor.commit();
        }
        return true;
    }
}
