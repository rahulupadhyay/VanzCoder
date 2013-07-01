/*
* José Guilherme Vanz <guilherme.sft@gmail.com>
* Classe Log eh responsavel por toda a parte de Logging da aplicação nativa
*/

#include <android/log.h>

#define LOG_TAG		"MYARVIDEO_NATIVE"
#define LOG(...)	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_DEBUG(...)	__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOG_WARN(...)	__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...)	__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
