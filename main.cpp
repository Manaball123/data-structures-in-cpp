#include <iostream>
#include <stdlib.h>
#include "runtime_bs.h"
#include <cstddef>
#include <iomanip>
#include "binary-tree.h"
#include <chrono>
#include "linked_list_at_d.h"
#include "linked_list_at_s.h"
#include "linked_list_st_d.h"
#include "linked_list_st_s.h"
#include "raw_data.h"

using namespace std;

using namespace BS;
using namespace BT;
using namespace ATLLD;
using namespace ATLLS;
using namespace STLLD;
using namespace STLLS;
using namespace RD;

void FillArr(unsigned short* arr)
{
    arr[0] = 0x0000;
}




int main()
{

    
   

    /*
    //data is here
    //its a long dtype but everything in it are shorts so its bad(social credit--;)
    
    unsigned long data[] =
    {
        0x7fff,
        0x0001,
        0x0002,
        0x0f00,
        0x7ff0,
        0x00f0,
        0x7bcd,
        0x1234,
        0xffff,
        0x1ffff,
    };
    //unsigned long* data[100000];
    //length of array
    unsigned int dataLen = sizeof(data) / sizeof(*data);
    unsigned int dataSize = sizeof(*data);



    //we can represent these numbers with at least these bits(per element)
    unsigned int minSize = RtBitset::GetMinLength((void*)data, dataSize, dataLen);
    cout << minSize << endl;

    //we should also allocate an array if we want our stuff back
    unsigned long* parsed = (unsigned long*)calloc(dataLen, dataSize);

    //now we will compress the data into a bitset
    //first we make the bitset
    //size will be number of elements * number of bits per element
    RtBitset bs1 = RtBitset(dataLen * minSize);
    //then we compress
    bs1.Compress((void*)data, dataLen, dataSize, minSize);

    //take a peek at the bitset
    bs1.PrintBitsF();
    
    //and then retrieve it back(lol)
    bs1.ParseCompressed((void*)parsed, dataLen, dataSize, minSize);
    //inspect memory now
    //(look at parsed)
    //loop so program doesnt close 
    
    //cout << (*data == *parsed) << endl;
    for (int i = 0; i < dataLen; i++)
    {
        cout << "Data: " << data[i];
        cout << "  Parsed: " << parsed[i] << endl;
    }


    

    //binary tree test thing
    /*
    BinaryTree* tree1 = new BinaryTree(0);

    long data[] = 
    {
        1,2,3,4,5,6,7,8,9,10
    };


    tree1->AddNode(2, (void*)&data[3]);
    cout << "hi" << endl;
    tree1->AddNode(5, (void*)&data[5]);
    
    tree1->AddNode(-1, (void*)&data[4]);
    tree1->AddNode(1000000, (void*)&data[9]);
    tree1->AddNode(-1337, (void*)&data[0]);
    tree1->AddNode(42069, (void*)&data[2]);
    tree1->AddNode(69420, (void*)&data[6]);
    cout << *((long*)tree1->LoopNav(69420)->element_ptr) << endl;
    */



    /*
    
    int* e0 = new int{ 0 };
    int *e1 = new int{ 1 };
    int *e2 = new int{ 2 };
    int *e3 = new int{ 3 };
    int *e4 = new int{ 4 };
    int *e5 = new int{ 5 };
    int *e6 = new int{ 6 };
    int *e7 = new int{ 7 };
    int *e8 = new int{ 8 };
    int *e9 = new int{ 9 };
    int *e10 = new int{ 10 };

    
    LinkedListS l1 = LinkedListS((void*)e0);

    l1.Push((void*)e1);
    l1.Push((void*)e2);
    l1.Push((void*)e3);
    l1.Push((void*)e4);
    l1.Push((void*)e5);
    l1.Push((void*)e6);
    l1.Push((void*)e7);
    l1.Push((void*)e8);
    l1.Push((void*)e9);
    l1.Push((void*)e10);

    cout << "hi" << endl;
    for (int i = 0; i < l1.length; i++)
    {

        cout << *(int*)l1[i] << endl;

    }
    cout << "ddddddddddddddddddddddddddddddddd" << endl;
    l1.Remove(7);
    

    for (int i = 0; i < l1.length; i++)
    {

        cout << *(int*)l1[i] << endl;

    }
    int* new_7 = new int{ 7 };
    l1.Insert(((void*)new_7), 6);

    for (int i = 0; i < l1.length; i++)
    {

        cout << *(int*)l1[i] << endl;

    }





    while(1){}
    
    */
    STLinkedListD<int> l1 = STLinkedListD<int>(1);

    l1.Push(2);
    l1.Push(5);
    l1.Push(10);

    for (int i = 0; i < l1.length; i++)
    {

        cout << l1[i] << endl;

    }

    l1.SequencedInsert(3);
    l1.SequencedInsert(7);
    l1.SequencedInsert(0);
    for (int i = 0; i < l1.length; i++)
    {

        cout << l1[i] << endl;

    }
    
}
