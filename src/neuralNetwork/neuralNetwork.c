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
#define BIAS 0.5 





//***********************************//
// Tests functions                   //
//**********************************///



int main(void)
{
  /*THIS IS JUST FOR TESTING*/
  /*NN with 3 layer, 1 input, 1 hidden 1 output*/
  /*No Learning for now*/

  Layer Input;
  Layer Hidden;
  Layer Output;

  initializeLayer(&Input, 3, 3);
  initializeLayer(&Hidden, 2, 2);
  initializeLayer(&Output, 1, 1);

  Input.Units[0].computedValue = 1;
  Input.weights[0][0] = 0.5;
  Input.weights[0][1] = 0.2;

  Input.Units[1].computedValue = 2;
  Input.weights[1][0] = 0.5;
  Input.weights[1][1] = 0.3;

  Input.Units[2].computedValue = 3;
  Input.weights[2][0] = 0.5;
  Input.weights[2][1] = 0.1;
  
  
  Hidden.weights[0][0] = 0.2;  
  Hidden.weights[1][0] = 0.1;
  
  
  computeSum(&Input, &Hidden);
  computeSum(&Hidden, &Output);

  //printValues(Hidden.Units[0]);
  //printValues(Hidden.Units[1]);
  printf("SOMME : %f, COMPUTE : %f \n", Output.Units[0].sumedValue, Output.Units[0].computedValue);

  freeLayer(&Input);
  freeLayer(&Hidden);
  freeLayer(&Output);

  return 0;
}


void initializeLayer(Layer *Layer, unsigned pNumberUnits, unsigned pNumberLinks)
{
  //Number link for the weights to each neural 
  //unsigned numberUnits = 0;
  unsigned numberLinks = 0;
  Neural Neural;
  
  //Number of Neuron on the Layer
  Layer->numberUnits = pNumberUnits;
  //Set the number of units of the next Layer 
  Layer->numberLinks = pNumberLinks;

  //Malloc tab of Neural of the Layer
  Layer->Units = malloc (sizeof (Neural) * pNumberUnits);
  
  //Malloc matrix for the weights of each Neural
  Layer->weights = malloc(sizeof(double) * pNumberUnits);
  
  for(; numberLinks < pNumberLinks; numberLinks++)
    {
      Layer->weights[numberLinks] = malloc(sizeof(double) * pNumberLinks);
    }
}

void freeLayer(Layer *Layer)
{
  unsigned i = 0;
  //Free the dynamic memory due to malloc
  //i.e All the Neural of the Layer
  free(Layer->Units);
  
  //Free the matrix of the weights
  for(i = 0; i < Layer->numberUnits; i++)
    {
      free(Layer->weights[i]);
    }
  free(Layer->weights);
}


void  computeSum(Layer *Layer1, Layer *Layer2)
{
  unsigned l1, l2;
  //Will sum the sumedValue of each Neural of the Layer
  for(l2 = 0; l2 < Layer2->numberUnits; l2++)
    {
      //Layer2->Units[l2].sumedValue = BIAS; 
      for(l1 = 0; l1 < Layer1->numberUnits; l1++)
	{
	  //WTFFFFFFF
	  printf(""
		   ""
		   "poids %f\n"
		 "", Layer1->weights[l1][l2]);

	  Layer2->Units[l2].sumedValue += 
	    Layer1->weights[l1][l2] * Layer1->Units[l1].computedValue;
	}
      Layer2->Units[l2].computedValue =  sigmoid(Layer2->Units[l2].sumedValue);
    }
}
double sigmoid(double x)
{
  return (1 /( 1 + exp(-1 * x)));
}
