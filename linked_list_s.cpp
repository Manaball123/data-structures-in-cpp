#include "linked_list_s.h"



using namespace LLS;



//Linked list node:

LLNodeS::LLNodeS()
{
	this->data = nullptr;
	this->next = nullptr;
}

LLNodeS::LLNodeS(void* data)
{
	this->data = data;
	this->next = nullptr;
}

LLNodeS::~LLNodeS()
{
	delete this->data;
	//this SHOULD automatically delete all subsequent nodes
	if (this->next != nullptr)
	{
		delete this->next;
	}
	
}

//Linked list:

LinkedListS::LinkedListS(void* data)
{
	this->rootNode = new LLNodeS(data);
	this->endNode = this->rootNode;
	this->length = 1;
}

LinkedListS::~LinkedListS()
{
	delete this->rootNode;
}

void* LinkedListS::operator[](unsigned int index)
{
	LLNodeS* currentNode = this->rootNode;
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

void LinkedListS::Push(void* data)
{
	LLNodeS* newNode = new LLNodeS(data);

	this->endNode->next = newNode;
	this->endNode = newNode;
	this->length++;

}


void LinkedListS::Extend(void* data)
{
	LLNodeS* newNode = new LLNodeS(data);

	newNode->next = this->rootNode;
	this->rootNode = newNode;
	this->length++;



}

void LinkedListS::Retract()
{
	LLNodeS* root_ptr = this->rootNode;
	this->endNode = this->endNode->next;

	delete root_ptr;

	this->length--;
}



void LinkedListS::Insert(void* data, unsigned int index)
{
	LLNodeS* currentNode = this->rootNode;

	if (index == this->length - 1)
	{
		this->Push(data);
	}
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

		if (currentNode->next != nullptr)
		{
			LLNodeS* ptr_cache = currentNode->next;
			currentNode->next = new LLNodeS(data);
			currentNode->next->next = ptr_cache;


		}
		else
		{
			currentNode->next = new LLNodeS(data);
		}
		
		this->length++;

	}
}


void LinkedListS::Remove(unsigned int index) 
{
	
	if (index > this->length)
	{
		return;
	}
	else if (index == 0)
	{
		this->Retract();
		return;
	}

	LLNodeS* currentNode = this->rootNode;
	for (unsigned int i = 0; i < index - 1; i++)
	{
		currentNode = currentNode->next;
	}
	//remove the element after currentNode(the node at the target index)
	LLNodeS* ptr_cache = currentNode->next->next;
	delete currentNode->next;
	currentNode->next = ptr_cache;
	this->length--;
}















