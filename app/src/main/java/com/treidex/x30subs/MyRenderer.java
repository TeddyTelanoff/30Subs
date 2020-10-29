package com.treidex.x30subs;

import static android.opengl.GLES20.*;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyRenderer implements GLSurfaceView.Renderer {
    private Mesh mMesh;

    public void onSurfaceCreated(GL10 unused, EGLConfig config) {
        glClearColor(0.14f, 0.14f, 0.14f, 1.0f);

        mMesh = new Mesh(new Vector[] {
                new Vector( 0.0f,  0.5f),
                new Vector(-0.5f, -0.5f),
                new Vector( 0.5f, -0.5f)
        }, new Vector[] {
                new Vector(1.0f, 0.0f, 0.0f, 1.0f),
                new Vector(0.0f, 1.0f, 0.0f, 1.0f),
                new Vector(0.0f, 0.0f, 1.0f, 1.0f)
        }, new int[] {
                0, 1, 2
        });
    }

    public void onDrawFrame(GL10 unused) {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    public void onSurfaceChanged(GL10 unused, int width, int height) {
        glViewport(0, 0, width, height);
    }

    public void renderMesh(Mesh mesh, Shader shader) {

    }
}
