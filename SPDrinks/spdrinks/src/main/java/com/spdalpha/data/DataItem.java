package com.spdalpha.data;

import android.annotation.SuppressLint;

/**
 * Created by Daniel on 1/25/14.
 */
public class DataItem {

    private String text;
    private String key;

    public static final String TEXT = "text";
    public static final String KEY = "key";

    public String getKey() {
        return key;
    }
    public void setKey( String key ) {
        this.key = key;
    }
    public String getText() {
        return text;
    }
    public void setText( String text ) {
        this.text = text;
    }

    public static DataItem createNew(String dataKey, String dataText) {
        DataItem item = new DataItem();
        item.setKey( dataKey );
        item.setText( dataText );
        return item;
    }
}
