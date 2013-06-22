/*
* JNI INTERFACE
* Here, there are all binds between java and native sources
* José Guilherme Vanz <guilherme.sft@gmail.com>
*/
#include <jni.h>
#include <stdio.h>


#include <QCAR/QCAR.h>
#include <QCAR/CameraDevice.h>
#include <QCAR/Renderer.h>
#include <QCAR/VideoBackgroundConfig.h>

#include "Log.h"


 // ---------------------------------------------------------------------------------------------------------

int screenWidth;
int screenHeight;
bool retratoMode;

// ---------------------------------------------------------------------------------------------------------

void configureVideo()
{
 LOG("configureVideoBackground");
    // Get the default video mode:
        QCAR::CameraDevice& cameraDevice = QCAR::CameraDevice::getInstance();
        QCAR::VideoMode videoMode = cameraDevice.
        getVideoMode(QCAR::CameraDevice::MODE_DEFAULT);


    // Configure the video background
        QCAR::VideoBackgroundConfig config;
        config.mEnabled = true;
        config.mSynchronous = true;
        config.mPosition.data[0] = 0.0f;
        config.mPosition.data[1] = 0.0f;

        if (retratoMode)
        {
        //LOG("configureVideoBackground PORTRAIT");
            config.mSize.data[0] = videoMode.mHeight
            * (screenHeight / (float)videoMode.mWidth);
            config.mSize.data[1] = screenHeight;

            if(config.mSize.data[0] < screenWidth)
            {
                LOG("Correcting rendering background size to handle missmatch between screen and video aspect ratios.");
                config.mSize.data[0] = screenWidth;
                config.mSize.data[1] = screenWidth * (videoMode.mWidth / (float)videoMode.mHeight);
            }
        }
        else
        {
        //LOG("configureVideoBackground LANDSCAPE");
            config.mSize.data[0] = screenWidth;
            config.mSize.data[1] = videoMode.mHeight
            * (screenWidth / (float)videoMode.mWidth);

            if(config.mSize.data[1] < screenHeight)
            {
                LOG("Correcting rendering background size to handle missmatch between screen and video aspect ratios.");
                config.mSize.data[0] = screenHeight
                * (videoMode.mWidth / (float)videoMode.mHeight);
                config.mSize.data[1] = screenHeight;
            }
        }

        LOG("Configure Video Background : Video (%d,%d), Screen (%d,%d), mSize (%d,%d)", videoMode.mWidth, videoMode.mHeight, screenWidth, screenHeight, config.mSize.data[0], config.mSize.data[1]);

    // Set the config:
        QCAR::Renderer::getInstance().setVideoBackgroundConfig(config);
}


JNIEXPORT void JNICALL
Java_com_example_myarvideo_MyARVideo_initNative(JNIEnv *, jobject, jint width, jint height)
{
	screenWidth = width;
	screenHeight = height;
}

JNIEXPORT void JNICALL
Java_com_example_myarvideo_MyARVideo_updateScreenSize(JNIEnv *, jobject, jint width, jint height)
{
	screenWidth = width;
	screenHeight = height;
	configureVideo();
}

JNIEXPORT void JNICALL
Java_com_example_myarvideo_MyARVideo_ehOrientacaoRetrato(JNIEnv *, jobject, jboolean isRetrato)
{
	retratoMode = isRetrato;
	LOG("ATUALIZOU ORIENTAÇÃO");
}

/*
* Função que inicia camera
*/
JNIEXPORT void JNICALL
Java_com_example_myarvideo_MyARVideo_startCamera(JNIEnv *, jobject)
{
	// QCAR::CameraDevice::CAMERA camera = QCAR::CameraDevice::getInstance();
	// if(camera){
	// 	LOG_WARN("CAMERA NAO ENCONTRADA");
	// }
	if(!QCAR::CameraDevice::getInstance().init(QCAR::CameraDevice::CAMERA_DEFAULT)){
		LOG_WARN("CAMERA NAO INICIADA");
		return;
	}
	configureVideo();
	
	// Select the default mode:
    	if (!QCAR::CameraDevice::getInstance().selectVideoMode(QCAR::CameraDevice::MODE_DEFAULT)){
      		return;
  	}

	if(QCAR::CameraDevice::getInstance().start()){
		LOG_WARN("CAMERA NAO COMEÇOU");
		return;
	}
	LOG_DEBUG("CAMERA INICIADA");
}

/*
* Função que para a camera
*/
JNIEXPORT void JNICALL
Java_com_example_myarvideo_MyARVideo_stopCamera(JNIEnv *, jobject)
{
	QCAR::CameraDevice::getInstance().stop();
	QCAR::CameraDevice::getInstance().deinit();
	LOG_DEBUG("CAMERA PARADA");
}

/*
* Função que renderiza os frames
*/
JNIEXPORT void JNICALL
Java_com_example_myarvideo_MyARVideo_renderFrame(JNIEnv *, jobject)
{

}
