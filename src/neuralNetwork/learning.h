#ifndef LEARNING_H
#define LEARNING_H

#include "structure.h"
#include "network.h"
#include "layer.h"

void compute_delta_output(struct s_network *network,
        long double *target, long double *computed);
void compute_delta_hidden(struct s_network *network);

/* Compute the delta weights for the previous Layer from the next
 ** Will be called by update Weights methods
 ** Compute also the new delta
 */
void compute_delta_weights(struct s_layer *previous, struct s_layer *next,
        long double eta, long double alpha);
//Compute the delta weights fot the entire network
void update_weights(struct s_network *network,
        long double *target, long double *computed,
        long double eta, long double alpha);

//Call all the learning functions
void learning(struct s_network *network, int nbPatterns, int *nbIterations,
        long double ***inputs, long double ***targets,
        long double ***computed, long double *error,
        long double eta, long double alpha, long double errorThreshold);
void compute_error(long double ***targets, long double ***outputs,
        int nbPatterns, long double *error);

#endif
