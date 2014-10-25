#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "network.h"


/*
 * layer methods
 */

void initializeLayer(struct s_layer *layer, int nbUnits, int nbWeights,
        long double bias)
{
    int u, w;
    layer->nbUnits = nbUnits;
    layer->nbWeights = nbWeights;

    //Malloc weights
    layer->weights = malloc(sizeof(long double) * nbUnits);
    for(u = 0; u < layer->nbUnits; u++)
    {
        layer->weights[u] = malloc(sizeof(long double) * nbWeights);
    }
    for(u = 0; u < layer->nbUnits; u++)
    {
        for(w = 0; w < layer->nbWeights; w++)
        {
            layer->weights[u][w] = randomValues();
        }
    }

    //Malloc deltaWeights
    layer->deltaWeights = malloc(sizeof(long double) * nbUnits);
    for(u = 0; u < layer->nbUnits; u++)
    {
        layer->deltaWeights[u] = malloc(sizeof(long double) * nbWeights);
    }
    for(u = 0; u < layer->nbUnits; u++)
    {
        for(w = 0; w < layer->nbWeights; w++)
        {
            layer->deltaWeights[u][w] = 0;
        }
    }

    //Malloc output
    layer->outputs = malloc(sizeof(long double) * nbUnits);

    //Malloc bias
    layer->bias = malloc(sizeof(long double) * nbUnits);
    for(u = 0; u < layer->nbUnits; u++)
        layer->bias[u] = bias;

    //Malloc deltaBias
    layer->deltaBias = malloc(sizeof(long double) * nbUnits);
    for(u = 0; u < layer->nbUnits; u++)
        layer->deltaBias[u] = 0;

    //Malloc delta
    layer->delta = malloc(sizeof(long double) * nbUnits);
    for(u = 0; u < layer->nbUnits; u++)
        layer->delta[u] = 0;

}

long double randomValues()
{
    static unsigned seed;

    if(!seed)
        srand(seed = (unsigned)time(NULL));
    return 1 - ((long double)rand()/(((long double)RAND_MAX) / 2.0));
}

void computeValues(struct s_layer *l1, struct s_layer *l2)
{
    long double sum;
    int prev, curr;
    for(curr = 0; curr < l2->nbUnits; curr++)
    {
        //Bias
        sum = l2->bias[curr];
        for(prev = 0; prev < l1->nbUnits; prev++)
        {
            sum += l1->outputs[prev] * l1->weights[prev][curr];
        }
        l2->outputs[curr] = sigmoid(sum);
    }
}

long double sigmoid(long double x)
{
    return (1 / (1 + exp(-x)));
}

/*
 * Network methods
 */

void initializeNetwork(struct s_network *network, struct s_layer *input,
        struct s_layer *hidden, struct s_layer *output)
{
    network->input = input;
    network->hidden = hidden;
    network->output = output;
}

void feedForward(struct s_network *network)
{
    computeValues(network->input, network->hidden);
    computeValues(network->hidden, network->output);
}

void setInputs(struct s_network *network, long double *inputs)
{
    network->input->outputs[0] = inputs[0];
    network->input->outputs[1] = inputs[1];
}

void outputsToList(struct s_network *network, long double **storeData)
{
    int u;
    for(u = 0; u < network->output->nbUnits; u++)
    {
        (*storeData)[u] = network->output->outputs[u];
    }
}

/*
 * Learning methods
 */

void computeDeltaO(struct s_network *network,
        long double *target, long double *computed)
{
    int u;
    for(u = 0; u < network->output->nbUnits; u++)
        network->output->delta[u] =
            (target[u] - computed[u]) * computed[u] * (1.0 - computed[u]);
}

void computeDeltaH(struct s_network *network)
{
    int u, out;
    long double sum;
    for(u = 0; u < network->hidden->nbUnits; u++)
    {
        sum = 0;
        for(out = 0; out < network->output->nbUnits; out++)
        {
            sum +=  network->hidden->weights[u][out] *
                network->output->delta[out];
        }
        network->hidden->delta[u] = sum *
            network->hidden->outputs[u] * (1.0 - network->hidden->outputs[u]);
    }
}

void computeDeltaWeights(struct s_layer *previous, struct s_layer *next,
        long double eta, long double alpha)
{
    int u,  w;
    for(w = 0; w < next->nbUnits; w++)
    {
        //Update Bias
        next->deltaBias[w] = (eta * next->delta[w]) +
            (alpha * next->deltaBias[w]);
        for(u = 0; u < previous->nbUnits; u++)
        {
            //Update the delta weights
            previous->deltaWeights[u][w] =
                (eta * previous->outputs[u] * next->delta[w]) +
                (alpha * previous->deltaWeights[u][w]);
            previous->weights[u][w] += previous->deltaWeights[u][w];
        }
    }
}

void updateWeights(struct s_network *network,
        long double *target, long double *computed,
        long double eta, long double alpha)
{
    computeDeltaO(network, target, computed);
    computeDeltaH(network);
    computeDeltaWeights(network->input, network->hidden, eta, alpha);
    computeDeltaWeights(network->hidden, network->output, eta, alpha);
}

void learning(struct s_network *network, int nbPatterns, int *nbIterations,
        long double ***inputs, long double ***targets,
        long double ***computed, long double *error,
	      long double eta, long double alpha, long double errorThreshold)
{
    int p;
    p = 0;

    static unsigned seed;

    if(!seed)
        srand(seed = (unsigned)time(NULL));

    while(*error > errorThreshold)
    {
	p =  (int) rand() % nbPatterns;
	setInputs(network, (*inputs)[p]);
	feedForward(network);
	outputsToList(network, &(*computed)[p]);
	updateWeights(network, (*targets)[p], (*computed)[p], eta, alpha);
	computeError(targets, computed, 4, error);
	(*nbIterations)++;
    }
    printf("Number iterations : %d\n\n", *nbIterations);
}

void computeError(long double ***targets, long double ***outputs,
        int nbPatterns, long double *error)
{
    int p;
    *error = 0;
    for(p = 0; p < nbPatterns; p++)
    {
        *error += 0.5 * ((*targets)[p][0] - (*outputs)[p][0]) *
            ((*targets)[p][0] - (*outputs)[p][0]);
    }
}
