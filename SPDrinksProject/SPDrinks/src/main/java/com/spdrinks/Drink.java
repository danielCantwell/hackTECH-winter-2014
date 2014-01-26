package com.spdrinks;

/**
 * Created by Albert on 1/25/14.
 *
 * TABLE INFORMATION
 *
 * ID           |INT        |PRI
 * session_id   |INT       |
 * time_created |TEXT       |
 */
public class Drink {

    int _id;
    int _session_id;
    long _time_created; //timestamp for creation

    public Drink(){

    }

    public Drink(int id, int session_id, long time_created){
        this._id = id;
        this._session_id = session_id;
        this._time_created = time_created;

    }

    public Drink(int session_id, long time_created){
        this._session_id = session_id;
        this._time_created = time_created;
    }

    public int getID(){
        return this._id;
    }

    public void setID(int id){
        this._id = id;
    }
    public int getSessionID(){
        return this._session_id;
    }

    public void setSessionID(int session_id){
        this._session_id = session_id;
    }

    public long getTimeCreated(){
        return this._time_created;
    }

    public void setTimeCreated(long time){
        this._time_created = time;
    }

}
