#ifndef NOHELP

#include "help.h"
#include <strings.h>

#include "../filters/filters.h"

int make_help(char ***keywords, char ***messages)
{
    int i, j, k;
    char **tmp_keywords, **tmp_messages;

    (*keywords) = NULL;
    (*messages) = NULL;
    j = 0;

    // loop over make_helps

    if((i = filter_make_help(&tmp_keywords, &tmp_messages)) < 0)
    {
        FREE(tmp_keywords);
        FREE(tmp_messages);
        FREE(keywords);
        FREE(messages);
        return -1;
    }
    *keywords = realloc(*keywords, (i + j) * sizeof(char*));
    *messages = realloc(*messages, (i + j) * sizeof(char*));

    for(k = 0; k < i; k++)
    {
        (*keywords)[j + k] = tmp_keywords[k];
        (*messages)[j + k] = tmp_messages[k];
    }

    j += i;

    FREE(tmp_keywords);
    FREE(tmp_messages);

    // End loop

    return j;
}

void show_all_keywords(char **keywords, size_t nb_helps)
{
    size_t i;
    printf("Keyword list :\n");
    for(i = 0; i < nb_helps; i++)
        printf(" - %s\n", keywords[i]);
}

int show_help(char *keyword)
{
    char **keywords, **messages;
    int nb_helps, i;

    nb_helps = make_help(&keywords, &messages);

    if(!nb_helps)
    {
        fprintf(stderr, "Can't show help: no help\n");
    }
    if(keyword == 0)
    {
        printf("No keyword specified.\n");
        show_all_keywords(keywords, nb_helps);
        return 0;
    }

    for(i = 0; i < nb_helps; i++)
    {
        if(!strcasecmp(keyword, keywords[i]))
        {
            printf("help : %s\n\n%s\n", keywords[i], messages[i]);
            return 0;
        }
    }

    printf("Keyword \"%s\": no help found\n", keyword);
    return 1;
}

#endif
