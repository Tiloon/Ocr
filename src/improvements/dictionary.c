#include "dictionary.h"

static long double get_matching_word_probability(char *charset,
        size_t charset_count, char *word, long double **chars)
{
    size_t i, j;
    long double probability;

    probability = 1;

    for(i = 0; word[i]; i++)
    {
        for(j = 0; j < charset_count; j++)
        {
            if(charset[j] == word[i])
            {
                if(chars[i][j] <= 0) // Should be chars[i][j] < ceil
                    return 0;

                probability *= chars[i][j];

                break;
            }
        }
    }

    return probability * i; // Probability times word size.
}

char * approcimative_match(long double **chars, size_t count, char *text,
        size_t text_len, struct s_dictionary *dictionary, char *charset,
        size_t charset_count)
{
    size_t index, i;
    long double max, tmp;

    if(count == 0)
        return NULL;


    // TODO
    if((text[text_len] == '.') ||
            (text[text_len] == '?') ||
            (text[text_len] == '!'))
        printf("Commence avec une maj\n");

    max = 0;
    index = dictionary->indexes[count];

    for(i = index; i < dictionary->indexes[count + 1]; i++)
    {
        tmp = get_matching_word_probability(charset, charset_count,
                dictionary->words[i], chars);

        if(tmp > max)
        {
            max = tmp;
            index = i;
        }
    }

    if(max <= 0)
        return NULL;

    return dictionary->words[index];
}

struct s_dictionary * load_dictionary(char *filename)
{
    struct s_dictionary *dictionary;
    struct stat stats;
    char *file, c;
    FILE *fd;
    size_t i, j, k, l;

    i = j = k = l = 0;

    if(stat(filename, &stats) != 0)
        return NULL;

    if(!(dictionary = calloc(1, sizeof(struct s_dictionary))))
    {
        LOG_ALLOC_ERR();
        return NULL;
    }

    if(!(file = calloc(stats.st_size, sizeof(char))))
    {
        FREE(dictionary);
        LOG_ALLOC_ERR();
        return NULL;
    }

    if(!(fd = fopen(filename, "r")))
    {
        FREE(file);
        FREE(dictionary);
        LOG_ALLOC_ERR();
        return NULL;
    }

    while(!feof(fd))
    {
        c = fgetc(fd);
        if(c == '\n')
        {
            file[i] = 0;
            dictionary->words = realloc(dictionary->words, (j + 2) *
                    sizeof(char*));
            dictionary->words[j] = file + i + 1;
            if(k > l)
            {
                dictionary->indexes = realloc(dictionary->indexes, (k + 2) *
                        sizeof(size_t));

                for(++l; l < k; l++)
                    dictionary->indexes[l] = 0;

                dictionary->indexes[k] = j;
            }
            j++;
            k = 0;
        }
        file[i] = c;
        i++;
        k++;
    }

    fclose(fd);

    return dictionary;
}































