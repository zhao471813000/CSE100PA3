#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "HCTree.hpp"

using namespace std;
using namespace testing;

class SimpleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree* tree;

  public:
    SimpleHCTreeFixture() {
        // initialization code here
        tree = new HCTree();
        vector<unsigned int> freqs(256);
        freqs['a'] = 2;
        freqs['b'] = 3;
        freqs['c'] = 4;
        freqs['d'] = 5;
        freqs['e'] = 2;
        tree->build(freqs);
    }
};

TEST_F(SimpleHCTreeFixture, TEST_ENCODE) {
    ostringstream os1;
    ostringstream os2;
    ostringstream os3;
    ostringstream os4;
    ostringstream os5;
    tree->encode('a', os1);
    ASSERT_EQ(os1.str(), "011");
    tree->encode('b', os2);
    ASSERT_EQ(os2.str(), "00");
    tree->encode('c', os3);
    ASSERT_EQ(os3.str(), "10");
    tree->encode('d', os4);
    ASSERT_EQ(os4.str(), "11");
    tree->encode('e', os5);
    ASSERT_EQ(os5.str(), "010");
}

TEST_F(SimpleHCTreeFixture, TEST_DECODE) {
    istringstream is("11");
    ASSERT_EQ(tree->decode(is), 'd');
    delete tree;
}

// class OneHCTreeFixture : public ::testing::Test {
//   protected:
//     HCTree* tree;

//   public:
//     OneHCTreeFixture() {
//         // initialization code here
//         vector<unsigned int> freqs(256);
//         freqs['f'] = 2;
//         tree->build(freqs);
//     }
// };

// TEST_F(OneHCTreeFixture, TEST_ENCODE) {
//     ostringstream os;
//     tree->encode('f', os);
//     ASSERT_EQ(os.str(), "0");
// }