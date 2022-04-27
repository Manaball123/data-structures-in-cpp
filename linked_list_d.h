#pragma once



// Bi-directional linked list:
// More memory, faster access times
namespace LLD
{
	//object that holds a data pointer and other stuff
	class LLNodeD
	{
	public:
		LLNodeD();
		//DO NOT POINT THIS TO STACK MEMORY
		//DO NOT POINT THIS TO STACK MEMORY
		//DO NOT POINT THIS TO STACK MEMORY
		//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		LLNodeD(void* data);
		~LLNodeD();
		//you should be keeping track of the data type
		void* data;
		LLNodeD* next;
		LLNodeD* prev;
		

	};

	class LinkedListD
	{
	public:
		LinkedListD(void* data);
		~LinkedListD();
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
		LLNodeD* rootNode;
		LLNodeD* endNode;
		unsigned int length;
		//only updates if a new node is added
		unsigned int halfLength;
	};
}
