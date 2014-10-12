#include "filters.h"
#include <stdlib.h>

const struct s_filter_entry filter_list[] = {
    {sample_filter, sample_filter_name, sample_filter_help_msg}
    // Other filters...
};

static char **filter_stack = NULL;

int get_filter_about(unsigned int id, char **name, char **help)
{
    // If id > filter_list.length, return fail
    if(id > (sizeof(filter_list) / sizeof(*filter_list)))
        return 1;

    if(name != NULL)
        *name = filter_list[id].filter_name;

    if(help != NULL)
        *help = filter_list[id].filter_help_message;
    return 0;
}


void print_filter_error(const char *str, const char *filter_name)
{
    fprintf(stderr, "Filter error (%s) : %s", filter_name, str);
}

int filters_apply_all(GdkPixbuf *picture)
{
    unsigned int i;
    printf("%p", picture);
    for(i = 0; filter_stack[i] != 0; i++)
    {
    }

    return 0;
}

int filter_add(char *name)
{
    static int filter_stack_count;
    char **tmp;
    unsigned int i;

    if(filter_stack == NULL)
    {
        filter_stack = malloc(2*sizeof(char**));
        filter_stack[0] = name;
        filter_stack[1] = NULL;
        filter_stack_count = 1;
        return 0;
    }

    tmp = filter_stack;
    filter_stack_count++;
    filter_stack = malloc((filter_stack_count + 1) * sizeof(char*));
    if(filter_stack == NULL)
    {
        fprintf(stderr, "malloc error : %d@%s", __LINE__, __FILE__);
        return 1;
    }
    for(i = 0; tmp[i] != NULL; i++)
        filter_stack[i] = tmp[i];
    filter_stack[filter_stack_count] = name;
    filter_stack[filter_stack_count] = NULL;
    free(tmp);

    return 0;
}
