#ifndef STRUCTURE_H
#define STRUCTURE_H

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

#endif
