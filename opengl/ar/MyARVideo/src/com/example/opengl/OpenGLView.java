package com.example.opengl;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class OpenGLView extends GLSurfaceView{

	private OpenGLRender render;
	
	/*----------------Native methods-------------------*/

	public native void updateScreenConfig(int width, int height);
	
	/*-------------------------------------------------*/
	
	public OpenGLView(Context context) {
		super(context);
	}
	
	public OpenGLRender getRender() {
		return render;
	}
	
	@Override
	public void setRenderer(Renderer renderer) {
		super.setRenderer(renderer);
	}

	
}
