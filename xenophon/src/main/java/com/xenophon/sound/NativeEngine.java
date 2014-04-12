package com.xenophon.sound;

/**
 * @author Ivan Ushakov
 * @since 4/12/2014
 */
public class NativeEngine {

    static {
        System.loadLibrary("native_engine");
    }

    public native void create();

    public native void play();

    public native void stop();

    public native void release();

}
