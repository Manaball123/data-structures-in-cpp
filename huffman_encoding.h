#pragma once


//#include "runtime_bs.h"
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include "runtime_bs.h"
#include "linked_list_st_d.h"


using namespace STLLD;
using namespace std;


//huffman encoding thing
namespace HMENC
{

	


	//le huffman binary tree thingy
	template <class dtype>
	class HMTree
	{

	public:

		class HMNode
		{

		public:

			//-------------------------NODE------------------------

			HMNode()
			{
				this->true_ptr = 0xffffffff;
				this->false_ptr = 0xffffffff;
				this->dataIndex = 0xffffffff;
			}


			HMNode(unsigned int dataIndex)
			{
				this->true_ptr = 0xffffffff;
				this->false_ptr = 0xffffffff;
				this->dataIndex = dataIndex;
			}

			HMNode(unsigned int true_ptr, unsigned int false_ptr)
			{
				this->true_ptr = true_ptr;
				this->false_ptr = false_ptr;
				this->dataIndex = 0xffffffff;
			}

			//THESE ARE NOT POINTERS!!!!!!!!!
			//THESE ARE OFFSETS FOR THE NODES ARRAY
			unsigned int true_ptr;
			unsigned int false_ptr;

			//array declared in the actual tree class
			//NOTE: this only needs to be initialized if this node is an end node
			//initialize this to 0xffffffff if the node is not an end node
			unsigned int dataIndex;

		};



		//array contains the actual data for the thing to seach up
		dtype* dataDict;

		
		//Pointer to array of nodes
		//You can decode by creating an empty class and replacing this with the thing you recieved
		HMNode* nodes;
		unsigned int nodesLength;
		unsigned int dictLength;
	
		//Constructs the tree, returns the compressed data
		//BS::RtBitset* Encode(void* data, unsigned int dataSize, unsigned int dataLength);
		//Recursive function that constructs an array of bitsets



		//----------------------TREE----------------------------------
		HMTree()
		{
		
		};
		~HMTree()
		{
			delete[] this->nodes;
			delete[] this->dataDict;
		}

		//
		/*
		void AllocateNodes(unsigned int length)
		{
			this->nodes = new HMNode[length];
			this->nodesLength = length;
		}
		*/
		void CopyNodes(unsigned int length, HMNode* ptr)
		{
			this->nodes = new HMNode[length];
			std::copy(ptr, ptr + length, this->nodes);
			this->nodesLength = length;
		}

		void CopyDict(unsigned int length, dtype* dict)
		{
			this->dataDict = new dtype[length];
			std::copy(dict, dict + length, this->dataDict);
		}


		

		//Recursively creates a key-value pair
		void ConstructMap(BS::RtBitset* bs_ptr, unsigned int position, BS::RtBitset* currentPattern)
		{
			if ((this->nodes[position]).dataIndex == 0xffffffff)
			{
			
				BS::RtBitset* truePattern = new BS::RtBitset(currentPattern);
				BS::RtBitset* falsePattern = new BS::RtBitset(currentPattern);
				truePattern->Reallocate(truePattern->length + 1);
				falsePattern->Reallocate(falsePattern->length + 1);
				truePattern->SetBit(truePattern->length - 1);
				falsePattern->ClearBit(falsePattern->length - 1);

				this->ConstructMap(bs_ptr, this->nodes[position].true_ptr, truePattern);
				this->ConstructMap(bs_ptr, this->nodes[position].false_ptr, falsePattern);
			}
			else
			{
				bs_ptr[this->nodes[position].dataIndex].Copy(currentPattern);
			}
		}


		BS::RtBitset* Encode(dtype* data, unsigned int length)
		{
			//temporary data dictionary
			vector<dtype> dataVec;
			vector<unsigned int> dataOccurences;



			//reads through every element of array
			for (unsigned int i = 0; i < length; i++)
			{

				//assume the value is indeed unique
				bool unique = 1;
				//cout << "Checking value " << data[i] << endl;
				//compares data with every discovered value
				for (unsigned int j = 0; j < dataVec.size() && unique; j++)
				{
					//i kinda liek this so im keeping it
					/*
					//checks every byte against the current value
					bool isDifferent = 0;
					for (unsigned int k = 0; k < dataSize && !isDifferent; k++)
					{

						//the pinnacle of clean code
						//anyways this checks the byte

						//at any point if one byte is different, then this element is not equal to the element checked against
						//Therefore, there is no point in further checking the bytes of this loop
						if (*(data_ptr + i * dataSize + k) != *(((char*)dataVec[i].data_ptr) + j))
						{
							//Don't go in further
							isDifferent = 1;


						}
					}
					//if no difference is found after check against every byte, then increment the counter
					if (!isDifferent)
					{
						dataOccurences[j]++;
						//the value is of course, not unique
						unique = 0;
					}

					*/
					//cout << "...against " << dataVec[j] << endl;
					if (dataVec[j] == data[i])
					{
						//cout << "It is not unique. " << endl;
						unique = 0;
						dataOccurences[j]++;
					}
				}
				//if the value is indeed unique after all the checks
				if (unique)
				{
					dataVec.push_back(data[i]);
					//this should sync with the datavec index
					dataOccurences.push_back(1);

				}


			}
			//Now that we have a list of all unique values and their counters, lets start mapping the thing

			//
			//Construct a linked list and create the nodes, according to data

			//Also data is stored seprately, in an array
			//It is accessed via indexes stored in dataIndex

			unsigned int uniquesLength = dataVec.size();
			this->dictLength = uniquesLength;
			//btw the endpoints should be at around 0, and the root should be the last node in the array
			unsigned int requiredNodes = 1 + 2 * (uniquesLength - 1);

			//Creates array of nodes
			this->nodes = new HMNode[requiredNodes];
			this->nodesLength = requiredNodes;

			//Create list with probability
			STLinkedListD<unsigned int> probabilityOrdered = STLinkedListD<unsigned int>(0);
			//This saves index of nodes of probablity saved above
			STLinkedListD<unsigned int> nodeIndexes = STLinkedListD<unsigned int>(0);

			//Initialize the lists first
			probabilityOrdered.SequencedInsert(dataOccurences[0]);
			//Remove the element on index 0(0) as it is actually unused
			probabilityOrdered.Remove(0);

			//REORDER all the nodes first
			//Note that the order in dataVec is unordered
			

			for (unsigned int i = 1; i < uniquesLength; i++)
			{
				//nodeIndexes.Insert(i, probabilityOrdered.SequencedInsert(dataOccurences[i]) - 1);
				nodeIndexes.Insert(i, probabilityOrdered.SequencedInsert(dataOccurences[i]) - 1);
				//cout << "inserted after index " << target << endl;
				//probabilityOrdered.PrintList();
				//nodeIndexes.PrintList();
			}
			//this contains all the nodes probability, ordered
			unsigned int* probArr = probabilityOrdered.GetArrayRepr();
			//index should be from 0 to datavec.size() - 1

			//Copies contents from the vector to the array
			this->dataDict = new dtype[uniquesLength];
			std::copy(dataVec.begin(), dataVec.end(), dataDict);

			//probabilityOrdered.PrintList();
			//nodeIndexes.PrintList();
			//Initialize the endpoints(ones that contains actual values)
			//(also constructs the "weights" list
			for (unsigned int i = 0; i < uniquesLength; i++)
			{
				this->nodes[i].dataIndex = i;
			}
			//Iterates through the remaining nodes, grouping ones with small weights together
			for (unsigned int i = uniquesLength; i < requiredNodes; i++)
			{
				this->nodes[i].false_ptr = nodeIndexes[0];
				this->nodes[i].true_ptr = nodeIndexes[1];
				unsigned int combinedProb = probabilityOrdered[0] + probabilityOrdered[1];
				nodeIndexes.Insert(i, probabilityOrdered.SequencedInsert(combinedProb) - 1);
				
				probabilityOrdered.Retract();
				probabilityOrdered.Retract();
				nodeIndexes.Retract();
				nodeIndexes.Retract();
				//probabilityOrdered.PrintList();
				//nodeIndexes.PrintList();

				
			}
			//All nodes SHOULD be populated at this point

			//Now we'll work on compressing the data
			//Creates a "map" that uses the index of data as keys, and a bitset as the value

			BS::RtBitset* bs_arr = new BS::RtBitset[dataVec.size()];
			BS::RtBitset* tempBs = new BS::RtBitset();
			ConstructMap(bs_arr, requiredNodes - 1, tempBs);
			//Now make another map with raw data -> bitset
			unordered_map<dtype, BS::RtBitset*> datamap;

			//Total bits required 
			unsigned int totalBits = 0;

			for (unsigned int i = 0; i < uniquesLength; i++)
			{
				//Create a key-value pair
				datamap.insert(std::make_pair(dataVec[i], (bs_arr + i)));
				totalBits += (((bs_arr + i)->length) * probArr[i]);
				//cout << "data: " << dataVec[i] << " index: " << i << "bit len: " << bs_arr[i].length << "pattern: " << endl;
				//bs_arr[i].PrintBitsF();
			}
			//Create the output bitset
			BS::RtBitset* output = new BS::RtBitset(totalBits);

			//Iterate through all elements
			unsigned int position = 0;
			for (unsigned int i = 0; i < length; i++)
			{
				//Find the current pattern
				
				BS::RtBitset* currPattern = datamap[data[i]];
				//std::cout << "data: " << data[i] << endl;
				//cout << "pattern length" << currPattern->length << ", pattern used : \n";
				
				
				//currPattern->PrintBitsF();
				
				
				//Append this into the final output
				for (unsigned int j = 0; j < currPattern->length; j++)
				{
					//TODO: Make the set pattern function and use that instead
					if (currPattern->operator[](j))
					{
						output->SetBit(position);
					}
					position++;
				}
			}
			//cout << "final";
			//output->PrintBitsF();
			return output;
		}

		//Make sure to point nodes to a node tree(node array) and place in datadict before decoding
		dtype* Decode(BS::RtBitset* bs, unsigned int length)
		{
			//bs->PrintBitsF();
			dtype* output = new dtype[length];
			unsigned int bit_ctr = 0;
			//iterate through all elements

			for (unsigned int i = 0; i < length; i++)
			{
				//The root is always at the end due to how the map is constructed
				unsigned int nodeAddr = this->nodesLength - 1;
				bool found = 0;
				while (!found)
				{
					if (this->nodes[nodeAddr].dataIndex != 0xffffffff)
					{
						found = 1;
						output[i] = this->dataDict[this->nodes[nodeAddr].dataIndex];
					}
					else
					{
						
						if (bs->operator[](bit_ctr))
						{
							bit_ctr++;
							nodeAddr = this->nodes[nodeAddr].true_ptr;
						}
						else
						{
							bit_ctr++;
							nodeAddr = this->nodes[nodeAddr].false_ptr;
						}
					}
				}
			}
			return output;
		}

		

	};

};




