#include <jni.h>

#include <GLES3/gl3.h>

extern "C" JNIEXPORT void JNICALL Java_com_treidex_x30subs_Mesh_create(
        JNIEnv* env, jobject $this)
{
//    glGenVertexArrays(1, vao, 0);
//    glBindVertexArray(vao[0]);
//
//    glGenBuffers(1, pbo, 0);
//    glBindBuffer(GL_ARRAY_BUFFER, pbo[0]);
//    glBufferData(GL_ARRAY_BUFFER, positions.length * Vector.BYTES, positionBuffer, GL_STATIC_DRAW);
//
//    glGenBuffers(1, cbo, 0);
//    glBindBuffer(GL_ARRAY_BUFFER, cbo[0]);
//    glBufferData(GL_ARRAY_BUFFER, colors.length * Vector.BYTES, colorBuffer, GL_STATIC_DRAW);
//
//    glGenBuffers(1, ibo, 0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[0]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.length * Integer.BYTES, indicesBuffer, GL_STATIC_DRAW);

    jclass thisClass = env->GetObjectClass($this);

    env->CallVoidMethod($this, env->GetMethodID(thisClass, "setup", "()V"));

    unsigned int vao, pbo, cbo, ibo;
    jobject pbb = env->GetObjectField($this, env->GetFieldID(thisClass, "positionBuffer", "Ljava/nio/FloatBuffer;"));
    jobject cbb = env->GetObjectField($this, env->GetFieldID(thisClass, "colorBuffer", "Ljava/nio/FloatBuffer;"));
    jobject ibb = env->GetObjectField($this, env->GetFieldID(thisClass, "indicesBuffer", "Ljava/nio/IntBuffer;"));

    jfloatArray pba = reinterpret_cast<jfloatArray>(env->CallObjectMethod(pbb, env->GetMethodID(env->GetObjectClass(pbb), "array", "()[F"))));
    jfloatArray cba = reinterpret_cast<jfloatArray>(env->CallObjectMethod(cbb, env->GetMethodID(env->GetObjectClass(cbb), "array", "()[F"))));
    jintArray iba = reinterpret_cast<jintArray>(env->CallObjectMethod(ibb, env->GetMethodID(env->GetObjectClass(ibb), "array", "()[I"))));

    jboolean isCopy;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &pbo);
    glBindBuffer(GL_ARRAY_BUFFER, pbo);
    glBufferData(GL_ARRAY_BUFFER, env->GetArrayLength(pba) * sizeof(float), env->GetFloatArrayElements(pba, &isCopy), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, env->GetArrayLength(cba) * sizeof(float), env->GetFloatArrayElements(cba, &isCopy), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, env->GetArrayLength(iba) * sizeof(unsigned int), env->GetIntArrayElements(iba, &isCopy), GL_STATIC_DRAW);

    env->SetIntField($this, env->GetFieldID(thisClass, "vao", "I"), (int)vao);
    env->SetIntField($this, env->GetFieldID(thisClass, "pbo", "I"), (int)pbo);
    env->SetIntField($this, env->GetFieldID(thisClass, "cbo", "I"), (int)cbo);
    env->SetIntField($this, env->GetFieldID(thisClass, "ibo", "I"), (int)ibo);
}

extern "C" JNIEXPORT void JNICALL Java_com_treidex_x30subs_Mesh_bind(
        JNIEnv* env, jobject $this)
{
//    glBindVertexArray(vao);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    jclass thisClass = env->GetObjectClass($this);

    unsigned int vao = env->GetIntField($this, env->GetFieldID(thisClass, "vao", "I"));
    unsigned int ibo = env->GetIntField($this, env->GetFieldID(thisClass, "ibo", "I"));

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}