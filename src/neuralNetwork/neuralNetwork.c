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

  initializeLayer(&Input, 2, 2);
  initializeLayer(&Hidden, 4, 4);
  initializeLayer(&Output, 2, 0);
  
  Input.Units[0].computedValue = 1;
  Input.Units[1].computedValue = 0;
  
  Input.weights[0][0] = 0.5;
  Input.weights[0][1] = 0.2;
  Input.weights[0][2] = 0.5;
  Input.weights[0][3] = 0.5; 
  
  Input.weights[1][0] = 0.5;
  Input.weights[1][1] = 0.2;
  Input.weights[1][2] = 0.5;
  Input.weights[1][3] = 0.5;

     
  Hidden.weights[0][0] = 0.2;  
  Hidden.weights[0][1] = 0.1;
  Hidden.weights[1][0] = 0.2;
  Hidden.weights[1][1] = 0.1;
  Hidden.weights[2][0] = 0.2;
  Hidden.weights[2][1] = 0.1;
  Hidden.weights[3][0] = 0.5;
  Hidden.weights[3][1] = 0.2;

    
  computeData(&Input, &Hidden, &Output);

  printf("SOMME : %Lf, COMPUTE : %Lf \n", Output.Units[0].sumedValue, Output.Units[0].computedValue);

  printf("SOMME : %Lf, COMPUTE : %Lf \n", Output.Units[1].sumedValue, Output.Units[1].computedValue);


  freeLayer(&Input);
  //freeLayer(&Hidden);
  //freeLayer(&Output);

  return 0;
}


void initializeLayer(Layer *Layer, unsigned pNumberUnits, unsigned pNumberLinks)
{
  //Number link for the weights to each neural 
  unsigned numberLinks = 0;
  Neural Neural;
  unsigned i;
  
  //Number of Neuron on the Layer
  Layer->numberUnits = pNumberUnits;
  //Set the number of units of the next Layer 
  Layer->numberLinks = pNumberLinks;

  //Malloc tab of Neural of the Layer
  Layer->Units = malloc (sizeof (Neural) * pNumberUnits);
  //Initialize Bias value for each neuron
  for(i=0; i<pNumberUnits;i++)
    Layer->Units[i].bias = FIRST_BIAS;
  //Malloc matrix for the weights of each neuron
  Layer->weights = malloc(sizeof(long double) * pNumberUnits);
  
  for(numberLinks = 0; numberLinks < pNumberLinks; numberLinks++)
    {
      Layer->weights[numberLinks] = malloc(sizeof(long double) * pNumberLinks);
    }

  /* 
  ** /Malloc matrix for the delta weights of each neuron
  **Layer->deltaWeights = malloc(sizeof(long double) * pNumberUnits);
  **for(i=0; i<pNumberUnits; i++)
  **{
  **	Layer->deltaWeights[i] = malloc(sizeof(long double) * pNumberLinks);
  **}
  */
    
  //Will be used for computing delta H
  //Layer-> sumDeltaOutputWeights = malloc(sizeof(long double) * pNumberUnits);
}

void freeLayer(Layer *Layer)
{
  //****************//
  //TODO
  //***************//


  /* Free the weights[][] tab
  ** for(x = 0; x < Layer->numberUnits; x++)
  **  {
  **     free(Layer->weights[x]);
  **  }
  */
  
  //Free the weights[] tab
  free(Layer->weights);
}


void  computeSum(Layer *Layer1, Layer *Layer2)
{
  unsigned l1, l2;
  //Will sum the sumedValue of each Neural of the Layer
  for(l2 = 0; l2 < Layer2->numberUnits; l2++)
    {
      Layer2->Units[l2].sumedValue = Layer2->Units[l2].bias; 
      for(l1 = 0; l1 < Layer1->numberUnits; l1++)
	{
	  Layer2->Units[l2].sumedValue += 
	    Layer1->weights[l1][l2] * Layer1->Units[l1].computedValue;
	}
      Layer2->Units[l2].computedValue =  sigmoid(Layer2->Units[l2].sumedValue);
    }
}

long double computeSum2(Layer *Layer1, unsigned units, Layer *Layer2)
{
  unsigned numberLinks;
  long double result = 0;
  for(numberLinks = 0; numberLinks < Layer2->numberUnits; numberLinks++)
    {
      result += Layer1->weights[units][numberLinks] *
	Layer2->Units[numberLinks].computedValue;
    }
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
