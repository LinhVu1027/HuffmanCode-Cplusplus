#ifndef _HUFFMAN_CODE_H_
#define _HUFFMAN_CODE_H_

#include <iostream>
#include <fstream>
#include <cstring>

#include "Reader.h"
#include "Writer.h"
#include "HCZHeader.h"

using namespace std;

#define ERR -1

#define SUCCESS 0
#define UN_IMPLEMENT -2
#define MAXBUFSIZE 10000

// convert byte to character
#define byte2Char(val) ((unsigned char) ((val) % 256))

// convert character to ASCII
#define char2Int(ch) ((int) (ch) < 0 ? 128 + (((int) (ch)) & 127): (((int) (ch)) & 127))

struct NodeHuff
{
public:
	unsigned char c;
	int freq;
	NodeHuff *nLeft, *nRight;
public:
	NodeHuff()
	{
		this->c = 255;
		this->freq = 0;
		nLeft = nRight = NULL;
	}
	NodeHuff(int freq, NodeHuff* left, NodeHuff* right)
	{
		this->c = 255;
		this->freq = freq;
		nLeft = left;
		nRight = right;
	}
};

struct unzipTree
{
public:
	int bin;
	char c;
	unzipTree* nLeft, *nRight;
public:
	unzipTree()
	{
		bin = -1;
		c = 255;
		nLeft = nRight = NULL;
	}
	unzipTree(int bin, char c)
	{
		this->bin = bin;
		this->c = c;
		nLeft = nRight = NULL;
	}

};


class HuffmanCode {
public:
    int zip(char* inputFile, char* outputFile);
    int unzip(char* inputFile, char* outputFile);
    HuffmanCode() {
    }

private:

};

void sortHeap (NodeHuff* heapHuff[], int num, int index);

#endif