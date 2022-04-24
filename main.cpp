#include <iostream>
#include <stdlib.h>
#include "runtime_bs.h"
#include <cstddef>
#include <iomanip>
#include "binary-tree.h"
#include <chrono>

using namespace std;

using namespace BS;
using namespace BT;

void FillArr(unsigned short* arr)
{
    arr[0] = 0x0000;
}




int main()
{

    
   

    
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

    














    while(1){}
    
    
}
