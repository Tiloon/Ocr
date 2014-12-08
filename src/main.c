#include "main.h"

static void show_main_help(void);
static int get_flags(int argc, char *argv[], struct s_flags *flags);
static int print_flag_error(char *flag, int error);


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

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
    if(!strcmp(argv[1], "gui"))
        return gui_main(argc - 1, argv + 1);
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
            wprintf(L"" BOLDCYAN "\nFilters\n" RESET);
        if(filters_apply_all(picture_get_pimage()))
        {
            if(FLAGS->verbosity)
                wprintf(L"" BOLDRED "FAIL: " RESET "can't apply filters\n");
            return 1;
        }
        if(FLAGS->verbosity)
            wprintf(L"" BOLDCYAN "All filters applied\n" RESET);

        if(FLAGS->filteroutput)
        {
            if(FLAGS->verbosity)
                wprintf(L"" BOLDCYAN "\nPreporcess output\n" RESET);
            if(picture_save_to_file(FLAGS->filteroutput))
            {
                if(FLAGS->verbosity)
                    wprintf(L"" BOLDRED "FAIL: " RESET "can't save to %s\n",
                            FLAGS->filteroutput);
                return 1;
            }
            else
            {
                wprintf(L"saved to %s\n", FLAGS->filteroutput);
            }
        }
        segment_and_save(picture_get_image());
    }
#ifndef NOGUI
    if(FLAGS->gui)
        gui_main(argc, argv);
#endif
    return 0;
}

int segment_and_save(GdkPixbuf *origin)
{
    GdkPixbuf *segmented;

    segmented = perform_ocr(origin, NULL);
    if(FLAGS->segmentation_output)
        return !picture_save_pixbuf(segmented, FLAGS->segmentation_output);

    return !segmented;
}

static void show_main_help()
{
    wprintf(L"OCAML : Optical Character Analysis and Machine Learning\n\
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
    -kerning                        Apply kerning segmentation (slower)\n\
    -v                              Verbose\n\n\
Neural network arguments :\n");
    print_nn_help();
    wprintf(L"\nMore about this software : http://ocrocaml.ovh/\n");
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
        else if(!strcmp(argv[i], "-rules"))
        {
            if(flags->rules)
                return print_flag_error(argv[i], FLAG_ALREADY_SET);
            flags->rules = 1;
            if(flags->verbosity)
                wprintf(L"" BOLDCYAN "Flags\n" RESET "Rules are set\n");
        }
        else if(!strcmp(argv[i], "-kerning"))
        {
            if(flags->kerning_segm)
                return print_flag_error(argv[i], FLAG_ALREADY_SET);
            flags->kerning_segm = 1;
            if(flags->verbosity)
                wprintf(L"" BOLDCYAN "Flags\n" RESET "Kerning segmentation is"
                        "set\n");
        }
        else if(!strcmp(argv[i], "-v"))
        {
            if(flags->verbosity)
                return print_flag_error(argv[i], FLAG_ALREADY_SET);
            flags->verbosity = 1;
            wprintf(L"" BOLDCYAN "Flags\n" RESET "Verbosity is set\n");
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
                wprintf(L"Image loaded (%s)\n", argv[i]);
        }
        else if(!strcmp(argv[i], "-f"))
        {
            i++;
            if(i >= argc)
                return print_flag_error(argv[i - 1], FLAG_MISSING_ARG);
            if(filter_add(argv[i]))
                return print_flag_error(argv[i], FLAG_INVALID_ARG);
            if(flags->verbosity)
                wprintf(L"Filter added : %s\n", argv[i]);
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

    wprintf(L"type \"ocrocaml -h\" for help\n\n");
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
