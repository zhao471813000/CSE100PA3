#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "HCTree.hpp"

using namespace std;
using namespace testing;

class SimpleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    SimpleHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 2;
        freqs['b'] = 3;
        freqs['c'] = 4;
        freqs['d'] = 5;
        freqs['e'] = 2;
        tree.build(freqs);
    }
};
TEST_F(SimpleHCTreeFixture, TEST_Serial) {
    tree.serial();
    vector<int> expectedChildState = {0, 1, 1, 0, 1, 0, 0, 1, 0, 0};
    vector<int> returnChildState = tree.getChildState();
    vector<unsigned char> expectedSymbolVec = {'b', 'e', 'a', 'c', 'd'};
    vector<unsigned char> returnSymbolVec = tree.getSymbolVec();

    ASSERT_EQ(expectedChildState, returnChildState);
    ASSERT_EQ(expectedSymbolVec, returnSymbolVec);
}

class ReconstructHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    ReconstructHCTreeFixture() {
        // initialization code here
        vector<int> ChildState = {0, 1, 1, 0, 1, 0, 0, 1, 0, 0};
        vector<unsigned char> symbolVec = {'b', 'e', 'a', 'c', 'd'};
        tree.reconstruct(ChildState, symbolVec);
    }
};
TEST_F(ReconstructHCTreeFixture, TEST_RECONSTRUCT) {
    istringstream is("11");
    ASSERT_EQ(tree.decode(is), 'd');
    istringstream is1("010");
    ASSERT_EQ(tree.decode(is1), 'e');
    istringstream is2("011");
    ASSERT_EQ(tree.decode(is2), 'a');
    istringstream is3("00");
    ASSERT_EQ(tree.decode(is3), 'b');
    istringstream is4("10");
    ASSERT_EQ(tree.decode(is4), 'c');
}

TEST_F(SimpleHCTreeFixture, TEST_ENCODE) {
    ostringstream os1;
    ostringstream os2;
    ostringstream os3;
    ostringstream os4;
    ostringstream os5;
    tree.encode('a', os1);
    ASSERT_EQ(os1.str(), "011");
    tree.encode('b', os2);
    ASSERT_EQ(os2.str(), "00");
    tree.encode('c', os3);
    ASSERT_EQ(os3.str(), "10");
    tree.encode('d', os4);
    ASSERT_EQ(os4.str(), "11");
    tree.encode('e', os5);
    ASSERT_EQ(os5.str(), "010");
}

TEST_F(SimpleHCTreeFixture, TEST_DECODE) {
    istringstream is("11");
    ASSERT_EQ(tree.decode(is), 'd');
    istringstream is1("010");
    ASSERT_EQ(tree.decode(is1), 'e');
    istringstream is2("011");
    ASSERT_EQ(tree.decode(is2), 'a');
    istringstream is3("00");
    ASSERT_EQ(tree.decode(is3), 'b');
    istringstream is4("10");
    ASSERT_EQ(tree.decode(is4), 'c');
}

class ComplexHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree2;

  public:
    ComplexHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 10;
        freqs['b'] = 10;
        freqs['c'] = 10;
        freqs['d'] = 10;
        freqs['e'] = 10;
        tree2.build(freqs);
    }
};

TEST_F(ComplexHCTreeFixture, TEST_ENCODE) {
    ostringstream os1;
    ostringstream os2;
    ostringstream os3;
    ostringstream os4;
    ostringstream os5;
    tree2.encode('a', os1);
    ASSERT_EQ(os1.str(), "10");
    tree2.encode('b', os2);
    ASSERT_EQ(os2.str(), "01");
    tree2.encode('c', os3);
    ASSERT_EQ(os3.str(), "00");
    tree2.encode('d', os4);
    ASSERT_EQ(os4.str(), "111");
    tree2.encode('e', os5);
    ASSERT_EQ(os5.str(), "110");
}

TEST_F(ComplexHCTreeFixture, TEST_DECODE) {
    istringstream is2("111");
    ASSERT_EQ(tree2.decode(is2), 'd');
}
class SpecialHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree3;

  public:
    SpecialHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 10;
        tree3.build(freqs);
    }
};

TEST_F(SpecialHCTreeFixture, TEST_Oneleaf) {
    ostringstream os;
    tree3.encode('a', os);
    ASSERT_EQ(os.str(), "0");
    istringstream is("0");
    ASSERT_EQ(tree3.decode(is), 'a');

    tree3.serial();
    vector<int> expectedChildState = {1};
    vector<int> returnChildState = tree3.getChildState();
    vector<unsigned char> expectedSymbolVec = {'a'};
    vector<unsigned char> returnSymbolVec = tree3.getSymbolVec();

    ASSERT_EQ(expectedChildState, returnChildState);
    ASSERT_EQ(expectedSymbolVec, returnSymbolVec);
}