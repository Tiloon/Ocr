#include "neuralNetwork.h"

long double get_init_rand_ratio()
{
    static unsigned seed;

    if(!seed)
        srand(seed = (unsigned)time(NULL));
    return 1 - ((double)rand()/(((double)RAND_MAX) / 2.0));
}

void initializeLayer(Layer *Layer, unsigned pNumberUnits,
        unsigned pNumberWeights)
{
    Neural Neural;
    unsigned i;

    //Number of Neuron on the Layer
    Layer->numberUnits = pNumberUnits;

    //Malloc tab of Neural of the Layer
    Layer->Units = malloc(sizeof (Neural) * pNumberUnits);

    for(i = 0; i < pNumberUnits; i++)
    {
        initializeNeuron(&Layer->Units[i], pNumberWeights);
    }
}

void initializeNeuron(Neural *Neuron, unsigned pNumberWeights)
{
    //w for numberWeights
    unsigned w;
    //Initialize each variables
    Neuron->computedValue = 0;
    Neuron->sumedValue = 0;
    Neuron->numberWeights = pNumberWeights;
    Neuron->delta = 0;
    Neuron->bias = FIRST_BIAS;
    Neuron->deltaBias = 0;

    //Malloc the weights tab
    Neuron->weights = malloc(sizeof(long double) * pNumberWeights);

    //Initialize all weights to 0. Will be aleatory later
    for(w = 0; w < pNumberWeights; w++)
    {
        Neuron->weights[w] = 0;
    }

    //Malloc the delta weights tab
    Neuron->deltaWeights = malloc(sizeof(long double) * pNumberWeights);

    //Initialize all the delta weights
    for(w = 0; w < pNumberWeights; w++)
    {
        Neuron->deltaWeights[w] = 0;
    }
}

void  computeSum(Layer *Layer1, Layer *Layer2)
{
    unsigned l1, l2;
    for(l2 = 0; l2 < Layer2->numberUnits; l2++)
    {
        Layer2->Units[l2].sumedValue = Layer2->Units[l2].bias;
        for(l1 = 0; l1 < Layer1->numberUnits; l1++)
        {
            Layer2->Units[l2].sumedValue +=
                Layer1->Units[l1].computedValue * Layer1->Units[l1].weights[l2];
        }
        Layer2->Units[l2].computedValue = sigmoid(Layer2->Units[l2].sumedValue);
    }
}

long double sigmoid(long double x)
{
    //return (1 / (1 + exp(-1 * x)));
    return tanh(x);
}

void computeData(Layer *Input, Layer *Hidden, Layer *Output)
{
    computeSum(Input, Hidden);
    computeSum(Hidden, Output);
}

void computeError(long double *expected, long double *computed,
        long double *error, unsigned nbOutputNeurons)
{
    // p as pattern and n as (output) neuron
    unsigned n;
    for(n = 0; n < nbOutputNeurons; n++)
    {
        *error += 0.5 *
            (expected[n] - computed[n]) *
            (expected[n] - computed[n]) ;
    }
}

void resultsToTab(Layer *OutputLayer, long double **results)
{
    unsigned u;
    for(u = 0; u < OutputLayer->numberUnits; u++)
        (*results)[u] = OutputLayer->Units[u].computedValue;
}

void computePattern(long double *patternInput,
        Layer *Input, Layer *Hidden, Layer *Output)
{
    unsigned n;
    for(n = 0; n < Input->numberUnits; n++)
    {
        Input->Units[n].computedValue = patternInput[n];
    }
    computeData(Input, Hidden, Output);
}

void computeDeltaOutput(Layer *Output, long double *expected,
        long double *computed)
{
    unsigned u;
    for(u = 0; u < Output->numberUnits; u++)
    {
        Output->Units[u].delta = (expected[u] - computed[u]) *
            computed[u] * (1.0 - computed[u]);
    }
}

void computeDeltaHidden(Layer *Hidden, Layer *Output)
{
    unsigned h, o;
    long double error;
    for(h = 0; h < Hidden->numberUnits; h++)
    {
        error = 0;
        for(o = 0; o < Output->numberUnits; o++)
        {
            error += (Hidden->Units[h].weights[o] * Output->Units[o].delta);
        }
        Hidden->Units[h].delta = Hidden->Units[h].computedValue *
            (1.0 - Hidden->Units[h].computedValue) * error;
    }
}

void computeDeltaWeight(long double eta, long double alpha,
        Layer *ToUpdate, Layer *Next)
{
    unsigned next, current;
    for(next = 0; next < Next->numberUnits; next++)
    {
        //First : update the bias next Layer
        Next->Units[next].deltaBias = (eta * Next->Units[next].delta) +
            (alpha * Next->Units[next].deltaBias);

        Next->Units[next].bias += Next->Units[next].deltaBias;
        for(current = 0; current < ToUpdate->numberUnits; current++)
        {
            //Then : update the weights from ToUpdate to Next
            ToUpdate->Units[current].deltaWeights[next] =
                (eta * ToUpdate->Units[current].weights[next]
                 * Next->Units[next].delta)
                + (alpha * ToUpdate->Units[current].deltaWeights[next]);

            ToUpdate->Units[current].weights[next] +=
                ToUpdate->Units[current].deltaWeights[next];
        }
    }
}
