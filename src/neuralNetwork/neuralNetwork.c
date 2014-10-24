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

#define FIRST_BIAS 0.5
#define ALPHA 0.3 //Used for learning part
#define ETA 0.01   //Also used for learning part
#define NUMBER_INPUTS 2 
#define NUMBER_OUTPUTS 1
#define NUMBER_PATTERN 4
//***********************************//
// Tests functions                   //
//**********************************///

void printAll(Layer *Layer)
{
    unsigned u;
    unsigned w;
    for(u = 0; u < Layer->numberUnits; u++)
    {
	printf("******************************\n"
	       "           Neuron %d          \n", u);      
	printf("Computed value : %Lf\n", Layer->Units[u].computedValue);
	printf("Sumed value : %Lf\n", Layer->Units[u].sumedValue);
	printf("delta : %Lf\n", Layer->Units[u].delta);
	printf("bias : %Lf\n", Layer->Units[u].bias);
	for(w = 0; w < Layer->Units[u].numberWeights; w++)
	    printf("Poids %d : %Lf\n", w, Layer->Units[u].weights[w]);
	for(w = 0; w < Layer->Units[u].numberWeights; w++)
	    printf("Delta Weights %d : %Lf\n", w, 
		   Layer->Units[u].deltaWeights[w]);
    }
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
 
    //double long **input;
    double long *input0;
    double long *input1;
    double long *input2;
    double long *input3;

    double long *expected0;
    double long *expected1;
    double long *expected2;
    double long *expected3;

    double long error = 0;

    double long *results;
    
    //Initialising neural network
    initializeLayer(&Input, 2, 2);
    initializeLayer(&Hidden, 2, 1);
    initializeLayer(&Output, 1, 1);
    
    //Set the starting weights
    Input.Units[0].weights[0] = 1.7;
    Input.Units[0].weights[1] = -1.2;
    
    Input.Units[1].weights[0] = -2.68;
    Input.Units[1].weights[1] = 1.3;
   
    Hidden.Units[0].weights[0] = 1.3;
    Hidden.Units[1].weights[0] = -1.3;
    
    //Initializing the inputs
    input0 = malloc(sizeof(long double) * NUMBER_INPUTS);
    input0[0] = 0;
    input0[1] = 0;
    input1 = malloc(sizeof(long double) * NUMBER_INPUTS);
    input1[0] = 0;
    input1[1] = 1;
    input2 = malloc(sizeof(long double) * NUMBER_INPUTS);
    input2[0] = 1;
    input2[1] = 0;
    input3 = malloc(sizeof(long double) * NUMBER_INPUTS);
    input3[0] = 1;
    input3[1] = 1;

    //Initializing the expected results
    expected0 = malloc(sizeof(long double) * NUMBER_OUTPUTS);
    expected0[0] = 0;
    expected1 = malloc(sizeof(long double) * NUMBER_OUTPUTS);
    expected1[0] = 1;
    expected2 = malloc(sizeof(long double) * NUMBER_OUTPUTS);
    expected2[0] = 1;
    expected3 = malloc(sizeof(long double) * NUMBER_OUTPUTS);
    expected3[0] = 0;
    
    //Initialising results tab
    results = malloc(sizeof(long double) * NUMBER_OUTPUTS);
    
    /*  Compute all the pattern for the beginning values
     *  will be used for compare the value after learning
     */

    computePattern(input0, &Input, &Hidden, &Output);
    printf("results for XOR 0 : %Lf\n", Output.Units[0].computedValue);
    computePattern(input1, &Input, &Hidden, &Output);
    printf("results for XOR 1 : %Lf\n", Output.Units[0].computedValue);
    // computePattern(input2, &Input, &Hidden, &Output);
    //printf("results for XOR 2 : %Lf\n", Output.Units[0].computedValue);
    // computePattern(input3, &Input, &Hidden, &Output);
    //printf("results for XOR 3 : %Lf\n", Output.Units[0].computedValue);
  
    unsigned i;
    for(i = 0; i < 5; i++)
    {
	computePattern(input0, &Input, &Hidden, &Output);
	resultsToTab(&Output, &results);
	computeError(expected0, results, &error, 1);
	computeDeltaOutput(&Output, expected0, results);
	computeDeltaHidden(&Hidden, &Output);
	computeDeltaWeight(ETA, ALPHA, &Input, &Hidden);
	computeDeltaWeight(ETA, ALPHA, &Hidden, &Output);
	

	computePattern(input1, &Input, &Hidden, &Output);
        resultsToTab(&Output, &results);
        computeError(expected1, results, &error, 1);
        computeDeltaOutput(&Output, expected1, results);
        computeDeltaHidden(&Hidden, &Output);
        computeDeltaWeight(ETA, ALPHA, &Input, &Hidden);
        computeDeltaWeight(ETA, ALPHA, &Hidden, &Output);
	error = 0;
	

	computePattern(input0, &Input, &Hidden, &Output);
	printf("results for XOR 0 : %Lf\n", Output.Units[0].computedValue);
	computePattern(input1, &Input, &Hidden, &Output);
	printf("results for XOR 1 : %Lf\n", Output.Units[0].computedValue);

    }

    computePattern(input0, &Input, &Hidden, &Output);
    printf("results for XOR 0 : %Lf\n", Output.Units[0].computedValue);
    computePattern(input1, &Input, &Hidden, &Output);
    printf("results for XOR 1 : %Lf\n", Output.Units[0].computedValue);

    
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
    Neuron->numberWeights = pNumberWeights;
    Neuron->delta = 0;
    Neuron->bias = FIRST_BIAS;
    Neuron->deltaBias = 0;
	
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

void computeError(long double *expected, long double *computed, 
		  long double *error, unsigned nbOutputNeurons)
{
    // p as pattern and n as (output) neuron 
    unsigned n;    
    for(n = 0; n < nbOutputNeurons; n++)
    {
	*error += 0.5 * 
	    (expected[n] - computed[n]) * 
	    (expected[n] - computed[n]) ;
    }
}

void resultsToTab(Layer *OutputLayer, long double **results)
{
    unsigned u;
    for(u = 0; u < OutputLayer->numberUnits; u++)
	(*results)[u] = OutputLayer->Units[u].computedValue;	
}

void computePattern(long double *patternInput,
		    Layer *Input, Layer *Hidden, Layer *Output)
{
    unsigned n;
    for(n = 0; n < Input->numberUnits; n++)
    {
	Input->Units[n].computedValue = patternInput[n];
    }
    computeData(Input, Hidden, Output);
}

void computeDeltaOutput(Layer *Output, long double *expected,
			long double *computed)
{
    unsigned u;
    for(u = 0; u < Output->numberUnits; u++)
    {
	Output->Units[u].delta = (expected[u] - computed[u]) * 
	    computed[u] * (1.0 - computed[u]);
    }
}

void computeDeltaHidden(Layer *Hidden, Layer *Output)
{
    unsigned h, o;
    long double error;
    for(h = 0; h < Hidden->numberUnits; h++)
    {
	error = 0;
	for(o = 0; o < Output->numberUnits; o++)
	{
	    error += (Hidden->Units[h].weights[o] * Output->Units[o].delta);
	}
	Hidden->Units[h].delta = Hidden->Units[h].computedValue *
	    (1.0 - Hidden->Units[h].computedValue) * error;
    }
}

void computeDeltaWeight(long double eta, long double alpha, 
			Layer *ToUpdate, Layer *Next)
{
    unsigned next, current;
    for(next = 0; next < Next->numberUnits; next++)
    {
    //First : update the bias next Layer
	Next->Units[next].deltaBias = (eta * Next->Units[next].delta) + 
	    (alpha * Next->Units[next].deltaBias);
	
	Next->Units[next].bias += Next->Units[next].deltaBias;
	for(current = 0; current < ToUpdate->numberUnits; current++)
	{
	    //Then : update the weights from ToUpdate to Next
	    ToUpdate->Units[current].deltaWeights[next] = 
		(eta * ToUpdate->Units[current].weights[next] 
		 * Next->Units[next].delta)
		+ (alpha * ToUpdate->Units[current].deltaWeights[next]);
	    
	    ToUpdate->Units[current].weights[next] += 
	ToUpdate->Units[current].deltaWeights[next];
	}
    }
}
