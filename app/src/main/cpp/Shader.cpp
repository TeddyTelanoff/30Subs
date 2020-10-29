#pragma once

#include <jni.h>

#include <GLES2/gl2.h>

#include "JNIUtil.hpp"

extern "C" JNIEXPORT int JNICALL Java_com_treidex_x30subs_Shader_loadShader(
        JNIEnv* env, jclass $class, jint type, jstring sourceStr)
{
//    int id = glCreateShader(type);
//    glShaderSource(id, source);
//    glCompileShader(id);
//
//    int[] status = new int[1];
//    glGetShaderiv(id, GL_COMPILE_STATUS, status, 0);
//    if (status[0] == GL_FALSE) {
//        String msg = glGetShaderInfoLog(id);
//        System.err.println("Error Compiling Shader: " + msg);
//    }
//
//    return id;

    unsigned int id = glCreateShader(type);
    const char* source = jstring2string(env, sourceStr).c_str();
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* msg = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, msg);

        printf("Error Compiling Shader: %s", msg);
    }

    return id;
}

extern "C" JNIEXPORT void JNICALL Java_com_treidex_x30subs_Shader_create(
        JNIEnv* env, jobject $this, jstring vPath, jstring fPath)
{
//    mVertexSource = FileUtil.readFile(vertexPath);
//    mFragmentSource = FileUtil.readFile(vertexPath);
//
//    mVertex = loadShader(GL_VERTEX_SHADER, mVertexSource);
//    mFragment = loadShader(GL_FRAGMENT_SHADER, mFragmentSource);
//
//    mProgram = glCreateProgram();
//    glAttachShader(mProgram, mVertex);
//    glAttachShader(mProgram, mFragment);
//
//    glLinkProgram(mProgram);
//    glValidateProgram(mProgram);
//
//    glDeleteShader(mVertex);
//    glDeleteShader(mFragment);

    jclass thisClass = env->GetObjectClass($this);

    //region Setting the Sources
    jfieldID mVertexSource = env->GetFieldID(thisClass, "mVertexSource", "Ljava/lang/String;");
    jfieldID mFragmentSource = env->GetFieldID(thisClass, "mFragmentSource", "Ljava/lang/String;");

    jclass fileUtilClass = env->FindClass("com/treidex/x30subs/FileUtil");
    jmethodID readFileMethod = env->GetStaticMethodID(fileUtilClass, "readFile", "(Ljava/lang/String;)Ljava/lang/String;");

    env->SetObjectField($this, mVertexSource, env->CallStaticObjectMethod(fileUtilClass, readFileMethod, vPath));
    env->SetObjectField($this, mFragmentSource, env->CallStaticObjectMethod(fileUtilClass, readFileMethod, fPath));
    //endregion

    //region Setting the Shaders
    int mVertexVal, mFragmentVal;

    jmethodID loadShaderMethod = env->GetStaticMethodID(thisClass, "loadShader", "(ILjava/lang/String;)I");
    env->SetIntField($this, env->GetFieldID(thisClass, "mVertex", "I"),
            mVertexVal = env->CallStaticIntMethod(thisClass, loadShaderMethod, GL_VERTEX_SHADER, env->GetObjectField($this, mVertexSource)));
    env->SetIntField($this, env->GetFieldID(thisClass, "mFragment", "I"),
            mFragmentVal = env->CallStaticIntMethod(thisClass, loadShaderMethod, GL_FRAGMENT_SHADER, env->GetObjectField($this, mFragmentSource)));
    //endregion

    //region Setting the Program
    int program = glCreateProgram();
    glAttachShader(program, mVertexVal);
    glAttachShader(program, mFragmentVal);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(mVertexVal);
    glDeleteShader(mFragmentVal);

    env->SetIntField($this, env->GetFieldID(thisClass, "mProgram", "I"),
            program);
    //endregion
}

extern "C" JNIEXPORT void JNICALL Java_com_treidex_x30subs_Shader_destroy(
        JNIEnv* env, jobject $this)
{
//    glDetachShader(mProgram, mVertex);
//    glDetachShader(mProgram, mFragment);
//    glDeleteProgram(mProgram);

    jclass thisClass = env->GetObjectClass($this);

    int mProgramVal = env->GetIntField($this, env->GetFieldID(thisClass, "mProgram", "I"));

    glDetachShader(mProgramVal, env->GetIntField($this, env->GetFieldID(thisClass, "mVertex", "I")));
    glDetachShader(mProgramVal, env->GetIntField($this, env->GetFieldID(thisClass, "mFragment", "I")));
    glDeleteProgram(mProgramVal);
}

extern "C" JNIEXPORT void JNICALL Java_com_treidex_x30subs_Shader_bind(
        JNIEnv* env, jobject $this)
{
//    glUseProgram(mProgram);

    glUseProgram(env->GetIntField($this, env->GetFieldID(env->GetObjectClass($this), "mProgram", "I")));
}

extern "C" JNIEXPORT int JNICALL Java_com_treidex_x30subs_Shader_getUniformLocation(
        JNIEnv* env, jobject $this, jstring name)
{
//    if (mUniformCache.containsKey(name))
//        return mUniformCache.get(name);
//
//    int loc = glGetUniformLocation(mProgram, name);
//    mUniformCache.put(name, loc);
//    return loc;

    jclass thisClass = env->GetObjectClass($this);

    jobject mUniformCache = env->GetObjectField($this, env->GetFieldID(thisClass, "mUniformCache", "Ljava/util/HashMap;"));
    jclass mUniformCacheClass = env->GetObjectClass(mUniformCache);

    if (env->CallBooleanMethod(mUniformCache, env->GetMethodID(mUniformCacheClass, "containsKey", "(Ljava/lang/Object;)Z"), name))
        return (int)env->CallObjectMethod(mUniformCache, env->GetMethodID(mUniformCacheClass, "get", "(Ljava/lang/Object;)Ljava/lang/Object;"), name);

    int loc = glGetUniformLocation(env->GetIntField($this, env->GetFieldID(thisClass, "mProgram", "I")), jstring2string(env, name).c_str());
    env->CallObjectMethod(mUniformCache, env->GetMethodID(mUniformCacheClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;"), name, (jobject)loc);
}