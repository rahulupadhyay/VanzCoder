package com.example.opengl;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

public class OpenGLRender implements GLSurfaceView.Renderer{

	/*----------------Native methods-------------------*/

	public native void renderFrame();
	
	/*-------------------------------------------------*/
	
	/**
	 * Renderiza frame
	 */
	@Override
	public void onDrawFrame(GL10 gl) {
		
	}

	/**
	 * Surface mududou de tamanho
	 */
	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		
	}

	/**
	 * Surface criada
	 */
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		
	}
	

}
