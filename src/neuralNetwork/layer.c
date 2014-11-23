#include "layer.h"

/*
 * layer methods
 */

void initialize_layer(struct s_layer *layer, int nbUnits, int nbWeights,
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
            layer->weights[u][w] = random_values();
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

void compute_values(struct s_layer *l1, struct s_layer *l2)
{
    long double sum;
    int prev, curr;
    for(curr = 0; curr < l2->nbUnits; curr++)
    {
        //Bias
        sum = l2->bias[curr];
        for(prev = 0; prev < l1->nbUnits; prev++)
            sum += l1->outputs[prev] * l1->weights[prev][curr];
	l2->outputs[curr] = sigmoid(sum);
	//l2->outputs[curr] = tanhyp(sum);
    }
}

long double sigmoid(long double x)
{
    return (1 / (1 + exp(-x)));
}

long double tanhyp(long double x)
{
    return tanh(x);
}
