#ifndef FILTERS_H
#define FILTERS_H

#include <gdk-pixbuf/gdk-pixbuf.h>
#include "../main.h"

#include "sample_filter.h"
// Every other filter

/*
 * Filters are function of this kind :
 * ErrorCode = Filter(Picture, parameters);
 *
 * parameter is a string of the format 'parm1=0,parm1="fze"'
 */
typedef int (t_filter)(GdkPixbuf*, size_t, char**);

struct s_filter_entry
{
    t_filter *filter_func;
    char *filter_name;
    char *filter_help_message;
};


int get_filter_about(unsigned int id, char **name, char **help);
void print_filter_error(const char *str, const char *filter_name);
int filters_apply_all(GdkPixbuf *picture);
int filter_add(char *name);

#endif
