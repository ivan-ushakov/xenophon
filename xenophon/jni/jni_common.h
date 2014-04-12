#ifndef _BEATPAD_JNI_COMMON
#define _BEATPAD_JNI_COMMON

#include <jni.h>

void throw_exception_common(JNIEnv *env, const char *class_name, const char *message);

void throw_io_exception(JNIEnv *env, const char *message);

void throw_exception(JNIEnv *env, const char *message);

jmethodID get_progress_method(JNIEnv *env);

#endif
