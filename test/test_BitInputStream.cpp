#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "BitInputStream.hpp"

using namespace std;
using namespace testing;

TEST(BitInputStreamTests, SIMPLE_TEST) {
    string bitsStr = "10000011";  // 10-bit

    string ascii = string(1, stoi(bitsStr, nullptr, 2));

    stringstream ss;
    ss.str(ascii);
    BitInputStream bis(ss);

    ASSERT_EQ(1, bis.readBit());
    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(0, bis.readBit());
    }
    // after 8 bits, buffer is filled again
    ASSERT_EQ(1, bis.readBit());
    ASSERT_EQ(1, bis.readBit());
}