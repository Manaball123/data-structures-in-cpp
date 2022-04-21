#include "runtime_bs.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstddef>
using namespace BS;
void PrintByte(char b)
{
    using namespace std;
    cout << setw(2) << setfill('0') << hex << (int)b;
}

RtBitset::RtBitset(unsigned int len)
{
    
    this->length = len;
    this->byteLength = (len / 8) + (len % 8 == 0 ? 0 : 1);
    //I hope this works, though it might not
    this->content = (unsigned char*)malloc(sizeof(char) * byteLength);

    //zeroes out the char array
    for (unsigned int i = 0; i < byteLength; i++)
    {
        this->content[i] = 0x00;
    }
};
RtBitset::~RtBitset()
{
    delete this->content;
}

bool RtBitset::GetBit(unsigned int byteIndex, unsigned short bitIndex)
{
    return (this->content[byteIndex] >> (7 - bitIndex) & 0x01);
};
//GetBit function but with index
bool RtBitset::GetBit(unsigned int index)
{
    return (this->content[index / 8] >> (7 - index % 8) & 0x01);
};

bool RtBitset::operator[](unsigned int index)
{
    return (this->content[index / 8] >> (7 - index % 8) & 0x01);
};


char RtBitset::GetByte(unsigned int index)
{
    return this->content[index];
}


void RtBitset::ToggleBit(unsigned int index)
{
    this->content[index / 8] ^= (1 << (7 - index % 8));
}


void RtBitset::SetBit(unsigned int index)
{
    this->content[index / 8] |= (1 << (7 - index % 8));

}

void RtBitset::ClearBit(unsigned int index)
{
    this->content[index / 8] &= ~(1 << (7 - index % 8));
}

void RtBitset::ToggleBits(unsigned int start, unsigned int end)
{
    //location of start and end byte( set everything inbetween)
    unsigned int sLoc = start / 8;
    unsigned int eLoc = end / 8;
    unsigned int delta = end - start;

    if (eLoc != sLoc)
    {

        for (unsigned int i = 0; i < 8 - (start % 8); i++)
        {
            this->content[sLoc] ^= (1 << i);
        }

        unsigned int endRecp = end % 8;
        for (unsigned int i = 0; i < (endRecp + 1); i++)
        {
            this->content[eLoc] ^= 1 << (i + 7 - endRecp);
        }


        for (unsigned int i = 1; i < delta / 8; i++)
        {
            this->content[i + sLoc] ^= 0xff;
        }
    }
    else
    {
        unsigned char mask = 0x00;

        for (unsigned short i = (7 - end % 8); i <= delta; i++)
        {
            this->content[sLoc] ^= 1 << i;
        }

    }

}

//The code below is trash(in the sense that it doesn't make sense), I tried my best to explain it tho
//Also I hate bitwise(kinda)

//Sets bits to 1 in specified range, inclusive
void RtBitset::SetBits(unsigned int start, unsigned int end)
{
    
    //location of start and end byte( set everything inbetween)
    unsigned int sLoc = start / 8;
    unsigned int eLoc = end / 8;
    unsigned int delta = end - start;
    //unsigned int deltaLoc = delta / 8;

    if (eLoc != sLoc)
    {
        /*
        * Decided not to use masks after all, waste of ram tbh
        unsigned char sMask = 0x00;
        unsigned char eMask = 0x00;
        */

       
        //generate mask in starting byte
        for (
            unsigned int i = 0;
            i < 8 - (start % 8);      //until i reaches number of bits in the start byte
            i++)
        {
            this->content[sLoc] |= (1 << i);    //generate the mask from left to right, from the right-most bit
        }

        unsigned short endRecp = end % 8;
        for (
            unsigned int i = 0;
            i < (endRecp + 1);        //refer to above(same thing essentially)
            i++)
        {
            this->content[eLoc] |= 1 << (i + 7 - endRecp);      //also generates from left to right, but does not start at the right-most bit
        }
        /*
        //apply the masks
        this->content[sLoc] |= sMask;
        this->content[eLoc] |= eMask;
        */

        for (
            unsigned int i = 1;     //Starts from 1 because index 0 is supposed to be the start byte, which shouldn't be replaced
            i < delta / 8;          //Iterates though all the bytes between end and start(delta is the bit delta so delta/8 is the byte delta)
            i++)                    //Note that this for loop does not run at all when delta < 2(bytes), which is an intended feature
        {
            this->content[i + sLoc] = 0xff;       //Fill the "inbetween" space with 0xff(11111111), from start to end
        }
    }
    //if startByte and endByte are at the same location
    else
    {

        for (
            unsigned short i = (7 - end % 8);   //starts from the end index, to the start index(both in the local byte)
            i <= delta;                         //iterates to the start index
            i++)
        {
            this->content[sLoc] |= 1 << i;      //replaces the bit with 1
        }


    }
    

    
   
}

//Yes, I just copied everything here, in case you're wondering
void RtBitset::ClearBits(unsigned int start, unsigned int end)
{
    //location of start and end byte( set everything inbetween)
    unsigned int sLoc = start / 8;
    unsigned int eLoc = end / 8;
    unsigned int delta = end - start;

    if (eLoc != sLoc)
    {
        

        //decided to use masks for this since this can reduce number of bitwise operations
        unsigned char sMask = 0x00;
        unsigned char eMask = 0x00;
        



        for (unsigned int i = 0; i < 8 - (start % 8); i++)
        {
            sMask |= (1 << i);
        }

        unsigned short endRecp = end % 8;
        for (unsigned int i = 0; i < (endRecp + 1); i++)
        {
            eMask |= 1 << (i + 7 - endRecp);
        }
        
        //apply the masks
        this->content[sLoc] &= ~sMask;
        this->content[eLoc] &= ~eMask;
        

        for (unsigned int i = 1; i < delta / 8; i++)
        {
            this->content[i + sLoc] = 0xff;
        }
    }
    else
    {
        unsigned char mask = 0x00;
        
        for (unsigned short i = (7 - end % 8); i <= delta;i++)
        {
            mask |= 1 << i;
        }

        this->content[sLoc] &= ~mask;


    }
    
    
}

//Very complex and cool and swag function(hood classic(certified(real(working 2022(no virus(no btc miner))))))
void RtBitset::SetPattern(unsigned int start,     //starting bit
    unsigned int times,                           //times for the pattern to repeat
    unsigned int patternLength,                   //length of pattern
    unsigned long pattern                         //the pattern
)
{



}

void RtBitset::PrintBits()
{
    std::cout << "[";
    for (unsigned int i = 0; i < this->length; i++)
    {
        std::cout << this->operator[](i) << " ";
    }
    std::cout << "]\n";
}

//formatted(like in a matrix and stuff)
void RtBitset::PrintBitsF()
{
    const unsigned int COLUMNS = 8;
    unsigned int len_ctr = this->length;
    using namespace std;

    //std::byte a{ 10 };
    
    
    unsigned int rows = this->length / COLUMNS + (length % COLUMNS == 0 ? 0 : 1);
    //unsigned short recp = length % 8;
    unsigned short padding_len = 1;
    while ((short)(rows / pow(10, padding_len)) > 0)
    {
        padding_len++;
    }
    //cout << padding_len;
    //current number length(10 = 2, 100 = 3, etc)
    unsigned short curr_len = 1;
    //padding for the column indexes indexes
    for (unsigned short i = 0; i < padding_len; i++)
    {
        cout << " ";
    };

    cout << "  0 1 2 3 4 5 6 7\n";
    for (unsigned short i = 0; i < padding_len; i++)
    {
        cout << " ";
    };

    cout << "  ---------------\n";
    for (unsigned short i = 0; i < rows; i++)
    {
        //if a new digit is needed
        if ((short)(i / pow(10, curr_len)) > 0)
        {
            curr_len++;
        }
        //print padding
        for (unsigned short j = 0; j < (padding_len - curr_len); j++)
        {
            cout << " ";
        }

        //index number
        cout << i << "| ";
        

        for (unsigned short j = 0; j < COLUMNS; j++)
        {
            cout << this->GetBit(i * COLUMNS + j) << " ";
        }
        cout << "\n";
    }
}



//not gonna implement this after all cuz u can just view memory lol
//Debug -> Windows -> Memory in case i forgor
void RtBitset::PrintBytes()
{

}


void RtBitset::Compress(
    void* data,                                //Pointer to data(array) to compress
    unsigned int numElements,                  //Number of elements in the array
    unsigned int originalSize,                 //In bytes
    unsigned int compressedSize               //BIT length of each data(use GetMinLength)
    )
{   
    using namespace std;
    //cast the pointer to an unsigned char
    char* data_ptr = (char*)data;
    char a;

    //bytes to check per element
    unsigned int checkedBytes = (compressedSize / 8) + ((compressedSize % 8) == 0 ? 0 : 1);
    //cin >> a;
    
    /*
    cout << "Address of startpoint: " << setw(2) << setfill('0') << hex << (long)data_ptr << endl;
    cout << "Expected endpoint: " << setw(2) << setfill('0') << hex << (long)data_ptr + (dataLength * dataSize) - 1 << endl;
    */


    //iterates through all the elements
    for (unsigned int i = 0; i < numElements; i++)
    {
        unsigned int counter = 0;
        //iterates through each byte of the data block(ignore bytes that shouldn't be checked)
        //Move to the next element if enough bytes are checked OR enough bits are checked
        for (unsigned int j = 0; j < checkedBytes || counter < compressedSize; j++)
        {
               
                unsigned char currentByte = *       //derefrence to get the data in that location
                (
                    data_ptr +                  //pointer to data array
                    (i * originalSize) +            //pointer to current block
                    j                           //pointer to current byte in block
                );      
                //unsigned char* ptr = data_ptr + 
            /*
            PrintByte(currentByte); 
            std::cout << endl;
            char a = 0x00;
            cin >> a;
            */
            
            //iterates though each bit of the byte
            //Move on to next byte if finished checking current byte OR checked enough bits(counter == length)
            //
            for (unsigned short k = 0; k < 8 || counter < compressedSize; k++, counter++)
            {

                if (currentByte >> k & 1)    //If the bit in location k is active
                {
                    //Set bit in bitset
                    this->SetBit(compressedSize * i          //position of the chunk
                        + compressedSize - counter - 1);     //offset by bit
                }
            }
            
            
        }
        
    }


}
//Doesn't really belong here but whatever
unsigned int RtBitset::GetMinLength(
    void* data,                       //pointer to array
    unsigned int dataSize,            //byte size of element in array
    unsigned int length               //number of elements
)
{
    //this works maybe
    char* data_ptr = (char*)data;
    unsigned int iterator = dataSize * length;


    unsigned short highestBit = 0;
    unsigned int highestByte = 0;
    //iterate though elements
    for (unsigned int i = 0; i < length; i++)
    {
        //iterate though bytes in element
        for (unsigned int j = highestByte; j < dataSize; j++)
        {
            char currentByte = *(data_ptr + i * dataSize + j);
            //if the checked byte isn't blank
            if (currentByte != 0x00)
            {
                //set highest byte to j(subsequent checks will start from here) if a new "record" for having the highest nonzero byte is found
                if (highestByte != j)
                {
                    highestByte = j;
                    //also reset the highest bit
                    highestBit = 0;
                }
                
                //iterate through the bits
                //also start from highest bit
                for (unsigned short k = highestBit; k < 8; k++)
                {
                    //if the bit is 1
                    if (currentByte >> k & 1)
                    {
                        //refresh the record
                        highestBit = k;
                    }
                }
            }
        }
    }

    return highestByte * 8 + highestBit + 1;
}



//populates the array pointed to

//MAKE SURE TO ALLOCATE MEMORY FOR THE PTR
//VERY IMPORTANT!!!!
void RtBitset::ParseCompressed(
    void* data,                 //Array of data to write to
    unsigned int numElements,   //Number of elements stored in the compressed bitset
    unsigned int size,           //Size of the original(uncompressed) elements
    unsigned int compressedSize   //Unit size of compressed elemnts
    )
{


    char* data_ptr = (char*)data;
    //bit and byte counters
    unsigned int bit_ctr = 0; 
    unsigned int byte_ctr = 0;
    unsigned short curr_index = 0;
    


    //iterate through the compressed elements
    for (unsigned int i = 0; i < numElements; i++)
    {
        //NOTE: BELOW IS AN UNOPTIMIZED IMPLEMENTATION
        //but i am lazy so too bad

        
        //frail attempt at an actually good one
        /*
        for (unsigned int j = 0; j < compressedSize; j++)
        {
            //iterates through
            bit_ctr++;
            if (bit_ctr > 7)
            {
                bit_ctr = 0;
                byte_ctr++;
            }
            char currentByte = *(data_ptr + byte_ctr); 

        }
        */
        //reset bit counter to 0
        //counts the number of bits checked in a element
        bit_ctr = 1;
        


        //fill in the bytes of each element
        //if filled in enough bytes skip the remaining elements
        for (unsigned int j = 0; j < size; j++)
        {
            //initialize the byte we're working on to 0
            *(data_ptr + i * size + j) = 0x00;

            //keep checking if more bits needs to be checked

            //iterate through each bit 
            for (unsigned short k = 0; k < 8 && bit_ctr <= compressedSize; k++, bit_ctr++)
            {
                curr_index = (i * compressedSize) + compressedSize - bit_ctr;
                if (this->GetBit((i * compressedSize) + compressedSize - bit_ctr))
                {
                    *(data_ptr + i * size + j) |= (1 << k);
                }
                     
            }
            
            


        }
        

    }
}





