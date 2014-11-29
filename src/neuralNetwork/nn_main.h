#ifndef NN_MAIN_H
#define NN_MAIN_H

#define PIXELS 256
#define PTTS 3
#include <stdlib.h>
#include <stdio.h>
#include "network.h"
#include <string.h>

struct s_flags_nn
{
    char **dataset_files;
    long double *inputsFlag;
    int inputsSet;
    int learning;
    int text_to_data;
    int serialize;
};

int nn_main(int argc, char *argv[]);

#endif
