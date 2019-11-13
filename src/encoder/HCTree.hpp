/**
 * Implements Huffman Coding tree as the compression algorithm.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"

using namespace std;

typedef priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> my_queue;

/** Implements Huffman Coding tree as the compression algorithm. */
class HCTree {
  private:
    // the root of HCTree
    // vector<HCNode*> leaves;  // a vector storing pointers to all leaf HCNodes
    HCNode* root;

    /* Decides whether the pointer points to a leaf. */
    bool isLeaf(HCNode* node) const;

    /* Store the code of each symbol in a lookup table--codeMap*/
    void buildCode(HCNode* node, string s);
    // unordered_map<byte, string> symbolToCodeMap;
    // unordered_map<string, byte> codeToSymbolMap;
    void deleteAll(HCNode* node);

  public:
    /* Initializes a new empty HCTree. */
    HCTree() : root(0) {}

    /* Destructor for HCTree. */
    ~HCTree();

    /* Builds the HCTree from the given frequency vector. Assume the vector must
     * have size 256 and each value at index i represents the frequency of char
     * with ASCII value i. To improve performance, only non-zero frequency
     * sysbol should be used to build the tree. The leaves vector must be
     * updated so that it can be used in encode() to improve performance.*/
    void build(const vector<unsigned int>& freqs);

    /* Write the encoding bits of given symbol to ostream. Writes each encoding
     * bit as char of either '0' or '1' to the ostream. */
    void encode(byte symbol, ostream& out) const;

    /* Decode the sequence of bits(represented as char of either '0' or '1')from
     * istream to return the coded symbol. */
    byte decode(istream& in) const;

    /* Writes the encoding bits of given symbol to the given BitOutputStream.
     * For this function, comprehensive search is not allowed. */
    void encode(byte symbol, BitOutputStream& out) const;

    /* TODO: add function header */
    byte decode(BitInputStream& in) const;
};

#endif  // HCTREE_HPP