#ifdef _NN_TEST

#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include "network.h"
#include <string.h>

struct s_flags
{
    long double input0;
    long double input1;
    int inputsSet;
    int learning;
    int iterations;
};

#endif
#endif
