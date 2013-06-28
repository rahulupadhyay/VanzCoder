package com.dbappz.example.gimbal;

import org.apache.http.params.CoreConnectionPNames;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import com.dbappz.example.gimbal.logging.Logger;
import com.qualcommlabs.usercontext.ContextCoreConnector;
import com.qualcommlabs.usercontext.ContextCoreConnectorFactory;
import com.qualcommlabs.usercontext.ContextCoreStatus;
import com.qualcommlabs.usercontext.ContextInterestsConnector;
import com.qualcommlabs.usercontext.ContextInterestsConnectorFactory;
import com.qualcommlabs.usercontext.ContextPlaceConnector;
import com.qualcommlabs.usercontext.ContextPlaceConnectorFactory;

public class MainActivity extends Activity {

	private ContextCoreConnector coreConnector;
	private ContextPlaceConnector placeConnector;
	private ContextInterestsConnector interestsConnector;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		this.initGimbal();
		Logger.LogDebug("onCreatre()");
		setContentView(R.layout.activity_main);
	}


	private void initGimbal(){
		this.coreConnector = ContextCoreConnectorFactory.get(this);
		this.placeConnector = ContextPlaceConnectorFactory.get(this);
		this.interestsConnector = ContextInterestsConnectorFactory.get(this);
		if(this.coreConnector.isPermissionEnabled()){
			iniciaServicoGimbal();
		}else{
			ContextCoreStatus status = this.coreConnector.getStatus();
			Logger.LogError(status.getStatusMessage());
		}
		Intent intentService = new Intent(this,DBGimbalService.class);
		intentService.setAction("com.dbappz.example.gimbal.GIMBAL_SERVICE"); // TODO - verificar o que eh exatamente o setAction
		startService(intentService);
	}


	private void iniciaServicoGimbal() {
		// TODO Auto-generated method stub

	}






}
