#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "network.h"

int main(void)
{
    srand(time(NULL));

    Layer Input;
    Layer Hidden;
    Layer Output;
    Network Network;
    
    double long *inputs00 = malloc(sizeof(long double) * 2);
    inputs00[0] = 0;
    inputs00[1] = 0;
    double long *inputs10 = malloc(sizeof(long double) * 2);
    inputs10[0] = 1;
    inputs10[1] = 0;

    
    initializeLayer(&Input, 2, 2, 0.5);
    initializeLayer(&Hidden, 2, 1, 0.5);
    initializeLayer(&Output, 1, 0, 0.5);

    initializeNetwork(&Network, &Input, &Hidden, &Output);
    
    feedForward(&Network);
    printLayer(Input, "Input\0");
    printLayer(Hidden, "Hidden\0");
    printLayer(Output, "Output\0");
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
