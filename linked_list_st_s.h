#pragma once



// Single directional linked list:
// Less memory, slower access times
namespace STLLS
{
	template <class dtype>
	class STLLNodeS
	{
	public:
		STLLNodeS();
		STLLNodeS(dtype data);
		~STLLNodeS();
		//you should be keeping track of the data type
		dtype data;
		STLLNodeS* next;
		

	};

	template <class dtype>
	class STLinkedListS
	{
	public:
		STLinkedListS(dtype data);
		~STLinkedListS();
		
		//add element at the end
		void Push(dtype data);
		//remove element at the end
		//void Pop();
		//adds element to the front
		void Extend(dtype data);
		//remove element at the front
		void Retract();

		//Inserts a new node AFTER given index
		void Insert(dtype data, unsigned int index);
		//Removes element at index
		void Remove(unsigned int index);

		void* operator[](unsigned int index);
		STLLNodeS<dtype>* rootNode;
		STLLNodeS<dtype>* endNode;

		unsigned int length;
	};
}
