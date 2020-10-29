#pragma once

#include <jni.h>

#include "JNIUtil.hpp"

extern "C" JNIEXPORT jstring JNICALL Java_com_treidex_x30subs_FileUtil_readFile(
        JNIEnv* env, jclass $class, jstring path)
{
    return env->NewStringUTF(ReadFile(jstring2string(env, path)).c_str());
}

extern "C" JNIEXPORT void JNICALL Java_com_treidex_x30subs_FileUtil_writeFile(
        JNIEnv* env, jclass $class, jstring path, jbyteArray array)
{
    WriteFile(jstring2string(env, path), jbytearraytochararray(env, array));
}