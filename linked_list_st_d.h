#pragma once
#include <iostream>


// Bi-directional linked list:
// More memory, faster access times
namespace STLLD
{
	//object that holds a data pointer and other stuff
	template <class dtype>
	class STLLNodeD
	{
	public:
		STLLNodeD()
		{
			this->data = nullptr;
			this->next = nullptr;
			this->prev = nullptr;
		}


		STLLNodeD(dtype data)
		{
			this->data = data;
			this->next = nullptr;
			this->prev = nullptr;
		}


		
		//data type here
		dtype data;
		STLLNodeD* next;
		STLLNodeD* prev;
		

	};
	template <class dtype>
	class STLinkedListD
	{
	public:

		STLLNodeD<dtype>* rootNode;
		STLLNodeD<dtype>* endNode;
		unsigned int length;
		//only updates if a new node is added
		unsigned int halfLength;

		STLinkedListD(dtype data)
		{
			this->rootNode = new STLLNodeD<dtype>(data);
			this->endNode = this->rootNode;
			this->length = 1;
			this->halfLength = 0;
		}

		~STLinkedListD()
		{
			STLLNodeD<dtype>* currentNode = this->rootNode;
			STLLNodeD<dtype>* nextNode;
			for (unsigned int i = 1; i < this->length - 1; i++)
			{
				nextNode = currentNode->next;
				delete currentNode;
				currentNode = nextNode;
			}
			delete currentNode;

		}

		//Returns data at given index
		dtype operator[](unsigned int index)
		{
			if (index == 0)
			{
				return this->rootNode->data;
			}
			else if (index == length - 1)
			{
				return this->endNode->data;
			}
			STLLNodeD<dtype>* currentNode;

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
						return 0;
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
						return 0;
					}


				}
				return currentNode->data;
			}

		}

		//Adds element at the end
		void Push(dtype data)
		{
			STLLNodeD<dtype>* newNode = new STLLNodeD<dtype>(data);

			this->endNode->next = newNode;
			newNode->prev = this->endNode;
			this->endNode = newNode;

			this->length++;
			this->halfLength = length / 2;

		}

		//Removes element at the end
		void Pop()
		{
			STLLNodeD<dtype>* end_ptr = this->endNode;
			this->endNode = this->endNode->prev;
			this->endNode->next = nullptr;
			delete end_ptr;

			this->length--;
			this->halfLength = length / 2;
		}

		//Adds element at the front
		void Extend(dtype data)
		{
			STLLNodeD<dtype>* newNode = new STLLNodeD<dtype>(data);
			this->rootNode->prev = newNode;
			newNode->next = rootNode;
			this->rootNode = newNode;

			this->length++;
			this->halfLength = length / 2;


		}

		//remove element at the front
		void Retract()
		{
			STLLNodeD<dtype>* root_ptr = this->rootNode;
			this->rootNode = this->rootNode->next;
			this->rootNode->prev = nullptr;
			delete root_ptr;

			this->length--;
			this->halfLength = length / 2;
		}

		//Inserts a new node AFTER given index
		//Insert after 0xffffffff to insert before index 0
		void Insert(dtype data, unsigned int index)
		{
			if (index == 0xffffffff)
			{

				this->Extend(data);
				return;

			}
			else if (index >= this->length)
			{
				return;
			}

			else if (index == this->length - 1)
			{
				this->Push(data);
				return;
			}



			else
			{
				STLLNodeD<dtype>* currentNode;
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

				STLLNodeD<dtype>* newNode = new STLLNodeD<dtype>(data);
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

		//Removes element at index
		void Remove(unsigned int index)
		{
			if (index >= this->length)
			{
				return;
			}

			else if (index == this->length - 1) 
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
				STLLNodeD<dtype>* currentNode;
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

		void AddAfterNode(STLLNodeD<dtype>* node_ptr, dtype data)
		{
			STLLNodeD<dtype>* newNode = new STLLNodeD<dtype>(data);
			//Reassigns the next node's previous pointer
			node_ptr->next->prev = newNode;

			//Assigns the new node's next pointer to the next node
			newNode->next = node_ptr->next;
			newNode->prev = node_ptr;
			//Assigns current node's next pointer to newNode
			node_ptr->next = newNode;

			this->length++;
			this->halfLength = length / 2;
		}

		//Automatically inserts a new element to the list, assuming that it is sorted
		//This probably would break if it isnt sorted
		//Returns the index it was inserted to
		//Returns 0xffffffff if inserted before root node
		unsigned int SequencedInsert(dtype data)
		{
			//insert before root if value is smaller than root
			if (data < this->rootNode->data)
			{
				this->Extend(data);
				return 0;
			}
			//Insert after end if value is bigger or equal to end
			else if (data >= this->endNode->data)
			{
				this->Push(data);
				return this->length - 1;
			}
			else
			{
				STLLNodeD<dtype>* currentNode = this->rootNode;
				for (unsigned int i = 1; i < this->length; i++)
				{
					if (currentNode->next->data > data)
					{

						if (currentNode->data <= data)
						{
							this->AddAfterNode(currentNode, data);
							return i;
						}
					}
					currentNode = currentNode->next;
				}
			}

		}

		void PrintList()
		{
			STLLNodeD<dtype>* currentNode = this->rootNode;
			std::cout << "[";
			for (unsigned int i = 1; i < this->length; i++)
			{
				std::cout << currentNode->data << ", ";
				currentNode = currentNode->next;
			}
			std::cout << currentNode->data << "]\n";
		}
		//Export the data into an array
		dtype* GetArrayRepr()
		{
			
			dtype* arr_ptr = new dtype[this->length];

			STLLNodeD<dtype>* currentNode = this->rootNode;
			arr_ptr[0] = currentNode->data;
			for (unsigned int i = 1;i < this->length; i++)
			{
				currentNode = currentNode->next;
				arr_ptr[i] = currentNode->data;
			}
			return arr_ptr;
		}
	};
}
