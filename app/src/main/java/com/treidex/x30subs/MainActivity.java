package com.treidex.x30subs;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.MotionEvent;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("native-lib");
    }

    private MySurfaceView glView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        glView = new MySurfaceView(this);
        setContentView(glView);
    }

    @Override
    public native boolean onTouchEvent(MotionEvent e);

    private void setText(String text) {
        TextView textView = findViewById(R.id.sample_text);
        textView.setText(text);
    }
}
