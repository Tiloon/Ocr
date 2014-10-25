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

//**********************************************//                                 
//               LEARNING METHODS               //                                 
//**********************************************// 

void computeDeltaO(Network *Network, 
		     long double *target, long double *computed);
void computeDeltaH(Network *network);
//TO DO
void computeDeltaWeights()
{

}
