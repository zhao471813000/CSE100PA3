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

/* Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {
    // open
    ifstream in;
    in.open(inFileName, ios::binary);

    // check empty file
    in.seekg(0, ios_base::end);
    unsigned int len = in.tellg();
    if (len == 0) {
        ofstream out;
        out.open(outFileName, ios::binary);
        out.close();
        return;
    }
    // in.seekg(0, ios_base::beg);
    vector<unsigned int> freqs(256, 0);

    // read and rebuild
    int index = 0;
    int numChar = 0;
    for (int i = 0; i < 256; i++) {
        in >> freqs[i];
        numChar += freqs[i];
    }
    HCTree tree;
    tree.build(freqs);

    // Open the output file
    ofstream out;
    out.open(outFileName, ios::binary | ios::trunc);
    byte symbol;
    while (numChar) {
        symbol = tree.decode(in);
        if (!out.good()) break;

        out << (char)symbol;
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
    // pseudoDecompression("compressed.txt", "decompressed.txt");
    return 0;
}
