#include "learning.h"
#include "network.h"
#include "structure.h"
#include "nn_main.h"
#include "layer.h"

void printVector2(long double *vector, size_t size)
{
    size_t u;
    for(u = 0; u < size; u++)
        printf(" |%Lf", vector[u]);
}


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
        next->bias[w] += next->deltaBias[w];
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
        long double eta, long double alpha,
        long double errorThreshold)
{
    int p;
    p = 0;

    static unsigned seed;

    if(!seed)
        srand(seed = (unsigned)time(NULL));

    while(*error > errorThreshold)
    {
	if(*nbIterations % 10000 == 0)
            printf("alpha : %Lf, eta : %Lf, it : %d; error : %Lf\n",alpha, eta, *nbIterations, *error);
        p =  (int) rand() % nbPatterns;
        set_inputs(network, (*inputs)[p]);
        feedforward(network);
        outputs_to_list(network, &(*computed)[p]);
        update_weights(network, (*targets)[p], (*computed)[p], eta, alpha);
        compute_error(targets, computed, nbPatterns, network->output->nbUnits,
                error);
        (*nbIterations)++;
    }
    printf("Number iterations : %d\n", *nbIterations);
    printf("Final error : %Lf\n\n", *error);
}

void learning2(struct s_network *network, int nbPatterns, int nbIterations,
        long double ***inputs, long double ***targets,
        long double ***computed, long double *error,
        long double eta, long double alpha)
{
    int p, it;
    p = 0;

    static unsigned seed;

    if(!seed)
        srand(seed = (unsigned)time(NULL));
    it = 0;
    while(it < nbIterations )
    {
        if(it % 10000 == 0)
            printf("it : %d; error : %Lf\n", it, *error);
        p =  (int) rand() % nbPatterns;
        set_inputs(network, (*inputs)[p]);
        feedforward(network);
        outputs_to_list(network, &(*computed)[p]);
        update_weights(network, (*targets)[p], (*computed)[p], eta, alpha);
        compute_error(targets, computed, nbPatterns, network->output->nbUnits,
                error);
        it++;
    }
    printf("Number iterations : %d\n\n", nbIterations);
}

void compute_error(long double ***targets, long double ***outputs,
        int nbPatterns, int nbUnits,  long double *error)
{
    int p, u;
    *error = 0;
    for(p = 0; p < nbPatterns; p++)
    {
        for(u = 0; u < nbUnits; u++)
        {
            *error += ((*targets)[p][u] - (*outputs)[p][u]) *
                ((*targets)[p][u] - (*outputs)[p][u]);
        }
    }
    *error = *error * 1 / nbPatterns;
}

void compute_error_fonts(long double ****targets, long double ****outputs,
                         int nb_patterns, int nb_fonts, long double nb_units,
                         long double *error)
{
    int p, u, f;
    *error = 0;
    for(f = 0; f < nb_fonts; f++)
    {
	for(p = 0; p < nb_patterns; p++)
	{
	    for(u = 0; u < nb_units; u++)
	    {
		*error += ((*targets)[f][p][u] - (*outputs)[f][p][u]) *
		    ((*targets)[f][p][u] - (*outputs)[f][p][u]);
	    }
	}
    }
    *error = *error * 1 / nb_patterns;
}

void learning_fonts(struct s_network *network, int nb_patterns,
		    int *nb_iterations, int nb_fonts,
		    long double ****inputs, long double ****targets,
		    long double ****computed, long double *error,
		    long double eta, long double alpha,
		    long double errorThreshold)
{
    int p, f;
    static unsigned seed;

    if(!seed)
	srand(seed = (unsigned)time(NULL));

    while(*error > errorThreshold)
    {
	for(f = 0; f < nb_fonts; f++)
	{
	    for(p = 0; p < nb_patterns; p++)
	    {
		update_learning_rate_momemtum(*error, &eta, &alpha);
		if(*nb_iterations % 1500 == 0)
		    printf("font : %d; alpha : %Lf; eta : %Lf;"
			   "it : %d; error : %Lf\n", f, alpha, eta,
			   *(nb_iterations), *error);
 		set_inputs(network, (*inputs)[f][p]);
		feedforward(network);
		outputs_to_list(network, &(*computed)[f][p]);
		compute_error_fonts(targets, computed, nb_patterns, nb_fonts,
				    network->output->nbUnits,
				    error);
		update_weights(network, (*targets)[f][p], (*computed)[f][p],
			       eta, alpha);
		//compute_error_fonts(targets, computed, nb_patterns, nb_fonts,
		//	      network->output->nbUnits,
		//	      error);
		(*nb_iterations)++;
	    }
	}
    }
    printf("Number iterations : %d\n", *nb_iterations);
    printf("Final error : %Lf\n\n", *error);
}

void update_learning_rate_momemtum(long double error,
				   long double *eta, long double *alpha)
{
    if(error < 5.9)
    {
        *eta = 0.1;
        *alpha = 0.1;
    }

    else if(error < 7)
    {
	*eta = 0.2 ;
	*alpha = 0.1;
    }
 }
