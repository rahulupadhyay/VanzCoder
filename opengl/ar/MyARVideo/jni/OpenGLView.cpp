

int screenWidth = 0;
int screenHeight = 0;


void configureScreen()
{
	//TODO - Fazer os calculos necessario para ajute da tela e do video
}

/**
	Atualiza configuração de tela
*/
JNIEXPORT void JNICALL
Java_com_example_opengl_OpenGLView_updateScreenConfig(JNIEnv *, jobject, jint width, jint height)
{
	screenWidth = width;
	screenHeight = height;

	configureScreen();
}