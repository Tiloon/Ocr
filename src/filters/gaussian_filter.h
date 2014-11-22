#ifndef GAUSSIAN_FILTER_H
#define GAUSSIAN_FILTER_H

#include "filters.h"

static char gaussian_filter_name[] = "gaussian_filter";
static char gaussian_filter_help_msg[] =
    "Gaussian filter\n\n"
    "This filter could be used to remove artifacts in the picture.\n"
    "Usage : \"gaussain_filter\" or \"gaussian_filter,size\"\nwhere size is"
    "the dimension of gaussian blur matrix.\nMore information : this filter "
    "O(2N)\n"
    "Authors :\n"
    "  - Pimzero\n";

extern int gaussian_filter(GdkPixbuf *picture, size_t nb_params, char **params);


#endif
