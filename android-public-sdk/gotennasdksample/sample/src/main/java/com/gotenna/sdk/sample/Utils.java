package com.gotenna.sdk.sample;

import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.CodingErrorAction;

/**
 * A generic utilities class.
 * <p>
 * Created on: 7/19/17.
 *
 * @author Thomas Colligan
 */

public class Utils
{
    public static String truncateUtf8String(String inputString, int maxBytes)
    {
        if (inputString == null)
        {
            return null;
        }

        Charset charset = Charset.forName("UTF-8");
        CharsetDecoder decoder = charset.newDecoder();

        byte[] inputStringBytes = inputString.getBytes(charset);

        if (inputStringBytes.length <= maxBytes)
        {
            return inputString;
        }

        // Ensure truncation by having byte buffer = maxBytes
        ByteBuffer byteBuffer = ByteBuffer.wrap(inputStringBytes, 0, maxBytes);
        CharBuffer charBuffer = CharBuffer.allocate(maxBytes);

        // Ignore an incomplete character
        decoder.onMalformedInput(CodingErrorAction.IGNORE);
        decoder.decode(byteBuffer, charBuffer, true);
        decoder.flush(charBuffer);

        return new String(charBuffer.array(), 0, charBuffer.position());
    }
}
