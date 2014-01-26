package com.spdrinks;

/**
 * Created by Albert on 1/25/14.
 * DRINK_SESSION TABLE STRUCTURE
 * session_id   |INT       |
 * SESSION_START |LONG       |
 * SESSION_END  |LONG
 * SESSION RATING | STRING
 * SESSION HEIGHT | double
 * SESSION WEIGHT | double
 * SESSION COMPLETE | BOOL
 */
public class DrinkSession {
	int _id;
	int _count;
	long _start;
	long _end;
	String _rating;
	double _height;
	double _weight;
	boolean _complete;

	public DrinkSession(){

	}

	public DrinkSession(int id, long start, double height, double weight){
		this._id = id;
		this._start = start;
		this._height = height;
		this._weight = weight;
		this._count = 1;
	}

	public int getID(){
		return this._id;
	}
	public void setID(int id){
		this._id = id;
	}

	public int getCount(){
		return this._count;
	}

	public void setCount(int count){
		this._count = count;
	}

	public long getStart(){
		return this._start;
	}

	public void setStart(long start){
		this._start = start;
	}

	public long getEnd(){
		return this._end;
	}

	public void setEnd(long end){
		this._end = end;
	}

	public boolean getComplete(){
		return this._complete;
	}

	public void setComplete(boolean complete){
		this._complete = complete;
	}
}
