#include <jni.h>

#include <GLES3/gl3.h>

extern "C" JNIEXPORT void JNICALL Java_com_treidex_x30subs_MyRenderer_renderMesh(
        JNIEnv* env, jobject $this, jobject mesh, jobject shader)
{
    jclass meshClass = env->GetObjectClass(mesh);
    jclass shaderClass = env->GetObjectClass(shader);

    env->CallVoidMethod(mesh, env->GetMethodID(meshClass, "bind", "()V"));
    env->CallVoidMethod(shader, env->GetMethodID(shaderClass, "bind", "()V"));

    glDrawElements(GL_TRIANGLES, env->GetArrayLength(reinterpret_cast<jarray>(env->GetObjectField(mesh, env->GetFieldID(meshClass, "positions", "[Lcom/treidex/x30subs/Vector;")))), GL_UNSIGNED_INT, 0);
}