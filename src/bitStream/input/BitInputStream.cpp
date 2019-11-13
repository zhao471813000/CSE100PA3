/**
 * This file realizes a bitwise input stream, i.e., allows for reading data
 * bit by bit by implementing a buffer. The general idea is first use a buffer
 * to store the current byte being read from an istream, then perform the proper
 * bitwise operations to read each bit in the buffer.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#include "BitInputStream.hpp"

/* Fills the one byte buffer from input stream. */
void BitInputStream::fill() {
    buf = in.get();
    nbits = 8;  // with 8 bits written to the buff, the buff is now full
}

/* Reads the next bit from the bit buffer. Fills the buffer with next byte
 * from input stream if all the bits have already been read. It should
 * return 0 if bit read is 0, and return 1 if bit read is 1. */
unsigned int BitInputStream::readBit() {
    if (nbits == 0) {
        fill();
    }
    nbits--;
    return (buf >> nbits) & 1;
}