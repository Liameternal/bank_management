//
// Created by liam on 9/6/21.
//
#include "myself.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <tgmath.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int OnBit(int x, int bit);

void RotateL(int x, int bit);

int main(void) {
    printf("the func abs(-1) is %d\n", ABS(-1));
    printf("The max one between %d an %d is %d\n", 3, 5, MAX(3, 5));
    char ch='*';
    if (IS_SIGN(ch))
        printf("%c is a sign\n",ch);
    else
        printf("%c is not a sign\n",ch);

    return 0;
}

int OnBit(int x, int bit) {
    BI_STRING b = IntToBiString(x);
    if (b[sizeof(int) * CHAR_BIT - bit] == '1')
        return 1;
    return 0;
}

void RotateL(int x, int bit) {
    BI_STRING b = IntToBiString(x);
    char ch;
    int k;
    for (int i = 0; i < bit; ++i) {
        for (int j = 0; j < sizeof(int) * CHAR_BIT - 1; ++j) {
            k = j + 1;
            ch = b[j];
            b[j] = b[k];
            b[k] = ch;
        }
    }
    ShowBiString(b);
}