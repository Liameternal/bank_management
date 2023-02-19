//
// Created by liam on 9/6/21.
//

#include "myself.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

char *StrGet(char *str, int n, FILE *fp) {
    char *ret_val;
    char *find;
    ret_val = fgets(str, n, fp);
    if (ret_val) {
        find = strchr(str, '\n');
        if (find)
            *find = '\0';
        else {
            while (fgetc(fp) != '\n')
                continue;
        }
    }

    return ret_val;
}

int BiStrToInt(BI_STRING b, int bits) {
    int num[bits];
    int total = 0;
    for (int i = 0; i < bits; ++i) {
        num[i] = b[i] - '0';
    }
    int i = bits - 1;
    int j = 0;
    for (; i >= 0; --i, ++j) {
        total += num[i] * pow(2, j);
    }
    return total;
}

BI_STRING IntToBiString(int x) {
    const static int size = sizeof(int) * CHAR_BIT;
    BI_STRING b = (BI_STRING)malloc((size + 1) * sizeof(char));
    if(!b)
        fprintf(stderr,"Malloc failed!\n");
    for (int i = size - 1; i >= 0; --i) {
        b[i] = (x & 01) + '0';
        x >>= 1;
    }
    b[size] = '\0';
    return b;
}

void ShowBiString(BI_STRING b) {
    printf("%s\n", b);
}
