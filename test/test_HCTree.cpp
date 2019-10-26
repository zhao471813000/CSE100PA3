/**
 * HCTree test
 *
 * Author: Sander Valstar
 */

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
        freqs['a'] = 1;
        tree.build(freqs);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SimpleHCTreeFixture, getRoot) {
    ASSERT_EQ(tree.getRoot()->symbol, '\0');
    ASSERT_EQ(tree.getRoot()->count, 0);
}

TEST_F(SimpleHCTreeFixture, encode) {
    ostringstream os;
    tree.encode('a', os);
    ASSERT_EQ(os.str(), "0");
}
