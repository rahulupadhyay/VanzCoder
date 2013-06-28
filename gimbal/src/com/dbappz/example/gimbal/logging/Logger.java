package com.dbappz.example.gimbal.logging;

import com.dbappz.example.gimbal.util.Util;

import android.util.Log;

/**
 * Classe para logging da aplicação
 * @author José Guilherme Vanz <jose.vanz@dbappz.com>
 */
public class Logger {

	private static final String APP_TAG = "GIMBAL_APP";

	public static void LogInfo(String msg) {
		Logger.Log(LogType.INFO, null, msg);
	}

	public static void LogWarn(String msg) {
		Logger.Log(LogType.WARN, null, msg);
	}

	public static void LogDebug(String msg) {
		Logger.Log(LogType.DEBUG, null, msg);
	}

	public static void LogError(String msg) {
		Logger.Log(LogType.ERROR, null, msg);
	}
	
	public static void LogInfoWithTag(String tag,String msg) {
		Logger.Log(LogType.INFO, tag, msg);
	}

	public static void LogWarnWithTag(String tag,String msg) {
		Logger.Log(LogType.WARN, tag, msg);
	}

	public static void LogDebugWithTag(String tag,String msg) {
		Logger.Log(LogType.DEBUG, tag, msg);
	}

	public static void LogErrorWithTag(String tag,String msg) {
		Logger.Log(LogType.ERROR, tag, msg);
	}

	private static void Log(LogType type, String sufixTag, String msg){
		if(Util.stringNullOrEmpty(msg)){
			return;
		}
		String tag = APP_TAG;
		if(Util.stringNotNullOrEmpty(sufixTag)){
			tag += sufixTag;
		}
		switch (type) {
		case DEBUG:
			Log.d(tag, msg);
			break;
		case WARN:
			Log.w(tag, msg);
			break;
		case ERROR:
			Log.e(tag, msg);
			break;
		default:
			Log.i(tag, msg);
			break;
		}
	}

	
}
