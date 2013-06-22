package com.example.opengl;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.example.myarvideo.MyARVideo;
import com.qualcomm.QCAR.QCAR;

import android.opengl.GLSurfaceView;

public class OpenGLRender implements GLSurfaceView.Renderer{
	
	private MyARVideo activity;

	/*-------------Native methods ------------------------*/
	public native void renderFrame();
	/* -------------------------------------------------- */
	
	public OpenGLRender(MyARVideo activity) {
		super();
		this.activity = activity;
	}
	
	@Override
	public void onDrawFrame(GL10 gl) {
		renderFrame();
		
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		this.activity.updateScreenSize(width, height);
		this.activity.atualizaOrientacao();
		QCAR.onSurfaceChanged(width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		QCAR.onSurfaceCreated();
	}

}
