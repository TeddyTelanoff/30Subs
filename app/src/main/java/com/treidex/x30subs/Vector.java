package com.treidex.x30subs;

public class Vector {
    public static final int SIZE = 4;
    public static final int BYTES = Float.BYTES * SIZE;

    public float x, y, z, w;

    public Vector() {}

    public Vector(final float x, final float y) {
        this.x = x;
        this.y = y;
    }

    public Vector(final float x, final float y, final float z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public Vector(final float x, final float y, final float z, final float w) {
        this.x = x;
        this.y = y;
        this.z = z;
        this.w = w;
    }

    public Vector(final float[] values) {
        if (values.length > 0) {
            this.x = values[0];
            if (values.length > 1) {
                this.y = values[1];
                if (values.length > 2) {
                    this.z = values[2];
                    if (values.length > 3)
                        this.w = values[3];
                }
            } else {
                this.y = values[0];
                this.z = values[0];
                this.w = values[0];
            }
        }
    }

    public final float[] asArray() {
        return new float[] { x, y, z, w };
    }
}
