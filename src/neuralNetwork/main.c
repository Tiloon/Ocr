#include <stdio.h>
#include <stdlib.h>

#include "network.h"

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

int main(void)
{
    //*******************************************//
    //             VARIABLES DECLARATIONS        //
    //*******************************************//

    struct s_layer input;
    struct s_layer hidden;
    struct s_layer output;
    struct s_network network;

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
    long double  *target11 = malloc(sizeof(long double) * 1);

    long double error;
    int iterations, i;

    //*******************************************//
    //          VARIABLES AFFECTATIONS           //
    //*******************************************//

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





    initializeLayer(&input, 2, 4, BIAS);
    initializeLayer(&hidden, 4, 1, BIAS);
    initializeLayer(&output, 1, 0, BIAS);

    initializeNetwork(&network, &input, &hidden, &output);

    printf("****************\n");
    printf("Starting results\n");

    setInputs(&network, inputs00);
    feedForward(&network);
    printOutput(&network);

    setInputs(&network, inputs10);
    feedForward(&network);
    printOutput(&network);

    setInputs(&network, inputs01);
    feedForward(&network);
    printOutput(&network);

    setInputs(&network, inputs11);
    feedForward(&network);
    printOutput(&network);

    learning(&network, 4, &iterations, &inputs, &targets, &results,&error,
	     ETA, ALPHA, 0.001);

    printf("******************\n");
    printf("AFTER LEARNING\n\n");

    setInputs(&network, inputs00);
    feedForward(&network);
    printOutput(&network);

    setInputs(&network, inputs10);
    feedForward(&network);
    printOutput(&network);

    setInputs(&network, inputs01);
    feedForward(&network);
    printOutput(&network);

    setInputs(&network, inputs11);
    feedForward(&network);
    printOutput(&network);
    printf("Error : %Lf\n", error);
    return 0;
}


