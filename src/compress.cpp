/**
 * Compress file. Pseudo compression with ascii encoding and naive header is for
 * checkpoint, and True compression with bitwise i/o and small header is for
 * final.
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

/* True compression with bitwise i/o and small header (final)
   To realize optimal header, the huffman tree is rebuilt from 0/1 serials and
   symbols of the leaves from the header.
   The header stores the first symbol, the number of nodes, symbols, and chars
   as int first. Then, the 0/1 sequence indicates whether this node is a
   internal node. Specific details about serial function is in HCTree. After
   that, the symbols are stored as char.
*/
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
    in.close();
    // build tree
    HCTree tree;
    tree.build(freqs);
    // Serialize the tree
    tree.serial();
    vector<int> childState = tree.getChildState();
    vector<unsigned char> symbolVec = tree.getSymbolVec();
    int numNode = childState.size();
    int numSymbol = symbolVec.size();

    ofstream out;
    // Open output file
    out.open(outFileName, ios::binary | ios::trunc);
    // print header

    // the first symbol to distinguish the padding zero
    out.write((char*)&symbolVec[0], sizeof(symbolVec[0]));
    out.write((char*)&numNode, sizeof(numNode));      // number of the nodes
    out.write((char*)&numSymbol, sizeof(numSymbol));  // number of the symbols
    out.write((char*)&numChars,
              sizeof(numChars));  // number of the chars in the input file
    BitOutputStream osh(out);

    for (int i : childState) {
        osh.writeBit(i);
    }
    osh.flush();  // write out unflush bits

    for (unsigned char c : symbolVec) {
        out.write((char*)&c, sizeof(c));
        // out<<c;
    }

    // open input file to encode
    byte symbol;

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
    if (isAsciiOutput) {
        pseudoCompression(argv[2], argv[3]);
    } else {
        trueCompression(argv[1], argv[2]);
    }
    return 0;
}
