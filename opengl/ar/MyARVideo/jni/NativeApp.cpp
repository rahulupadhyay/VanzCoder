/*
* José Guilherme Vanz <guilherme.sft@gmail.com>
*/

#include "NativeApp.h"
#include "Log.h"

NativeApp::NativeApp()
{
	screenWidth = 0;
	screenHeight = 0;
	renderer = new Renderer();
}

void NativeApp::initApp(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	LOG("Native application inicialized");
}

void NativeApp::startCamera()
{
	//TODO
	LOG("Camera stated");
}

void NativeApp::stopCamera()
{
	//TODO
	LOG("Camera stoped");
}

void NativeApp::updateScreenSize(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	renderer->configureVideo();	
}

Renderer* NativeApp::getRenderer()
{
	return renderer;
}

NativeApp::~NativeApp()
{
	delete renderer;
}