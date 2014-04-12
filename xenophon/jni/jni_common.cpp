#include "jni_common.h"

#include "log.h"

void throw_exception_common(JNIEnv *env, const char *class_name, const char *message)
{
    jclass clazz = env->FindClass(class_name);
    if (clazz == 0)
    {
        LOGE("fail to find class for exception");
        return;
    }

    env->ThrowNew(clazz, message); 
}

void throw_io_exception(JNIEnv *env, const char *message)
{
    throw_exception_common(env, "java/io/IOException", message);
}

void throw_exception(JNIEnv *env, const char *message)
{
    throw_exception_common(env, "java/lang/Exception", message);
}

jmethodID get_progress_method(JNIEnv *env)
{
    jclass clazz = env->FindClass("com/xme/beatpad/encoder/MuxerAdapter");
    if (clazz == 0)
    {        
        return 0;
    }

    return env->GetMethodID(clazz, "setProgress", "(I)V");    
}
