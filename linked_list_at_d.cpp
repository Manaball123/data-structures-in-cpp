#include "linked_list_at_d.h"
#include <stdlib.h>


using namespace ATLLD;





//Linked list node:

ATLLNodeD::ATLLNodeD()
{
	this->data = nullptr;
	this->next = nullptr;
	this->prev = nullptr;
}

ATLLNodeD::ATLLNodeD(void* data)
{
	this->data = data;
	this->next = nullptr;
	this->prev = nullptr;
}

ATLLNodeD::~ATLLNodeD()
{
	free(this->data);
	
}

//Linked list:

ATLinkedListD::ATLinkedListD(void* data)
{
	this->rootNode = new ATLLNodeD(data);
	this->endNode = this->rootNode;
	this->length = 1;
	this->halfLength = 0;
}

ATLinkedListD::~ATLinkedListD()
{
	ATLLNodeD* currentNode = this->rootNode;
	ATLLNodeD* nextNode;
	for (unsigned int i = 0; i < this->length; i++)
	{
		nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
	delete currentNode;

}
//Returns the data pointer at the node specified
void* ATLinkedListD::operator[](unsigned int index)
{
	if (index == 0)
	{
		return this->rootNode->data;
	}
	else if(index == length - 1)
	{
		return this->endNode->data;
	}
	ATLLNodeD* currentNode;

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

void ATLinkedListD::Push(void* data)
{
	ATLLNodeD* newNode = new ATLLNodeD(data);

	this->endNode->next = newNode;
	newNode->prev = this->endNode;
	this->endNode = newNode;

	this->length++;
	this->halfLength = length / 2;
		
}
void ATLinkedListD::Pop()
{
	ATLLNodeD* end_ptr = this->endNode;
	this->endNode = this->endNode->prev;
	this->endNode->next = nullptr;
	delete end_ptr;

	this->length--;
	this->halfLength = length / 2;
}


void ATLinkedListD::Extend(void* data)
{
	ATLLNodeD* newNode = new ATLLNodeD(data);
	this->rootNode->prev = newNode;
	newNode->next = rootNode;
	this->rootNode = newNode;

	this->length++;
	this->halfLength = length / 2;

		
}

void ATLinkedListD::Retract()
{
	ATLLNodeD* root_ptr = this->rootNode;
	this->endNode = this->endNode->next;
	this->endNode->prev = nullptr;
	delete root_ptr;

	this->length--;
	this->halfLength = length / 2;
}


void ATLinkedListD::Insert(void* data, unsigned int index)
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
		ATLLNodeD* currentNode;
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

		ATLLNodeD* newNode = new ATLLNodeD(data);
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


void ATLinkedListD::Remove(unsigned int index) 
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
		ATLLNodeD* currentNode;
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