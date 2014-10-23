typedef struct Neural Neural;
struct Neural
{
    long double computedValue;
    long double sumedValue;
    long double *weights;
    //number of weights to each next neuron
    unsigned numberWeights; 
    //Will be used for computing the delta for delta2
    long double delta;
    //Will be used for computing the final variation for updating the weights
    long double *deltaWeights;
};
typedef struct Layer Layer;
struct Layer
{
    long double biasWeight;
    long double bias;
    long double deltaBias;
    unsigned numberUnits;
    Neural *Units;
};

//Compute the sum of each neuron on Layer1 to each neuron on Layer2
//And also call sigmoid function and update each neuron value
void computeSum(Layer *Layer1, Layer *Layer2);


long double sigmoid(long double x);
void initializeLayer(Layer *Layer, unsigned numberUnits, 
		     unsigned numberWeights);
void freeLayer(Layer *Layer);
void initializeNeuron(Neural *Neural, unsigned numberWeights);
void freeNeuron(Neural *Neural);
void computeData(Layer *Input, Layer *Hidden, Layer *Output);

/* Compute the error between what expected and what computed
** Will be used for continuing (or not) the learning loop 
*/
void computeError(long double **expected, long double **computed,
		  long double *error, unsigned nbOutputNeurons);


/* Compute the delta for each output neurone
** expected is a tab of value of length OuputLayer.Units
*/
void  computeDeltaOutput(long double **expected, Layer *OutputLayer);


// Compute the delta for each hidden neurone
void computeDeltaHidden(Layer *HiddenLayer, Layer *OutputLayer);

/* Compute the delta weight which use delta Hidden and delta Output
** It is used for Weights Input -> Hidden and Hidden -> Output
** It is the same calculus
*/
void computeDeltaWeight(long double eta, long double alpha, 
			Layer *LayerToUpdate, Layer *NextLayer);


//Give all the computed output values in a tab
void resultsToTab(Layer *OutputLayer, long double **results);

//Give the patternInput in input neurons and start computing
void computePattern(long double *patternInput,
                    Layer *Input, Layer *Hidden, Layer *Output);

//Call the computeError function for all the patterns
void computeError2(long double ***expected, long double ***computed,
                   long double *error, unsigned pNumberNeurons);

//Call all the learning functions for one specific pattern
void learnOnePattern(Layer *Input, Layer *Hidden, Layer *Output,
		     long double *pattern, long double **resultsList, 
		     long double **expectedResults,
		     long double *error, long double eta, long double alpha,
		     long double numberIterations);

void learnListPattern(Layer *Input, Layer *Hidden, Layer *Output,
		      long double ***pattern, unsigned numberPattern,
		      long double ***resultsList,
		      long double ***expectedResults,
		      long double *error, long double eta, long double alpha,
		      long double numberIterations);
