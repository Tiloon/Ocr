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
    FILE *file = NULL;
    file = fopen("serialized", "w+");
    if(file == NULL)
    {
        printf("File not opened\n");
        return;
    }
    network_to_text(file, network);
    fclose(file);
}

void printMatrix (long double ***matrix, int x, int y)
{
    int x1, y1;
    for(x1 = 0; x1 < x; x1++)
    {
        for(y1 = 0; y1 < y; y1++)
        {
            printf("Matrix[%d][%d] = (%Lf)\n", x1, y1,
                    (*matrix)[x1][y1]);
        }
    }
}

void printVector(long double *vector, size_t size)
{
    size_t u;
    for(u = 0; u < size; u++)
        printf("%Lf ", vector[u]);
}

void printInputVector(long double *vector, size_t size)
{
    size_t u;
    printf("\n");
    for(u = 0; u < size; u++)
    {
        if(u != 0 && u % 16 == 0)
            printf("\n");
        if(vector[u] > 0)
            printf("+%Lf", vector[u]);
        else
            printf("%Lf", vector[u]);
    }
}

void printResultsVector(long double *vector, size_t size)
{
    size_t u;
    for(u = 0; u < size; u++)
    {
        printf("%zu: %Lf\n", u, vector[u]);
    }
}

void print_matching_char(long double *vector, size_t size)
{
    size_t max, i;
    max = 0;
    for(i = 0; i < size; i++)
        max = (vector[max] < vector[i]) ? i : max;
    printf("%c", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"[max]);
}


/*
 *  testing functions
 */

static int checkFlags(int argc, char* argv[], struct s_flags_nn *flags, long double ****inputs);
static int print_flag_error();
static void print_nn_help();

int nn_main(int argc, char *argv[])
{
    //*******************************************//
    //             VARIABLES DECLARATIONS        //
    //*******************************************//

    //NETWORK
    struct s_neural_network neural_network;
    struct s_flags_nn flags;

    //NETWORKS PARAMETERS
<<<<<<< HEAD
    int NUMBER_FONTS = 1;
=======
    int NUMBER_FONTS = 3;
    int NUMBER_PATTERNS = 52;
    int NUMBER_PIXELS_CHARACTER = 256;
    int NUMBER_INPUT_NEURONS = NUMBER_PIXELS_CHARACTER;
    int NUMBER_HIDDEN_NEURONS = 0.1 * NUMBER_INPUT_NEURONS;
    long double ETA = 0.4;
    long double ALPHA = 0.4;
    long double BIAS = 0.5;
    long double ERROR = 0.08;
>>>>>>> 0f17370cf7b577c2605e587240f29f40e9406101
    long double error;
    int iterations;


    long double ***all_inputs;

    long double ***all_results = calloc(NUMBER_FONTS, sizeof(long double));
    long double ***all_targets = calloc(NUMBER_FONTS, sizeof(long double));

    //inputsUser is used so as to debug/check the NN
    long double *inputsUser = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));

    int a, b;
    for(a = 0; a < NUMBER_FONTS; a++)
    {
        all_results[a] = calloc(NUMBER_PATTERNS, sizeof(long double));
        all_targets[a] = calloc(NUMBER_PATTERNS, sizeof(long double));
    }
    for(a = 0; a < NUMBER_FONTS; a++)
        for(b = 0; b < NUMBER_PATTERNS; b++)
        {
            all_results[a][b] = calloc(NUMBER_PIXELS_CHARACTER,
                    sizeof(long double));
            all_targets[a][b] = calloc(NUMBER_PIXELS_CHARACTER,
                    sizeof(long double));
        }

    for(a = 0; a < NUMBER_FONTS; a++)
        for(b = 0; b < NUMBER_PATTERNS; b++)
            all_targets[a][b][b] = 1;

    //*******************************************//
    //          VARIABLES AFFECTATIONS           //
    //*******************************************//

    //Initialize the flags structs
    flags.learning = 0;
    flags.serialize = 0;
    iterations = 0;
    error = 100;

    if(checkFlags(argc, argv, &flags, &all_inputs))
        return 1;
    else
    {
        initialization_neural_network(&neural_network, NUMBER_PATTERNS,
                NUMBER_INPUT_NEURONS,
                NUMBER_HIDDEN_NEURONS,
                BIAS);
        inputsUser = all_inputs[0][0 + 9];

        if(flags.learning == 0)
        {
            //Compute just for checking
            printResultsVector(compute_character(&neural_network.network,
                        inputsUser), NUMBER_PATTERNS);
        }
        else
        {
            learning_fonts(&neural_network.network, NUMBER_PATTERNS, &iterations,
                    NUMBER_FONTS, &all_inputs, &all_targets,
                    &all_results,
                    &error, ETA, ALPHA, ERROR);
            printResultsVector(compute_character(&neural_network.network,
                        inputsUser), NUMBER_PATTERNS);
            if(flags.serialize)
                serialization(&neural_network.network);
        }
    }
    printf("\n\n");
    return 0;
}

static int checkFlags(int argc, char *argv[], struct s_flags_nn *flags,
        long double ****p_all_inputs)
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
                // TODO : REMOVE THIS FUCKIN TEST BUT BZKFERZGFROZKZGKOEROGER
                // BAPTISTE WANT THIS SHIT BECAUSE SOME TIMES ITS PAIN IN
                // THE ASS TO UNDERSTAND THAT I MAKE GOOD CODE EVERY FUCKIN
                // DAY BUT WHEN I SLEEP I MAKE SOME AWESOME FUCKING GODLIKE
                // CODE.
                // LET ME SLEEP !!!!!!!!!!!!!!!!!

                // Sleeping is cheating
                // You are weak
                // Nixon said : what an old cock sucker
                size_t dzed;
                (*p_all_inputs) = load_image_set(flags->dataset_files, 52, &dzed);
            }
        }
        else
            return print_flag_error();
    }
    return 0;
}


static int print_flag_error(void)
{
    printf("Flag ERROR : type -h for help\n");
    return 1;
}

static void print_nn_help(void)
{
    printf("\n\n./main then -\"your arguments\"\n");
    printf("Here is the list of available args : \n"
            "-learning -> start the learning process\n"
            "-serialize -> serialize the NN into serialize\n"
            "-datasetsfiles 2.png\n\n");
}
