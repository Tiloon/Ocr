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
    
    unsigned i = 0;
        
    //Initialising neural network
    initializeLayer(&Input, 2, 2);
    initializeLayer(&Hidden, 2, 1);
    initializeLayer(&Output, 1, 1);
    
    Input.Units[0].computedValue = 0;
    Input.Units[0].weights[0] = 0.5;
    Input.Units[0].weights[1] = 0.2;
    
    Input.Units[1].computedValue = 0;
    Input.Units[1].weights[0] = 0.5;
    Input.Units[1].weights[1] = 0.3;
   
    Hidden.Units[0].weights[0] = 0.2;
    Hidden.Units[1].weights[0] = 0.1;
    

    error = 0;
    
    computePattern(input1, &Input, &Hidden, &Output);
    printf("La valeur calculée pour (0,0) est : %Lf\n",
	   Output.Units[0].computedValue);
    
    for(i = 0; i < 100000; i++)
    {
	computePattern(input1, &Input, &Hidden, &Output);
	resultsToTab(&Output, &results);
	computeError(&expected1, &results, &error, 1);
	computeDeltaOutput(&expected1, &Output);
	computeDeltaHidden(&Hidden, &Output);
	computeDeltaWeight(ETA, ALPHA, &Input, &Hidden);
	computeDeltaWeight(ETA, ALPHA, &Hidden, &Output);
    }
    printf("La valeur calculée pour (0,1) après %d itérations " 
	   "d'apprentissage est : %Lf\n",
	   i, Output.Units[0].computedValue);
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

//----------------------------//
//         TO DO              //
//----------------------------//

/*void freeLayer(Layer *Layer)
  {
  //TO DO
  }
  void freeNeuron(Neural *Neural)
  {
  //TO DO
  }
*/

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

void computeAllPatern(long double ***patternList, unsigned pNumberPatterns,
		      Layer *Input, Layer*Hidden, Layer *Output,
		      long double ***resultsTabPatterns)
{
    unsigned p;
    for(p = 0; p < pNumberPatterns; p++)
    {
	computePattern((*patternList)[p], Input, Hidden, Output);
	resultsToTab(Output, resultsTabPatterns[p]);
    }
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
