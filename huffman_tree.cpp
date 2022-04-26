#include "huffman_tree.h"
#include "raw_data.h"
#include <stdlib.h>
#include <vector>



using namespace HMENC;
using namespace std;


HMTree::HMTree(void* data, unsigned int dataSize, unsigned int dataLength)
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
	//
	unsigned int smallest = 0;
	unsigned int smaller = 0;


}





