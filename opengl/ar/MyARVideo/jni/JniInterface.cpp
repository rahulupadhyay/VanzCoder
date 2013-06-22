/*
* JNI INTERFACE
* Here, there are all binds between java and native sources
* José Guilherme Vanz <guilherme.sft@gmail.com>
*/
#include <jni.h>
#include "NativeApp.h"

NativeApp * native = new NativeApp(); //Pointer to Native application

JNIEXPORT void JNICALL
Java_com_example_myarvideo_MyARVideo_initNative(JNIEnv *, jobject, jint width, jint height)
{

}

JNIEXPORT void JNICALL
Java_com_example_myarvideo_MyARVideo_updateScreenSize(JNIEnv *, jobject, jint width, jint height)
{
	native->updateScreenSize(width,height);
}
