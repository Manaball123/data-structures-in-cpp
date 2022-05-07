#include "huffman_encoding.h"
#include "raw_data.h"
#include <stdlib.h>
#include <vector>
#include "linked_list_st_d.h"


using namespace HMENC;
using namespace STLLD;
using namespace std;



//-------------------------NODE------------------------

HMNode::HMNode()
{
	this->true_ptr = 0xffffffff;
	this->false_ptr = 0xffffffff;
	this->dataIndex = 0xffffffff;
}


HMNode::HMNode(unsigned int dataIndex)
{
	this->true_ptr = 0xffffffff;
	this->false_ptr = 0xffffffff;
	this->dataIndex = dataIndex;
}

HMNode::HMNode(unsigned int true_ptr, unsigned int false_ptr)
{
	this->true_ptr = true_ptr;
	this->false_ptr = false_ptr;
	this->dataIndex = 0xffffffff;
}

//----------------------TREE----------------------------------


void HMTree::ConstructMap(BS::RtBitset* bs_ptr, unsigned int position)
{
	if (this->nodes[position]->dataIndex == 0xffffffff)
	{
		this->ConstructMap(bs_ptr, this->nodes[position].true_ptr);
		this->ConstructMap(bs_ptr, this->nodes[position].false_ptr);
	}
	else
	{
		bs_ptr[this->nodes[position].dataIndex]
	}
}


BS::RtBitset* HMTree::Encode(void* data, unsigned int dataSize, unsigned int dataLength)
{
	unsigned int unique_ctr = 0;
	char* data_ptr = (char*)data;
	//temporary data dictionary
	vector<RD::RawData> dataVec;
	vector<unsigned int> dataOccurences;
	


	//reads through every data block
	for (unsigned int i = 0; i < dataLength; i++)
	{

		//assume the value is indeed unique
		bool unique = 1;
		//compares data with every discovered value
		for (unsigned int j = 0; j < dataVec.size() && unique; j++)
		{
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


		}
		//if the value is indeed unique after all the checks
		if (unique)
		{
			//increment thing by 1
			//THE TYPE ENFORCING EXPERIENCE
			//POV: u cant preform pointer arithmetic on void but u can cast it to char and to void 
			dataVec.push_back(RD::RawData((void*)((char*)data + i), dataSize));
			//this should sync with the datavec index
			dataOccurences.push_back(1);
			
		}
	
		
	}
	//Now that we have a list of all unique values and their counters, lets start mapping the thing

	//
	//Construct a linked list and create the nodes, according to data

	//Also data is stored seprately, in an array
	//It is accessed via indexes stored in dataIndex


	//btw the endpoints should be at around 0, and the root should be the last node in the array
	unsigned int requiredNodes = 1 + 2 * (dataVec.size() - 1);

	//Creates array of nodes
	this->nodes = new HMNode[requiredNodes];
	
	//Create list with probability
	STLinkedListD<unsigned int> probabilityOrdered = STLinkedListD<unsigned int>(0);
	//This saves index of nodes of probablity saved above
	STLinkedListD<unsigned int> nodeIndexes = STLinkedListD<unsigned int>(0);

	//Initialize the lists first
	probabilityOrdered.SequencedInsert(dataOccurences[0]);
	//Remove the element on index 0(0) as it is actually unused
	probabilityOrdered.Remove(0);
	

	for (unsigned int i = 1; i < dataVec.size(); i++)
	{
		probabilityOrdered.SequencedInsert(dataOccurences[i]);
		nodeIndexes.Push(i);
	}
	

	
	


	//Initialize the endpoints(ones that contains actual values)
	//(also constructs the "weights" list
	for (unsigned int i = 0; i < dataVec.size(); i++)
	{
		this->nodes[i].dataIndex = i;
	}
	//Iterates through the remaining nodes, grouping ones with small weights together
	for (unsigned int i = dataVec.size(); i < requiredNodes; i++)
	{
		this->nodes[i].false_ptr = nodeIndexes[0];
		this->nodes[i].true_ptr = nodeIndexes[1];
		unsigned int combinedProb = probabilityOrdered[0] + probabilityOrdered[1];
		probabilityOrdered.Retract();
		probabilityOrdered.Retract();
		nodeIndexes.Retract();
		nodeIndexes.Retract();
		nodeIndexes.Insert(i, probabilityOrdered.SequencedInsert(combinedProb) - 1);
	}
	//All nodes SHOULD be populated at this point

	//Now we'll work on compressing the data
	//Creates a "map" that uses the index of data as keys, and a bitset as the value
	
	BS::RtBitset* bs_arr = new BS::RtBitset[10];
	return new BS::RtBitset(1);
}





