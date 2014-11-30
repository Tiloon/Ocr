#ifndef ROT_FILTER_H
#define ROT_FILTER_H

#include "filters.h"

static char rot_filter_name[] = "rot_filter";

#ifndef NOHELP

static char rot_filter_help_msg[] =
    "Rot filter\n\n"
    "This filter is a filter that will detect the rotation of the image\nand apply the rotation so that the image is in the right rotation.\n"
    ""
    ""
    "\n"
    "Authors :\n"
    "  - Cyril\n";

#endif

extern int rot_filter(GdkPixbuf *picture, size_t nb_params, char **params);


#endif

