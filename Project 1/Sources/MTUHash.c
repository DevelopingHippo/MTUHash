#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// This is Done!
void expansion_operation(int new_block[48], const int old_block[32]) {

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
            new_block[count] = old_block[expanded];
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


void substitute_operation(int new_block[32], const int old_block[48]) {

    int substituted_block[8][6];

    int count = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            substituted_block[i][j] = old_block[count];
        }
    }


    int substituteArray[4][16] = {
            {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0 ,7},
            {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
            {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
            {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    };

    count = 0;
    // Substitution Operation
    for(int i = 0; i < 8; i++)
    {
        int row = (2 * substituted_block[i][0]) + substituted_block[i][5];

        int columnBinary[] = { substituted_block[i][1], substituted_block[i][2], substituted_block[i][3], substituted_block[i][4]};
        int column = convertToBinary(columnBinary);

        new_block[count] = substituted_block[row][column];
    }

}


void XOR_operation(int *fullBlock, int blockCount, int blockToOperateOn) {



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
            for(int j = 0; j < blockCount; j++)
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
        printf("Debug: %d | %d\n", count, intBinaryInput[count]);
        buffer = getchar();
        if( (count != 0) && (count % 32 == 0) && (buffer != '\n'))
        {
            newIntBinaryInput = (int *) malloc ((32 * (blockCount + 1)) * sizeof(int));

            for(int i = 0; i < 32 * blockCount; i++)
            {
                newIntBinaryInput[i] = intBinaryInput[i];
            }
            free(intBinaryInput);
            intBinaryInput = newIntBinaryInput;
            newIntBinaryInput = NULL;
            blockCount++;
        }
        count++;
    }




    hashInput(intBinaryInput, blockCount);

    printf("Hashed Output: ");

    for(int i = 0; i < blockCount * 32; i++)
    {
        printf("%d", intBinaryInput[i]);
    }
    return 0;
}