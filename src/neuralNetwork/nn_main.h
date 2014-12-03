#ifndef NN_MAIN_H
#define NN_MAIN_H

#define PTTS 3

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "consts.h"
#include "network.h"

struct s_flags_nn
{
    char **dataset_files;
    int learning;
    int serialize;
};

void print_matching_char(long double *vector, size_t size, struct s_network
        *network);
int nn_main(int argc, char *argv[]);
void print_nn_help(void);

#endif
