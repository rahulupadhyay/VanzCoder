/*
* José Guilherme Vanz <guilherme.sft@gmail.com>
*/

#include <stdio.h>

#include "Renderer.h"
#include "Log.h"

class NativeApp
{

private:
	int screenWidth;
	int screenHeight;
	Renderer * renderer;

public:
	NativeApp(); //Constructor
	~NativeApp();
	void initApp(int width, int height); //init all native stuff
	void startCamera(); //start camera
	void stopCamera(); //stop camera
	void updateScreenSize(int width, int height); //update screen sizes
	Renderer* getRenderer();
};