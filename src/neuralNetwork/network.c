#include "network.h"

long double random_values()
{
    static unsigned seed;

    if(!seed)
        srand(seed = (unsigned)time(NULL));
    return 1 - ((long double)rand()/(((long double)RAND_MAX) / 2.0));
}

void initialize_network(struct s_network *network, struct s_layer *input,
        struct s_layer *hidden, struct s_layer *output)
{
    network->input = input;
    network->hidden = hidden;
    network->output = output;
}

void feedforward(struct s_network *network)
{
    compute_values(network->input, network->hidden);
    compute_values(network->hidden, network->output);
}

void set_inputs(struct s_network *network, long double *inputs)
{
    int u;
    for(u = 0; u < network->input->nbUnits; u++)
        network->input->outputs[u] = inputs[u];
}

void outputs_to_list(struct s_network *network, long double **store_data)
{
    int u;
    for(u = 0; u < network->output->nbUnits; u++)
        (*store_data)[u] = network->output->outputs[u];
}

void stat_to_dyn(long double stat[], size_t size, long double *vector)
{
    size_t i;
    for(i = 0; i < size; i++)
        vector[i] = stat[i];
}
