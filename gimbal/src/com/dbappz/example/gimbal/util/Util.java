package com.dbappz.example.gimbal.util;

/**
 * Classe utilitaria
 * @author José Guilherme Vanz <jose.vanz@dbappz.com>
 *
 */
public class Util {
	
	public static boolean stringNullOrEmpty(String s){
		return s == null || s.isEmpty();
	}

	public static boolean stringNotNullOrEmpty(String s){
		return !Util.stringNullOrEmpty(s);
	}
}
