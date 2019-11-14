/**
 * This file realizes a bitwise output stream, i.e., allows for writing data
 * bit by bit by implementing a buffer. The general idea is first use a buffer
 * to store the current byte being written from an ostream, then perform the
 * proper bitwise operations to write each bit in the buffer.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#include "BitOutputStream.hpp"

/* Sends the buffer to the output stream, and then clear the buffer to allow
 * further use. */
void BitOutputStream::flush() {
    out.put(buf);
    // out.flush();
    buf = 0;
    nbits = 0;
}

/* Writes the least signficant bit of the given int to the bit buffer. Flush the
 * buffer if it is full*/
void BitOutputStream::writeBit(int i) {
    i &= 1;
    if (i == 1)
        buf |= 1 << (7 - nbits);
    else
        buf &= ~(1 << (7 - nbits));
    nbits++;
    if (nbits == 8) flush();
}
