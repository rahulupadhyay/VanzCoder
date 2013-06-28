package com.dbappz.example.gimbal;

import com.dbappz.example.gimbal.logging.Logger;

import android.app.Application;
import android.content.ComponentCallbacks;
import android.content.res.Configuration;

/**
 * Classe responsavel pela gerencia da aplicação
 * @author José Guilherme Vanz <jose.vanz@dbappz.com>
 *
 */
public class GimbalApp extends Application {

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		Logger.LogDebugWithTag("_APP", "onConfigurationChanged()");
	}

	@Override
	public void onCreate() {
		super.onCreate();
		Logger.LogDebugWithTag("_APP", "onCreate()");
	}

	@Override
	public void onLowMemory() {
		super.onLowMemory();
		Logger.LogWarnWithTag("_APP", "onLowMemory()");
	}

	@Override
	public void onTerminate() {
		super.onTerminate();
		Logger.LogDebugWithTag("_APP", "onTerminate()");
	}

	@Override
	public void onTrimMemory(int level) {
		super.onTrimMemory(level);
		Logger.LogWarnWithTag("_APP", "onTrimMemory()");
	}

	@Override
	public void registerActivityLifecycleCallbacks(
			ActivityLifecycleCallbacks callback) {
		super.registerActivityLifecycleCallbacks(callback);
		Logger.LogDebugWithTag("_APP", "registerActivityLifecycleCallacks()");
	}

	@Override
	public void registerComponentCallbacks(ComponentCallbacks callback) {
		super.registerComponentCallbacks(callback);
		Logger.LogDebugWithTag("_APP", "registerComponentCallbacks()");
	}

	@Override
	public void unregisterActivityLifecycleCallbacks(
			ActivityLifecycleCallbacks callback) {
		super.unregisterActivityLifecycleCallbacks(callback);
		Logger.LogDebugWithTag("_APP", "unregisterActivityLifecyclesCallbacks()");
	}

	@Override
	public void unregisterComponentCallbacks(ComponentCallbacks callback) {
		super.unregisterComponentCallbacks(callback);
		Logger.LogDebugWithTag("_APP", "unregisterComponentCallbacks()");
	}
	
	

}
