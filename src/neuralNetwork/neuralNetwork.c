//***********************************************************************//
//                      THE GAME                                         //
//***********************************************************************//


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "neuralNetwork.h"


//*************************************//
//            DEFINE                   //
//*************************************//

#define FIRST_BIAS 0
#define ALPHA 0.5 //Used for learning part
#define eta 0.1   //Also used for learning part


//***********************************//
// Tests functions                   //
//**********************************///



int main(void)
{
    /*THIS IS JUST FOR TESTING*/
    /*NN with 3 layer, 1 input, 1 hidden 1 output*/
    /*No Learning for now*/

    //Variables declaration
    Layer Input;
    Layer Hidden;
    Layer Output;
 
    long double error;

    initializeLayer(&Input, 3, 2);
    initializeLayer(&Hidden, 2, 1);
    initializeLayer(&Output, 1, 1);
    
    Input.Units[0].computedValue = 1;
    Input.Units[0].weights[0] = 0.5;
    Input.Units[0].weights[1] = 0.2;
   
    
    Input.Units[1].computedValue = 2;
    Input.Units[1].weights[0] = 0.5;
    Input.Units[1].weights[1] = 0.3;

 
    Input.Units[2].computedValue = 3;
    Input.Units[2].weights[0] = 0.5;
    Input.Units[2].weights[1] = 0.1;

    Hidden.Units[0].weights[0] = 0.2;
    Hidden.Units[1].weights[0] = 0.1;

    
    computeData(&Input, &Hidden, &Output);
    
    printf("%Lf\n"
	   "%Lf\n\n"
	   ,Output.Units[0].sumedValue, Output.Units[0].computedValue);

    return 0;
}


void initializeLayer(Layer *Layer, unsigned pNumberUnits, unsigned pNumberWeights)
{
    Neural Neural;
    unsigned i;
  
    //Number of Neuron on the Layer
    Layer->numberUnits = pNumberUnits;
  
    //Malloc tab of Neural of the Layer
    Layer->Units = malloc(sizeof (Neural) * pNumberUnits);

    for(i = 0; i < pNumberUnits; i++)
    {
	initializeNeuron(&Layer->Units[i], pNumberWeights);
    }
}

void initializeNeuron(Neural *Neuron, unsigned pNumberWeights)
{
    //w for numberWeights
    unsigned w;
    //Initialize each variables
    Neuron->computedValue = 0;
    Neuron->sumedValue = 0;
    Neuron->bias = FIRST_BIAS;
    Neuron->numberWeights = pNumberWeights;
    Neuron->delta = 0;
    Neuron->delta2 = 0;

    //Malloc the weights tab
    Neuron->weights = malloc(sizeof(long double) * pNumberWeights);
    
    //Initialize all weights to 0. Will be aleatory later
    for(w = 0; w < pNumberWeights; w++)
    {
	Neuron->weights[w] = 0;
    }
}

void freeLayer(Layer *Layer)
{
    //TO DO
}
void freeNeuron(Neural *Neural)
{
    //TO DO
}


void  computeSum(Layer *Layer1, Layer *Layer2)
{
    unsigned l1, l2;

    for(l2 = 0; l2 < Layer2->numberUnits; l2++)
    {
	Layer2->Units[l2].sumedValue = Layer2->Units[l2].bias;
	for(l1 = 0; l1 < Layer1->numberUnits; l1++)
	{
	    Layer2->Units[l2].sumedValue += 
		Layer1->Units[l1].computedValue * Layer1->Units[l1].weights[l2]; 
	}
	Layer2->Units[l2].computedValue = sigmoid(Layer2->Units[l2].sumedValue);
    }
}

long double computeSum2(Layer *Layer1, unsigned units, Layer *Layer2)
{
    unsigned numberLinks;
    long double result = 0;
    return result;
}



long double sigmoid(long double x)
{
    return (1 / (1 + exp(-1 * x)));
}
void computeData(Layer *Input, Layer *Hidden, Layer *Output)
{
    computeSum(Input, Hidden);
    computeSum(Hidden, Output);
}

void computeError(long double **expected, long double **computed, 
		  long double *error,
		  unsigned nbPatterns, unsigned nbOutputNeurons)
{
    // p as pattern and n as (output) neuron 
    unsigned p, n;
    for(p=0; p < nbPatterns; p++)
    {
	for(n=0; n < nbOutputNeurons; n++)
	{
	    *error += 0.5 * 
		(expected[p][n] - computed[p][n]) * 
		(expected[p][n] - computed[p][n]) ;
	}
    }
}

void computeDeltaOutput(long double **expected, Layer *OutputLayer, 
			unsigned numberPatterns)
{
    //p as patterns, n as (output) neurons
    unsigned p, n;
    for(p = 0; p < numberPatterns; p++)
    {
	for(n = 0; n < OutputLayer->numberUnits; n++)
	{
	    //Compute the delta for each output neuron
	    //This calculus is actually the derivate of the sigmoid function
	    OutputLayer->Units[n].delta = 
		(expected[p][n] - OutputLayer->Units[n].computedValue) * 
		OutputLayer->Units[n].computedValue *
		(1.0 - OutputLayer->Units[n].computedValue);
	}
    }
}
 

void computeDeltaHidden(Layer *HiddenLayer, Layer *OutputLayer)
{
    long double sumValueWeights;
    //hN for Hidden neurons and On for Output neurons 
    unsigned hN;
    unsigned oN;
  
    for(hN = 0; hN < HiddenLayer->numberUnits; hN++)
    {
	for(oN = 0; oN < OutputLayer->numberUnits; oN++)
	{
	    //Compute the delta for each hidden neuron
	    sumValueWeights = 0;
	  
	  
	}     
    }
}
