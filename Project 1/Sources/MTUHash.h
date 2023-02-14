//
// Created by thadg on 2/3/2023.
//

#ifndef MTUHASH_MTUHASH_H
#define MTUHASH_MTUHASH_H

void expansion_operation(int *expanded_block, const int portion_block[32]);
int binaryToInt(const int digits[4]);
void intToBinary(int integer, int minorBlock[4]);
void substitute_operation(int *portion_block, const int expanded_block[48]);
void XOR_operation(int *fullBlock, int blockCount, int blockToOperateOn);
void final_XOR_operation(int *finalBlock, int *fullBlock, int blockCount);
void MTUHash(int *finalBlock, int *fullBlock, int blockCount);

#endif //MTUHASH_MTUHASH_H
