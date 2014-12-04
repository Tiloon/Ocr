#include "main.h"

#define TEXT_BLOCK_SIZE 512

static void show_main_help(void);
static int get_flags(int argc, char *argv[], struct s_flags *flags);
static int print_flag_error(char *flag, int error);
static GdkPixbuf* segmentation_full(GdkPixbuf *origin);


int main(int argc, char *argv[])
{
    FLAGS->gui = 0;
    FLAGS->verbosity = 0;
    FLAGS->filename = NULL;
    FLAGS->filteroutput = NULL;

    if(argc <= 1)
    {
        show_main_help();
        return 0;
    }

    if(!strcmp(argv[1], "nn"))
        return nn_main(argc - 1, argv + 1);

#ifndef NOHELP
    if(!strcmp(argv[1], "help"))
        return show_help(argc > 2 ? argv[2] : 0);
#endif

    if(get_flags(argc, argv, FLAGS))
    {
        show_main_help();
        return 1;
    }

    if(FLAGS->filename)
    {
        if(FLAGS->verbosity)
            printf(BOLDCYAN "\nFilters\n" RESET);
        if(filters_apply_all(picture_get_image()))
        {
            if(FLAGS->verbosity)
                printf(BOLDRED "FAIL: " RESET "can't apply all filters\n");
            return 1;
        }
        if(FLAGS->verbosity)
            printf(BOLDCYAN "All filters applied\n" RESET);

        if(FLAGS->filteroutput)
        {
            if(FLAGS->verbosity)
                printf(BOLDCYAN "\nPreporcess output\n" RESET);
            if(picture_save_to_file(FLAGS->filteroutput))
            {
                if(FLAGS->verbosity)
                    printf(BOLDRED "FAIL: " RESET "can't save to %s\n",
                            FLAGS->filteroutput);
                return 1;
            } else
                printf("saved to %s\n", FLAGS->filteroutput);
        }
        // Debug
        picture_save_pixbuf(segmentation_full(picture_get_image()),
                "./segmentation_demo.png");
    }
#ifndef NOGUI
    if(FLAGS->gui)
        gui_main(argc, argv);
#endif
    return 0;
}

static int append_to_output(wchar_t *word, wchar_t **output,
        size_t *output_size, size_t *output_pos)
{
    size_t i;
    for(i = 0; word[i]; i++)
    {
        while((*output_pos) + i + 1 >= (*output_size))
        {
            (*output_size) += TEXT_BLOCK_SIZE;
            (*output) = realloc(*output, (*output_size) * sizeof(wchar_t));
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

static GdkPixbuf* segmentation_full(GdkPixbuf *origin)
{
    GdkPixbuf *pixbuf;
    struct s_binarypic *pic, *mask;
    struct s_rectangle *chars, *lines, *blocs;
    struct s_neural_network neural_network;
    struct s_dictionary *dictionary;
    size_t itr_chars, itr_lines, itr_blocs, itr_spaces, *spaces, output_size,
           output_pos;
    char *vectorized;
    long double *nn_inputs;
    wchar_t *output, *current;

    mask = NULL;
    if(!(pic = calloc(1, sizeof(struct s_binarypic))))
    {
        LOG_ALLOC_ERR();
        return 0;
    }
    pixbuf = NULL;
    blocs = NULL;
    lines = NULL;
    chars = NULL;
    dictionary = NULL;
    if(FLAGS->dictionary_file)
    {
        if(FLAGS->verbosity)
            printf(BOLDCYAN "Loading dictionary\n" RESET);
        //dictionary = load_dictionary(FLAGS->dictionary_file);
    }
    initialization_neural_network(&neural_network, NUMBER_PATTERNS,
            NUMBER_INPUT_NEURONS,
            NUMBER_HIDDEN_NEURONS,
            BIAS);

    output_pos = 0;
    output_size = TEXT_BLOCK_SIZE;
    output = calloc(output_size, sizeof(wchar_t));
    current = calloc(TEXT_BLOCK_SIZE, sizeof(wchar_t));
    gdk_to_binary(origin, pic);
    binary_to_gdk(pic, &pixbuf);
    mask = copy_binarypic(pic);
    morph_erode(mask->pixels, mask->w, mask->h, mask->w / 100, mask->h / 100);

    blocs = split_blocs(mask);

    if(!blocs)
        return pixbuf;
    for(itr_blocs = 0; blocs[itr_blocs].h || blocs[itr_blocs].w; itr_blocs++)
    {
        lines = split_lines(pic, blocs + itr_blocs);
        if(lines)
        {
            for(itr_lines = 0; lines[itr_lines].h || lines[itr_lines].w;
                    itr_lines++)
            {
                chars = split_chars(pic, lines + itr_lines);
                spaces = get_spaces(chars);
                itr_spaces = 0;

                if(chars)
                {
                    for(itr_chars = 0; chars[itr_chars].h || chars[itr_chars].w;
                            itr_chars++)
                    {
                        vectorized = vectorize_char(pic, chars + itr_chars);
                        if(!vectorized)
                        {
                            FREE(chars);
                            FREE(lines);
                            FREE(blocs);
                            FREE(pic);
                            LOG_ALLOC_ERR();
                            return NULL;
                        }
                        nn_inputs = vector_bool_to_nn(vectorized, 256);
                        print_matching_char(
                                compute_character(&neural_network.network,
                                    nn_inputs),
                                NUMBER_PATTERNS, &neural_network.network);
                        FREE(vectorized);
                        draw_rectangle(pixbuf, chars + itr_chars, ~0, 0, 0);
                        if(spaces[itr_spaces] && spaces[itr_spaces] == itr_chars + 1)
                        {
                            append_to_output(L" ", &output, &output_size,
                                    &output_pos);
                            itr_spaces++;
                        }
                    }
                }
                FREE(spaces);
                FREE(chars);
                draw_rectangle(pixbuf, lines + itr_lines, 0, 0, ~0);
                append_to_output(L" ", &output, &output_size, &output_pos);
            }
        }
        FREE(lines);
        draw_rectangle(pixbuf, blocs + itr_blocs, 0, ~0, 0);
        append_to_output(L"\n", &output, &output_size, &output_pos);
    }
    FREE(blocs);
    FREE(pic);
    // Wprintf + fwide or printf because a stream can only be byte OR wide
    // oriented, but not both
    printf("%ls", output);

    return pixbuf;
}


static void show_main_help()
{
    printf("OCAML : Optical Character Analysis and Machine Learning\n\
(Compiled : " __DATE__ " " __TIME__")\n\
usage : ocrocaml [args] -i file     Process file\n"
#ifndef NOGUI
"   or : ocrocaml -gui               Graphical Interface\n"
#endif
"   or : ocrocaml nn [args]          Neural network setup\n"
#ifndef NOHELP
"   or : ocrocaml help \"keyword\"     Get help about keyword\n"
#endif
"\n\
Arguments : \n\
    -f \"filter\"[,opt]               Apply filter with options\n\
    -i \"file\"                       Load picture \"file\"\n\
    -ofilters \"file\"                Save file after applying filters\n\
    -osegmentation \"file\"           Save file after segmentation\n\
    -dictionary \"file\"              Load a spell checking file\n\
    -v                              Verbose\n\n\
Neural network arguments :\n");
    print_nn_help();
    printf("\nMore about this software : http://ocrocaml.ovh/\n");
}

static int get_flags(int argc, char *argv[], struct s_flags *flags)
{
    int i;
    for (i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], "-gui"))
        {
            if(flags->gui)
                return print_flag_error(argv[i], FLAG_ALREADY_SET);
            flags->gui = 1;
        }
        else if(!strcmp(argv[i], "-v"))
        {
            if(flags->verbosity)
                return print_flag_error(argv[i], FLAG_ALREADY_SET);
            flags->verbosity = 1;
            printf(BOLDCYAN "Flags\n" RESET "Verbosity is set\n");
        }
        else if(!strcmp(argv[i], "-i"))
        {
            if(flags->filename)
                return print_flag_error(argv[i], FLAG_ALREADY_SET);
            i++;
            if(i >= argc)
                return print_flag_error(argv[i - 1], FLAG_MISSING_ARG);
            flags->filename = argv[i];
            if(picture_load_from_file(argv[i]))
                return print_flag_error(argv[i], FLAG_INVALID_ARG);
            if(flags->verbosity)
                printf("Image loaded (%s)\n", argv[i]);
        }
        else if(!strcmp(argv[i], "-f"))
        {
            i++;
            if(i >= argc)
                return print_flag_error(argv[i - 1], FLAG_MISSING_ARG);
            if(filter_add(argv[i]))
                return print_flag_error(argv[i], FLAG_INVALID_ARG);
            if(flags->verbosity)
                printf("Filter added : %s\n", argv[i]);
        }
        else if(!strcmp(argv[i], "-ofilters"))
        {
            if(flags->filteroutput)
                return print_flag_error(argv[i], FLAG_ALREADY_SET);

            i++;
            if(i >= argc)
                return print_flag_error(argv[i - 1], FLAG_MISSING_ARG);
            flags->filteroutput = argv[i];
        }
        else if(!strcmp(argv[i], "-dictionary"))
        {
            if(flags->dictionary_file)
                return print_flag_error(argv[i], FLAG_ALREADY_SET);

            i++;
            if(i >= argc)
                return print_flag_error(argv[i - 1], FLAG_MISSING_ARG);
            flags->dictionary_file = argv[i];
        }
        else if(!strcmp(argv[i], "-osegmentation"))
        {
            if(flags->segmentation_output)
                return print_flag_error(argv[i], FLAG_ALREADY_SET);

            i++;
            if(i >= argc)
                return print_flag_error(argv[i - 1], FLAG_MISSING_ARG);
            flags->segmentation_output = argv[i];
        }
        else
        {
            return print_flag_error(argv[i], FLAG_UNDEFINED);
        }
    }
    return 0;
}

static int print_flag_error(char *flag, int error)
{
    if(error & FLAG_ALREADY_SET)
        fprintf(stderr, "Error : flag already set : %s\n", flag);
    if(error & FLAG_UNDEFINED)
        fprintf(stderr, "Error : flag undefined : %s\n", flag);
    if(error & FLAG_MISSING_ARG)
        fprintf(stderr, "Error : missing argument for flag : %s\n", flag);
    if(error & FLAG_INVALID_ARG)
        fprintf(stderr, "Error : invalid argument '%s'\n", flag);

    printf("type \"ocrocaml -h\" for help\n\n");
    return 1;
}

struct s_flags *flags(void)
{
    static struct s_flags *ptr;
    if(!ptr)
    {
        if(!(ptr = calloc(1, sizeof(struct s_flags))))
        {
            LOG_ALLOC_ERR();
            return 0;
        }
    }
    return ptr;
}
