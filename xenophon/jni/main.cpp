#include <memory>
#include <exception>
#include <string>
#include <sstream>
#include <vector>

#include <assert.h>

#include <jni.h>
#include <android/log.h>

#include "log.h"
#include "jni_common.h"
#include "common.h"
#include "engine.h"
#include "wtoscillator.h"

std::unique_ptr<engine_t> engine;

extern "C" void Java_com_xenophon_sound_NativeEngine_create(JNIEnv *env, jobject jobj)
{
    try
    {
        engine.reset(new engine_t());
        engine->create();

        std::unique_ptr<plugin_t> wto(new wt_oscillator_t());
        engine->add_plugin(wto);
    }
    catch (const std::exception &e)
    {
        throw_exception(env, "internal error");
    }
    catch (const sl_exception &e)
    {
        std::string m = make_string() << "OpenSL error: " << e.error();
        throw_exception(env, m.c_str());
    }        
}

extern "C" void Java_com_xenophon_sound_NativeEngine_play(JNIEnv *env, jobject jobj) 
{
    try
    {
        engine->player()->start();
    }
    catch (const std::exception &e)
    {
        throw_exception(env, "internal error");
    }
    catch (const sl_exception &e)
    {
        std::string m = make_string() << "OpenSL error: " << e.error();
        throw_exception(env, m.c_str());
    }    
}

extern "C" void Java_com_xenophon_sound_NativeEngine_stop(JNIEnv *env, jobject jobj) 
{
    try
    {    
        engine->player()->stop();
    }
    catch (const std::exception &e)
    {
        throw_exception(env, "internal error");
    }
    catch (const sl_exception &e)
    {
        std::string m = make_string() << "OpenSL error: " << e.error();
        throw_exception(env, m.c_str());
    }
}

extern "C" void Java_com_xenophon_sound_NativeEngine_release(JNIEnv *env) 
{
    engine.reset(nullptr);
}
