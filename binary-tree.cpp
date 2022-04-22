#include "binary-tree.h"
using namespace BT;



BinaryTree::BinaryTree(long rootKey)
{

	this->root = new BTNode(rootKey);

}


BinaryTree::~BinaryTree()
{

}
//Me when the stack overflow :flushed:
//Navigates the tree with recursion
BTNode* BinaryTree::RecNav(
	long key,	
	BTNode* ptr	//Set this to root if you're calling this
)
{
	//if reached destination
	if (key == ptr->key)
	{
		return ptr;
	}
	//if did not reach destination
	//Check which direction to navigate to

	//if key is larger than key in ptr
	else if (key > ptr->key)
	{
		
		if (ptr->large_ptr != nullptr)
		{
			return this->RecNav(key, ptr->large_ptr);
		}
		else
		{
			return nullptr;
		}
	}
	//if key is smaller than key in ptr
	else
	{
		if (ptr->small_ptr != nullptr)
		{
			return this->RecNav(key, ptr->small_ptr);
		}
		else
		{
			return nullptr;
		}
		
	}
	
}

//superior ngl
BTNode* BinaryTree::LoopNav(long key)
{
	BTNode* curr_ptr = this->root;

	while (1)
	{

		if (curr_ptr->key == key)
		{
			return curr_ptr;
		}
		//if key is larger than key in ptr
		else if (curr_ptr->key < key)
		{
			if (curr_ptr->large_ptr != nullptr)
			{
				curr_ptr = curr_ptr->large_ptr;
			}
			else
			{
				return nullptr;
			}
			
		}
		//if key is smaller than key in ptr
		else
		{
			if (curr_ptr->small_ptr != nullptr)
			{
				curr_ptr = curr_ptr->small_ptr;
			}
			else
			{
				return nullptr;
			}
		}
	}
}

//0000: success
//ffff: fail(haha get it cuz f = fail)
short BinaryTree::AddNode(long key, void* value_ptr) 
{
	BTNode* curr_ptr = this->root;
	while (1)
	{
		if (curr_ptr->key == key)
		{
			return 0xffff;
		}
		//if key is larger than key in ptr
		else if (curr_ptr->key < key)
		{
			if (curr_ptr->large_ptr == nullptr)
			{
				curr_ptr->large_ptr = new BTNode(key);
				curr_ptr->large_ptr->element_ptr = value_ptr;
			}

		}
		//if key is smaller than key in ptr
		else
		{
			if (curr_ptr->small_ptr == nullptr)
			{
				curr_ptr->small_ptr = new BTNode(key);
				curr_ptr->small_ptr->element_ptr = value_ptr;
			}

		}
	}
}























