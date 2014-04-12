#ifndef _BEATPAD_COMMON
#define _BEATPAD_COMMON

#include <exception>
#include <sstream>

#include <jni.h>

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include "log.h"

class sl_exception
{
    SLresult _error;

public:
    sl_exception(SLresult error) : _error(error) {};

    const SLresult &error() const
    {
        return _error;
    }
};

class array_t
{
    JNIEnv *_env;
    jintArray _original;
    int *_array;

public:
    array_t(JNIEnv *env, jintArray original) : _env(env), _original(original)
    {
        _array = _env->GetIntArrayElements(_original, JNI_FALSE);
        if (_array == NULL)
        {
            LOGE("fail get offsets array");
            throw std::exception();
        }
    };

    ~array_t()
    {
        _env->ReleaseIntArrayElements(_original, _array, JNI_ABORT);
    }

    int *data()
    {
        return _array;
    }
};

class make_string
{
public:
    template<class T>
    make_string& operator<< (const T& arg)
    {
        m_stream << arg;
        return *this;
    }

    operator std::string() const
    {
        return m_stream.str();
    }
protected:
    std::stringstream m_stream;
};

#endif
