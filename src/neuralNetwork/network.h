#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "structure.h"
#include "layer.h"
#include "learning.h"

#define ETA 0.8
#define ALPHA 0.4
#define BIAS 0

long double random_values(void);

void initialize_network(struct s_network *network,
        struct s_layer *input, struct s_layer *hidden, struct s_layer *output);
void free_network(struct s_network *network);
//Compute the pattern (call setInputs to set a pattern)
void feedforward(struct s_network *network);
//Give inputs pattern to the neural network
void set_inputs(struct s_network *network, long double *inputs);
void outputs_to_list(struct s_network *network, long double **store_data);


#endif
