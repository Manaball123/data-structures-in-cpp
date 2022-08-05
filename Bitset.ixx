export module Bitset;

#include "typedefs.hpp"
//#include <stdlib.h>
//#include <memory>


//bitset allocated at runtime
namespace DS
{
    export
    class Bitset
    {


    public:

        //pointer to content on heap
        char* content;

        //note that these 2 indexes are different
        //length in bits
        uint32 length;

        //length in bytes
        uint32 byteLength;





        //Creates a bitset with bit length n
        //len: bit length of bitset
        Bitset(uint32 len)
        {

            this->length = len;
            this->byteLength = (len / 8) + (len % 8 == 0 ? 0 : 1);
            this->content = new char[this->byteLength];
            this->ClearMemory();

        };

        //Creates a bitset with size 0
        Bitset()
        {

            this->length = 0;
            this->byteLength = 0;
            this->content = nullptr;
            //this->ClearMemory();


        };


        //Creates a new bitset and copies the content of the specified bitset over
        //bs: pointer to bitset with content
        Bitset(Bitset* bs)
        {
            this->length = bs->length;
            this->byteLength = bs->byteLength;
            this->content = new char[byteLength];
            
            CopyMemory(this->content, bs->content, bs->byteLength);
        }

        //Expands the bitset to length n
        //len: size to expand to
        int Reallocate(uint32 len)
        {
            uint32 newByteLength = (len / 8) + (len % 8 == 0 ? 0 : 1);
            char* newmem_ptr = new char[newByteLength];



            if (newmem_ptr != nullptr)
            {
                //Copy all bytes over to new position
                CopyMemory(newmem_ptr, this->content, this->byteLength);

                delete[] this->content;
                this->content = newmem_ptr;
                this->length = len;
                this->byteLength = newByteLength;
                return 1;
            }
            else
            {
                return 0;
            }
        }

        //Copies content and other attributes from the specified bitset to the current bitset
        bool Copy(Bitset* bs)
        {
            char* newmem_ptr = new char[bs->byteLength];

            if (newmem_ptr != nullptr)
            {


                this->length = bs->length;
                this->byteLength = bs->byteLength;
                //Copy over the content
                CopyMemory(newmem_ptr, bs->content, bs->byteLength);
                delete[] this->content;
                this->content = newmem_ptr;

                return 1;
            }
            else
            {
                return 0;
            }
        }

        //Its just the destructor what do u want
        ~Bitset()
        {
            delete[] this->content;
        }

        //Returns the state of the specified bit in specified byte 
        //byteIndex: index of byte in the bitset
        //bitIndex: index of bit at the specified byte
        bool GetBit(uint32 byteIndex, uint16 bitIndex)
        {
            return (this->content[byteIndex] >> (7 - bitIndex) & 1);
        };
        //GetBit function but with index
        //
        bool GetBit(uint32 index)
        {
            return (this->content[index / 8] >> (7 - index % 8) & 1);
        };

        bool operator[](uint32 index)
        {
            return (this->content[index / 8] >> (7 - index % 8) & 1);
        };


        char GetByte(uint32 index)
        {
            return this->content[index];
        }


        void ToggleBit(uint32 index)
        {
            this->content[index / 8] ^= (1 << (7 - index % 8));
        }


        void SetBit(uint32 index)
        {
            this->content[index / 8] |= (1 << (7 - index % 8));

        }

        void ClearBit(uint32 index)
        {
            this->content[index / 8] &= ~(1 << (7 - index % 8));
        }



        void ToggleBits(uint32 start, uint32 end)
        {
            //location of start and end byte( set everything inbetween)
            uint32 sLoc = start / 8;
            uint32 eLoc = end / 8;
            uint32 delta = end - start;

            if (eLoc != sLoc)
            {

                for (uint32 i = 0; i < 8 - (start % 8); i++)
                {
                    this->content[sLoc] ^= (1 << i);
                }

                uint32 endRecp = end % 8;
                for (uint32 i = 0; i < (endRecp + 1); i++)
                {
                    this->content[eLoc] ^= 1 << (i + 7 - endRecp);
                }


                for (uint32 i = 1; i < delta / 8; i++)
                {
                    this->content[i + sLoc] ^= 0xff;
                }
            }
            else
            {
                char mask = 0x00;

                for (uint8 i = (7 - end % 8); i <= delta; i++)
                {
                    this->content[sLoc] ^= 1 << i;
                }

            }

        }


        //The code below is trash(in the sense that it doesn't make sense), I tried my best to explain it tho
        //Also I hate bitwise(kinda)

        //Sets bits to 1 in specified range, inclusive
        void SetBits(uint32 start, uint32 end)
        {

            //location of start and end byte( set everything inbetween)
            uint32 sLoc = start / 8;
            uint32 eLoc = end / 8;
            uint32 delta = end - start;
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
                    uint32 i = 0;
                    i < 8 - (start % 8);      //until i reaches number of bits in the start byte
                    i++)
                {
                    this->content[sLoc] |= (1 << i);    //generate the mask from left to right, from the right-most bit
                }

                uint16 endRecp = end % 8;
                for (
                    uint32 i = 0;
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
                    uint32 i = 1;     //Starts from 1 because index 0 is supposed to be the start byte, which shouldn't be replaced
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
                    uint16 i = (7 - end % 8);   //starts from the end index, to the start index(both in the local byte)
                    i <= delta;                         //iterates to the start index
                    i++)
                {
                    this->content[sLoc] |= 1 << i;      //replaces the bit with 1
                }


            }




        }

        //Yes, I just copied everything here, in case you're wondering
        void ClearBits(uint32 start, uint32 end)
        {
            //location of start and end byte( set everything inbetween)
            uint32 sLoc = start / 8;
            uint32 eLoc = end / 8;
            uint32 delta = end - start;

            if (eLoc != sLoc)
            {


                //decided to use masks for this since this can reduce number of bitwise operations
                char mask = 0x00;




                for (uint32 i = 0; i < 8 - (start % 8); i++)
                {
                    mask |= (1 << i);
                }

                uint16 endRecp = end % 8;
                for (uint32 i = 0; i < (endRecp + 1); i++)
                {
                    mask |= 1 << (i + 7 - endRecp);
                }

                //apply the masks
                this->content[sLoc] &= ~mask;
                this->content[eLoc] &= ~mask;


                for (uint32 i = 1; i < delta / 8; i++)
                {
                    this->content[i + sLoc] = 0xff;
                }
            }
            else
            {
                char mask = 0x00;

                for (uint8 i = (7 - end % 8); i <= delta; i++)
                {
                    mask |= 1 << i;
                }

                this->content[sLoc] &= ~mask;


            }


        }

        //Very complex and cool and swag function(hood classic(certified(real(working 2022(no virus(no btc miner))))))
        void SetPattern(uint32 start,     //starting bit
            uint32 times,                           //times for the pattern to repeat
            uint32 patternLength,                   //length of pattern
            uint64 pattern                         //the pattern
        )
        {



        }
        //Debug only aka no
        /*
        void PrintBits()
        {
            std::cout << "[";
            for (unsigned int i = 0; i < this->length; i++)
            {
                std::cout << this->operator[](i) << " ";
            }
            std::cout << "]\n";
        }

        //formatted(like in a matrix and stuff)
        void PrintBitsF()
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




        */
        
        void Compress(
            char* data_ptr,                     //Pointer to data(array) to compress
            uint32 numElements,                 //Number of elements in the array
            uint32 originalSize,                //In bytes
            uint32 compressedSize               //BIT length of each data(use GetMinLength)
        )
        {


            //bytes to check per element
            uint32 checkedBytes = (compressedSize / 8) + ((compressedSize % 8) == 0 ? 0 : 1);
            //cin >> a;
            uint32 counter = 1;
            /*
            cout << "Address of startpoint: " << setw(2) << setfill('0') << hex << (long)data_ptr << endl;
            cout << "Expected endpoint: " << setw(2) << setfill('0') << hex << (long)data_ptr + (dataLength * dataSize) - 1 << endl;
            */


            //iterates through all the elements
            for (uint32 i = 0; i < numElements; i++)
            {
                counter = 1;
                //iterates through each byte of the data block(ignore bytes that shouldn't be checked)
                //Move to the next element if enough bytes are checked OR enough bits are checked
                for (uint32 j = 0; j < checkedBytes && counter <= compressedSize; j++)
                {

                    char currentByte = *   //derefrence to get the data in that location
                        (
                            data_ptr +                  //pointer to data array
                            (i * originalSize) +        //pointer to current block
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
                    for (uint8 k = 0; k < 8 && counter <= compressedSize; k++, counter++)
                    {

                        if (currentByte >> k & 1)    //If the bit in location k is active
                        {

                            //Set bit in bitset
                            this->SetBit(compressedSize * (i + 1)          //position of the chunk
                                - counter);                                //offset by bit

                            //set bit but better
                            ///this->content[compressedSize * i] |= 1 << (compressedSize - counter - 1);
                            //nvm
                        }
                    }


                }

            }


        }
        //Doesn't really belong here but whatever
        uint32 GetMinLength(
            void* data,                           //pointer to array
            uint32 dataSize,                      //byte size of element in array
            uint32 length                         //number of elements
        )
        {
            char* data_ptr = (char*)data;
            //this works maybe

            uint32 iterator = dataSize * length;


            uint16 highestBit = 0;
            uint32 highestByte = 0;
            //iterate though elements
            for (uint32 i = 0; i < length; i++)
            {
                //iterate though bytes in element
                for (uint32 j = highestByte; j < dataSize; j++)
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
                        for (uint16 k = highestBit; k < 8; k++)
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
        void ParseCompressed(
            void* data,                 //Array of data to write to
            uint32 numElements,         //Number of elements stored in the compressed bitset
            uint32 size,                //Size of the original(uncompressed) elements
            uint32 compressedSize       //Unit size of compressed elemnts
        )
        {


            char* data_ptr = (char*)data;
            //bit and byte counters
            uint32 bit_ctr = 0;
            uint32 byte_ctr = 0;
            uint16 curr_index = 0;



            //iterate through the compressed elements
            for (uint16 i = 0; i < numElements; i++)
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
                for (uint32 j = 0; j < size; j++)
                {
                    //initialize the byte we're working on to 0
                    *(data_ptr + i * size + j) = 0x00;

                    //keep checking if more bits needs to be checked

                    //iterate through each bit 
                    for (uint8 k = 0; k < 8 && bit_ctr <= compressedSize; k++, bit_ctr++)
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
        private:
            static void CopyMemory(void* dst, void* src, uint32 len)
            {
                for (uint32 i = 0; i < len; i++)
                {
                    ((char*)dst)[i] = ((char*)src)[i];
                }
            }
            void ClearMemory()
            {
                for (uint32 i = 0; i < this->byteLength; i++)
                {
                    this->content[i] = 0x00;
                }
            }









    };
}




