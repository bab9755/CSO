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
    printf("\n");
}

long int_multiply(int x, int y){
   

    long lx = (long)x;
    long ly = (long)y;
    long result = 0;

    for (int i = 0; i < 32; i++) {
        long mask = (long)1 << i;
        if ((ly & mask) != 0) {
            result += lx;
        }
        lx <<= 1;
    }

    return result;

    // long lx = x;
    // long ly = y;
    // long result = 0;
    // for(int i = sizeof(long); i >= 0; i--){
    //     if(ly & 1){
    //         result += lx;
    //     }
    //     lx <<= 1;
    //     ly >>= 1;
    // }
    // return result;

}

float float_multiply(float a, float b){
    unsigned int val_a = *((unsigned int*) &a); //type cast a into a float and dereference it
    unsigned int val_b = *((unsigned int*) &b);

    if(val_a == 0 || val_b == 0){
        return 0.0;
    }
    unsigned int exp_a = (val_a >> 23) & 0xFF; //the mask corresponds to  11111111
    unsigned int mant_a = val_a & 0x007FFFFF; //the mask corresponds to 23 one's
    unsigned int exp_b = (val_b >> 23) & 0xFF;
    unsigned int mant_b = val_b & 0x007FFFFF;

    unsigned int exp_result = exp_a + exp_b - 127; //get the exponent for the result

    unsigned int mant_a_with_1 = (mant_a | (1 << 23)); //set the 24th bit to 1
    unsigned int mant_b_with_1 = (mant_b | (1 << 23));
    unsigned long mant_result = int_multiply(mant_a_with_1, mant_b_with_1); 
    //shift the result right by 23
    mant_result >>= 23;
    if ((mant_result & (1 << 24)) != 0) {
        mant_result >>= 1;
        exp_result++;
    }
    unsigned int mant_result_32 = (unsigned int)mant_result;
    //extracting the signs for both a and b
    unsigned int sign_a = (val_a >> 31) & 1;
    unsigned int sign_b = (val_b >> 31) & 1;
    unsigned int sign_result = sign_a ^ sign_b;
    //get the int result for the float
    unsigned int result = (sign_result << 31) | (exp_result << 23) | mant_result_32;


    return *((float*) &result); //typecase into a float and return


}
