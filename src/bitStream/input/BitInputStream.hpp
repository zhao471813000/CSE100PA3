/**
 * This file realizes a bitwise input stream, i.e., allows for reading data
 * bit by bit by implementing a buffer. The general idea is first use a buffer
 * to store the current byte being read from an istream, then perform the proper
 * bitwise operations to read each bit in the buffer.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** This class implements a bitwise input stream, i.e., allows for reading data
 * bit by bit by implementing a buffer. */
class BitInputStream {
  private:
    char buf;     // one byte buffer of bits
    int nbits;    // number of bits have been writen to buf
    istream& in;  // reference to the input stream to use

  public:
    /* Constructor of BitInputStream. Initializes member variable. */
    explicit BitInputStream(istream& is) : in(is), nbits(0), buf(0){};

    /* Fills the one byte buffer from input stream. */
    void fill();

    /* Reads the next bit from the bit buffer. Fills the buffer with next byte
     * from input stream if all the bits have already been read. It should
     * return 0 if bit read is 0, and return 1 if bit read is 1. */
    unsigned int readBit();
};

#endif