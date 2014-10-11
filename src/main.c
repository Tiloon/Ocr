#include "main.h"



void show_help(void);
int get_flags(int argc, char *argv[], struct s_flags *flags);
int print_flag_error(char *flag, int error);

int main(int argc, char *argv[])
{
    struct s_flags flags;

    flags.gui = 0;
    flags.filename = 0;

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

    if(flags.gui)
        gui_main(argc, argv);

    return 0;
}


void show_help()
{
    printf(
        "OCAML : Optical Character Analysis and Machine Learning\n"
        "(Compiled : " __DATE__ " " __TIME__")\n"
        "usage : ocrocaml [arguments] -i file    Process file\n"
        "   or : ocrocaml -gui                   Graphical Interface\n"
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
            if(load_from_file(argv[i]))
                return print_flag_error(argv[i], FLAG_INVALID_ARG);
            printf("Image loaded (%s)\n", argv[i]);
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
