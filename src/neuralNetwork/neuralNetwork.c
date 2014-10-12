#include <stdio.h>
#include <stdlib.h>

#include "neuralNetwork.h"

int main(void)
{
  Layer Input;
  Layer Hidden;
  Layer Output;
  initializeLayer(&Input, 3, 2);
  initializeLayer(&Hidden, 2, 1);
  initializeLayer(&Output, 1, 1);
  return 0;
}

void initializeNeural(Neural *Neural)
{

}
void initializeLayer(Layer *Layer, unsigned pNumberUnits, unsigned pNumberLinks)
{
  unsigned numberLinks = 0; //Number link for the weights to each neural
  unsigned numberUnits = 0;
  Neural Neural;
  //Number of Neural on the Layer
  Layer->numberUnits = pNumberUnits;
  //Malloc tab of Neural of the Layer
  Layer->Units = malloc (sizeof (Neural) * pNumberUnits);
  
  //Initialize each Neural on the Layer
  for(; numberUnits < pNumberLinks; numberUnits++)
    {
      //TODO
      //Layer->Units[numberUnits] = initializeNeural(&Neural);
    }
  //Malloc matrix for the weights of each Neural
  Layer->weights = malloc(sizeof(double) * pNumberUnits);
  for(; numberLinks < pNumberLinks; numberLinks++)
    {
      Layer->weights[numberLinks] = malloc(sizeof(double) * pNumberLinks);
    }
}
void freeNeural(Neural *Neural)
{
}

void freeLayer(Layer *Layer)
{
  unsigned i = 0;
  for(; i <Layer->numberUnits; i++)
    {
      
    }
}


double computeSum(double output, double weight)
{
  return 0;
}
double computeOutput(double sumedResult)
{
  return 0;
}
