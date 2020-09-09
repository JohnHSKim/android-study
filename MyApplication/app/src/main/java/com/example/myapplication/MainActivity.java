package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("native-lib");
    }

    public native void nativeProcessBitmap(Bitmap bitmap);

    private ImageView mImg1, mImg2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mImg1 = (ImageView) findViewById(R.id.img_test1);
        mImg2 = (ImageView) findViewById(R.id.img_test2);
    }

    public void onLoadClick(View view) {
        Bitmap originalBitmap = loadBitmap();
        mImg1.setImageBitmap(originalBitmap);

        Bitmap resultBitmap = processBitmap(originalBitmap);
        mImg2.setImageBitmap(resultBitmap);
    }

    private Bitmap loadBitmap() {
        Bitmap bmp = null;
        AssetManager am = getResources().getAssets();
        try {
            InputStream is = am.open("cat.png");
            bmp = BitmapFactory.decodeStream(is);
            is.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return bmp;
    }

    private Bitmap processBitmap(Bitmap bitmap) {
        Bitmap bmp = bitmap.copy(Bitmap.Config.ARGB_8888, true);
        nativeProcessBitmap(bmp);
        return bmp;
    }


}
