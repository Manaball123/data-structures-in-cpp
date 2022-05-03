#include "linked_list_st_s.h"



using namespace STLLS;



//Linked list node:
template <class dtype>
STLLNodeS<dtype>::STLLNodeS()
{
	this->data = nullptr;
	this->next = nullptr;
}

template <class dtype>
STLLNodeS<dtype>::STLLNodeS(dtype data)
{
	this->data = data;
	this->next = nullptr;
}

template <class dtype>
STLLNodeS<dtype>::~STLLNodeS()
{
	delete this->data;
	
	
}

//Linked list:
template <class dtype>
STLinkedListS<dtype>::STLinkedListS(dtype data)
{
	this->rootNode = new STLLNodeS(data);
	this->endNode = this->rootNode;
	this->length = 1;
}

template <class dtype>
STLinkedListS<dtype>::~STLinkedListS()
{
	
	STLLNodeS* currentNode = this->rootNode;
	STLLNodeS* nextNode;
	for (unsigned int i = 0; i < this->length; i++)
	{
		nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
	delete currentNode;
}

template <class dtype>
void* STLinkedListS<dtype>::operator[](unsigned int index)
{
	STLLNodeS* currentNode = this->rootNode;
	for (unsigned int i = 0; i < index; i++)
	{
		if (currentNode->next != nullptr)
		{
			currentNode = currentNode->next;
		}
		else
		{
			return nullptr;
		}
		

	}
	return currentNode->data;
}

template <class dtype>
void STLinkedListS<dtype>::Push(dtype data)
{
	STLLNodeS* newNode = new STLLNodeS(data);

	this->endNode->next = newNode;
	this->endNode = newNode;
	this->length++;

}

template <class dtype>
void STLinkedListS<dtype>::Extend(dtype data)
{
	STLLNodeS* newNode = new STLLNodeS(data);

	newNode->next = this->rootNode;
	this->rootNode = newNode;
	this->length++;



}

template <class dtype>
void STLinkedListS<dtype>::Retract()
{
	STLLNodeS* root_ptr = this->rootNode;
	this->rootNode = this->rootNode->next;

	delete root_ptr;

	this->length--;
}


template <class dtype>
void STLinkedListS<dtype>::Insert(dtype data, unsigned int index)
{
	

	if (index == this->length - 1)
	{
		this->Push(data);
		return;
	}
	else if (index == 0)
	{
		this->Extend(data);
		return;
	}
	else
	{
		STLLNodeS* currentNode = this->rootNode;
		for (unsigned int i = 0; i < index; i++)
		{
			if (currentNode->next != nullptr)
			{
				currentNode = currentNode->next;
			}
			else
			{
				//break loop if out of bounds
				return;
			}
		}



		if (currentNode->next != nullptr)
		{
			STLLNodeS* ptr_cache = currentNode->next;
			currentNode->next = new STLLNodeS(data);
			currentNode->next->next = ptr_cache;


		}
		else
		{
			currentNode->next = new STLLNodeS(data);
		}

		this->length++;

		
	}
	
	
}

template <class dtype>
void STLinkedListS<dtype>::Remove(unsigned int index)
{

	if (index > this->length - 1)
	{
		return;
	}


	else if (index == 0)
	{
		this->Retract();
		return;
	}
	else
	{
		STLLNodeS* currentNode = this->rootNode;
		for (unsigned int i = 1; i < index; i++)
		{
			currentNode = currentNode->next;
		}
		//save the address of node after deleted node first
		STLLNodeS* ptr_cache = currentNode->next->next;
		//remove the element after currentNode(the node at the target index)
		delete currentNode->next;
		currentNode->next = ptr_cache;
		this->length--;
	}

	
}