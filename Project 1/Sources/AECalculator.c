#include "MTUHash.h"
#include <stdio.h>
#include <stdlib.h>


double AFRCalculation(int *finalBlock, int *fullBlock, int blockCount) {

    int *originalBlock;
    originalBlock = (int *) malloc ((32 * (blockCount)) * sizeof(int));

    int *comparisonBlock;
    comparisonBlock = (int *) malloc ((32) * sizeof(int));

    double AFRAverage[(32 * blockCount)];

    // Move Data into Constant originalBlock
    for(int i = 0; i < 32 * blockCount; i++)
    {
        originalBlock[i] = fullBlock[i];
    }

    // First Hash Output
    MTUHash(comparisonBlock, fullBlock, blockCount);

    printf("\nHashed Output: ");
    for(int i = 0; i < 32; i++)
    {
        printf("%d", comparisonBlock[i]);
    }


    // Iterate through each bit and replace it and rehash
    for(int i = 0; i < 32 * blockCount; i++)
    {
        for(int j = 0; j < 32 * blockCount; j++)
        {
            fullBlock[j] = originalBlock[j];
        }
        if(fullBlock[i] == 1)
        {
            fullBlock[i] = 0;
        }
        else
        {
            fullBlock[i] = 1;
        }

        MTUHash(finalBlock, fullBlock, blockCount);

        int sameCount = 0;
        for(int j = 0; j < 32; j++)
        {
            if(comparisonBlock[j] == finalBlock[j])
            {
                sameCount++;
            }
        }
        double AFR = (sameCount / 32.00);
        AFRAverage[i] = AFR;
    }

    // Calculate the Average of all AFR values
    double average = 0;
    for(int i = 0; i < 32 * blockCount; i++)
    {
        average += AFRAverage[i];
    }
    return (average / (32 * blockCount));
}


int main() {

    FILE* inFile;
    FILE* outFile;
    char buffer;

    int *intBinaryInput;
    int *newIntBinaryInput;
    int *finalBlock;
    int *originalBlock;
    finalBlock = (int *) malloc (32 * sizeof(int));
    intBinaryInput = (int *) malloc (32 * sizeof(int));

    int count = 0;
    int blockCount = 1;

    inFile = fopen("C:\\Users\\thadg\\CLionProjects\\MTUHash\\Project 1\\Sources\\Hashin.txt", "r");
    outFile = fopen("C:\\Users\\thadg\\CLionProjects\\MTUHash\\Project 1\\Sources\\AFR.txt", "a");

    if(NULL == inFile)
    {
        printf("\nHashin.txt does not Exist!");
        return 0;
    }

    buffer = fgetc(inFile);
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

    originalBlock = (int *) malloc ((32 * blockCount) * sizeof(int));

    for(int i = 0; i < 32 * blockCount; i++)
    {
        originalBlock[i] = intBinaryInput[i];
    }

    double afraverage = AFRCalculation(finalBlock, intBinaryInput, blockCount);

    fprintf(outFile, "\n%lf = AFR Average from input ", afraverage);
    for(int i = 0; i < 32 * blockCount; i++)
    {
        fprintf(outFile, "%d", originalBlock[i]);
    }

    fclose(outFile);
    return 0;
}