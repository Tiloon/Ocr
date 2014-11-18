#ifdef _NN_TEST

#include <stdio.h>
#include <stdlib.h>

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


void printOutput(struct s_network *network)
{
    printf("Output value : %Lf\n", network->output->outputs[0]);
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


    long double *inputsUser = malloc(sizeof(long double) * 2);
    long double **inputs = malloc(sizeof(long double) * 4);
    long double **targets = malloc(sizeof(long double) * 4);
    long double **results = malloc(sizeof(long double) * 4);
    long double *inputs00 = malloc(sizeof(long double) * 2);
    long double *inputs10 = malloc(sizeof(long double) * 2);
    long double *inputs01 = malloc(sizeof(long double) * 2);
    long double *inputs11 = malloc(sizeof(long double) * 2);
    long double *target00 = malloc(sizeof(long double) * 1);
    long double *target10 = malloc(sizeof(long double) * 1);
    long double *target01 = malloc(sizeof(long double) * 1);
    long double *target11 = malloc(sizeof(long double) * 1);

    long double error;
    int iterations, i;

    //*******************************************//
    //          VARIABLES AFFECTATIONS           //
    //*******************************************//

    //Initialize the flags structs
    flags.inputsSet = 0;
    flags.learning = 0;
    flags.iterations = -1;

    //Malloc all the matrix
    for(i = 0; i < 4; i++)
    {
        inputs[i] = malloc(sizeof(long double) * 2);
        targets[i] = malloc(sizeof(long double) * 1);
        results[i] = malloc(sizeof(long double) * 1);
    }

    iterations = 0;
    error = 100;

    //Set the inputs
    inputs00[0] = 0;
    inputs00[1] = 0;
    inputs10[0] = 1;
    inputs10[1] = 0;
    inputs01[0] = 0;
    inputs01[1] = 1;
    inputs11[0] = 1;
    inputs11[1] = 1;

    inputs[0] = inputs00;
    inputs[1] = inputs01;
    inputs[2] = inputs10;
    inputs[3] = inputs11;

    //Set the targets
    target00[0] = 0;
    target10[0] = 1;
    target01[0] = 1;
    target11[0] = 0;

    targets[0] = target00;
    targets[1] = target10;
    targets[2] = target01;
    targets[3] = target11;

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
