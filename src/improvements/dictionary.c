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

static wchar_t * get_matching_word_probability(wchar_t *charset,
        size_t charset_count, wchar_t *word, long double **chars,
        long double *seil, wchar_t *output)
{
    size_t i, j;
    long double probability, tmp;
    wchar_t c0;


    probability = 1;
    c0 = 0;

    for(i = 0; word[i] && chars[i]; i++)
    {
        if(probability < *seil)
            return NULL;

        if(i == 0)
        {
            probability = get_char_probability(towlower(word[i]), charset,
                    charset_count, chars[i]);
            tmp = get_char_probability(towupper(word[i]), charset,
                    charset_count, chars[i]);

            if(tmp > probability)
            {
                c0 = towupper(word[i]);
            }
            else
            {
                c0 = towlower(word[i]);
            }
        }
        else
        {
            probability *= get_char_probability(word[i], charset, charset_count, chars[i]);
        }
    }

    for(j = 0; word[j]; j++)
    {
        output[j] = word[j];
        if((j == 0) && c0)
            output[0] = c0;
    }
    *seil = probability;

    return word;
}

static wchar_t * get_number_probability(long double **chars, size_t count,
        wchar_t *charset, size_t charset_count, long double *seil,
        wchar_t *output)
{
    size_t numbers[16], i, j, max;
    long double probability;

    probability = 1;

    for(i = 0; i < charset_count; i++)
    {
        if((charset[i] >= L'0') && (charset[i] <= L'9'))
            numbers[charset[i] - L'0'] = i;

        if(charset[i] == L'+')
            numbers[10] = i;

        if(charset[i] == L'-')
            numbers[11] = i;

        if(charset[i] == L'/')
            numbers[12] = i;

        if(charset[i] == L'=')
            numbers[13] = i;

        if(charset[i] == L'.')
            numbers[14] = i;

        if(charset[i] == L',')
            numbers[15] = i;
    }

    for(i = 0; i < count; i++)
    {
        if(probability < *seil)
            return NULL;

        max = 0;
        for(j = 0; j < 16; j++)
        {
            if(chars[i][numbers[j]] > chars[i][numbers[max]])
                max = j;
        }
        probability *= chars[i][numbers[max]];
        if(max < 10)
            output[i] = L'0' + max;
        if(max == 10)
            output[i] = L'+';
        if(max == 11)
            output[i] = L'-';
        if(max == 12)
            output[i] = L'/';
        if(max == 13)
            output[i] = L'=';
        if(max == 14)
            output[i] = L'.';
        if(max == 15)
            output[i] = L',';
    }

    (*seil) = probability;
    return output;
}

wchar_t * approcimative_match(long double **chars, size_t count,
        struct s_dictionary *dictionary, wchar_t *charset,
        size_t charset_count)
{
    size_t index, i;
    long double max, tmp;

    wchar_t *output;

    if(count == 0)
        return NULL;

    max = 0;

    output = calloc(count, sizeof(wchar_t));
    get_number_probability(chars, count, charset, charset_count, &max, output);

    if(count > dictionary->index_max)
        return NULL;

    index = dictionary->indexes[count];

    for(i = index; i < dictionary->indexes[count + 1]; i++)
    {
        tmp = max;
        get_matching_word_probability(charset, charset_count,
                dictionary->words[i], chars, &tmp, output);

        if(tmp > max)
        {
            max = tmp;
            index = i;
        }
    }

    if(max <= 0)
        return NULL;

    return output; //dictionary->words[index];
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
