#ifdef _NN_TEST

#include <stdio.h>
#include <stdlib.h>

#include "char.h"
#include "network.h"
#include "layer.h"
#include "nn_main.h"
#include "structure.h"
#include "learning.h"
/*
 * CHECKING FUNCTIONS
 */


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
	printf("%Lf", vector[u]);
}

void printOutput(struct s_network *network)
{
    int u;
    for(u = 0; u < network->output->nbUnits; u++)
    {
	printf("\n %Lf", network->output->outputs[u]);
    }
    printf("\n");
}

/*
 *  testing functions
 */

int checkFlags(int argc, char* argv[], struct s_flags *flags);
int print_flag_error();
void printHelp();

int main(int argc, char *argv[])
{
    //*******************************************//
    //             VARIABLES DECLARATIONS        //
    //*******************************************//

    struct s_layer input;
    struct s_layer hidden;
    struct s_layer output;
    struct s_network network;
    struct s_flags flags;

    int NUMBER_PATTERNS = 10;
    int NUMBER_PIXELS_CHARACTER = 256;

    //inputsUser is used so as to debug/check the NN
    long double *inputsUser = calloc(NUMBER_PIXELS_CHARACTER,
				     sizeof(long double));
    /*
    * *inputs is a matrix with NB_PATTERNS vector
    * contains all the inputs of the NN i-e
    * all the vector of each character recognizable
    * vectors are size of NUMBER_PIXELS_CHARACTER as size
    */

    long double **inputs = calloc(NUMBER_PATTERNS,
				  sizeof(long double));

    /*
     * targets is a matrix of NUM_PATTERNS vector
     * contains all the expected results for each patterns
     * size of vector of each expected results NUM_PATTERN
     */
    long double **targets = calloc(NUMBER_PATTERNS,
				   sizeof(long double));
    /*
     * results is a matrix of NUM_PATTERNS vector
     * contains the results of each patterns
     * Will be compared to targets
     * each vector are size of NUM_PATTERNS
     */
    long double **results = calloc(NUMBER_PATTERNS,
                                   sizeof(long double));

    /*
     * Here are all the vector for each PATTERNS (= nb characters)
     * Will fill the **inputs matrix
     * Vectors are size of NUM_PIXELS_CHARACTERS (=256)
     */
    long double *inputsA = calloc(NUMBER_PIXELS_CHARACTER,
                                   sizeof(long double));
    long double *inputsB = calloc(NUMBER_PIXELS_CHARACTER,
                                   sizeof(long double));
    long double *inputsC = calloc(NUMBER_PIXELS_CHARACTER,
                                   sizeof(long double));

    long double error;
    int iterations, i;

    //*******************************************//
    //          VARIABLES AFFECTATIONS           //
    //*******************************************//

    //Initialize the flags structs
    flags.inputsSet = 0;
    flags.learning = 0;
    flags.iterations = -1;

    /*
     * calloc all the matrix (malloc are for weak people parait-il)
     * **inputs && targets && results
     */

    for(i = 0; i < NUMBER_PATTERNS; i++)
    {
        inputs[i] = calloc(NUMBER_PIXELS_CHARACTER,
			   sizeof(long double));
        targets[i] = calloc(NUMBER_PATTERNS,
			    sizeof(long double));
        results[i] = calloc(NUMBER_PATTERNS,
                            sizeof(long double));
    }

    iterations = 0;
    error = 100;

    //Set the inputs
    stat_to_dyn(CHAR_A, NUMBER_PIXELS_CHARACTER, inputsA);
    stat_to_dyn(CHAR_B, NUMBER_PIXELS_CHARACTER, inputsB);
    stat_to_dyn(CHAR_C, NUMBER_PIXELS_CHARACTER, inputsC);

    //Set the targets
    for(i = 0; i < NUMBER_PATTERNS; i++)
	targets[i][i] = 1;


    if(checkFlags(argc, argv, &flags))
        return 1;
    else
    {
        if(flags.inputsSet == 0)
            return 1;
        else
        {
            initialize_layer(&input, 2, 4, BIAS);
            initialize_layer(&hidden, 4, 1, BIAS);
            initialize_layer(&output, 1, 0, BIAS);

            initialize_network(&network, &input, &hidden, &output);

            inputsUser[0] = flags.input0;
            inputsUser[1] = flags.input1;
            if(flags.learning == 0)
            {
                set_inputs(&network, inputsUser);
                feedforward(&network);
                printOutput(&network);
            }
            else
            {
                if(flags.iterations == -1)
                    learning(&network, 4, &iterations,
                            &inputs, &targets, &results, &error,
                            ETA, ALPHA, 0.001);
                else
                {
                    //TODO
                    learning2(&network, 4, flags.iterations,
                            &inputs, &targets, &results, &error,
                            ETA, ALPHA);
                }
                set_inputs(&network, inputsUser);
                feedforward(&network);
                printOutput(&network);
            }
        }
    }
    printf("\n\n");
    return 0;
}

int checkFlags(int argc, char *argv[], struct s_flags *flags)
{
    int i;
    if(argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        printHelp();
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
        else if(strcmp(argv[i], "-iterations") == 0)
        {
            if(i + 1 >= argc)
                return print_flag_error();
            else
            {
                i++;
                flags->iterations = atoi(argv[i]);
            }
        }
        else if(strcmp(argv[i], "-inputs:00") == 0)
        {
            if(flags->inputsSet)
                return print_flag_error();
            flags->input0 = 0;
            flags->input1 = 0;
            flags->inputsSet = 1;
        }
        else if(strcmp(argv[i], "-inputs:01") == 0)
        {
            if(flags->inputsSet)
                return print_flag_error();
            flags->input0 = 0;
            flags->input1 = 1;
            flags->inputsSet = 1;
        }
        else if(strcmp(argv[i], "-inputs:10") == 0)
        {
            if(flags->inputsSet)
                return print_flag_error();
            flags->input0 = 1;
            flags->input1 = 0;
            flags->inputsSet = 1;
        }
        else if(strcmp(argv[i], "-inputs:11") == 0)
        {
            if(flags->inputsSet)
                return print_flag_error();
            flags->input0 = 1;
            flags->input1 = 1;
            flags->inputsSet = 1;
        }
        else
            return print_flag_error();
    }
    return 0;
}


int print_flag_error()
{
    printf("Flag ERROR : type -h for help\n");
    return 1;
}

void printHelp()
{
    printf("\n\n./main then -\"your arguments\"\n");
    printf("Here is the list of available args : \n"
            "-inputs:00 -> set the inputs to (0,0)\n"
            "-inputs:01 -> set the inputs to (0,1)\n"
            "-inputs:10 -> set the inputs to (1,0)\n"
            "-inputs:11 -> set the inputs to (1,1)\n"
            "-learning -> start the learning process\n"
            "-iterations [white space] \"your number\"\n\n"
            "For example for inputs (0,1) and for learning with 2500 "
            "iterations :\n"
            "--> .\\main -inputs:01 -learning -iterations 2500\n\n");
}

#endif
