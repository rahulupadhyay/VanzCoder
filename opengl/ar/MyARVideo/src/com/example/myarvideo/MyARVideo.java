package com.example.myarvideo;

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
		// TODO Auto-generated method stub
		
	}
	private void atualizaOrientacao(){
		Configuration config = getResources().getConfiguration();
		if(config.orientation == Configuration.ORIENTATION_PORTRAIT){
			this.isRetrato = true;
		}else{
			this.isRetrato = false;
		}
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
