#pragma once


#include "runtime_bs.h"


//huffman encoding thing
namespace HMENC
{

	class HMNode
	{

	public:

		HMNode();
		//~HMNode();
		HMNode(unsigned int true_ptr, unsigned int false_ptr);
		HMNode(unsigned int dataIndex);


		//THESE ARE NOT POINTERS!!!!!!!!!
		//THESE ARE OFFSETS FOR THE NODES ARRAY
		unsigned int true_ptr;
		unsigned int false_ptr;

		//array declared in the actual tree class
		//NOTE: this only needs to be initialized if this node is an end node
		//initialize this to 0xffffffff if the node is not an end node
		unsigned int dataIndex;

	};


	//le huffman binary tree thingy
	class HMTree
	{

	public:
		//how to store class tutorial:
		//1. cast everything into a char
		//(thats it)

		//array contains the actual data for the thing to seach up
		char* dataDict;
		//IN BYTES
		unsigned int dataSize;
		
		//Pointer to array of nodes
		//You can decode by creating an empty class and replacing this with the thing you recieved
		HMNode* nodes;


		HMTree();

		
		//Constructs the tree, returns the compressed data
		BS::RtBitset* Encode(void* data, unsigned int dataSize, unsigned int dataLength);
		//Recursive function that constructs an array of bitsets
		void ConstructMap(BS::RtBitset* bs_ptr, unsigned int position, unsigned int counter);
		
		char* Decode();
	};

};




