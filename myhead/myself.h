//
// Created by liam on 9/6/21.
//
#include <stdio.h>

#ifndef SINGLE_MYSELF_H
#define SINGLE_MYSELF_H

#define MAX(X, Y) ((X)>(Y)?(X):(Y))
#define ABS(X) ((X)>0?(X):-(X))
#define IS_SIGN(X) ((X)=='+'||(X)=='-'?1:0)

typedef char *BI_STRING;

char *StrGet(char *str, int n, FILE *fp);

int BiStrToInt(BI_STRING b, int bits);

BI_STRING IntToBiString(int x);

void ShowBiString(BI_STRING b);

#endif//SINGLE_MYSELF_H
