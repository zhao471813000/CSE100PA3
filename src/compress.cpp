/**
 * Compress file.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

using namespace std;

/* Pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(string inFileName, string outFileName) {
    unsigned int size = 256;
    string infile(inFileName);
    string outfile(outFileName);

    // open
    ifstream in;
    in.open(inFileName, ios::binary);
    // count symbols to get freqs
    vector<unsigned int> freqs(256, 0);
    int numChars = 0;
    unsigned char ch;
    int isEmpty = 1;
    while (1) {
        ch = in.get();
        if (!in.good()) break;
        freqs[(int)ch]++;
        isEmpty = 0;
    }
    in.close();
    // check empty file
    if (isEmpty) {
        ofstream out;
        out.open(outFileName, ios::binary);
        out.close();
        return;
    }
    // build tree
    HCTree tree;
    tree.build(freqs);

    // Open output file
    ofstream out;
    out.open(outFileName, ios::binary | ios::trunc);
    // header
    for (int i = 0; i < 256; i++) {
        // out.write((const char*)(&freqs[i]), sizeof(freqs[i]));
        out << freqs[i];
        out << '\n';
    }
    byte symbol;
    // open file
    in.open(inFileName, ios::binary);
    while (1) {
        symbol = in.get();
        if (!in.good()) break;
        tree.encode(symbol, out);
    }

    out.close();
    in.close();
}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {}

/* Main program that runs the compress */
int main(int argc, char** argv) {
    pseudoCompression(argv[1], argv[2]);
    // pseudoCompression("data/check3.txt", "compressed.txt");
    return 0;
}
