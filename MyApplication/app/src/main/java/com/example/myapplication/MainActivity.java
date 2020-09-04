package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    public int i = 0, j = 0;
    private static final String TAG = "MayActivity";
    TextView textView;
    EditText ei;
    EditText ej;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example 2-01, call to a native method
//        TextView tv = findViewById(R.id.sample_text);
//        tv.setText(stringFromJNI());

        // Example 2-02, pass value to native
//        String input = getLine("input value : ", 100);
//        tv.setText(input);

        // Example 2-03, Call java method from native
        textView = findViewById(R.id.label);
        ei = findViewById(R.id.i);
        ej = findViewById(R.id.j);

        Button button = (Button)findViewById(R.id.sum);
        button.setOnClickListener(saveListener);
    }

    private View.OnClickListener saveListener = new View.OnClickListener() {
        public void onClick(View v) {
            try {
                i = Integer.parseInt(ei.getText().toString());
            } catch (NumberFormatException e) {
                i = 0;
            }

            try {
                j = Integer.parseInt(ej.getText().toString());
            } catch (NumberFormatException e) {
                j = 0;
            }

            JNICallBackMethod m = new JNICallBackMethod(i, j);
            String s = "return method " + m.PrinttoString();

            Log.v(TAG, s);
            textView.setText(s);
        }
    };

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    private native String getLine(String prompt, int value);

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

}
