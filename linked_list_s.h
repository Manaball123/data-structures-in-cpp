#pragma once



// Single directional linked list:
// Less memory, slower access times
namespace LLS
{
	class LLNodeS
	{
	public:
		LLNodeS();
		LLNodeS(void* data);
		~LLNodeS();
		//you should be keeping track of the data type
		void* data;
		LLNodeS* next;
		

	};

	class LinkedListS
	{
	public:
		LinkedListS(void* data);
		~LinkedListS();
		
		//add element at the end
		void Push(void* data);
		//remove element at the end
		//void Pop();
		//adds element to the front
		void Extend(void* data);
		//remove element at the front
		void Retract();

		//Inserts a new node AFTER given index
		void Insert(void* data, unsigned int index);
		//Removes element at index
		void Remove(unsigned int index);

		void* operator[](unsigned int index);
		LLNodeS* rootNode;
		LLNodeS* endNode;

		unsigned int length;
	};
}
