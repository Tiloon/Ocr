#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "network.h"

#define ETA 0.5
#define ALPHA 0.6
#define BIAS 0.5
//**********************************************//
//                 CHECK FUNCTIONS              //
//**********************************************//
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


int main(void)
{
    srand(time(NULL));
    
    //*******************************************//
    //             VARIABLES DECLARATIONS        //
    //*******************************************//
    
    Layer Input;
    Layer Hidden;
    Layer Output;
    Network Network;

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
    
    iterations = 1000;
    error = 0;
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


    

            
    initializeLayer(&Input, 2, 3, BIAS);
    initializeLayer(&Hidden, 3, 1, BIAS);
    initializeLayer(&Output, 1, 0, BIAS);

    initializeNetwork(&Network, &Input, &Hidden, &Output);
    

/* WORKING TRAINING    
    for(i = 0; i < iterations; i++)
    { 
	setInputs(&Network, inputs00);
	feedForward(&Network);
	outputsToList(&Network, &results);
	updateWeights(&Network, target00, results, 0.5, 0.1);
	printOutput(Network);

	
	setInputs(&Network, inputs10);
	feedForward(&Network);
        outputsToList(&Network, &results);
        updateWeights(&Network, target10, results, 0.5, 0.1);
	printOutput(Network);
    }
*/
/*
    learning(&Network, 4, 0, &inputs, &targets, &results, 0.5, 0.1);
    
    setInputs(&Network, inputs00);                                             
    feedForward(&Network);                                                     
    printOutput(Network);

    setInputs(&Network, inputs10);
    feedForward(&Network);
    printOutput(Network);

    setInputs(&Network, inputs01);
    feedForward(&Network);
    printOutput(Network);

    setInputs(&Network, inputs11);
    feedForward(&Network);
    printOutput(Network);
*/

    learning(&Network, 4, 500000, &inputs, &targets, &results,&error,
	     ETA, ALPHA);
    printf("computed\n");
    printMatrix(&results, 4, 1);
    
    return 0;
}


//***************************************************//
//               LAYER METHODS                       //
//***************************************************//

void initializeLayer(Layer *Layer, int nbUnits, int nbWeights,
		     long double bias)
{
    int u, w;
    Layer->nbUnits = nbUnits;
    Layer->nbWeights = nbWeights;

    //Malloc weights
    Layer->weights = malloc(sizeof(long double) * nbUnits);
    for(u = 0; u < Layer->nbUnits; u++)
    {
	Layer->weights[u] = malloc(sizeof(long double) * nbWeights);
    }
    for(u = 0; u < Layer->nbUnits; u++)
    {
	for(w = 0; w < Layer->nbWeights; w++)
	{
	    Layer->weights[u][w] = randomValues(); 
	}
    }
    
    //Malloc deltaWeights
    Layer->deltaWeights = malloc(sizeof(long double) * nbUnits);
    for(u = 0; u < Layer->nbUnits; u++)
    {
        Layer->deltaWeights[u] = malloc(sizeof(long double) * nbWeights);
    }
    for(u = 0; u < Layer->nbUnits; u++)
    {
	for(w = 0; w < Layer->nbWeights; w++)
        {
            Layer->deltaWeights[u][w] = 0;
        }
    }

    //Malloc output
    Layer->outputs = malloc(sizeof(long double) * nbUnits);
    
    //Malloc bias
    Layer->bias = malloc(sizeof(long double) * nbUnits);
    for(u = 0; u < Layer->nbUnits; u++)
	Layer->bias[u] = bias;
    
    //Malloc deltaBias
    Layer->deltaBias = malloc(sizeof(long double) * nbUnits);
    for(u = 0; u < Layer->nbUnits; u++)
	Layer->deltaBias[u] = 0;

    //Malloc delta
    Layer->delta = malloc(sizeof(long double) * nbUnits);
    for(u = 0; u < Layer->nbUnits; u++)
	Layer->delta[u] = 0;
    
}

void printLayer(Layer Layer, char *str)
{
    int u, w;
    
    printf("\n***************\n");
    printf("layer %s\n\n", str);
    printf("nb units %d \n", Layer.nbUnits);
    printf("nb weights %d\n\n", Layer.nbWeights);
    
    for(u = 0; u < Layer.nbUnits; u++)
    {
	printf("neuron : %d\n", u);
	printf("bias : %Lf\n", Layer.bias[u]);
	printf("delta bias : %Lf\n", Layer.deltaBias[u]);
	printf("output : %Lf\n", Layer.outputs[u]);
	printf("delta : %Lf\n\n", Layer.delta[u]);
    }

    for(u = 0; u < Layer.nbUnits; u++)
    {
	for(w = 0; w < Layer.nbUnits; w++)
	{
	    printf("weights[%d][%d] : %Lf\n", u, w, Layer.weights[u][w]);
	}
    }
    for(u = 0; u < Layer.nbUnits; u++)
    {
        for(w = 0; w < Layer.nbUnits; w++)
        {
            printf("delta weights[%d][%d] : %Lf\n", u, w,
		   Layer.deltaWeights[u][w]);
	}
    }

}

long double randomValues()
{
    static unsigned seed;
    
    if(!seed)
        srand(seed = (unsigned)time(NULL));
    return 1 - ((long double)rand()/(((long double)RAND_MAX) / 2.0));
}

void computeValues(Layer *L1, Layer *L2)
{
    long double sum;
    int prev, curr;
    for(curr = 0; curr < L2->nbUnits; curr++)
    {
	//Bias
	sum = L2->bias[curr];
	for(prev = 0; prev < L1->nbUnits; prev++)
	{
	    sum += L1->outputs[prev] * L1->weights[prev][curr];
	}
	L2->outputs[curr] = sigmoid(sum);
    }
}

long double sigmoid(long double x)
{
    return (1 / (1 + exp(-x)));
}

//***************************************************//
//               NETWORK METHODS                     //
//***************************************************//

void initializeNetwork(Network *Network,
		       Layer *Input, Layer *Hidden, Layer *Output)
{
    Network->Input = Input;
    Network->Hidden = Hidden;
    Network->Output = Output;
}

void printOutput(Network Network)
{
    printf("Output value : %Lf\n", Network.Output->outputs[0]);
}

void feedForward(Network *Network)
{
    computeValues(Network->Input, Network->Hidden);
    computeValues(Network->Hidden, Network->Output);
}

void setInputs(Network *Network, long double *inputs)
{
    Network->Input->outputs[0] = inputs[0];
    Network->Input->outputs[1] = inputs[1];
}

void outputsToList(Network *Network, long double **storeData)
{
    int u;
    for(u = 0; u < Network->Output->nbUnits; u++)
    {
	(*storeData)[u] = Network->Output->outputs[u];
    }
}

//**********************************************//
//               LEARNING METHODS               //
//**********************************************//

void computeDeltaO(Network *Network,
                     long double *target, long double *computed)
{
    int u;
    for(u = 0; u < Network->Output->nbUnits; u++)
        Network->Output->delta[u] =
            (target[u] - computed[u]) * computed[u] * (1.0 - computed[u]);
}

void computeDeltaH(Network *Network)
{
    int u, out;
    long double sum;
    for(u = 0; u < Network->Hidden->nbUnits; u++)
    {
	sum = 0;
	for(out = 0; out < Network->Output->nbUnits; out++)
	{
	    sum +=  Network->Hidden->weights[u][out] * 
		Network->Output->delta[out];    
	}
	Network->Hidden->delta[u] = sum * 
	    Network->Hidden->outputs[u] * (1.0 - Network->Hidden->outputs[u]);
    }
}

void computeDeltaWeights(Layer *Previous, Layer *Next,
			 long double eta, long double alpha)
{
    int u,  w;
    for(w = 0; w < Next->nbUnits; w++)
    {
	//Update Bias
	Next->deltaBias[w] = (eta * Next->delta[w]) +
	    (alpha * Next->deltaBias[w]); 
	for(u = 0; u < Previous->nbUnits; u++)
	{
	    //Update the delta weights
	    Previous->deltaWeights[u][w] = 
		(eta * Previous->outputs[u] * Next->delta[w]) +
		(alpha * Previous->deltaWeights[u][w]);
	    Previous->weights[u][w] += Previous->deltaWeights[u][w];
	}
    }
}

void updateWeights(Network *Network,
		   long double *target, long double *computed,
		   long double eta, long double alpha)
{
    computeDeltaO(Network, target, computed);
    computeDeltaH(Network);
    computeDeltaWeights(Network->Input, Network->Hidden, eta, alpha);
    computeDeltaWeights(Network->Hidden, Network->Output, eta, alpha);
}

void learning(Network *Network, int nbPatterns, int nbIterations,
	      long double ***inputs, long double ***targets, 
	      long double ***computed, long double *error,
	      long double eta, long double alpha)
{
    int p, i;

    for(i = 0; i < nbIterations; i++)
    {
	for(p = 0; p < nbPatterns; p++)
	{
	    setInputs(Network, (*inputs)[p]);
	    feedForward(Network);
	    outputsToList(Network, &(*computed)[p]);
	    updateWeights(Network, (*targets)[p], (*computed)[p], eta, alpha);
	    computeError(targets, computed, 4, error);
	    if(p % 10 == 0)
		printf("error %Lf\n", *error);
	}
    }
}

void computeError(long double ***targets, long double ***outputs,
		  int nbPatterns, long double *error)
{
    int p;
    *error = 0;
    for(p = 0; p < nbPatterns; p++)
    {
	*error += 0.5 * ((*targets)[p][0] - (*outputs)[p][0]) * 
	    ((*targets)[p][0] - (*outputs)[p][0]);
    } 
}
