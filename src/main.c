#include "main.h"

void show_help(void);
int get_flags(int argc, char *argv[], struct s_flags *flags);
int print_flag_error(char *flag, int error);
GdkPixbuf* segmentation_demo(GdkPixbuf *origin);

int main(int argc, char *argv[])
{
    struct s_flags flags;

    flags.gui = 0;
    flags.filename = NULL;
    flags.filteroutput = NULL;

    if(argc <= 1)
    {
        show_help();
        return 0;
    }

    if(get_flags(argc, argv, &flags))
    {
        show_help();
        return 1;
    }

    if(flags.filename)
    {
        if(filters_apply_all(picture_get_image()))
            return 1;

        if(flags.filteroutput)
        {
            if(picture_save_to_file(flags.filteroutput))
                return 1;
        }
        // Debug
        picture_save_pixbuf(segmentation_demo(picture_get_image()),
                "./segmentation_demo.png");
    }
    if(flags.gui)
        gui_main(argc, argv);
    return 0;
}

GdkPixbuf* segmentation_demo(GdkPixbuf *origin)
{
    GdkPixbuf *pixbuf;
    struct s_binarypic *pic, *mask;
    struct s_rectangle *chars, *lines, *blocs;
    size_t itr_chars, itr_lines, itr_blocs;

    pic = calloc(1, sizeof(struct s_binarypic));
    pixbuf = NULL;

    gdk_to_binary(origin, pic);
    binary_to_gdk(pic, &pixbuf);
    mask = copy_binarypic(pic);
    morph_erode(mask->pixels, mask->w, mask->h, 12, 12);

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
                if(chars)
                {
                    for(itr_chars = 0; chars[itr_chars].h || chars[itr_chars].w;
                            itr_chars++)
                    {
                        draw_rectangle(pixbuf, chars[itr_chars], ~0, 0, 0);
                    }
                }
                free(chars);
                draw_rectangle(pixbuf, lines[itr_lines], 0, 0, ~0);
            }
        }
        free(lines);
        draw_rectangle(pixbuf, blocs[itr_blocs], 0, ~0, 0);
    }
    free(blocs);
    free(pic);

    return pixbuf;
}


void show_help()
{
    printf(
            "OCAML : Optical Character Analysis and Machine Learning\n"
            "(Compiled : " __DATE__ " " __TIME__")\n"
            "usage : ocrocaml [arguments] -i file    Process file\n"
            "   or : ocrocaml -gui                   Graphical Interface\n"
            "   or : ocrocaml -help \"keyword\"        Get help about keywod"
            "\n\n"
            "Arguments : \n"
            "    -f \"filter\"[,opt]      apply filter with options\n"
            "    -i \"file\"              load picture \"file\"\n"
            "    -ofilters \"file\"       save file after applying filters\n"
            "\n\n"
            "More about this software : http://ocrocaml.ovh/\n");
}

int get_flags(int argc, char *argv[], struct s_flags *flags)
{
    int i;
    for (i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-gui") == 0)
        {
            if(flags->gui)
                return print_flag_error(argv[i], FLAG_ALREADY_SET);
            flags->gui = 1;
        }
        else if(strcmp(argv[i], "-i") == 0)
        {
            if(flags->filename)
                return print_flag_error(argv[i], FLAG_ALREADY_SET);
            i++;
            if(i >= argc)
                return print_flag_error(argv[i - 1], FLAG_MISSING_ARG);
            flags->filename = argv[i];
            if(picture_load_from_file(argv[i]))
                return print_flag_error(argv[i], FLAG_INVALID_ARG);
            printf("Image loaded (%s)\n", argv[i]);
        }
        else if(strcmp(argv[i], "-f") == 0)
        {
            i++;
            if(i >= argc)
                return print_flag_error(argv[i - 1], FLAG_MISSING_ARG);
            if(filter_add(argv[i]))
                return print_flag_error(argv[i], FLAG_INVALID_ARG);
            printf("Filter added : %s\n", argv[i]);
        }
        else if(strcmp(argv[i], "-ofilters") == 0)
        {
            if(flags->filteroutput)
                return print_flag_error(argv[i], FLAG_ALREADY_SET);

            i++;
            if(i >= argc)
                return print_flag_error(argv[i - 1], FLAG_MISSING_ARG);
            flags->filteroutput = argv[i];
        }
        else
            return print_flag_error(argv[i], FLAG_UNDEFINED);
    }
    return 0;
}

int print_flag_error(char *flag, int error)
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
