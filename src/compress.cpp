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
#include "cxxopts.hpp"

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
void trueCompression(string inFileName, string outFileName) {
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
        numChars++;
    }
    // freqs[10] = 0;
    // freqs[97] = freqs[98] = freqs[99] = freqs[100] = 1;
    in.close();
    // build tree
    HCTree tree;
    tree.build(freqs);
    // Serialize the tree
    tree.serial();
    vector<int> childState = tree.getChildState();
    vector<char> symbolVec = tree.getSymbolVec();
    int numNode = childState.size();
    int numSymbol = symbolVec.size();
    // Open output file
    // print header
    ofstream out;
    out.open(outFileName, ios::binary | ios::trunc);
    out.write((char*)&numNode, sizeof(numNode));
    out.write((char*)&numSymbol, sizeof(numSymbol));
    out.write((char*)&numChars, sizeof(numChars));
    BitOutputStream osh(out);

    for (int i : childState) {
        osh.writeBit(i);
    }
    osh.flush();  // write out unflush bits

    for (char c : symbolVec) {
        out.write((char*)&c, sizeof(c));
    }

    // open input file to encode
    byte symbol;
    // ifstream in;
    in.open(inFileName, ios::binary);
    BitOutputStream os(out);
    while (1) {
        symbol = (unsigned char)in.get();
        if (in.eof()) break;
        tree.encode(symbol, os);
    }
    os.flush();

    out.close();
    in.close();
}

/* Main program that runs the compress */
int main(int argc, char** argv) {
    // do option parsing with cxxopts
    cxxopts::Options options("./compress",
                             "Compresses files using Huffman Encoding");
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
    // bool isAsciiOutput = false;
    if (isAsciiOutput) {
        pseudoCompression(argv[2], argv[3]);
        // pseudoCompression("data/check1.txt", "compressed.txt");
    } else {
        trueCompression(argv[1], argv[2]);
        // trueCompression("data/warandpeace.txt", "compressed.txt");
    }
    return 0;
}
