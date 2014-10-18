typedef struct Neural Neural;
struct Neural
{
    long double computedValue;
    long double sumedValue;
    long double bias;
    long double *weights;
    //number of weights to each next neuron
    unsigned numberWeights; 
    //Will be used for computing the delta for delta2
    long double delta;
    //Will be used for computing the final variation for updating the weights
    long double delta2;
};
typedef struct Layer Layer;
struct Layer
{
    unsigned numberUnits;
    //* unsigned numberLinks;
    Neural *Units;
    //* long double **weights;
};

//Compute the sum of each neuron on Layer1 to each neuron on Layer2
//And also call sigmoid function and update each neuron value
void computeSum(Layer *Layer1, Layer *Layer2);

//compute the sum for one neuron unit from layer1
//to layer2 and return a result
//will be used to compute delta Hiddenx
long double computeSum2(Layer *Layer1, unsigned unit, Layer *Layer2);
long double sigmoid(long double x);
void initializeLayer(Layer *Layer, unsigned numberUnits, 
		     unsigned numberWeights);
void freeLayer(Layer *Layer);
void initializeNeuron(Neural *Neural, unsigned numberWeights);
void freeNeuron(Neural *Neural);
void computeData(Layer *Input, Layer *Hidden, Layer *Output);

/* Compute the error between what expected and what computed
** Will be used for continuing (or not) the learning loop 
** Expected x= nbPattern to recognize, y= nbOutput neurons
*/
void computeError(long double **expected, long double **computed, long double *error, unsigned nbPatterns, unsigned nbOutputNeurons);


/* Compute the delta for each output neurone
** expected is a tab of value of length OuputLayer.Units
*/
void  computeDeltaOutput(long double **expected, Layer *OutputLayer,
			 unsigned numberPatterns);

// Compute the delta for each hidden neurone
void computeDeltaHidden(Layer *HiddenLayer, Layer *OutputLayer);

/* Compute the delta weight which use delta Hidden and delta Output
** It is used for Weights Input -> Hidden and Hidden -> Output
** It is the same calculus
*/
long double computeDeltaWeight(long double eta, long double alpha, Layer *nextLayer, Layer *ActualLayer);

//Will use the computeDeltaWeight function to update the value of the weights
void updateWeights(Layer *LayerToUpdate);
