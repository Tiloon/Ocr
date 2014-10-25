#ifndef NETWORK_H
#define NETWORK_H

typedef struct Layer Layer;
struct Layer
{
    //Weights between two layers
    long double **weights;
    long double **deltaWeights;
    //List of output values of each neuron
    long double *outputs;
    //List of bias, one bias for each neuron
    long double *bias;
    long double *deltaBias;
    long double *delta;
    //Number units on the layer
    int nbUnits;
    //Number of weights
    int nbWeights;
};

typedef struct Network Network;
struct Network
{
    Layer *Input;
    Layer *Hidden;
    Layer *Output;
};


//***************************************************//
//               LAYER METHODS                       //
//***************************************************//
void initializeLayer(Layer *Layer, int nbUnits, int nbWeights,
        long double startingBias);
void freeLayer(Layer *Layer);
void printLayer(Layer Layer, char *str);
long double randomValues();
//Update the output of the layer2 from the Layer1 output
void computeValues(Layer *L1, Layer *L2);
long double sigmoid(long double x);

//***************************************************//
//               NETWORK METHODS                     //
//***************************************************//
void initializeNetwork(Network *Network,
        Layer *Input, Layer *Hidden, Layer *Output);
void freeNetwork(Network *Network);
void printOutput(Network Network);
//Compute the pattern (call setInputs to set a pattern)
void feedForward(Network *Network);
//Give inputs pattern to the neural network
void setInputs(Network *Network, long double *inputs);
void outputsToList(Network *Network, long double **storeResults);
//**********************************************//
//               LEARNING METHODS               //
//**********************************************//

void computeDeltaO(Network *Network,
        long double *target, long double *computed);
void computeDeltaH(Network *network);

/* Compute the delta weights for the previous Layer from the next
 ** Will be called by update Weights methods
 ** Compute also the new delta
 */
void computeDeltaWeights(Layer *Previous, Layer *Next,
        long double eta, long double alpha);
//Compute the delta weights fot the entire network
void updateWeights(Network *Network,
        long double *target, long double *computed,
        long double eta, long double alpha);

//Call all the learning functions
void learning(Network *Network, int nbPatterns, int nbIterations,
        long double ***inputs, long double ***targets,
        long double ***computed, long double *error,
        long double eta, long double alpha);
void computeError(long double ***targets, long double ***outputs,
        int nbPatterns, long double *error);

#endif
