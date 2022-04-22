#include "binary-tree-node.h"


namespace BT
{
    
    class BinaryTree
    {
        //root node
        BTNode *root;


        

    public:
        BinaryTree(long rootKey);
        ~BinaryTree();

        //returns result value
        short AddNode(long key, void* value_ptr);
        //void AddToStack(long key);
        BTNode* LoopNav(long key);
        BTNode* RecNav(
            long key,
            BTNode* ptr	//Set this to root if you're calling this
        );




    };
}



