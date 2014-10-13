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

static char **filter_stack = NULL;


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

char* filter_get_name(char *rule, char **params)
{
    unsigned int i;
    char *filtername;

    for(i = 0; rule[i] && (rule[i] != ','); i++)
        ;

    // no params => *params = "\0"
    // else params is set after the first comma.
    if(params)
        *params = rule + i + (!rule[i]);

    if(!rule[i])
        return rule;

    filtername = malloc(sizeof(char) * i);
    strncpy(filtername, rule, i - 1);
    filtername[i - 1] = 0;

    return filtername;
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
    char *params;

    if(filter_stack == NULL)
        return 0;

    for(i = 0; filter_stack[i] != NULL; i++)
    {
        id = filter_get_id(filter_get_name(filter_stack[i], &params));
        if(filter_list[id].filter_func(picture, params))
            return 1;
    }

    return 0;
}

int filter_add(char *rule)
{
    static int filter_stack_count;
    char **tmp;
    unsigned int i;
    char* filtername;

    filtername = filter_get_name(rule, NULL);
    if(filter_get_id(filtername) < 0)
    {
        print_filter_error("Filter doesn't exists.\n", filtername);
        return 1;
    }

    if(filter_stack == NULL)
    {
        filter_stack = malloc(2*sizeof(char**));
        filter_stack[0] = rule;
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
    filter_stack[filter_stack_count] = rule;
    filter_stack[filter_stack_count] = NULL;
    free(tmp);

    return 0;
}
