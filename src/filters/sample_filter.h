#ifndef SAMPLE_FILTER_H
#define SAMPLE_FILTER_H

#include "filters.h"

static char sample_filter_name[] = "sample_filter";

#ifndef NOHELP

static char sample_filter_help_msg[] =
    "Sample filter\n\n"
    "This filter is just a sample. The only way it affects pictures is by"
    "changing\ndarkest pixels to black and the others to white. The default"
    "ceil is 50\% but\nyou can change it with \"ceil=xx\" where xx is the new"
    "ceil percentage.\n\n"
    "Authors :\n"
    "  - Pimzero\n";

#endif

extern int sample_filter(GdkPixbuf **picture, size_t nb_params,
        char **params);


#endif
