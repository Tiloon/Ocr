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

#define FIRST_BIAS 1
#define ALPHA 0.5 //Used for learning part
#define ETA 0.1   //Also used for learning part


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
	printf("bias : %Lf\n", Layer->bias);
	printf("delta bias : %Lf\n", Layer->deltaBias);
	printf("bias weight : %Lf\n", Layer->biasWeight);
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
    
    unsigned p;
    
    long double *results;
    results = malloc(sizeof(long double) *1);
    long double error = 0;
    
    long double **patternList;
    patternList = malloc(sizeof(long double) * 4);
    for(p = 0; p < 4; p++)
	patternList[p] = malloc(sizeof(long double) * 1);  
    long double **expectedResults;
    expectedResults = malloc(sizeof(long double) * 4);
    for(p = 0; p < 4; p++)
	expectedResults[p] = malloc(sizeof(long double) * 1);

    //Declaration of XOR input truth table
    long double *input0;
    input0 = malloc(sizeof(long double) * 2);
    input0[0] = 0;
    input0[1] = 0;
   	
    long double *input1;
    input1 = malloc(sizeof(long double) * 2);
    input1[0] = 1;
    input1[1] = 0;
    
    long double *input2;
    input2 = malloc(sizeof(long double) * 2);
    input2[0] = 0;
    input2[1] = 1;
    
    long double *input3;
    input3 = malloc(sizeof(long double) * 2);
    input3[0] = 1;
    input3[1] = 1;
    
    //Gather all pattern in a list
    patternList[0] = input0;
    patternList[1] = input1;
    patternList[2] = input2;
    patternList[3] = input3;
    
    //Declaration of expected result (of XOR truth table)
    long double *expected0;
    expected0 = malloc(sizeof(long double)*1);
    expected0[0] = 0;
    
    long double *expected1;
    expected1 = malloc(sizeof(long double)*1);
    expected1[0] = 1;

    long double *expected2;
    expected2 = malloc(sizeof(long double)*1);
    expected2[0] = 1;
    
    long double *expected3;
    expected3 = malloc(sizeof(long double)*1);
    expected3[0] = 0;
    
    //Gather all expected results in a list
    expectedResults[0] = expected0;
    expectedResults[1] = expected1;
    expectedResults[2] = expected2;
    expectedResults[3] = expected3;
    
    //Will be used for storing the list of results according to each patterns
    long double **computedPatternResults;
    computedPatternResults = malloc(sizeof(long double) * 4);
    for(p = 0; p < 4; p++)
	computedPatternResults[p] = malloc(sizeof(long double) * 1);
            
    //Initialising neural network
    initializeLayer(&Input, 2, 2);
    initializeLayer(&Hidden, 2, 1);
    initializeLayer(&Output, 1, 1);
    
    Input.Units[0].weights[0] = 0.8;
    Input.Units[0].weights[1] = 0.2;
    
    Input.Units[1].weights[0] = 0.4;
    Input.Units[1].weights[1] = 0.6;
   
    Hidden.Units[0].weights[0] = 0.7;
    Hidden.Units[1].weights[0] = 0.3;
    

    error = 0;
    
    //Quick example of learning on 1 input
   
    int iterations = 100;

    learnOnePattern(&Input, &Hidden, &Output, input0, &results, &expected0,       
                    &error, ETA, ALPHA, iterations);
    
    printf("\n\nInput\n\n");                                                       
    printAll(&Input);                                                              
    printf("Hidden\n\n");                                                          
    printAll(&Hidden);                                                             
    printf("Output\n\n");                                                          
    printAll(&Output);

    computePattern(input0, &Input, &Hidden, &Output);                              
    printf("XOR 0 : %Lf <-- \n\n", Output.Units[0].computedValue); 

    computePattern(input1, &Input, &Hidden, &Output);
    printf("XOR 1 : %Lf <-- \n\n", Output.Units[0].computedValue);
    
    
    return 0;
}


void initializeLayer(Layer *Layer, unsigned pNumberUnits, 
		     unsigned pNumberWeights)
{
    Neural Neural;
    unsigned i;
   
    Layer->bias = FIRST_BIAS;
    Layer->deltaBias  = 0;
    Layer->biasWeight = 1;
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
	Layer2->Units[l2].sumedValue = Layer2->bias * Layer2->biasWeight;
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

void computeError(long double **expected, long double **computed, 
		  long double *error, unsigned nbOutputNeurons)
{
    // p as pattern and n as (output) neuron 
    unsigned n;    
    for(n = 0; n < nbOutputNeurons; n++)
    {
	*error += 0.5 * 
	    ((*expected)[n] - (*computed)[n]) * 
	    ((*expected)[n] - (*computed)[n]) ;
    }
}

void computeDeltaOutput(long double **expected, Layer *OutputLayer)
{
    // n as (output) neurons
    unsigned n;
    for(n = 0; n < OutputLayer->numberUnits; n++)
    {
	//Compute the delta for each output neuron
	//This calculus is actually the derivate of the sigmoid function
	OutputLayer->Units[n].delta = 
	    ((*expected)[n] - OutputLayer->Units[n].computedValue) * 
	    OutputLayer->Units[n].computedValue *
	    (1.0 - OutputLayer->Units[n].computedValue);
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

void computeDeltaWeight(long double eta, long double alpha, 
			Layer *LayerToUpdate, Layer *NextLayer)
{
    unsigned next, current;
    for(next = 0; next < NextLayer->numberUnits; next++)
    {
	NextLayer->deltaBias = 
	    (eta * NextLayer->Units[next].delta) +
	    (alpha * NextLayer->deltaBias);
	NextLayer->biasWeight += NextLayer->deltaBias;
	for(current = 0; current < LayerToUpdate->numberUnits; current++)
	{
	    LayerToUpdate->Units[current].deltaWeights[next] =
		(eta * LayerToUpdate->Units[0].computedValue * 
		 NextLayer->Units[next].delta)+		
		(alpha * LayerToUpdate->Units[current].deltaWeights[next]);
	    
	    LayerToUpdate->Units[current].weights[next] += 
		LayerToUpdate->Units[0].deltaWeights[next];	 
		 
	}
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

void computeError2(long double ***expected, long double ***computed,
		   long double *error, unsigned pNumberNeurons)
{
    unsigned p;
    for(p = 0; p < pNumberNeurons; p++)
    {
	computeError(expected[p], computed[p], error, pNumberNeurons);
    }
}

void learnOnePattern(Layer *Input, Layer *Hidden, Layer *Output,
                     long double *pattern, long double **resultsList,
                     long double **expectedResults,
                     long double *error, long double eta, long double alpha,
                     long double numberIterations)
{
    unsigned i;
    for(i = 0; i < numberIterations; i++)
    {
	computePattern(pattern, Input, Hidden, Output);
	resultsToTab(Output, resultsList);
        computeError(expectedResults, resultsList, error, 1);
	computeDeltaOutput(expectedResults, Output);
        computeDeltaHidden(Hidden, Output);
        computeDeltaWeight(eta, alpha, Input, Hidden);
	computeDeltaWeight(eta, alpha, Hidden, Output);
    }
}

void learnListPattern(Layer *Input, Layer *Hidden, Layer *Output,
                      long double ***pattern, unsigned numberPattern,
		      long double ***resultsList,
                      long double ***expectedResults,
                      long double *error, long double eta, long double alpha,
                      long double numberIterations)
{
    // p counts patterns and i counts iterations
    unsigned p, i;

    for(i = 0; i < numberIterations; i++)
    {
	for(p = 0; p < numberPattern; p++)
	{
	    learnOnePattern(Input, Hidden, Output, (*pattern)[p], 
			    &(*resultsList)[p], &(*expectedResults)[p],
			    error, eta, alpha, 1);
	}
    }
}
