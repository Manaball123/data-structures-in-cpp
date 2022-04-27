#include "binary-tree-node.h"
using namespace BT;

BTNode::BTNode(long key)
{
	this->key = key;
	//init all pointers to null
	element_ptr = large_ptr = small_ptr = nullptr;
}
BTNode::~BTNode()
{
	//no more ptrs :sob:
	delete element_ptr, large_ptr, small_ptr;
}


void* BTNode::Get()
{
	return this->element_ptr;
}






