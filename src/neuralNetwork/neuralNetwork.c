//*************************************************************** ***//
//                      THE GAME                                     //
//*******************************************************************//


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "neuralNetwork.h"


//*************************************//
//            DEFINE                   //
//*************************************//

#define FIRST_BIAS 0
#define ALPHA 0.5 //Used for learning part
#define ETA 0.1   //Also used for learning part


//***********************************//
// Tests functions                   //
//**********************************///
void printt(long double ***tab)
{
    unsigned j = 0, i = 0;
    for(i = 0; i < 4; i++)
	for(j = 0; j < 2; j++)
	    printf("%Lf\n\n", (*tab)[i][j]);
}

int main(void)
{
    /*THIS IS JUST FOR TESTING*/
    /*NN with 3 layer, 1 input, 1 hidden 1 output*/
    /*No Learning for now*/

    //Variables declaration
    
    Layer Input;
    Layer Hidden;
    Layer Output;
 
    long double error = 0;
    long double *results;
    
    long double *input1 = {0, 0};
    long double *input2 = {1, 0};
    long double *input3 = {0, 1};
    long double *input4 = {1, 1};

    unsigned i = 0;
        
    long double **expected;
    long double **computed;

    computed = malloc(sizeof(long double) * 4);
    for(i = 0; i < 4; i++)
        computed[i] = malloc(sizeof(long double) * 1);

    computed[0][0] = 0.537430;
    computed[1][0] = 0.544749;
    computed[2][0] = 0.545359;
    computed[3][0] = 0.551927;

    
    expected = malloc(sizeof(long double) * 4);
    for(i = 0; i < 4; i++)
    	expected[i] = malloc(sizeof(long double) * 1);
    
    
    expected[0][0] = 0;
    expected[1][0] = 1;
    expected[2][0] = 1;
    expected[3][0] = 0;
            
    initializeLayer(&Input, 2, 2);
    initializeLayer(&Hidden, 2, 1);
    initializeLayer(&Output, 1, 1);
    
    Input.Units[0].computedValue = 1;
    Input.Units[0].weights[0] = 0.5;
    Input.Units[0].weights[1] = 0.2;
   
    
    Input.Units[1].computedValue = 1;
    Input.Units[1].weights[0] = 0.5;
    Input.Units[1].weights[1] = 0.3;
   
    Hidden.Units[0].weights[0] = 0.2;
    Hidden.Units[1].weights[0] = 0.1;
    
    
    computeData(&Input, &Hidden, &Output);

    for(i = 0; i < 1000; i++)
    {
	error = 0;
        //TO DO
	computePattern(&expected, &computed, input1, 4, &Input, &Hidden,
		       &Output, ETA, ALPHA, &error, results);
	printf("%Lf\n", Output.Units[0].computedValue); 
    }

    
    return 0;
}


void initializeLayer(Layer *Layer, unsigned pNumberUnits, 
		     unsigned pNumberWeights)
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
    Neuron->deltaBias = 0;
    Neuron->numberWeights = pNumberWeights;
    Neuron->delta = 0;
    
    //Malloc the weights tab
    Neuron->weights = malloc(sizeof(long double) * pNumberWeights);
    
    //Initialize all weights to 0. Will be aleatory later
    for(w = 0; w < pNumberWeights; w++)
    {
	Neuron->weights[w] = 0;
    }

    //Malloc the delta weights tab
    Neuron->deltaWeights = malloc(sizeof(long double) * pNumberWeights);
    
    //Initialize all the delta weights
    for(w = 0; w < pNumberWeights; w++)
    {
	Neuron->deltaWeights[w] = 0;
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

long double sigmoid(long double x)
{
    return (1 / (1 + exp(-1 * x)));
}
void computeData(Layer *Input, Layer *Hidden, Layer *Output)
{
    computeSum(Input, Hidden);
    computeSum(Hidden, Output);
}

void computeError(long double ***expected, long double ***computed, 
		  long double *error,
		  unsigned nbPatterns, unsigned nbOutputNeurons)
{
    // p as pattern and n as (output) neuron 
    unsigned p, n;    
    for(p = 0; p < nbPatterns; p++)
    {	
	for(n = 0; n < nbOutputNeurons; n++)
	{
	    *error += 0.5 * 
		((*expected)[p][n] - (*computed)[p][n]) * 
		((*expected)[p][n] - (*computed)[p][n]) ;
	}
    }
}

void computeDeltaOutput(long double ***expected, Layer *OutputLayer, 
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
		((*expected)[p][n] - OutputLayer->Units[n].computedValue) * 
		OutputLayer->Units[n].computedValue *
		(1.0 - OutputLayer->Units[n].computedValue);
	}
    }
}
 

void computeDeltaHidden(Layer *HiddenLayer, Layer *OutputLayer)
{
    long double deltaH;
    //h for Hidden neurons and O for Output neurons 
    unsigned h;
    unsigned o;
  
    for(h = 0; h < HiddenLayer->numberUnits; h++)
    {
	deltaH = 0;
	for(o = 0; o < OutputLayer->numberUnits; o++)
	{
	    //Compute the delta for each hidden neuron
	    deltaH +=  
		(HiddenLayer->Units[h].weights[o] *
		 OutputLayer->Units[o].delta);
	}
	deltaH = deltaH * HiddenLayer->Units[h].computedValue
	    * (1.0 - HiddenLayer->Units[h].computedValue);
	HiddenLayer->Units[h].delta = deltaH;
    }
}

void computeDeltaWeight(long double eta0, long double alpha,
			Layer *LayerToUpdate, Layer *NextLayer)
{
    //for counting the units of the Layer to update, n for next Layer
    unsigned u, n;
    for(u = 0; u < LayerToUpdate->numberUnits; u++)
    {
	//Update deltaBias
	LayerToUpdate->Units[u].deltaBias = 
	    (eta0 * LayerToUpdate->Units[u].computedValue)
	    + (alpha * LayerToUpdate->Units[u].deltaBias); 
	//Update Bias Weight
	LayerToUpdate->Units[u].bias += LayerToUpdate->Units[u].deltaBias;
    
	for(n = 0; n < NextLayer->numberUnits; n++)
	{
	    LayerToUpdate->Units[u].deltaWeights[n] = 
		(eta0 * LayerToUpdate->Units[u].computedValue  *
		 NextLayer->Units[n].delta) + 
		(alpha * LayerToUpdate->Units[u].deltaWeights[n]);
	    
	    LayerToUpdate->Units[u].weights[n] += 
		LayerToUpdate->Units[u].deltaWeights[n];
	}
    }
}

void resultsToTab(Layer *OutputLayer, long double **results)
{
    *results = malloc (sizeof(long double)  * OutputLayer->numberUnits);
    unsigned u;
    for(u = 0; u < OutputLayer->numberUnits; u++)
    {
	(*results)[u] = OutputLayer->Units[u].computedValue;	
    }
}

void learning(long double ***expected, long double ***computed,
	      long double *error, unsigned nbPatterns,
	      Layer *Input, Layer *Hidden, Layer *Output,
	      long double eta0, long double alpha)
{
    computeError(expected, computed, error, nbPatterns, Output->numberUnits);
    computeDeltaOutput(expected, Output, nbPatterns);
    computeDeltaHidden(Hidden, Output);
    computeDeltaWeight(eta0, alpha, Input, Hidden);
    computeDeltaWeight(eta0, alpha, Hidden, Output);
}

void computePattern(long double ***expected, long double ***computed,
                    long double *patterns, long double nbPatterns,
                    Layer *Input, Layer *Hidden, Layer *Output,
                    long double eta0, long double alpha, long double *error,
                    long double *results)
{
    unsigned u;
    for(u = 0; u < Input->numberUnits; u++)
    {
	Input->Units[u].computedValue = patterns[u];
	learning(expected, computed, error, nbPatterns, Input, Hidden,
		 Output, eta0, alpha);
    }
}
