#pragma once


#include "runtime_bs.h"


//huffman encoding thing
namespace HMENC
{
	//le huffman binary tree thingy
	class HMTree
	{

	public:
		//how to store class tutorial:
		//1. cast everything into a char
		//(thats it)
		char* dataDict;
		unsigned int dataSize;
		BS::RtBitset* bitDict;


		HMTree(void* data, unsigned int dataSize, unsigned int dataLength);
		~HMTree();


		char* Decode();
	};
};




