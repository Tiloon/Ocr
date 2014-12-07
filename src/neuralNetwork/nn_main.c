#include <stdio.h>
#include <stdlib.h>

#include "network.h"
#include "layer.h"
#include "nn_main.h"
#include "structure.h"
#include "learning.h"
#include "serialization.h"
#include "learn_from_pics.h"

/*
 * CHECKING FUNCTIONS
 */

static void serialization(struct s_network *network)
{
    FILE *file = NULL, *file2 = NULL;
    file = fopen("serialized", "w+");
    file2 = fopen("charset", "r+");
    if(file2 == NULL)
    {
        file2 = fopen("charset", "w+");
        network_to_text(file, network, file2, 1);
    }
    else
        network_to_text(file, network, file2, 0);

    fclose(file);
    fclose(file2);
}


void printMatrix (long double ***matrix, int x, int y)
{
    int x1, y1;
    for(x1 = 0; x1 < x; x1++)
    {
        for(y1 = 0; y1 < y; y1++)
        {
            wprintf(L"Matrix[%d][%d] = (%Lf)\n", x1, y1,
                    (*matrix)[x1][y1]);
        }
    }
}

void printVector(long double *vector, size_t size)
{
    size_t u;
    for(u = 0; u < size; u++)
        wprintf(L"%Lf ", vector[u]);
}

void printInputVector(long double *vector, size_t size)
{
    size_t u;
    wprintf(L"\n");
    for(u = 0; u < size; u++)
    {
        if(u != 0 && u % 16 == 0)
            wprintf(L"\n");
        if(vector[u] > 0)
            wprintf(L"+%Lf", vector[u]);
        else
            wprintf(L"%Lf", vector[u]);
    }
}

void printResultsVector(long double *vector, size_t size)
{
    size_t u;
    for(u = 0; u < size; u++)
    {
        wprintf(L"%zu: %Lf\n", u, vector[u]);
    }
}

long double * nn_clone_output(long double *vector, struct s_network *network)
{
    size_t i, max;
    long double *copy;

    for(max = 0; (network->charset)[max]; max++);

    copy = calloc(max + 2, sizeof(long double));

    for(i = 0; i <= max; i++)
        copy[i] = vector[i];

    return copy;
}

wchar_t get_matching_char(long double *vector, struct s_network *network)
{
    size_t i, max;

    max = 0;
    for(i = 0; network->charset[i]; i++)
        max = (vector[max] < vector[i]) ? i : max;

    return network->charset[max];
}

void print_matching_char(long double *vector, struct s_network *network)
{
    wprintf(L"%lc", get_matching_char(vector, network));

    /*
     * print the string in charset
     */
    //wprintf(L"%ls", network->charset);
}


/*
 *  testing functions
 */

static int checkFlags(int argc, char* argv[], struct s_flags_nn *flags);
static int print_flag_error();

int nn_main(int argc, char *argv[])
{
    //*******************************************//
    //             VARIABLES DECLARATIONS        //
    //*******************************************//

    //NETWORK
    struct s_neural_network neural_network;
    struct s_flags_nn flags;

    //NETWORKS PARAMETERS
    size_t fonts_count;
    long double error;
    int iterations;

    long double ***all_inputs, ***all_results, ***all_targets;

    //inputsUser is used so as to debug/check the NN
    //long double *inputsUser;

    size_t i, j;

    fonts_count = 0;
    //inputsUser = calloc(NUMBER_PIXELS_CHARACTER, sizeof(long double));



    //*******************************************//
    //          VARIABLES AFFECTATIONS           //
    //*******************************************//

    //Initialize the flags structs
    flags.learning = 0;
    flags.serialize = 0;
    iterations = 0;
    error = 25;

    if(checkFlags(argc, argv, &flags))
        return 1;
    else
    {
        initialization_neural_network(&neural_network, NUMBER_PATTERNS,
                NUMBER_INPUT_NEURONS,
                NUMBER_HIDDEN_NEURONS,
                BIAS);
	//wprintf(L"%ls\n", neural_network.network.charset);
        all_inputs = load_image_set(flags.dataset_files,
                NUMBER_PATTERNS, &fonts_count);


        all_results = calloc(fonts_count, sizeof(long double **));
        //all_targets = calloc(fonts_count, sizeof(long double **));
        all_targets = calloc(fonts_count, sizeof(long double));

        for(i = 0; i < fonts_count; i++)
        {
            all_results[i] = calloc(NUMBER_PATTERNS, sizeof(long double*));
            all_targets[i] = calloc(NUMBER_PATTERNS, sizeof(long double));
            for(j = 0; j < NUMBER_PATTERNS; j++)
            {
                all_results[i][j] = calloc(NUMBER_PIXELS_CHARACTER,
                        sizeof(long double));
                all_targets[i][j] = calloc(NUMBER_PATTERNS,
                        sizeof(long double));
                all_targets[i][j][j] = 1;
            }
        }

        learning_fonts(&neural_network.network, NUMBER_PATTERNS, &iterations,
                fonts_count, &all_inputs, &all_targets,
                &all_results,
                &error, ETA, ALPHA, ERROR);

        if(flags.serialize)
            serialization(&neural_network.network);
    }
    wprintf(L"\n\n");
    return 0;
}

static int checkFlags(int argc, char *argv[], struct s_flags_nn *flags)
{
    int i;
    if(argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        print_nn_help();
        return 1;
    }
    for (i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-learning") == 0)
        {
            if(flags->learning)
                return print_flag_error();
            flags->learning = 1;
        }
        else if(strcmp(argv[i], "-serialize") == 0)
        {
            if(flags->serialize)
                return print_flag_error();
            flags->serialize = 1;
        }
        else if(!strcmp(argv[i], "-datasetsfiles"))
        {
            if(i + 1 >= argc)
                return print_flag_error();
            else
            {
                i++;
                flags->dataset_files = parse_file_cslist(argv[i]);
            }
        }
        /*	else if(!strcmp(argv[i], "-charset"))
            {
            if(i + 1 >= argc)
            return print_flag_error();
            i++;
            flags->reference_order = calloc(200, sizeof(char));
            flags->reference_order = argv[i];
            }
            */
            else
                return print_flag_error();
    }
    return 0;
}


static int print_flag_error(void)
{
    fprintf(stderr, "Flag ERROR : type -h for help\n");
    return 1;
}

void print_nn_help(void)
{
    wprintf(L""
"    -learning                       Start the learning process\n"
"    -serialize                      Serialize the NN into serialize\n"
"    -datasetsfiles [files]          Comma separated file list\n\n");
}
