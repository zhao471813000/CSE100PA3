/**
 * HCTree test
 *
 * Author: Sander Valstar
 */

#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "BitOutputStream.hpp"

using namespace std;
using namespace testing;

unsigned char reverse(unsigned char b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

TEST(BitOutputStreamTests, SIMPLE_TEST) {
    stringstream ss;
    BitOutputStream bos(ss);
    cout << "writing... " << endl;
    bos.writeBit(1);
    bos.flush();
    unsigned char nextByte = ss.get();
    ASSERT_EQ(reverse(nextByte), 1);
}
