#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "HCNode.hpp"

using namespace std;
using namespace testing;
class SimpleHCNodeFixture : public ::testing::Test {
  protected:
    HCNode* node1;
    HCNode* node2;
    HCNode* node3;

  public:
    SimpleHCNodeFixture() {
        // initialization code here
        node1 = new HCNode(10, 'a');
        node2 = new HCNode(10, 'b');
        node3 = new HCNode(20, 'c');
    }
};

TEST_F(SimpleHCNodeFixture, TEST_COMPARTOR) {
    HCNodePtrComp comp;
    ASSERT_EQ(comp(node1, node2), true);
    ASSERT_EQ(comp(node3, node1), true);
}

TEST_F(SimpleHCNodeFixture, TEST_OPERATOR) {
    ostringstream os;
    os << (*node1);
    ASSERT_EQ(os.str(), "[10,97]");
}