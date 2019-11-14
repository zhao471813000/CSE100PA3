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
#include "cxxopts.hpp"

/* Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {
    // open
    ifstream in;
    in.open(inFileName, ios::binary);

    // check empty file
    FileUtils fileutils;
    if (fileutils.isEmptyFile(inFileName)) {
        ofstream out;
        out.open(outFileName, ios::binary | ios::trunc);
        out.close();
        return;
    }
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
        if (in.eof()) break;
        out << (char)symbol;
        numChar--;
    }

    in.close();
    out.close();
}

/* True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {
    // open
    ifstream in;
    in.open(inFileName, ios::binary);

    // check empty file
    FileUtils fileutils;
    if (fileutils.isEmptyFile(inFileName)) {
        ofstream out;
        out.open(outFileName, ios::binary | ios::trunc);
        out.close();
        return;
    }

    // read and rebuild
    int numNode;
    int numSymbol;
    int numChars;
    unsigned char firstCh;
    in.read((char*)&firstCh, sizeof(firstCh));
    in.read((char*)&numNode, sizeof(numNode));
    in.read((char*)&numSymbol, sizeof(numSymbol));
    in.read((char*)&numChars, sizeof(numChars));
    vector<int> childState;
    vector<unsigned char> symbolVec;
    BitInputStream ish(in);
    for (int i = 0; i < numNode; i++) {
        int temp = ish.readBit();
        childState.push_back(temp);
    }

    unsigned char c;
    while (c != firstCh) {
        in.read((char*)&c, sizeof(c));
    }
    symbolVec.push_back(c);
    for (int i = 1; i < numSymbol; i++) {
        in.read((char*)&c, sizeof(c));
        symbolVec.push_back(c);
    }

    HCTree tree;
    // tree.build(freqs);
    tree.reconstruct(childState, symbolVec);

    // Open the output file
    ofstream out;
    byte symbol;
    out.open(outFileName, ios::binary | ios::trunc);
    BitInputStream is(in);
    // in.get();
    for (int i = 0; i < numChars; i++) {
        symbol = tree.decode(is);
        if (in.eof()) break;
        out << (unsigned char)symbol;
    }

    in.close();
    out.close();
}

/* Main program that runs the uncompress */
int main(int argc, char* argv[]) {
    //    do option parsing with cxxopts
    cxxopts::Options options("./decompress",
                             "Decompresses files using Huffman Encoding");
    options.positional_help("./path_to_input_file ./path_to_output_file");
    bool isAsciiOutput = false;
    string inFileName, outFileName;
    options.allow_unrecognised_options().add_options()(
        "ascii", "Write output in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAsciiOutput))(
        "input", "", cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit");
    options.parse_positional({"input", "output"});
    auto userOptions = options.parse(argc, argv);
    if (userOptions.count("help") || !FileUtils ::isValidFile(inFileName) ||
        outFileName.empty()) {
        cout << options.help({""}) << std ::endl;
        exit(0);
    }
    if (isAsciiOutput) {
        pseudoDecompression(argv[2], argv[3]);
        // pseudoCompression("data/check1.txt", "compressed.txt");
    } else {
        trueDecompression(argv[1], argv[2]);
        // trueDecompression("compressed.txt", "decompressed.txt");
    }
    return 0;
}
