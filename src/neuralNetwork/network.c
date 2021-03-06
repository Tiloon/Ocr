#include "network.h"
#include "layer.h"
#include "serialization.h"

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

void initialization_neural_network(struct s_neural_network *neural_network,
        int nb_patterns, int nb_inputs,
        int nb_hidden_neurons, long double bias)
{
    super_initialization_network(&neural_network->network,
            &neural_network->input,
            &neural_network->hidden,
            &neural_network->output,
            nb_patterns, nb_inputs,
            nb_hidden_neurons,
            bias);
}

void super_initialization_network(struct s_network *network,
        struct s_layer *input,
        struct s_layer *hidden,
        struct s_layer *output,
        int nb_patterns, int nb_inputs,
        int nb_hidden_neurons,
        long double bias)
{
    initialize_layer(input, nb_inputs, nb_hidden_neurons, bias);
    initialize_layer(hidden, nb_hidden_neurons,
            nb_patterns, bias);
    initialize_layer(output, nb_patterns,
            0, bias);

    initialize_network(network, input, hidden, output);
    import_serialization(network);
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

long double *outputs_to_list2(struct s_network *network)
{
    long double *outputs;
    int u;
    outputs = calloc(network->output->nbUnits,
            sizeof(long double));
    for(u = 0; u < network->output->nbUnits; u++)
        outputs[u] = network->output->outputs[u];
    return outputs;
}

long double *compute_character (struct s_network *network,
        long double *inputs)
{
    long double *outputs;
    outputs = calloc(network->output->nbUnits, sizeof(long double));
    set_inputs(network, inputs);
    feedforward(network);
    outputs = outputs_to_list2(network);
    return outputs;
}

void import_serialization(struct s_network *network)
{
    FILE *file = NULL;
    FILE *file2 = NULL;
    size_t i = 0;
    file = fopen("serialized", "r+");
    file2 = fopen("charset", "r+");
    if(file != NULL && file2 != NULL)
    {
        text_to_network(file, network, file2);
        fclose(file);
        fclose(file2);
        for(i = 0; (network->charset)[i]; i++);
        network->charset_len = i;
    }
    else
    {
        if(file == NULL)
            printf("FILE = NULL\n");
        if(file2 == NULL)
            printf("FILE = NULL\n");
        network->charset_len = 0;
    }
}

