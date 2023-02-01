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
    int binaryInt;
    long binary;

    for(int i = 0; i < 4; i++)
    {
        if(digits[i] == 1)
        {
            binary += pow(1,i * 10);
        }
        printf("%ld", binary);
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


    // Substitution Operation
    for(int i = 0; i < 8; i++)
    {
        int row = (2 * substituted_block[i][0]) + substituted_block[i][5];

        int columnBinary[] = { substituted_block[i][1], substituted_block[i][2], substituted_block[i][3], substituted_block[i][4]};

        int column = convertToBinary(columnBinary);
    }

    count = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            new_block[count] = substituted_block[i][j];
        }
    }

}


void XOR_operation(int new_block[32], int old_block[32]) {


}

void hashInput(int block[32]){

    int expanded_block[48];
    int substituted_block[32];

    expansion_operation(expanded_block, block);
    substitute_operation(substituted_block, expanded_block);

//    for(int i = 0; i < 15; i++)
//    {
//        //substitute_operation(substituted_block, expanded_block);
//        //XOR_operation(block, substituted_block);
//    }
//    XOR_operation(block, block);
}

// This is done!
void reformatInput(const char stringInput[32], int intInput[32]) {
    for(int i = 0; i < 32; i++)
    {
        char compareString = stringInput[i];
        char compareOne = '1';
        char compareZero = '0';

        if(compareString == compareOne)
        {
            intInput[i] = 1;
        }
        else if(compareString == compareZero)
        {
            intInput[i] = 0;
        }
        else
        {
            printf("Input not in Binary Format!");
            exit(0);
        }
    }
}

int main() {
    char binaryStringInput[1000];
    int binaryIntInput[1000];
    int sizeOfInput;
    // Take in user input for the binary string to be hashed
    printf("What is the size of the input message: ");
    scanf("%d", &sizeOfInput);
    printf("What is your input message: ");
    scanf("%s", &binaryStringInput[0]);

    reformatInput(binaryStringInput, binaryIntInput);
    hashInput(binaryIntInput);

    for(int i = 0; i < 32; i++)
    {
        printf("%d", binaryIntInput[i]);
    }

    return 0;
}