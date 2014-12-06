#include "dictionary.h"

static long double get_char_probability(wchar_t c, wchar_t *charset,
        size_t charset_count, long double *chars)
{
    size_t i;
    for(i = 0; i < charset_count; i++)
    {
        if(charset[i] == c)
            return chars[i];
    }

    return -1;
}

static long double get_matching_word_probability(wchar_t *charset,
        size_t charset_count, wchar_t *word, long double **chars,
        long double seil)
{
    size_t i;
    long double probability;

    probability = 1;

    for(i = 0; word[i] && chars[i]; i++)
    {
        if(probability < seil)
            return 0;

        probability *= get_char_probability(word[i], charset, charset_count, chars[i]);
    }

    return probability; // Probability times word size.
}

wchar_t * approcimative_match(long double **chars, size_t count,
        struct s_dictionary *dictionary, wchar_t *charset,
        size_t charset_count)
{
    size_t index, i;
    long double max, tmp;

    if(count == 0)
        return NULL;

    max = 0;

    if(count > dictionary->index_max)
        return NULL;

    index = dictionary->indexes[count];

    for(i = index; i < dictionary->indexes[count + 1]; i++)
    {
        tmp = get_matching_word_probability(charset, charset_count,
                dictionary->words[i], chars, max);

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
    wchar_t *file;
    wint_t c;
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

    if(!(file = calloc(stats.st_size, sizeof(wchar_t))))
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

    dictionary->indexes = calloc(2, sizeof(size_t));

    while((c = getwc(fd)) != WEOF)
    {
        if(c == '\n')
        {
            file[i] = 0;
            dictionary->words = realloc(dictionary->words, (j + 2) *
                    sizeof(wchar_t*));
            dictionary->words[j] = file + i + 1;
            if(k > l)
            {
                dictionary->indexes = realloc(dictionary->indexes, (k + 2) *
                        sizeof(size_t));

                for(++l; l < k; l++)
                    dictionary->indexes[l] = 0;

                dictionary->indexes[k] = j;
                dictionary->indexes[k + 1] = 0;
                dictionary->index_max = k;
            }
            j++;
            i++;
            k = 0;
        }
        else
        {
            file[i] = c;
            i++;
            k++;
        }
    }

    fclose(fd);

    return dictionary;
}
