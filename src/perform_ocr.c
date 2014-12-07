#include "perform_ocr.h"

#define TEXT_BLOCK_SIZE 512
#define WORD_BLOC_SIZE 64 

static int append_wchar_to_output(wchar_t c, wchar_t **output,
        size_t *output_size, size_t *output_pos)
{
    while((*output_pos) + 2 + TEXT_BLOCK_SIZE >= (*output_size))
    {
        (*output_size) += TEXT_BLOCK_SIZE;
        (*output) = realloc(*output, (1 + *output_size) * sizeof(wchar_t));
        if(!(*output))
        {
            LOG_ALLOC_ERR();
            return -1;
        }
    }
    (*output)[*output_pos] = c;

    (*output_pos)++;
    (*output)[*output_pos] = 0;
    return 0;
}

static int append_to_output(wchar_t *word, wchar_t **output,
        size_t *output_size, size_t *output_pos)
{
    size_t i;
    for(i = 0; word[i]; i++)
    {
        while((*output_pos) + i + 2 + TEXT_BLOCK_SIZE >= (*output_size))
        {
            (*output_size) += TEXT_BLOCK_SIZE;
            (*output) = realloc(*output, (1 + *output_size) * sizeof(wchar_t));
            if(!(*output))
            {
                LOG_ALLOC_ERR();
                return -1;
            }
        }
        (*output)[*output_pos + i] = word[i];
    }

    (*output_pos) += i;
    (*output)[*output_size] = 0;
    return 0;
}

static int append_to_vector_word(long double *vector, long double ***output,
        size_t *output_size, size_t *output_pos)
{
    //wprintf(L"%zu - %zu\n", *output_pos, *output_size);
    while((*output_pos) + WORD_BLOC_SIZE >= (*output_size))
    {
        (*output_size) *= 2;
        (*output) = realloc(*output,
                (2 + *output_size) * sizeof(long double*));
        if(!(*output))
        {
            LOG_ALLOC_ERR();
            return -1;
        }
    }
    (*output)[*output_pos] = vector;
    (*output_pos)++;
    (*output)[*output_pos] = NULL;

    return 0;
}

static int free_vector_word(long double **output,
        size_t *output_size, size_t *output_pos)
{
    size_t i;
    for(i = 0; output[i] && (i < *output_size); i++)
    {
        FREE(output[i]);
    }

    (*output_pos) = 0;

    return 0;
}

static wchar_t * get_dictionary_match(long double **chars, size_t count,
        struct s_dictionary *dictionary, struct s_neural_network *nn)
{
    wchar_t *match;

    match = approcimative_match(chars, count, dictionary,
            nn->network.charset, nn->network.charset_len);

    return match;
}

GdkPixbuf* perform_ocr(GdkPixbuf *origin)
{
    GdkPixbuf *pixbuf;
    struct s_binarypic *pic, *mask, *letter;
    struct s_rectangle *chars, *lines, *blocs, *segm;
    struct s_neural_network nnetwork;
    size_t itr_chars, itr_lines, itr_blocs, itr_spaces, *spaces, output_size,
           output_pos, word_size, word_pos;
    char *vectorized;
    long double *nn_inputs, *nn_output, **current_word_outputs;
    wchar_t *output, *current, *tmp_word, c;
    int letternb;

    mask = NULL;
    letter = NULL;
    if(!(pic = calloc(1, sizeof(struct s_binarypic))))
    {
        LOG_ALLOC_ERR();
        return NULL;
    }

    pixbuf = NULL;
    blocs = NULL;
    lines = NULL;
    chars = NULL;

    //s_rectangle initalisation for segm
    segm = calloc(1,sizeof(struct s_rectangle));
    segm->x = 0;
    segm->y = 0;
    segm->w = 1;
    segm->h = 1;

    // Neural network initialisation
    initialization_neural_network(&nnetwork, NUMBER_PATTERNS,
            NUMBER_INPUT_NEURONS,
            NUMBER_HIDDEN_NEURONS,
            BIAS);

    // Output text initialisation
    output_pos = 0;
    output_size = TEXT_BLOCK_SIZE;
    output = calloc(output_size, sizeof(wchar_t));
    current = calloc(TEXT_BLOCK_SIZE, sizeof(wchar_t));

    // Dictionary word search initialization
    if(FLAGS->dictionary)
    {
        word_size = WORD_BLOC_SIZE;
        word_pos = 0;
        current_word_outputs = calloc(word_size, sizeof(long double*));
    }

    // Binarization
    gdk_to_binary(origin, pic);

    // Bloc segmentation
    blocs = split_blocs(pic);

    if(FLAGS->segmentation_output)
        binary_to_gdk(pic, &pixbuf);

    if(!blocs)
        return pixbuf;

    // Loop across each blocs (paragraphs...)
    for(itr_blocs = 0; blocs[itr_blocs].h || blocs[itr_blocs].w; itr_blocs++)
    {
        lines = split_lines(pic, blocs + itr_blocs);
        // Loop across each lines
        for(itr_lines = 0;
                lines && (lines[itr_lines].h || lines[itr_lines].w);
                itr_lines++)
        {
            chars = split_chars(pic, lines + itr_lines);

            spaces = get_spaces(chars);
            itr_spaces = 0;

            // Loop across each characters
            for(itr_chars = 0;
                    chars && (chars[itr_chars].h && chars[itr_chars].w);
                    itr_chars++)
            {

                //segmentation
                letter = kerning(pic, chars + itr_chars);
                //reinitialise segm
                segm->x = 0;
                segm->y = 0;
                segm->w = letter->w;
                segm->h = letter->h;
                segm = split_chars(letter, segm);

                for(letternb = 0; segm && (segm[letternb].h 
                            || segm[letternb].w); letternb++)
                {
                    //new segm
                    vectorized = vectorize_char(letter, segm + letternb);
                    //old seg
                    //vectorized = vectorize_char(pic, chars + itr_chars);

                    if(!segm[letternb+1].h && !segm[letternb+1].w)
                        FREE(letter);
                    if(!vectorized)
                    {
                        FREE(chars);
                        FREE(lines);
                        FREE(blocs);
                        FREE(pic);
                        LOG_ALLOC_ERR();
                        return NULL;
                    }
                    nn_inputs = vector_bool_to_nn(vectorized,
                            NUMBER_PIXELS_CHARACTER);

                    nn_output = compute_character(&nnetwork.network, nn_inputs);

                    if(FLAGS->dictionary)
                    {
                        nn_output = nn_clone_output(nn_output, 
                            &(nnetwork.network));
                        append_to_vector_word(nn_output,
                                &current_word_outputs, &word_size, &word_pos);
                    }
                    else
                    {
                        c = get_matching_char(nn_output, &(nnetwork.network));

                        if(c)
                        {
                            append_wchar_to_output(c, &output, &output_size,
                                    &output_pos);
                        }
                        else
                        {
                            fprintf(stderr, "Bad character");
                        }
                    }

                    FREE(vectorized);
                    if(pixbuf)
                        draw_rectangle(pixbuf, chars + itr_chars, ~0, 0,
                                0);
                    if(spaces[itr_spaces] &&
                            (spaces[itr_spaces] == itr_chars + 1))
                    {
                        if(FLAGS->dictionary)
                        {
                            tmp_word = get_dictionary_match(
                                    current_word_outputs,
                                    word_pos, FLAGS->dictionary, &nnetwork);
                            if(tmp_word)
                            {
                                if(append_to_output(tmp_word, &output, 
                                            &output_size,
                                            &output_pos) == -1)
                                {
                                    FREE(chars);
                                    FREE(lines);
                                    FREE(blocs);
                                    FREE(pic);
                                    return NULL;
                                }
                            }
                            free_vector_word(current_word_outputs, &word_size,
                                    &word_pos);
                        }

                        if(append_to_output(L" ", &output, &output_size,
                                    &output_pos) == -1)
                        {
                            FREE(chars);
                            FREE(lines);
                            FREE(blocs);
                            FREE(pic);
                            return NULL;
                        }
                        itr_spaces++;
                    }
                }
            }
            FREE(spaces);
            FREE(chars);
            if(pixbuf)
                draw_rectangle(pixbuf, lines + itr_lines, 0, 0, ~0);
            append_to_output(L" ", &output, &output_size, &output_pos);
        }
        FREE(lines);
        if(pixbuf)
            draw_rectangle(pixbuf, blocs + itr_blocs, 0, ~0, 0);
        append_to_output(L"\n", &output, &output_size, &output_pos);
    }
    FREE(blocs);
    FREE(pic);
    wprintf(L"%ls", output);

    return pixbuf;
}
