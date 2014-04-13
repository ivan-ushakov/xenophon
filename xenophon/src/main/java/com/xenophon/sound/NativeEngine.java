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

    public native void midiNoteOn(int channel, int midiNote, int velocity);

    public native void midiNoteOff(int channel, int midiNote, int velocity);

    public native void release();

}
