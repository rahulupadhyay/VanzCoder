package com.example.myarvideo;

import com.example.opengl.OpenGLRender;
import com.example.opengl.OpenGLView;
import com.qualcomm.QCAR.QCAR;

import android.os.Bundle;
import android.app.Activity;
import android.content.res.Configuration;
import android.util.DisplayMetrics;
import android.view.Menu;
import android.view.WindowManager;

public class MyARVideo extends Activity {

	private AppStatus status = AppStatus.NOT_INIT;

	private int screenWidth = 0;
	private int screenHeight = 0;
	
	private int QCARFlags = QCAR.GL_20;
	private boolean isRetrato;
	
	private OpenGLView view;

	/* ---------- Native Methods ---------------- */
	/*
	 * Inicia a parte nativa da app
	 */
	private native void initNative(int width, int height);
	/*
	 * Atualiza o tamanho da tela
	 * */
	public native void updateScreenSize(int width, int height);
	/*
	 * Inicia o tracker da imagem
	 */
	private native void initTracker();
	
	/*
	 * Atualiza orientacao do device
	 * */
	public native void ehOrientacaoRetrato(boolean ehRetrato);
	
	/*
	 * Métodos para inicar a parar a camera
	 */
	public native void startCamera();
	public native void stopCamera();

	/* ---------------------------------------- */

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		updateAppStatus(AppStatus.INITING);
	}

	private void initApp() {
		/*
		 * Inicializa a parta da aplicação que não tem ligação com o QCAR
		 * */
		this.atualizaOrientacao();
		this.storeScreenSizes();
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		
		/*
		 * Inicializa o QCAR
		 * */
		int progresso = -1;
		do{
			progresso = QCAR.init();
		}while(progresso >= 0 && progresso < 100);
		
		/*
		 * Inicia tracker
		 * */
		this.initTracker();
		
		/*
		 * Inicia a parte nativa
		 */
		this.initNative(screenWidth, screenHeight);
		/*
		 * Inicia AR
		 */
		this.initAR();
	}
	
	private void initAR() {
		// Create OpenGL ES view:
				int depthSize = 16;
				int stencilSize = 0;
				boolean translucent = QCAR.requiresAlpha();
				this.view = new OpenGLView(this);
				this.view.init(this.QCARFlags, translucent, depthSize, stencilSize);
				this.view.setRenderer(new OpenGLRender(this));
				this.setContentView(this.view);
	
	}
	
	public void atualizaOrientacao(){
		Configuration config = getResources().getConfiguration();
		if(config.orientation == Configuration.ORIENTATION_PORTRAIT){
			this.isRetrato = true;
		}else{
			this.isRetrato = false;
		}
		this.ehOrientacaoRetrato(isRetrato);
	}

	private void storeScreenSizes() {
		 //Update screen size
        DisplayMetrics metrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metrics);
        screenWidth = metrics.widthPixels;
        screenHeight = metrics.heightPixels;
	}
	
	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		this.storeScreenSizes();
		this.atualizaOrientacao();
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
