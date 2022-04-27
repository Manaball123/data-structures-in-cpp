#include "raw_data.h"
#include <stdlib.h>

using namespace RD;


//Data type to "fix" c++ data type enforcing thing
//Uses an extra memory pointer and int for size so kinda bad
RawData::RawData(void* data, unsigned int dataSize)
{
	this->data_ptr = data;
	this->dataSize = dataSize;
}

RawData::RawData(unsigned int dataSize)
{
	this->data_ptr = malloc(dataSize);
	this->dataSize = dataSize;
}

RawData::~RawData()
{
	delete this->data_ptr;
}















