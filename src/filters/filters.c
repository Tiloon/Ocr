#include "filters.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glib.h>

#define FILTER_LIST_SZE 1

const struct s_filter_entry filter_list[] = {
    {sample_filter, sample_filter_name, sample_filter_help_msg}
    // Other filters...
};

struct s_filter_rule
{
    size_t param_count;
    char *name;
    char **params;
};

struct s_filter_rule **filter_stack = NULL;


int filter_get_id(const char *name)
{
    unsigned int i;
    for(i = 0; i < FILTER_LIST_SZE; i++)
    {
        if(strcmp(name, filter_list[i].filter_name) == 0)
            return i;
    }

    // Filer not found
    return -1;
}

struct s_filter_rule* filter_get_rule(char *rule)
{
    size_t i;
    struct s_filter_rule *filter = calloc(1, sizeof(struct s_filter_rule));
    filter->name = rule;
    for(i = 0; rule[i]; i++)
    {
        if(rule[i] == ',')
        {
            filter->params = realloc(filter->params,
                    (1 + filter->param_count) * sizeof(char*));
            rule[i] = 0;
            filter->params[filter->param_count] = rule + i + 1;
            (filter->param_count)++;
            i++;
        }
        //rule[i] = 0;
    }

    if(!rule[i])
        return filter;

    return filter;
}

int get_filter_about(unsigned int id, char **name, char **help)
{
    // If id > filter_list.length, return fail
    if(id > FILTER_LIST_SZE)
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
    int id;
    struct s_filter_rule* filter;

    if(filter_stack == NULL)
        return 0;

    for(i = 0; filter_stack[i] != NULL; i++)
    {
        filter = filter_stack[i];
        if(FLAGS->verbosity)
            printf("Applying \"" CYAN "%s" RESET "\"\n", filter->name);
        id = filter_get_id(filter->name);
        if(filter_list[id].filter_func(picture, filter->param_count,
                    filter->params))
            return 1;
    }

    return 0;
}

// Filter : filter_name:param1,param2
int filter_add(char *rule)
{
    static int filter_stack_count;
    struct s_filter_rule* filter;

    filter = filter_get_rule(rule);
    if(filter_get_id(filter->name) < 0)
    {
        print_filter_error("Filter doesn't exists.\n", filter->name);
        return 1;
    }

    filter_stack = realloc(filter_stack, (filter_stack_count + 2) *
            sizeof(struct s_filter_rule));
    if(filter_stack == NULL)
    {
        fprintf(stderr, "malloc error : %d@%s", __LINE__, __FILE__);
        return 1;
    }
    filter_stack[filter_stack_count] = filter;
    filter_stack[filter_stack_count + 1] = NULL;
    filter_stack_count++;

    return 0;
}
