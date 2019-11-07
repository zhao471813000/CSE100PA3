/**
 * Uncompress file.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

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
/* Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {
    // open
    ifstream in;
    in.open(inFileName, ios::binary);

    // check empty file
    if (isEmptyFile(inFileName)) {
        ofstream out;
        out.open(outFileName, ios::binary);
        out.close();
        return;
    }

    in.seekg(0, ios_base::beg);
    vector<unsigned int> count(256, 0);

    // read and rebuild
    int index = 0;
    int numChar = 0;
    for (int i = 0; i < 256; i++) {
        count[i] = in.get();
        numChar += count[i];
    }
    HCTree tree;
    tree.build(count);

    // Open the output file
    ofstream out;
    out.open(outFileName, ios::binary);
    byte symbol;
    while (numChar) {
        if (!out.good()) break;
        symbol = tree.decode(in);
        out.write((char*)symbol, sizeof(symbol));
        numChar--;
    }

    in.close();
    out.close();
}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {}

/* Main program that runs the uncompress */
int main(int argc, char* argv[]) {
    pseudoDecompression(argv[1], argv[2]);
    return 0;
}
