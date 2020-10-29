#pragma once

#include <jni.h>

#include <sstream>

extern "C" JNIEXPORT jboolean JNICALL Java_com_treidex_x30subs_MainActivity_onTouchEvent(
        JNIEnv* env, jobject $this, jobject e)
{
    jclass eClass = env->GetObjectClass(e);
    float mouseX = env->CallFloatMethod(e, env->GetMethodID(eClass, "getX", "()F"));
    float mouseY = env->CallFloatMethod(e, env->GetMethodID(eClass, "getY", "()F"));

    std::stringstream ss;
    ss << "Tapped at (" << mouseX << ", " << mouseY << ")";

    jclass thisClass = env->GetObjectClass($this);
    env->CallVoidMethod($this, env->GetMethodID(thisClass, "setText", "(Ljava/lang/String;)V"), env->NewStringUTF(ss.str().c_str()));

    return false;

    jclass superMegaClass = env->GetSuperclass(env->GetSuperclass(env->GetSuperclass(env->GetSuperclass(env->GetSuperclass(thisClass)))));
    return env->CallBooleanMethod($this, env->GetMethodID(superMegaClass, "onTouchEvent", "(Landroid/view/MotionEvent;)Z"), e);
}