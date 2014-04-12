package com.xenophon.ui;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import com.xenophon.R;
import com.xenophon.sound.NativeEngine;

/**
 * @author Ivan Ushakov
 * @since 4/12/2014
 */
public class EngineTestActivity extends Activity {

    private static final String TAG = EngineTestActivity.class.getName();

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        new Thread(new Runnable() {
            @Override
            public void run() {
                NativeEngine engine = new NativeEngine();
                try {
                    Thread.sleep(3 * 1000);
                    engine.create();
                    Log.i(TAG, "starting...");
                    engine.play();

                    Thread.sleep(3 * 1000);
                    engine.stop();
                    Log.i(TAG, "stopped");
                } catch (Exception e) {
                    Log.e(TAG, "error", e);
                } finally {
                    engine.release();
                }
            }
        }).start();
    }
}
