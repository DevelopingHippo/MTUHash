#include <stdio.h>
#include <stdlib.h>

// This is Done!
void expansion_operation(int expanded_block[48], const int portion_block[32]) {

    // Expansion Array
    int expansionArray[8][6] = {
            {32, 1, 2, 3, 4, 5},
            {4, 5, 6, 7, 8, 9},
            {8, 9, 10, 11, 12, 13},
            {12, 13, 14, 15, 16, 17},
            {16, 17, 18, 19, 20, 21},
            {20, 21, 22, 23, 24, 25},
            {24, 25, 26, 27, 28,29},
            {28, 29, 30, 31, 32, 1}
    };

    int count = 0;

    // Expansion Operation
    for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++)
        {
            int expanded = expansionArray[i][j] - 1;
            expanded_block[count] = portion_block[expanded];
            count++;
        }
    }
}


int convertToBinary(const int digits[4]) {
    int binaryInt = 0;

    if(digits[0] == 1)
    {
        binaryInt += 8;
    }
    if(digits[1] == 1)
    {
        binaryInt += 4;
    }
    if(digits[2] == 1)
    {
        binaryInt += 2;
    }
    if(digits[3] == 1)
    {
        binaryInt += 1;
    }
    return binaryInt;
}

void intToBinary(int integer, int minorBlock[4])
{
    if(integer == 15)
    {
        minorBlock[0] = 1;
        minorBlock[1] = 1;
        minorBlock[2] = 1;
        minorBlock[3] = 1;
    }
    else if(integer == 14)
    {
        minorBlock[0] = 1;
        minorBlock[1] = 1;
        minorBlock[2] = 1;
        minorBlock[3] = 0;
    }
    else if(integer == 13)
    {
        minorBlock[0] = 1;
        minorBlock[1] = 1;
        minorBlock[2] = 0;
        minorBlock[3] = 1;
    }
    else if(integer == 12)
    {
        minorBlock[0] = 1;
        minorBlock[1] = 1;
        minorBlock[2] = 0;
        minorBlock[3] = 0;
    }
    else if(integer == 11)
    {
        minorBlock[0] = 1;
        minorBlock[1] = 0;
        minorBlock[2] = 1;
        minorBlock[3] = 1;
    }
    else if(integer == 10)
    {
        minorBlock[0] = 1;
        minorBlock[1] = 0;
        minorBlock[2] = 1;
        minorBlock[3] = 0;
    }
    else if(integer == 9)
    {
        minorBlock[0] = 1;
        minorBlock[1] = 0;
        minorBlock[2] = 0;
        minorBlock[3] = 1;
    }
    else if(integer == 8)
    {
        minorBlock[0] = 1;
        minorBlock[1] = 0;
        minorBlock[2] = 0;
        minorBlock[3] = 0;
    }
    else if(integer == 7)
    {
        minorBlock[0] = 0;
        minorBlock[1] = 1;
        minorBlock[2] = 1;
        minorBlock[3] = 1;
    }
    else if(integer == 6)
    {
        minorBlock[0] = 0;
        minorBlock[1] = 1;
        minorBlock[2] = 1;
        minorBlock[3] = 0;
    }
    else if(integer == 5)
    {
        minorBlock[0] = 0;
        minorBlock[1] = 1;
        minorBlock[2] = 0;
        minorBlock[3] = 1;
    }
    else if(integer == 4)
    {
        minorBlock[0] = 0;
        minorBlock[1] = 1;
        minorBlock[2] = 0;
        minorBlock[3] = 0;
    }
    else if(integer == 3)
    {
        minorBlock[0] = 0;
        minorBlock[1] = 0;
        minorBlock[2] = 1;
        minorBlock[3] = 1;
    }
    else if(integer == 2)
    {
        minorBlock[0] = 0;
        minorBlock[1] = 0;
        minorBlock[2] = 1;
        minorBlock[3] = 0;
    }
    else if(integer == 1)
    {
        minorBlock[0] = 0;
        minorBlock[1] = 0;
        minorBlock[2] = 0;
        minorBlock[3] = 1;
    }
    else if(integer == 0)
    {
        minorBlock[0] = 0;
        minorBlock[1] = 0;
        minorBlock[2] = 0;
        minorBlock[3] = 0;
    }
}


void substitute_operation(int portion_block[32], const int expanded_block[48]) {

    int substituted_block[8][6];

    int count = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            substituted_block[i][j] = expanded_block[count];
        }
    }


    int substituteArray[4][16] = {
            {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0 ,7},
            {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
            {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
            {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    };

    // Substitution Operation
    for(int i = 0; i < 8; i++)
    {
        int row = (2 * substituted_block[i][0]) + substituted_block[i][5];

        int columnBinary[] = { substituted_block[i][1], substituted_block[i][2], substituted_block[i][3], substituted_block[i][4]};
        int column = convertToBinary(columnBinary);

        int minorBlock[4];

        intToBinary(substituted_block[row][column], minorBlock);

        for(int j = 1; j < 5; j++)
        {
            substituted_block[i][j] = minorBlock[j - 1];
        }
    }

    count = 0;
    for(int i = 0; i < 8; i++)
    {
        portion_block[count] = substituted_block[i][1];
        count++;
        portion_block[count] = substituted_block[i][2];
        count++;
        portion_block[count] = substituted_block[i][3];
        count++;
        portion_block[count] = substituted_block[i][4];
        count++;
    }

}


void XOR_operation(int *fullBlock, int blockCount, int blockToOperateOn) {

    // If there is only 2 total blocks
    if(blockCount == 2)
    {
        // swap bit placement with second block
        for(int i = 0; i < 32; i++)
        {
            int buffer = fullBlock[i];
            fullBlock[i] = fullBlock[i + 32];
            fullBlock[i + 32] = buffer;
        }
    }
    else
    {
        // Iterate through each block
        for(int i = 0; i < blockCount - 1; i++)
        {
            // If the operatedBlock is not selected
            if(i != blockToOperateOn)
            {
                // For each bit
                for(int j = 0; j < 32; j++)
                {
                    // If the bit is the same as the bit in the other block replace with 0
                    if((fullBlock[j + ((blockToOperateOn) * 32)] == 1 && fullBlock[j + (i * 32)] == 1) || (fullBlock[j + ((blockToOperateOn) * 32)] == 0 && fullBlock[j + (i * 32)] == 0) )
                    {
                        fullBlock[j + ((blockToOperateOn) * 32)] = 0;
                    }
                    // if not replace with 1
                    else
                    {
                        fullBlock[j + ((blockToOperateOn) * 32)] = 1;
                    }
                }
            }
        }
    }
}

void hashInput(int *fullBlock, const int blockCount){

    int expanded_block[48];
    int portionBlock[32];


    for(int i = 0; i < 15; i++)
    {
        // If only 1 block only do substitution and expansion, no XOR
        if(blockCount == 1)
        {
            expansion_operation(expanded_block, fullBlock);
            substitute_operation(fullBlock, expanded_block);
        }
        else
        {
            // Start Iterating through each block
            for(int j = 0; j < blockCount - 1; j++)
            {
                // Move the block from the fullBlock to the portionBlock
                for(int x = 0; x < 32; x++)
                {
                    portionBlock[x] = fullBlock[ x + (32 * j)];
                }

                expansion_operation(expanded_block, portionBlock);
                substitute_operation(portionBlock, expanded_block);

                // Move the changed portionBlock values back into the fullBlock
                for(int x = 0; x < 32; x++)
                {
                    fullBlock[32 * j] = portionBlock[x];
                }

                //Preform XOR operation
                XOR_operation(fullBlock, blockCount, j);
            }
        }
    }

    // Final XOR operation
    for(int i = 0; i < blockCount; i++)
    {
        XOR_operation(fullBlock, blockCount, i);
    }
}


int main() {


    printf("What binary input would you like to be hashed?\n");

    int *intBinaryInput;
    int *newIntBinaryInput;

    intBinaryInput = (int *) malloc (32 * sizeof(int));

    int count = 0;
    int blockCount = 1;
    char buffer;
    buffer = getchar();
    while(buffer != '\n')
    {
        if(buffer == '1')
        {
            intBinaryInput[count] = 1;
        }
        else if(buffer == '0')
        {
            intBinaryInput[count] = 0;
        }
        else
        {
            printf("Input not in Binary Format!");
            return 0;
        }
        buffer = getchar();
        count++;
        if( (count % 32 == 0) && (buffer != '\n') )
        {
            newIntBinaryInput = (int *) malloc ((32 * (blockCount + 1)) * sizeof(int));

            for(int i = 0; i < 32 * blockCount; i++)
            {
                newIntBinaryInput[i] = intBinaryInput[i];
            }
            free(intBinaryInput);
            intBinaryInput = newIntBinaryInput;
            blockCount++;
        }
    }

    hashInput(intBinaryInput, blockCount);

    printf("\nHashed Output: ");

    for(int i = 0; i < blockCount * 32; i++)
    {
        printf("%d", intBinaryInput[i]);
    }
    return 0;
}