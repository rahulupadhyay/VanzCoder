package com.example.myarvideo;

import android.app.Activity;
import android.os.Bundle;

public class MyARVideo extends Activity {

	private AppStatus appStatus = AppStatus.NOT_INITIALIZED;

	/*----------------Native methods-------------------*/

	public native void initNativeApp();
	
	/*-------------------------------------------------*/

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		updateApp(appStatus.INICIALIZATION);

	}

	@Override
	protected void onPostCreate(Bundle savedInstanceState) {
		super.onPostCreate(savedInstanceState);
	}

	public void updateApp(AppStatus status) {

		switch (status) {
			case INICIALIZATION:
				initApp();
				break;
			case NATIVE_INICIALIZATION:
				initNative();
				break;
			case RUNNING:
				break;
			case STOP:
				break;
		}

	}

	/*
	 * Inicializa a parte que tem relacionamento com o QCAR
	 */
	private void initNative() {
		// TODO Auto-generated method stub
	}

	/*
	 * Inicializa a parte que não tem relação ao QCAR
	 */
	private void initApp() {
		// TODO Auto-generated method stub
	}

}
