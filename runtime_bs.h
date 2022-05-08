
#include "stdlib.h"
//bitset allocated at runtime
namespace BS
{
    class RtBitset
    {
       
        

        public:
            RtBitset(unsigned int len);
            RtBitset(RtBitset* bs);
            RtBitset();
            ~RtBitset();
            //pointer to content on heap
            unsigned char* content;

            //length in bits
            unsigned int length;

            //length in bytes
            unsigned int byteLength;

            //note that these 2 indexes are different
            //USED FOR GETTING A BIT ONLY, DO NOT USE FOR SET BIT
            bool operator[](unsigned int index);

            bool GetBit(unsigned int byteIndex);
            bool GetBit(unsigned int byteIndex, unsigned short bitIndex);

            //Gets a "chunk" of data from the bitset
            char GetByte(unsigned int index);

            void ToggleBit(unsigned int index);

            void SetBit(unsigned int index);

            void ClearBit(unsigned int index);

            void ToggleBits(unsigned int start, unsigned int end);
            void SetBits(unsigned int start, unsigned int end);
            void ClearBits(unsigned int start, unsigned int end);

            //no
            void SetPattern(unsigned int start, unsigned int times, unsigned int patternLength, unsigned long pattern);

            void PrintBits();

            
            void PrintBytes();

            void PrintBitsF();

            void PrintBytesF();

            //Note that this overrides the current values in the bitset
            void Compress(
                void* data,                                //Pointer to data(array) to compress
                unsigned int numElements,                  //Number of elements in the array
                unsigned int originalSize,                 //In bytes
                unsigned int compressedSize               //BIT length of each data(use GetMinLength)
                );

            //Returns the minimal amount of bits required to represent an array of information
            static unsigned int GetMinLength(
                void* data,                       //pointer to array
                unsigned int dataSize,            //byte size of element in array
                unsigned int length               //number of elements
            );

            
            void ParseCompressed(
                void* data,                 //Array of data to write to
                unsigned int numElements,   //Number of elements stored in the compressed bitset
                unsigned int size,           //Size of the original(uncompressed) elements
                unsigned int compressedSize   //Unit size of compressed elemnts
            );

            bool Reallocate(unsigned int len);


    };
}




