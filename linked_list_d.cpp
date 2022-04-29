#include "linked_list_d.h"
#include <stdlib.h>


using namespace LLD;





//Linked list node:

LLNodeD::LLNodeD()
{
	this->data = nullptr;
	this->next = nullptr;
	this->prev = nullptr;
}

LLNodeD::LLNodeD(void* data)
{
	this->data = data;
	this->next = nullptr;
	this->prev = nullptr;
}

LLNodeD::~LLNodeD()
{
	free(this->data);
	
}

//Linked list:

LinkedListD::LinkedListD(void* data)
{
	this->rootNode = new LLNodeD(data);
	this->endNode = this->rootNode;
	this->length = 1;
	this->halfLength = 0;
}

LinkedListD::~LinkedListD()
{
	LLNodeD* currentNode = this->rootNode;
	LLNodeD* nextNode;
	for (unsigned int i = 0; i < this->length; i++)
	{
		nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
	delete currentNode;

}
//Returns the data pointer at the node specified
void* LinkedListD::operator[](unsigned int index)
{
	if (index == 0)
	{
		return this->rootNode->data;
	}
	else if(index == length - 1)
	{
		return this->endNode->data;
	}
	LLNodeD* currentNode;

	//determines where to start from
	if (index > this->halfLength)
	{
		currentNode = this->endNode;
		//search backwards
		for (unsigned int i = this->length - 1; i > index; i--)
		{
			if (currentNode->prev != nullptr)
			{
				currentNode = currentNode->prev;
			}
			else
			{
				return nullptr;
			}
			
		}
		return currentNode->data;


	}
	else
	{
		currentNode = this->rootNode;
		//search forwards
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
	
}

void LinkedListD::Push(void* data)
{
	LLNodeD* newNode = new LLNodeD(data);

	this->endNode->next = newNode;
	newNode->prev = this->endNode;
	this->endNode = newNode;

	this->length++;
	this->halfLength = length / 2;
		
}
void LinkedListD::Pop()
{
	LLNodeD* end_ptr = this->endNode;
	this->endNode = this->endNode->prev;
	this->endNode->next = nullptr;
	delete end_ptr;

	this->length--;
	this->halfLength = length / 2;
}


void LinkedListD::Extend(void* data)
{
	LLNodeD* newNode = new LLNodeD(data);
	this->rootNode->prev = newNode;
	newNode->next = rootNode;
	this->rootNode = newNode;

	this->length++;
	this->halfLength = length / 2;

		
}

void LinkedListD::Retract()
{
	LLNodeD* root_ptr = this->rootNode;
	this->endNode = this->endNode->next;
	this->endNode->prev = nullptr;
	delete root_ptr;

	this->length--;
	this->halfLength = length / 2;
}


void LinkedListD::Insert(void* data, unsigned int index)
{
	if (index > this->length)
	{
		return;
	}

	if (index == this->length)
	{
		this->Push(data);
		this->length++;
		this->halfLength = length / 2;
	}

	else
	{
		LLNodeD* currentNode;
		if (index > this->halfLength)
		{
			//search backwards
			currentNode = this->endNode;
			for (unsigned int i = this->length - 1; i > index; i--)
			{
				if (currentNode->prev != nullptr)
				{
					currentNode = currentNode->prev;
				}
				else
				{
					return;
				}

			}

		}
		else
		{
			//search forwards
			currentNode = this->rootNode;
			for (unsigned int i = 0; i < index; i++)
			{
				if (currentNode->next != nullptr)
				{
					currentNode = currentNode->next;
				}
				else
				{
					return;
				}


			}
		}

		LLNodeD* newNode = new LLNodeD(data);
		//Reassigns the next node's previous pointer
		currentNode->next->prev = newNode;
		//Assigns the new node's next pointer to the next node
		newNode->next = currentNode->next;
		newNode->prev = currentNode;
		//Assigns current node's next pointer to newNode
		currentNode->next = newNode;
		
		


		this->length++;
		this->halfLength = length / 2;
	}
	
	
}


void LinkedListD::Remove(unsigned int index) 
{
	if (index > this->length)
	{
		return;
	}

	if (index == this->length)
	{
		this->Pop();
		return;

	}
	else if (index == 0)
	{
		this->Retract();

		return;
	}
	else
	{
		LLNodeD* currentNode;
		if (index > this->halfLength)
		{
			//search backwards
			currentNode = this->endNode;
			for (unsigned int i = this->length - 1; i > index; i--)
			{
				if (currentNode->prev != nullptr)
				{
					currentNode = currentNode->prev;
				}
				else
				{
					return;
				}

			}

		}
		else
		{
			//search forwards
			currentNode = this->rootNode;
			for (unsigned int i = 0; i < index; i++)
			{
				if (currentNode->next != nullptr)
				{
					currentNode = currentNode->next;
				}
				else
				{
					return;
				}


			}
		}


		currentNode->prev->next = currentNode->next;
		currentNode->next->prev = currentNode->prev;
		delete currentNode;


		this->length--;
		this->halfLength = length / 2;
	}

}