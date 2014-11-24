#ifdef _NN_TEST

#ifndef MAIN_H
#define MAIN_H
#define PIXELS 256
#define PTTS 3
#include <stdlib.h>
#include <stdio.h>
#include "network.h"
#include <string.h>

struct s_flags
{
    long double *inputsFlag;
    int inputsSet;
    int learning;
    int iterations;
    int text_to_data;
    int serialize;
};

#endif
#endif
