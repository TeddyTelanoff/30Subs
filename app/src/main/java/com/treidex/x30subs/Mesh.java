package com.treidex.x30subs;

import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.nio.ByteOrder;
import java.nio.IntBuffer;

public class Mesh {
    private FloatBuffer positionBuffer;
    private FloatBuffer colorBuffer;
    private IntBuffer indicesBuffer;

    public Vector[] positions;
    public Vector[] colors;
    public int[] indices;

    public Mesh(final Vector[] positions, final Vector[] colors, final int[] indices) {
        this.positions = positions;
        this.colors = colors;
        this.indices = indices;

        ByteBuffer pbb = ByteBuffer.allocate(positions.length * Vector.BYTES);
        pbb.order(ByteOrder.nativeOrder());

        positionBuffer = pbb.asFloatBuffer();
        for (Vector v : positions)
            positionBuffer.put(v.asArray());

        positionBuffer.rewind();

        ByteBuffer cbb = ByteBuffer.allocate(colors.length * Vector.BYTES);
        cbb.order(ByteOrder.nativeOrder());

        colorBuffer = cbb.asFloatBuffer();
        for (Vector v : colors)
            colorBuffer.put(v.asArray());

        colorBuffer.rewind();

        ByteBuffer ibb = ByteBuffer.allocate(indices.length * Integer.BYTES);
        ibb.order(ByteOrder.nativeOrder());

        indicesBuffer = ibb.asIntBuffer();
        indicesBuffer.put(indices);

        indicesBuffer.rewind();
    }
}