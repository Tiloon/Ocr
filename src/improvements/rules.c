#include "rules.h"

static wchar_t get_best_in_bounds(long double *nn_outs, wchar_t *charset,
        size_t charset_count, wchar_t min, wchar_t max, long double *score)
{
    size_t i;
    int best;

    max = -1;
    for(i = 0; i < charset_count; i++)
    {
        if((charset[i] >= min) && (charset[i] <= max))
        {
            if((best == -1) || (nn_outs[i] > nn_outs[best]))
            {
                best = i;
            }
        }
    }

    if(score)
        *score = nn_outs[best];

    return charset[best];
}

static int is_wlower(wchar_t c)
{
    return iswlower(c) ||
        (c == 0xFB00) ||
        (c == 0xFB01) ||
        (c == 0xFB02) ||
        (c == 0xE0) ||
        (c == 0xE9) ||
        (c == 0xE8);
}

static int is_walpha(wchar_t c)
{
    return iswalpha(c) ||
        (c == 0xFB00) ||
        (c == 0xFB01) ||
        (c == 0xFB02) ||
        (c == 0xE0) ||
        (c == 0xE9) ||
        (c == 0xE8);
}

static wchar_t get_best_lower(long double *nn_outs, wchar_t *charset,
        size_t charset_count,long double *score)
{
    size_t i;
    int best;

    best = -1;

    for(i = 0; i < charset_count; i++)
    {
        if(is_wlower(charset[i]))
        {
            if((best == -1) || (nn_outs[i] > nn_outs[best]))
            {
                best = i;
            }
        }
    }

    if(score)
        *score = nn_outs[best];

    return charset[best];
}

static wchar_t get_best_alpha(long double *nn_outs, wchar_t *charset,
        size_t charset_count,long double *score)
{
    size_t i;
    int best;

    best = -1;

    for(i = 0; i < charset_count; i++)
    {
        if(is_walpha(charset[i]))
        {
            if((best == -1) || (nn_outs[i] > nn_outs[best]))
            {
                best = i;
            }
        }
    }

    if(score)
        *score = nn_outs[best];

    return charset[best];
}

inline long double get_char_score(long double *nn_outs, wchar_t *charset,
        size_t charset_count, wchar_t character)
{
    size_t i;

    for(i = 0; i < charset_count; i++)
    {
        if(charset[i] == character)
            return nn_outs[i];
    }
    return 0;
}

static wchar_t get_best_number(long double *nn_outs, wchar_t *charset,
        size_t charset_count, long double *score)
{
    return get_best_in_bounds(nn_outs, charset, charset_count, L'0', L'9',
            score);
}


static int is_wspecialchar(wchar_t c)
{
    return (c == L'(') ||
        (c == L')') ||
        (c == L':') ||
        (c == L',') ||
        (c == L'-') ||
        (c == L';') ||
        (c == L'!') ||
        (c == L'?') ||
        (c == L'!');
}

wchar_t * match_rule(long double **chars, size_t count,
        struct s_neural_network *network)
{
    // Rules for a word : [(),-.:;?i!]?([0-9]*|([A-Z]?[a-zàéèflfiff]*-?))[!(),-.:;?s
    wchar_t *word, *word_tmp, c;
    size_t i;
    int is_first_char, is_alpha;
    long double max_alpha, max_num, tmp1, tmp2;
    wchar_t *charset;
    size_t charset_count;

    charset = network->network.charset;
    charset_count = network->network.charset_len;

    word = calloc(count + 1, sizeof(wchar_t));
    word_tmp = calloc(count + 1, sizeof(wchar_t));

    c = get_matching_char(chars[0], &(network->network));
    is_first_char = is_wspecialchar(c);
    is_alpha = !iswdigit(c);

    word[0] = c;
    word_tmp[0] = c;

    tmp1 = 0;
    tmp2 = 0;
    max_num = 0;
    max_alpha = 0;

    for(i = 1; i < count; i++)
    {
        tmp1 = tmp2 = 0;
        word_tmp[i] = get_best_number(chars[i], charset, charset_count, &tmp1);
        if((i == 1) && is_first_char)
            word[i] = get_best_alpha(chars[i], charset, charset_count, &tmp2);
        else
            word[i] = get_best_lower(chars[i], charset, charset_count, &tmp2);

        max_alpha += tmp2;
        max_num += tmp1;
        if(i == count - 1)
        {
            c = get_matching_char(chars[i], &(network->network));
            if(is_wspecialchar(c))
            {
                word[i] = word_tmp[i] = c;
            }
        }
    }

    if(max_alpha > max_num)
    {
        free(word_tmp);
        return word;
    }
    free(word);
    return word_tmp;
}
