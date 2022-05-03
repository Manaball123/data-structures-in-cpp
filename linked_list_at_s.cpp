#include "linked_list_at_s.h"



using namespace ATLLS;



//Linked list node:

ATLLNodeS::ATLLNodeS()
{
	this->data = nullptr;
	this->next = nullptr;
}

ATLLNodeS::ATLLNodeS(void* data)
{
	this->data = data;
	this->next = nullptr;
}

ATLLNodeS::~ATLLNodeS()
{
	delete this->data;
	
	
}

//Linked list:

ATLinkedListS::ATLinkedListS(void* data)
{
	this->rootNode = new ATLLNodeS(data);
	this->endNode = this->rootNode;
	this->length = 1;
}

ATLinkedListS::~ATLinkedListS()
{
	
	ATLLNodeS* currentNode = this->rootNode;
	ATLLNodeS* nextNode;
	for (unsigned int i = 0; i < this->length; i++)
	{
		nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
	delete currentNode;
}

void* ATLinkedListS::operator[](unsigned int index)
{
	ATLLNodeS* currentNode = this->rootNode;
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

void ATLinkedListS::Push(void* data)
{
	ATLLNodeS* newNode = new ATLLNodeS(data);

	this->endNode->next = newNode;
	this->endNode = newNode;
	this->length++;

}


void ATLinkedListS::Extend(void* data)
{
	ATLLNodeS* newNode = new ATLLNodeS(data);

	newNode->next = this->rootNode;
	this->rootNode = newNode;
	this->length++;



}

void ATLinkedListS::Retract()
{
	ATLLNodeS* root_ptr = this->rootNode;
	this->rootNode = this->rootNode->next;

	delete root_ptr;

	this->length--;
}



void ATLinkedListS::Insert(void* data, unsigned int index)
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
		ATLLNodeS* currentNode = this->rootNode;
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
			ATLLNodeS* ptr_cache = currentNode->next;
			currentNode->next = new ATLLNodeS(data);
			currentNode->next->next = ptr_cache;


		}
		else
		{
			currentNode->next = new ATLLNodeS(data);
		}

		this->length++;

		
	}
	
	
}


void ATLinkedListS::Remove(unsigned int index)
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
		ATLLNodeS* currentNode = this->rootNode;
		for (unsigned int i = 1; i < index; i++)
		{
			currentNode = currentNode->next;
		}
		//save the address of node after deleted node first
		ATLLNodeS* ptr_cache = currentNode->next->next;
		//remove the element after currentNode(the node at the target index)
		delete currentNode->next;
		currentNode->next = ptr_cache;
		this->length--;
	}

	
}