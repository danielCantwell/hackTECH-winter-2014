package com.spdrinks;
import android.content.ContentValues;
import android.content.Context;
import android.database.sqlite.*;
import android.database.Cursor;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Albert on 1/25/14.
 */

public class DatabaseHandler extends SQLiteOpenHelper {

    public static final int DATABASE_VERSION = 1;
    public static final String DATABASE_NAME = "SPDrinks.db";

    public static final String TABLE_DRINKS = "drinks";
    public static final String DRINK_ID = "_id";
    public static final String DRINK_SESSION_ID ="session_id";
    public static final String DRINK_TIME = "time";

    public static final String TABLE_DRINKING_SESSION = "drinking_session";
    public static final String SESSION_ID = "_id";
    public static final String SESSION_START = "start";
    public static final String SESSION_END = "end";
    public static final String SESSION_COUNT = "count";
    public static final String SESSION_RATING = "rating";
    public static final String SESSION_HEIGHT = "height";
    public static final String SESSION_WEIGHT = "weight";
    public static final String SESSION_COMPLETE = "session_complete";



    public DatabaseHandler(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase database) {
        //Create Drinks
        String CREATE_DRINKS_TABLE = "CREATE TABLE "
                + TABLE_DRINKS + " (" + DRINK_ID + " integer primary key autoincrement, " +
                DRINK_SESSION_ID + " INTEGER," + DRINK_TIME + " INTEGER)";
        database.execSQL(CREATE_DRINKS_TABLE);

        //Create Drink Sessions
        String CREATE_DRINK_SESSIONS_TABLE = "CREATE TABLE " + TABLE_DRINKING_SESSION + " (" + SESSION_ID + " integer primary key autoincrement,"
                + SESSION_START + " TEXT," + SESSION_END + " TEXT," + SESSION_COUNT + " INTEGER," + SESSION_RATING + " TEXT," +
                SESSION_HEIGHT + " TEXT," + SESSION_WEIGHT + " TEXT," + SESSION_COMPLETE + " TEXT);";
        database.execSQL(CREATE_DRINK_SESSIONS_TABLE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
    String SQL_DELETE_ENTRIES =  "DROP TABLE IF EXISTS " + TABLE_DRINKING_SESSION +","+ TABLE_DRINKS;
        db.execSQL(SQL_DELETE_ENTRIES);
        onCreate(db);
    }

    public void deleteDB(){
        SQLiteDatabase db = this.getReadableDatabase();
        String SQL_DELETE_ENTRIES =  "DROP TABLE IF EXISTS "+ TABLE_DRINKS;
        db.execSQL(SQL_DELETE_ENTRIES);
       SQL_DELETE_ENTRIES =  "DROP TABLE IF EXISTS "+ TABLE_DRINKING_SESSION;
        db.execSQL(SQL_DELETE_ENTRIES);
    }

    void addDrink(Drink drink){
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(DRINK_SESSION_ID, drink.getSessionID());
        values.put(DRINK_TIME, drink.getTimeCreated());
        db.insert(TABLE_DRINKS, null, values);
        db.close();
    }

    Drink getDrink(int id){
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.query(TABLE_DRINKS, new String[]{ DRINK_ID, DRINK_SESSION_ID, DRINK_TIME},
                DRINK_ID + "=?", new String[] { String.valueOf(id)}, null, null, null, null);
        if(cursor != null){
            cursor.moveToFirst();
        }
        Drink drink = new Drink(Integer.parseInt(cursor.getString(0)),Integer.parseInt(cursor.getString(1)),Integer.parseInt(cursor.getString(2)));
        return drink;
    }

    public List<Drink> getSessionDrinks(int session_id){
        List<Drink> DrinkList = new ArrayList<Drink>();

        String selectQuery =  "Select  * FROM " + TABLE_DRINKS + " WHERE session_id = " + session_id;
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor cursor = db.rawQuery(selectQuery, null);
        if (cursor.moveToFirst()) {
            do {
                Drink drink = new Drink();
                drink.setID(Integer.parseInt(cursor.getString(0)));
                drink.setSessionID(Integer.parseInt(cursor.getString(1)));
                drink.setTimeCreated(Integer.parseInt(cursor.getString(2)));
                // Adding drink to list
                DrinkList.add(drink);
            } while (cursor.moveToNext());
        }

        return DrinkList;
    }


}

