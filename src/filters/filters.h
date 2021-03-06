#ifndef FILTERS_H
#define FILTERS_H

#include <gdk-pixbuf/gdk-pixbuf.h>

#include "../main.h"
#include "../redef.h"

#include "sample_filter.h"
#include "gaussian_filter.h"
#include "rot_filter.h"
// Every other filter

/*
 * Filters are function of this kind :
 * ErrorCode = Filter(Picture, parameters);
 *
 * parameter is a string of the format 'parm1=0,parm1="fze"'
 */
typedef int (t_filter)(GdkPixbuf**, size_t, char**);

struct s_filter_entry
{
    t_filter *filter_func;
    char *filter_name;
#ifndef NOHELP
    char *filter_help_message;
#endif
};

void print_filter_error(const char *str, const char *filter_name);
int filters_apply_all(GdkPixbuf **picture);
int filter_add(char *name);

#ifndef NOHELP
int filter_make_help(char ***keywords, char ***message);
#endif

#endif
