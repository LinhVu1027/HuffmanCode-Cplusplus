#ifndef _HUFFMAN_CODE_CPP_
#define _HUFFMAN_CODE_CPP_

#include "HuffmanCode.h"

// convert byte to character
#define byte2Char(val) ((unsigned char) ((val) % 256))

// convert character to ASCII
#define char2Int(ch) ((int) (ch) < 0 ? 128 + (((int) (ch)) & 127): (((int) (ch)) & 127))

void sortHeap (NodeHuff* heapHuff[], int num, int index)
{
	for (int i = index; i < num+index-1; i++)
		for (int j = i+1; j < index+num; j++)
		{
			if (heapHuff[i]->freq > heapHuff[j]->freq)
			{
				NodeHuff* temp = heapHuff[i];
				heapHuff[i] = heapHuff[j];
				heapHuff[j] = temp;
			}
			else if (heapHuff[i]->freq == heapHuff[j]->freq)
			{
				if (heapHuff[i]->c > heapHuff[j]->c)
				{
					NodeHuff* temp = heapHuff[i];
					heapHuff[i] = heapHuff[j];
					heapHuff[j] = temp;
				}
			}
		}
}

void traversalTree(char* tbeBin[], NodeHuff *root, char strBit[], int nbit, int tbeBitOfChar[])
{
	if (root->nLeft == NULL && root->nRight==NULL)
	{
		strBit[nbit] = '\0';
		int index = root->c;
		tbeBitOfChar[index] = nbit;
		tbeBin[index] = new char [nbit];
		for (int i = 0; i <= nbit; i++)
			tbeBin[index][i] = strBit[i];
		return;
	}
	else 
	{
		strBit[nbit] = '0';
		traversalTree(tbeBin, root->nLeft, strBit, nbit+1, tbeBitOfChar);
		strBit[nbit] = '1';
		traversalTree(tbeBin, root->nRight, strBit, nbit+1, tbeBitOfChar);
	}
}

void insertTree(unzipTree* root, char c, int nbit, char* bitList)
{
	for( int i = 0; i<nbit; i++)
		if( bitList[i] == '0')
		{
			if(root->nLeft == NULL)
			{
			unzipTree* node = new unzipTree(0, c);
			root->nLeft = node;
			}
		root = root->nLeft;
		}
		else
		{
			if(root->nRight == NULL)
			{
			unzipTree* node = new unzipTree(1, c);
			root->nRight = node;
			}
		root = root->nRight;
		}
}

int HuffmanCode::zip(char* inputFile, char* outputFile) {
    // TODO implement for zip
	Reader* reader = new Reader(inputFile);


	/****************************************************/
	int tbeFreq[CHAR_SET_SIZE];
	for (int i = 0; i < CHAR_SET_SIZE; i++)
		tbeFreq[i] = 0;

	while (reader->isHasNext())
	{
		char c = reader->readChar();
		tbeFreq[char2Int(c)]++;
	}
	/****************************************************/
/*	for (int i = 0 ; i < 256; i++)
	{
		cout << i << "\t" << tbeFreq[i] << endl;
	}*/

	/****************************************************/
	int totalChar = 0;
	int n = 0;
	
	NodeHuff** heapHuff = new NodeHuff* [CHAR_SET_SIZE];
	for (int i = 0; i < CHAR_SET_SIZE; i++)
		heapHuff[i] = new NodeHuff();
	for (int i = 0; i < CHAR_SET_SIZE; i++)
	{
		if (tbeFreq[i] != 0)
		{
			heapHuff[n]->c = byte2Char(i);
			heapHuff[n]->freq = tbeFreq[i];
			totalChar++;
			n++;
		}
	} 

/*	for (int i = 0 ; i < 256; i++)
	{
		cout << i << "\t" << heapHuff[i]->c << "\t" << heapHuff[i]->freq << endl;
	}*/

	int* freqChar = new int[totalChar];
	for (int i = 0; i < totalChar; i++)
		freqChar[i] = heapHuff[i]->freq;
	/****************************************************/
	

	/****************************************************/
	int indexStart = 0;
	int indexLast = n-1;
	sortHeap(heapHuff, n, indexStart);

/*	for (int i = 0 ; i < 256; i++)
	{
		cout << i << "\t" << heapHuff[i]->c << "\t" << heapHuff[i]->freq << endl;
	}*/

	while (n > 1)
	{
		NodeHuff* temp = new NodeHuff(heapHuff[indexStart]->freq+heapHuff[indexStart+1]->freq, heapHuff[indexStart], heapHuff[indexStart+1]);
		heapHuff[++indexLast] = temp;
		indexStart = indexStart + 2;
		n--;
		sortHeap(heapHuff, n, indexStart);
	} 
	/****************************************************/
/*	for (int i = 0 ; i < 256; i++)
	{
		cout << i << "\t" << heapHuff[i]->c << "\t" << heapHuff[i]->freq << endl;
	}
	cout << indexLast << endl;*/

	/****************************************************/
	char* tbeBin[CHAR_SET_SIZE];
	for (int i = 0; i < CHAR_SET_SIZE; i++)
		tbeBin[i] = "";
	char strBit[100];
	int tbeBitOfChar[CHAR_SET_SIZE];
	traversalTree(tbeBin, heapHuff[indexLast], strBit , 0, tbeBitOfChar);

/*	for (int i = 0 ; i < 256; i++)
	{
		cout << i << "\t" << tbeBitOfChar[i] << "\t" << tbeBin[i] << endl;
	} */

	n--;
	char* chars = new char[totalChar];
	char** bitList = new char* [totalChar];
	int* bitOfChar = new int [totalChar];
	for (int i = 0; i < CHAR_SET_SIZE; i++)
	{
		if (tbeBin[i] != "")
		{
			chars[n] = i;
			bitOfChar[n] = tbeBitOfChar[i];
			bitList[n] = tbeBin[i];
			n++;
		}
	} 
	/****************************************************/
/*	for (int i = 0; i < totalChar; i++)
	{
		cout << i << "\t" << bitList[i] << endl;
	} */


	/****************************************************/
	int sizeBody = 0;
	int totalBit;
	for (int i = 0; i < totalChar; i++)
	{
		sizeBody += bitOfChar[i]*freqChar[i];
		totalBit += bitOfChar[i];
	}

/*	cout << "bodySize: " << sizeBody << endl;
	cout << "totalChar: " << totalChar << endl;
	cout << "totalBit: " << totalBit << endl;
	for (int i = 0; i < totalChar; i++)
	{
		cout << i  << "\t" << chars[i] << "\t" << freqChar[i] << "\t" << bitOfChar[i] << "\t" << bitList[i] << endl;
	} */

	Writer* writer = new Writer(outputFile);
	HCZHeader* header = new HCZHeader();
	header->setBodySize(sizeBody);
	header->setTotal(totalChar, totalBit);
	for (int i = 0; i < totalChar; i++)
		header->set(chars[i], bitOfChar[i], bitList[i]);
	header->write(writer);
	delete header;
	/****************************************************/


	/****************************************************/
	int count = 0;
	char c;
	char* str = NULL;
	while(count < sizeBody)
	{
		c = reader->readChar();
		str = tbeBin[char2Int(c)];
		for(int i = 0; str[i]!='\0'; i++)
		{
			writer->writeBit(str[i]-'0');
			count++;
		}
	}

	delete reader;
	delete writer;
	for (int i = 0; i < CHAR_SET_SIZE; i++)
		delete heapHuff[i];
	delete heapHuff;
	delete freqChar;
	delete chars;
	for (int i = 0; i < totalChar; i++)
		delete bitList[i];
	delete bitList;
	delete bitOfChar;

    cout << "zipping...";
	return SUCCESS;
}

int HuffmanCode::unzip(char* inputFile, char* outputFile) {
    // TODO implement for unzip
	HCZHeader* header = new HCZHeader();
	Reader* reader = new Reader(inputFile);
	header->read(reader);

	int totalChar, totalBit;
	header->getTotal(totalChar, totalBit);
	int bodySize = header->getBodySize();
	/****************************************************/


	/****************************************************/
	unzipTree* root = new unzipTree();
	char *bitList = new char[100];
	int nbit;
	for (int i = 0; i < CHAR_SET_SIZE; i++)
	{
		header->get(byte2Char(i), nbit, bitList);
		if (nbit)
			insertTree(root, byte2Char(i), nbit, bitList);
	}
	delete header;

	Writer* writer = new Writer(outputFile);
	int bit;
	unzipTree* temp = root;
	for (int i = 0; i < bodySize; i++)
	{
		bit = reader->readBit();
		if (bit == 0) temp = temp->nLeft;
		else temp = temp->nRight;
		if (temp->nLeft == NULL && temp->nRight == NULL)
		{
			writer->writeByte(char2Int(temp->c));
			temp = root;
		}
	}

	delete reader;
	delete writer;


    cout << "unzipping...";
    return SUCCESS;
}


#endif