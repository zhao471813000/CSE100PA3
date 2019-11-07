/**
 * Implements Huffman Coding tree as the compression algorithm.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#include "HCTree.hpp"
const unsigned int R = 256;
unordered_map<byte, string> symbolToCodeMap;

/* Destructor for HCTree. */
HCTree::~HCTree() { deleteAll(root); }

/* Builds the HCTree from the given frequency vector. Assume the vector must
 * have size 256 and each value at index i represents the frequency of char
 * with ASCII value i. To improve performance, only non-zero frequency
 * sysbol should be used to build the tree. The leaves vector must be
 * updated so that it can be used in encode() to improve performance.*/
void HCTree::build(const vector<unsigned int>& freqs) {
    my_queue pq;
    for (unsigned int i = 0; i < R; i++) {
        if (freqs[i] > 0) {
            HCNode* n =
                new HCNode(freqs[i], (byte)i, nullptr, nullptr, nullptr);
            pq.push(n);
            // leaves[i] = n;
        }
    }
    if (pq.empty()) return;

    /*if (pq.size() == 1) {
        // if only one node in priority queue, assign it to be left child
        HCNode* left = pq.top();
        pq.pop();
        HCNode* parent = new HCNode(left->count, left->symbol);
        parent->c0 = left;
        left->p = parent;
        pq.push(parent);
    }*/
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
    symbolToCodeMap.clear();
    buildCode(root, "");
}

/* Decides whether the pointer points to a leaf. */
bool HCTree::isLeaf(HCNode* node) const {
    return (node->c0 == nullptr) && (node->c1 == nullptr);
}

/* Creates a lookup table of codings for each non-zero-frequency symbol. */
void HCTree::buildCode(HCNode* node, string s) {
    if (isLeaf(node)) {
        symbolToCodeMap[node->symbol] = s;
        // codeToSymbolMap[s] = node->symbol;
        return;
    }
    buildCode(node->c0, s + '0');
    buildCode(node->c1, s + '1');
}

/* Write the encoding bits of given symbol to ostream. Writes each encoding
 * bit as char of either '0' or '1' to the ostream. */
void HCTree::encode(byte symbol, ostream& out) const {
    string s = symbolToCodeMap[symbol];
    for (char ch : s) {
        out.put(ch);
    }
}

/* Decode the sequence of bits(represented as char of either '0' or '1')from
 * istream to return the coded symbol. */
byte HCTree::decode(istream& in) const {
    char chr;
    HCNode* curr = root;
    while (!isLeaf(curr)) {
        chr = in.get();
        if (in.eof()) {
            return ' ';
        }
        if (chr == '0') {
            curr = curr->c0;
        }

        else if (chr == '1') {
            curr = curr->c1;
        }
    }
    return curr->symbol;
}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {}

/* TODO */
byte HCTree::decode(BitInputStream& in) const { return ' '; }

void HCTree::deleteAll(HCNode* node) {
    if (node == nullptr) {
        return;
    }
    deleteAll(node->c0);
    deleteAll(node->c1);
    delete node;
}
