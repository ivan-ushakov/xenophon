package com.xenophon.ui;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.CompoundButton;
import android.widget.Switch;
import com.evilduck.piano.views.instrument.PianoView;
import com.xenophon.R;
import com.xenophon.sound.NativeEngine;

/**
 * @author Ivan Ushakov
 * @since 4/12/2014
 */
public class EngineTestActivity extends Activity {

    private static final String TAG = EngineTestActivity.class.getName();

    private Switch engineSwitch;

    private NativeEngine engine;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        PianoView pianoView = (PianoView) findViewById(R.id.instrument_view);
        pianoView.setOnKeyTouchListener(new PianoView.OnKeyTouchListener() {
            @Override
            public void onTouchUp(int midiCode) {
                Log.d(TAG, "note up midi code: " + midiCode);
                engine.midiNoteOff(0, midiCode, 0);
            }

            @Override
            public void onTouchDown(int midiCode) {
                Log.d(TAG, "note down midi code: " + midiCode);
                engine.midiNoteOn(0, midiCode, 0);
            }
        });

        engineSwitch = (Switch) findViewById(R.id.engine_switch);
        engineSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    Log.d(TAG, "playing...");
                    engine.play();
                } else {
                    Log.d(TAG, "stopping...");
                    engine.stop();
                }
            }
        });

        engine = new NativeEngine();
    }

    @Override
    protected void onResume() {
        super.onResume();
        engine.create();
    }

    @Override
    protected void onPause() {
        super.onPause();

        engine.stop();
        engine.release();

        engineSwitch.setChecked(false);
    }
}
