#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>

#define ETA 0.5
#define ALPHA 0.6
#define BIAS 0.5

struct s_layer
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

struct s_network
{
    struct s_layer *input;
    struct s_layer *hidden;
    struct s_layer *output;
};


/*
 * Layer methods
 */
void initializeLayer(struct s_layer *layer, int nbUnits, int nbWeights,
        long double startingBias);
void freeLayer(struct s_layer *layer);
long double randomValues();
//Update the output of the layer2 from the Layer1 output
void computeValues(struct s_layer *l1, struct s_layer *l2);
long double sigmoid(long double x);

/*
 * Network methods
 */
void initializeNetwork(struct s_network *network,
        struct s_layer *input, struct s_layer *hidden, struct s_layer *output);
void freeNetwork(struct s_network *network);
//Compute the pattern (call setInputs to set a pattern)
void feedForward(struct s_network *network);
//Give inputs pattern to the neural network
void setInputs(struct s_network *network, long double *inputs);
void outputsToList(struct s_network *network, long double **storeResults);

/*
 * Learning methods
 */
void computeDeltaO(struct s_network *network,
        long double *target, long double *computed);
void computeDeltaH(struct s_network *network);

/* Compute the delta weights for the previous Layer from the next
 ** Will be called by update Weights methods
 ** Compute also the new delta
 */
void computeDeltaWeights(struct s_layer *previous, struct s_layer *next,
        long double eta, long double alpha);
//Compute the delta weights fot the entire network
void updateWeights(struct s_network *network,
        long double *target, long double *computed,
        long double eta, long double alpha);

//Call all the learning functions
void learning(struct s_network *network, int nbPatterns, int nbIterations,
        long double ***inputs, long double ***targets,
        long double ***computed, long double *error,
        long double eta, long double alpha);
void computeError(long double ***targets, long double ***outputs,
        int nbPatterns, long double *error);

#endif
