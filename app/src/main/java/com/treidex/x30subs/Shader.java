package com.treidex.x30subs;

import static android.opengl.GLES20.*;

public class Shader {
    private int mProgram, mVertex, mFragment;
    public final String vertexFile, fragmentFile;

    public Shader(String vertexPath, String fragmentPath) {
        vertexFile = FileUtil.readFile(vertexPath);
        fragmentFile = FileUtil.readFile(vertexPath);

        mVertex
    }

    public static native int loadShader(int type, String shaderCode);
}
