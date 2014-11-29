#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "structure.h"
#include "layer.h"
#include "learning.h"

long double random_values(void);

void initialization_neural_network(struct s_neural_network *neural_network,
				   int nb_patterns, int nb_inputs,
                                   int nb_hidden_neurons, long double bias);
void initialize_network(struct s_network *network,
        struct s_layer *input, struct s_layer *hidden, struct s_layer *output);
void super_initialization_network(struct s_network *network,
				  struct s_layer *input,
				  struct s_layer *hidden,
				  struct s_layer *output,
				  int nb_patterns, int nb_inputs,
				  int nb_hidden_neurons,
				  long double bias);
void free_network(struct s_network *network);
//Compute the pattern (call setInputs to set a pattern)
void feedforward(struct s_network *network);
//Give inputs pattern to the neural network
void set_inputs(struct s_network *network, long double *inputs);
void outputs_to_list(struct s_network *network, long double **store_data);
long double *outputs_to_list2(struct s_network *network);
void stat_to_dyn(long double stat[], size_t size, long double *vector);
long double *compute_character(struct s_network *network, long double *inputs);
void import_serialization(struct s_network *network);
#endif
