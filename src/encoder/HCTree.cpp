/**
 * Implements Huffman Coding tree as the compression algorithm.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#include "HCTree.hpp"
const unsigned int R = 256;
/* Destructor for HCTree. */
HCTree::~HCTree() {}

/* Builds the HCTree from the given frequency vector. Assume the vector must
 * have size 256 and each value at index i represents the frequency of char
 * with ASCII value i. To improve performance, only non-zero frequency
 * sysbol should be used to build the tree. The leaves vector must be
 * updated so that it can be used in encode() to improve performance.*/
void HCTree::build(const vector<unsigned int>& freqs) {
    my_queue pq;
    for (unsigned int i = 0; i < R; i++) {
        if (freqs[i] > 0) {
            pq.push(new HCNode(freqs[i], (byte)i, nullptr, nullptr, nullptr));
        }
    }
    // size == 1 ?
    while (pq.size() > 1) {
        HCNode* left = pq.top();
        pq.pop();
        HCNode* right = pq.top();
        pq.pop();
        HCNode* parent = new HCNode(left->count + right->count, left->symbol,
                                    left, right, nullptr);
        left->p = parent;
        right->p = parent;
        pq.push(parent);
    }
    root = pq.top();
    pq.pop();
}

/* Write the encoding bits of given symbol to ostream. Writes each encoding
 * bit as char of either '0' or '1' to the ostream. */
void HCTree::encode(byte symbol, ostream& out) const {}

/* Decode the sequence of bits(represented as char of either '0' or '1')from
 * istream to return the coded symbol. */
byte HCTree::decode(istream& in) const { return ' '; }

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {}

/* TODO */
byte HCTree::decode(BitInputStream& in) const { return ' '; }
