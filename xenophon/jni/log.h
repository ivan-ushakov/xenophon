#ifndef _BEATPAD_LOG

#include <android/log.h> 

#define LOG_TAG "OPEN_SL_TEST"

#define LOGI(format, args...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, format, ##args);
#define LOGE(format, args...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, format, ##args);

#endif
