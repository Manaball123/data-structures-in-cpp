#pragma once



// Bi-directional linked list:
// More memory, faster access times
namespace ATLLD
{
	//object that holds a data pointer and other stuff
	class ATLLNodeD
	{
	public:
		ATLLNodeD();
		//DO NOT POINT THIS TO STACK MEMORY
		//DO NOT POINT THIS TO STACK MEMORY
		//DO NOT POINT THIS TO STACK MEMORY
		//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		ATLLNodeD(void* data);
		~ATLLNodeD();
		//you should be keeping track of the data type
		void* data;
		ATLLNodeD* next;
		ATLLNodeD* prev;
		

	};

	class ATLinkedListD
	{
	public:
		ATLinkedListD(void* data);
		~ATLinkedListD();
		//add element at the end
		void Push(void* data);
		//remove element at the end
		void Pop();
		//adds element to the front
		void Extend(void* data);
		//remove element at the front
		void Retract();

		//Inserts a new node AFTER given index
		void Insert(void* data, unsigned int index);
		//Removes element at index
		void Remove(unsigned int index);

		void* operator[](unsigned int index);
		ATLLNodeD* rootNode;
		ATLLNodeD* endNode;
		unsigned int length;
		//only updates if a new node is added
		unsigned int halfLength;
	};
}
