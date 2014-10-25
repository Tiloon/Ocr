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
    network->input->outputs[0] = inputs[0];
    network->input->outputs[1] = inputs[1];
}

void outputs_to_list(struct s_network *network, long double **store_data)
{
    int u;
    for(u = 0; u < network->output->nbUnits; u++)
        (*store_data)[u] = network->output->outputs[u];
}

