#include <jni.h>

#include <cstdio>
#include <sstream>

std::string ReadFile(const std::string& filepath)
{
    FILE* fs = fopen(filepath.c_str(), "rb");

    fseek(fs, 0, SEEK_END);
    const int size = ftell(fs);
    const int allocSize = size + 1;
    char* buff = (char*)alloca(allocSize);
    rewind(fs);

    if (buff == nullptr)
    {
        fclose(fs);
        return "";
    }

    fread(buff, sizeof(char), size, fs);
    fclose(fs);
    buff[size] = 0;

    return buff;
}
void WriteFile(const std::string& filepath, const char* const text)
{
    FILE* fs = fopen(filepath.c_str(), "w+");

    fputs(text, fs);
    fflush(fs);

    fclose(fs);
}

std::string jstring2string(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

char* jbytearraytochararray(JNIEnv *env, jbyteArray array) {
    int len = env->GetArrayLength (array);
    char* buf = new char[len];
    env->GetByteArrayRegion (array, 0, len, reinterpret_cast<jbyte*>(buf));
    return buf;
}

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

extern "C" JNIEXPORT jint JNICALL Java_com_treidex_x30subs_Shader_loadShader(
        JNIEnv* env, jclass $class, jstring path, jbyteArray array)
{
    WriteFile(jstring2string(env, path), jbytearraytochararray(env, array));
}