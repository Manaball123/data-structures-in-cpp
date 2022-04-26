#pragma once




namespace RD
{
	struct RawData
	{
		void* data_ptr;
		unsigned int dataSize;
		//either link to data
		RawData(void* data, unsigned int dataSize);
		//...or just allocate space for new data
		RawData(unsigned int dataSize);
		
		~RawData();
	};
}




