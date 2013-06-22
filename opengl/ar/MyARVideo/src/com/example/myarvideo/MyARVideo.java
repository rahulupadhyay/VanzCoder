package com.example.myarvideo;

import android.os.Bundle;
import android.app.Activity;
import android.util.DisplayMetrics;
import android.view.Menu;

public class MyARVideo extends Activity {

	private AppStatus status = AppStatus.NOT_INIT;

	private int screenWidth = 0;
	private int screenHeight = 0;

	/* ---------- Native Methods ---------------- */
	private native void initNative(int width, int height);

	public native void updateScreenSize(int width, int height);

	/* ---------------------------------------- */

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		updateAppStatus(AppStatus.INITING);
	}

	private void initApp() {
		storeScreenSizes();
		// TODO init app
		// TODO init native app
		this.initNative(screenWidth, screenHeight);
		
	}
	
	

	private void storeScreenSizes() {
		 //Update screen size
        DisplayMetrics metrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metrics);
        screenWidth = metrics.widthPixels;
        screenHeight = metrics.heightPixels;
	}

	private void updateAppStatus(AppStatus status) {

		switch (status) {
		case INITING:
			// TODO
			initApp();
			break;
		case INITED:
			// TODO
			break;
		case RUNNING:
			// TODO
			break;
		case STOP:
			// TODO
			break;
		}
	}
}
