#include <iostream>
#include <stdlib.h>
#include "runtime_bs.h"
#include <cstddef>
#include <iomanip>


using namespace std;

using namespace BS;

void FillArr(unsigned short* arr)
{
    arr[0] = 0x0000;
}



int main()
{

    
    /*
    //unsigned short arr[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};
    unsigned short arr[] = {0x1A2B, 0x3C4D};

    //unsigned short arr[] = { 0x0000 };

    //waste memory here
    unsigned short peepoo[] = { 
        0x0001,   //0000 0001 - 1
        0x0002,   //0000 0010 - 2
        0x0004,   //0000 0100 - 3
        0x000f,    //0000 1111 - 4
        0x0010,   //0001 0000 - 5
    };
    unsigned short poopee[5];
    RtBitset bs1 = RtBitset(16 * sizeof(arr) / sizeof(arr[0]));

    //bs1.Compress((void*)arr, 16, (sizeof(arr) / sizeof(arr[0])), sizeof(short));
    //bs1.PrintBitsF();

    //cout << RtBitset::GetMinLength((void*)peepoo, sizeof(long), (sizeof(peepoo) / sizeof(peepoo[0]))) << endl;;
    unsigned int size = (sizeof(peepoo) / sizeof(peepoo[0])) * RtBitset::GetMinLength((void*)peepoo, sizeof(short), (sizeof(peepoo) / sizeof(peepoo[0])));
    RtBitset bs = RtBitset(size);

    bs.Compress( (void*)peepoo, RtBitset::GetMinLength((void*)peepoo, sizeof(short), (sizeof(peepoo) / sizeof(peepoo[0]))), ( sizeof(peepoo) / sizeof(peepoo[0]) ), sizeof(short) );
    bs.PrintBitsF();
    bs.ParseCompressed((void*)poopee, 5, sizeof(short), RtBitset::GetMinLength((void*)peepoo, sizeof(short), (sizeof(peepoo) / sizeof(peepoo[0]))));
    
    while (1)
    {

    }
    */


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
    //length of array
    unsigned int dataLen = sizeof(data) / sizeof(*data);
    unsigned int dataSize = sizeof(*data);

    //we can represent these numbers with at least these bits(per element)
    unsigned int minSize = RtBitset::GetMinLength((void*)data, dataSize, dataLen);
    cout << minSize << endl;

    //we should also allocate an array if we want our stuff back
    unsigned long* parsed = new unsigned long[dataLen];

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
    
    cout << (*data == *parsed) << endl;
    while(1){}
    
    
}
