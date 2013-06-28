package com.dbappz.example.gimbal;

import com.qualcommlabs.usercontext.ContentListener;
import com.qualcommlabs.usercontext.PlaceEventListener;
import com.qualcommlabs.usercontext.protocol.ContentEvent;
import com.qualcommlabs.usercontext.protocol.PlaceEvent;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

/**
 * Serviço responsavel pelo tratamento dos eventos de evento e interesse do Gimbal 
 * @author José Guilherme Vanz <jose.vanz@dbappz.com>
 *
 */
public class DBGimbalService extends Service implements PlaceEventListener, ContentListener{

	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void contentEvent(ContentEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void placeEvent(PlaceEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
