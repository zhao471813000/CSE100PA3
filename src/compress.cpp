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
    // check empty files
    FileUtils fileutils;
    if (fileutils.isEmptyFile(inFileName)) {
        ofstream out;
        out.open(outFileName, ios::binary | ios::trunc);
        out.close();
        return;
    }

    ifstream in;
    in.open(inFileName, ios::binary);

    // count symbols to get freqs
    vector<unsigned int> freqs(256, 0);
    int numChars = 0;
    unsigned char ch;
    while (1) {
        ch = in.get();
        if (in.eof()) break;
        freqs[(int)ch]++;
    }

    // build tree
    HCTree tree;
    tree.build(freqs);

    in.close();
    // Open output file
    ofstream out;
    out.open(outFileName, ios::binary | ios::trunc);
    // write header
    for (int i = 0; i < 256; i++) {
        out << freqs[i];
        out << '\n';
    }
    byte symbol;
    // open input file to encode
    in.open(inFileName, ios::binary);
    while (1) {
        symbol = in.get();
        if (in.eof()) break;
        tree.encode(symbol, out);
    }

    out.close();
    in.close();
}

/* True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {}

/* Main program that runs the compress */
int main(int argc, char** argv) {
    pseudoCompression(argv[1], argv[2]);
    // pseudoCompression("data/check1.txt", "compressed.txt");
    return 0;
}
