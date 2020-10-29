package com.treidex.x30subs;

public class FileUtil {
    public static native String readFile(String path);
    public static native void writeFile(String path, byte[] data);
    public static void writeFile(String path, String text) {
        writeFile(path, text.getBytes());
    }
}
