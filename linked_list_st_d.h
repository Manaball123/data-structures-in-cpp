#pragma once



// Bi-directional linked list:
// More memory, faster access times
namespace STLLD
{
	//object that holds a data pointer and other stuff
	template <class dtype>
	class STLLNodeD
	{
	public:
		STLLNodeD();
		//DO NOT POINT THIS TO STACK MEMORY
		//DO NOT POINT THIS TO STACK MEMORY
		//DO NOT POINT THIS TO STACK MEMORY
		//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		STLLNodeD(dtype data);
		~STLLNodeD();
		//data type here
		dtype data;
		STLLNodeD* next;
		STLLNodeD* prev;
		

	};
	template <class dtype>
	class STLinkedListD
	{
	public:
		STLinkedListD(dtype data);
		~STLinkedListD();
		//add element at the end
		void Push(dtype data);
		//remove element at the end
		void Pop();
		//adds element to the front
		void Extend(dtype data);
		//remove element at the front
		void Retract();

		//Inserts a new node AFTER given index
		void Insert(dtype data, unsigned int index);
		//Removes element at index
		void Remove(unsigned int index);

		void* operator[](unsigned int index);
		STLLNodeD<dtype>* rootNode;
		STLLNodeD<dtype>* endNode;
		unsigned int length;
		//only updates if a new node is added
		unsigned int halfLength;
	};
}
