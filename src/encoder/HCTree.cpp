/**
 * Implements Huffman Coding tree as the compression algorithm.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#include "HCTree.hpp"
#include "HCNode.hpp"

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
            HCNode* n = new HCNode(freqs[i], i);
            pq.push(n);
            // leaves[i] = n;
        }
    }
    if (pq.size() == 0) {
        return;
    } else if (pq.size() == 1) {
        // if only one node in priority queue, assign it to be left child
        HCNode* left = pq.top();
        pq.pop();
        root = new HCNode(left->count, left->symbol);
        root->c0 = left;
        root->c1 = nullptr;
        left->p = root;
        symbolToCodeMap.clear();
        symbolToCodeMap[left->symbol] = '0';
        return;
    } else {
        while (pq.size() > 1) {
            HCNode* left = pq.top();
            pq.pop();
            HCNode* right = pq.top();
            pq.pop();
            HCNode* parent =
                new HCNode(left->count + right->count, left->symbol);
            parent->c0 = left;
            parent->c1 = right;
            left->p = parent;
            right->p = parent;
            pq.push(parent);
        }
        root = pq.top();
        pq.pop();
        symbolToCodeMap.clear();
        buildCode(root, "");
    }
}

/* Decides whether the pointer points to a leaf. */
bool HCTree::isLeaf(HCNode* node) const {
    return (node->c0 == nullptr) && (node->c1 == nullptr);
}

/* Creates a lookup table of codings for each non-zero-frequency symbol. */
void HCTree::buildCode(HCNode* node, string s) {
    if (isLeaf(node)) {
        symbolToCodeMap[node->symbol] = s;
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
        if (chr == '0')
            curr = curr->c0;
        else if (chr == '1')
            curr = curr->c1;
    }
    return curr->symbol;
}

/* Writes the encoding bits of given symbol to the given BitOutputStream. For
 * this function, comprehensive search is not allowed. */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    string str = symbolToCodeMap[symbol];
    for (char ch : str) {
        if (ch == '0') out.writeBit(0);
        if (ch == '1') out.writeBit(1);
    }
}

/* Decodes the sequence of bits from the given BitInputStream to return coded
 * symbol. */
byte HCTree::decode(BitInputStream& in) const {
    HCNode* curr = root;
    while (!isLeaf(curr)) {
        unsigned int i = in.readBit();
        if (i == 0) curr = curr->c0;
        if (i == 1) curr = curr->c1;
    }
    return curr->symbol;
}
/* Serializes HCtree.*/
void HCTree::serial() {
    if (root->c0 != nullptr &&
        root->c1 == nullptr) {  // special case, only one leaf
        childState.push_back(1);
        symbolVec.push_back(root->c0->symbol);
    } else {
        childState.push_back(0);
        serialHelper(root);
    }
}
/* Serial helper to do preorder traverse using recursion.*/
void HCTree::serialHelper(HCNode* node) {
    if (isLeaf(node)) {
        symbolVec.push_back(node->symbol);
        childState.push_back(0);
        return;
    } else {
        childState.push_back(1);
    }
    serialHelper(node->c0);
    serialHelper(node->c1);
}
/* Reconstructs the HCTree.
   count all set to 1, internal nodes symbol sets to ' ' empty space. */
void HCTree::reconstruct(vector<int> childState,
                         vector<unsigned char> symbolVec) {
    if (childState[0] == 1) {
        // root only has one left leaf --special case
        HCNode* left = new HCNode(1, symbolVec[0]);
        root = new HCNode(1, ' ');
        root->c0 = left;
        left->p = root;
        return;
    } else {
        int cindex = 1;
        int sindex = 0;
        root = reconstructHelper(childState, symbolVec, cindex, sindex);
    }
}

/* Reconstructs Helper the HCTree. */
HCNode* HCTree::reconstructHelper(vector<int> childState,
                                  vector<unsigned char> symbolVec, int& cindex,
                                  int& sindex) {
    if (childState[cindex] == 0) {
        HCNode* curr = new HCNode(1, symbolVec[sindex]);
        sindex++;
        return curr;
    } else {
        HCNode* curr = new HCNode(1, ' ');
        cindex++;
        curr->c0 = reconstructHelper(childState, symbolVec, cindex, sindex);

        cindex++;
        curr->c1 = reconstructHelper(childState, symbolVec, cindex, sindex);
        return curr;
    }
}

void HCTree::deleteAll(HCNode* node) {
    if (node == nullptr) {
        return;
    }
    if (node->c0) {
        deleteAll(node->c0);
    }
    if (node->c1) {
        deleteAll(node->c1);
    }
    delete node;
}

