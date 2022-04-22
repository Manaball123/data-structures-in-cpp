#include "binary-tree-node.h"
using namespace BT;

BTNode::BTNode(long key)
{
	this->key = key;
	//init all pointers to null
	element_ptr = large_ptr = small_ptr = nullptr;
}


void* BTNode::Get()
{
	return this->element_ptr;
}




