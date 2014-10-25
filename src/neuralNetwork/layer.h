#ifndef LAYER_H
#define LAYER_H

#include "structure.h"
#include "network.h"
#include "learning.h"

/*
 * Layer methods
 */
void initialize_layer(struct s_layer *layer, int nbUnits, int nbWeights,
        long double startingBias);

void free_layer(struct s_layer *layer);

//Update the output of the layer2 from the Layer1 output
void compute_values(struct s_layer *l1, struct s_layer *l2);

long double sigmoid(long double x);

#endif
