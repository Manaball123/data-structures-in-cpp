

namespace BT
{
    class BTNode
    {
        //pointers to other nodes
        BTNode* small_ptr;
        BTNode* large_ptr;
        
        //pointer to the element stored in the node
        void* element_ptr;

        //key
        long key;
        
    public:
        BTNode(long key);
        ~BTNode();

            
    };
}




