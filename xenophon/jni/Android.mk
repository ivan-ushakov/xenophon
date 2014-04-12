LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)
 
LOCAL_MODULE    	:= native_engine
LOCAL_SRC_FILES 	:= wtoscillator.cpp jni_common.cpp object.cpp player.cpp engine.cpp main.cpp
LOCAL_CPPFLAGS 		:= -fexceptions -std=c++11
LOCAL_LDLIBS		:= -llog -landroid -lOpenSLES

include $(BUILD_SHARED_LIBRARY)
