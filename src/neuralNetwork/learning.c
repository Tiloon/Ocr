#include "learning.h"

void compute_delta_output(struct s_network *network,
        long double *target, long double *computed)
{
    int u;
    for(u = 0; u < network->output->nbUnits; u++)
        network->output->delta[u] =
            (target[u] - computed[u]) * computed[u] * (1.0 - computed[u]);
}

void compute_delta_hidden(struct s_network *network)
{
    int u, out;
    long double sum;
    for(u = 0; u < network->hidden->nbUnits; u++)
    {
        sum = 0;
        for(out = 0; out < network->output->nbUnits; out++)
        {
            sum += network->hidden->weights[u][out] *
                network->output->delta[out];
        }
        network->hidden->delta[u] = sum *
            network->hidden->outputs[u] * (1.0 - network->hidden->outputs[u]);
    }
}

void compute_delta_weights(struct s_layer *previous, struct s_layer *next,
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

void update_weights(struct s_network *network,
        long double *target, long double *computed,
        long double eta, long double alpha)
{
    compute_delta_output(network, target, computed);
    compute_delta_hidden(network);
    compute_delta_weights(network->input, network->hidden, eta, alpha);
    compute_delta_weights(network->hidden, network->output, eta, alpha);
}

void learning(struct s_network *network, int nbPatterns, int *nbIterations,
        long double ***inputs, long double ***targets,
        long double ***computed, long double *error,
        long double eta, long double alpha, long double errorThreshold)
{
    int p;
    p = 0;

    while(*error > errorThreshold)
    {
        p =  (int) rand() % nbPatterns;
        set_inputs(network, (*inputs)[p]);
        feedforward(network);
        outputs_to_list(network, &(*computed)[p]);
        update_weights(network, (*targets)[p], (*computed)[p], eta, alpha);
        compute_error(targets, computed, 4, error);
        (*nbIterations)++;
    }
    printf("Number iterations : %d\n\n", *nbIterations);
}

void compute_error(long double ***targets, long double ***outputs,
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
