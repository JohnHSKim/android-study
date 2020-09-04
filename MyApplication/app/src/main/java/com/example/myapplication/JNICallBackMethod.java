package com.example.myapplication;

public class JNICallBackMethod {
    private int x, y, sum;
    static {
        System.loadLibrary("native-lib");
    }

    public native String PrinttoString();

    public JNICallBackMethod() {
        this.x = 0;
        this.y = 0;
        this.sum = 0;
    }

    public JNICallBackMethod(int x, int y) {
        this.x = x;
        this.y = y;
        this.sum = x + y;
    }

    @Override
    public String toString() {
        String str = "JNICallBackMethod[" + x + " + " + y + " = " + sum + "]";
        return str;
    }
}
