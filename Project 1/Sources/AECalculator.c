#include "MTUHash.h"
#include <stdio.h>
#include <stdlib.h>








int main() {

    FILE* inFile;
    FILE* outFile;
    char buffer;

    int *intBinaryInput;
    int *newIntBinaryInput;
    int *finalBlock;

    finalBlock = (int *) malloc (32 * sizeof(int));
    intBinaryInput = (int *) malloc (32 * sizeof(int));

    int count = 0;
    int blockCount = 1;

    inFile = fopen("C:\\Users\\thadg\\CLionProjects\\MTUHash\\Project 1\\Sources\\Hashin.txt", "r");
    outFile = fopen("AFR.txt", "w");



    if(NULL == inFile)
    {
        printf("\nHashin.txt does not Exist!");
        return 0;
    }

    buffer = fgetc(inFile);
    while(buffer != '\n')
    {
        printf("%c", buffer);
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
        buffer = fgetc(inFile);
        if(buffer == EOF)
        {
            break;
        }
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
    fclose(inFile);

    MTUHash(finalBlock, intBinaryInput, blockCount);


    printf("\nFinal Output: ");
    for(int i = 0; i < 32; i++)
    {
        printf("%d", finalBlock[i]);
    }

    fclose(outFile);
    return 0;
}

