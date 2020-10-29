package com.treidex.x30subs;

import java.util.HashMap;

import static android.opengl.GLES20.*;

public class Shader {
    private int mProgram, mVertex, mFragment;
    private String mVertexSource, mFragmentSource;
    private HashMap<String, Integer> mUniformCache = new HashMap<>();

    public Shader(String vertexPath, String fragmentPath) {
        create(vertexPath, fragmentPath);
    }

    public native void create(String vertexPath, String fragmentPath);
    public native void destroy();

    public native void bind();

    public native int getUniformLocation(String name);

    public static native int loadShader(int type, String source);

    public String getmVertexSource() {
        return mVertexSource;
    }

    public String getFragmentSource() {
        return mFragmentSource;
    }

    public int getProgram() {
        return mProgram;
    }
}
