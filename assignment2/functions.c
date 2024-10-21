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

long int_multiply(long x, long y){
    long lx = x;
    long ly = y;
    long result = 0;
    for(int i = sizeof(long); i >= 0; i--){
        if(ly & 1){
            result += lx;
        }
        lx <<= 1;
        ly >>= 1;
    }
    return result;
}

float float_multiply(float a, float b){
    float val_a = a;
    float val_b = b;
    float result = 0;
}
