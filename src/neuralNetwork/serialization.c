#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "serialization.h"

/*
 * All this part is dedicated to convert the neural network
 * from DATA to a text file. For more information about structure,
 *  please see serialization.h
 *
 */


void network_to_text(FILE *file, struct s_network *network, FILE *file2, int is_char_set)
{
    set_general_data(file, network);
    set_specific_data(file, network);
    if(is_char_set == 1)
	set_charset(file2);
    file2++;
}

void set_charset(FILE *file)
{
    wchar_t *data = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#$%&\
'()*+,-./0123456789:;=?@\[\\]_{|}~\x89\x90\x919\x92\xFB00\xFB01\xFB02\xFB03\xFB04\0";

    fwprintf(file, data);
}

void set_general_data(FILE *file, struct s_network *network)
{
    set_number_units(file, network);
    set_number_weights(file, network);
}

void set_specific_data(FILE *file, struct s_network *network)
{
    set_weights_bias(file, network);
}

void set_number_units(FILE *file, struct s_network *network)
{
    if(file == NULL)
    {
        printf("FILE NULL : set_number_units\n");
        return;
    }
    int nb_inputs, nb_hidden, nb_outputs;
    nb_inputs = network->input->nbUnits;
    nb_hidden = network->hidden->nbUnits;
    nb_outputs = network->output->nbUnits;
    fprintf(file, "%d %d %d ", nb_inputs, nb_hidden, nb_outputs);
}

void set_number_weights(FILE *file, struct s_network *network)
{
    if(file == NULL)
    {
        printf("FILE NULL : set_number_weights\n");
        return;
    }
    int nb_w_inputs, nb_w_hidden, nb_w_outputs;
    nb_w_inputs = network->input->nbWeights;
    nb_w_hidden = network->hidden->nbWeights;
    nb_w_outputs = network->output->nbWeights;
    printf("ok");
    fprintf(file, "%d %d %d \n", nb_w_inputs, nb_w_hidden, nb_w_outputs);
}

void set_weights(FILE *file, struct s_network *network)
{
    set_weights_layer(file, network->input);
    set_weights_layer(file, network->hidden);
    set_weights_layer(file, network->output);
}

void set_bias(FILE *file, struct s_network *network)
{
    set_bias_layer(file, network->input);
    set_bias_layer(file, network->hidden);
    set_bias_layer(file, network->output);
}

void set_weights_bias(FILE *file, struct s_network *network)
{
    set_weights_layer(file, network->input);
    set_bias_layer(file, network->input);
    set_weights_layer(file, network->hidden);
    set_bias_layer(file, network->hidden);
    set_weights_layer(file, network->output);
    set_bias_layer(file, network->output);
}

void set_weights_layer(FILE *file, struct s_layer *layer)
{
    if(file == NULL)
    {
        printf("file == NULL : set_weights_layer()\n");
        return;
    }
    int nb_units, nb_weights;
    for(nb_units = 0; nb_units < layer->nbUnits; nb_units++)
    {
        for(nb_weights = 0; nb_weights < layer->nbWeights; nb_weights++)
            fprintf(file, "%Lf \n", layer->weights[nb_units][nb_weights]);
    }
}

void set_bias_layer(FILE *file, struct s_layer *layer)
{
    if(file == NULL)
    {
        printf("file == NULL : set_bias_layer()\n");
        return;
    }
    int nb_units;
    for(nb_units = 0; nb_units < layer->nbUnits; nb_units++)
        fprintf(file, "%Lf \n", layer->bias[nb_units]);
}


/*
 * All this part is dedicated to convert the neural network
 * from a text file to a working neural network.
 * For more information about program structure,
 *  please see serialization.h
 *
 */

void text_to_network(FILE *file, struct s_network *network, FILE *file2)
{
    get_general_data(file, network);
    get_specific_data(file, network);
    get_charset(file2, network);
}

void get_general_data(FILE *file, struct s_network *network)
{
    fscanf(file, "%d %d %d %d %d %d",
            &network->input->nbUnits,
            &network->hidden->nbUnits,
            &network->output->nbUnits,
            &network->input->nbWeights,
            &network->hidden->nbWeights,
            &network->output->nbWeights);
}
void get_specific_data(FILE *file, struct s_network *network)
{
    get_weights_bias(file, network);
}
void get_bias(FILE *file, struct s_network *network);
void get_weights(FILE *file, struct s_network *network);

void get_weights_bias(FILE *file, struct s_network *network)
{
    get_weights_layer(file, network->input);
    get_bias_layer(file, network->input);
    get_weights_layer(file, network->hidden);
    get_bias_layer(file, network->hidden);
    get_weights_layer(file, network->output);
    get_bias_layer(file, network->output);
}
void get_bias_layer(FILE *file, struct s_layer *layer)
{
    int nb_units;
    for(nb_units = 0; nb_units < layer->nbUnits; nb_units++)
    {
        fscanf(file, "%Lf", &layer->bias[nb_units]);
    }
}
void get_weights_layer(FILE *file, struct s_layer *layer)
{
    int nb_units, nb_weights;
    for(nb_units = 0; nb_units < layer->nbUnits; nb_units++)
    {
        for(nb_weights = 0; nb_weights < layer->nbWeights; nb_weights++)
            fscanf(file, "%Lf", &layer->weights[nb_units][nb_weights]);
    }
}

void get_charset(FILE *file, struct s_network *network)
{
    if(file != NULL)
    {
	network->charset = calloc (network->input->nbUnits, sizeof(wchar_t));
	fwscanf(file, L"%ls", network->charset);
    }
}
