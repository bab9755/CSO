#include <stdio.h> // to use printf and scanf
#include <stdlib.h> // to use malloc
#include <string.h> // to use strlen, strcmp, and strcpy
#include "functions.h"

#define MASK 0xF

void print_bits(int x){
    for(int i=sizeof(int); i >= 0; i--){
        if(x & (1 << i)){
            printf("1");
        } else{
            printf("0"); 
        }
    }
}

int64_t int_multiply(int32_t x, int32_t y){
    int64_t lx = x;
    int64_t ly = y;
    int64_t result = 0;
    for(int i = sizeof(int64_t); i >= 0; i--){
        if(ly >> i & 1){
            result += lx;
        }
        lx <<= 1;
        ly >>= 1;
    }
    return result;
}
