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

bool isEmptyFile(string fileName) {
    ifstream inFile;
    // if the given file is empty, output empty file
    inFile.open(fileName, ios::binary);
    inFile.get();
    if (inFile.eof()) {
        inFile.close();
        return true;
    }
    inFile.close();
    return false;
}
/* Pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(string inFileName, string outFileName) {
    unsigned int size = 256;
    string infile(inFileName);
    string outfile(outFileName);

    // check empty file
    if (isEmptyFile(inFileName)) {
        ofstream out;
        out.open(outFileName, ios::binary);
        out.close();
        return;
    }

    // 1. open
    ifstream in;
    in.open(inFileName, ios::binary);
    // 2. count symbols to get freqs
    vector<unsigned int> freqs(256, 0);
    int numChars = 0;
    unsigned char ch;
    while (1) {
        ch = in.get();
        if (!in.good()) break;
        freqs[(int)ch]++;
    }
    in.close();
    // 3. build tree
    HCTree* tree;
    tree->build(freqs);

    // 4. Open output file for writing.
    ofstream out;
    out.open(outFileName, ios::trunc);

    // 5. header
    for (int i = 0; i < 256; i++) {
        out.write((const char*)(&freqs[i]), sizeof(freqs[i]));
        out.put('\n');
    }

    // open file
    in.open(inFileName, ios::binary);

    byte symbol;
    while (1) {
        symbol = in.get();
        if (!in.good()) break;
        tree->encode(symbol, out);
    }

    out.close();
    in.close();
    delete tree;
    return;
}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {}

/* Main program that runs the compress */
int main(int argc, char* argv[]) {
    pseudoCompression(argv[1], argv[2]);
    return 0;
}
