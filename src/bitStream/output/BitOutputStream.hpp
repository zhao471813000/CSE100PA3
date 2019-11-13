/**
 * This file realizes a bitwise output stream, i.e., allows for writing data
 * bit by bit by implementing a buffer. The general idea is first use a buffer
 * to store the current byte being written from an ostream, then perform the
 * proper bitwise operations to write each bit in the buffer.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** This class implements a bitwise output stream, i.e., allows for writing data
 * bit by bit by implementing a buffer. */
class BitOutputStream {
  private:
    char buf;      // one byte buffer of bits
    int nbits;     // number of bits have been writen to buf
    ostream& out;  // reference to the output stream to use

  public:
    /* Constructor of BitOutputStream. Initializes member variable to be the
     * proper values. */
    explicit BitOutputStream(ostream& os) : out(os), nbits(0), buf(0){};

    /* Sends the buffer to the output stream, and then clear the buffer to allow
     * further use. */
    void flush();

    /* Writes the least signficant bit of the given int to the bit buffer. Flush
     * the buffer if it is full*/
    void writeBit(int i);
};

#endif
