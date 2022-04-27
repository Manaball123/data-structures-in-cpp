

namespace BT
{
    class BTNode
    {

        
    public:
        //pointers to other nodes
        BTNode* small_ptr;
        BTNode* large_ptr;

        //pointer to the element stored in the node
        void* element_ptr;
        BTNode(long key);
        ~BTNode();

        void* Get();

        //key
        long key;
            
    };
}




