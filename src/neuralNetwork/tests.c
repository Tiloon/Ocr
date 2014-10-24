#include "neuralNetwork.h"

//***********************************//
// Tests functions                   //
//**********************************///

void printAll(Layer *Layer)
{
    unsigned u;
    unsigned w;
    for(u = 0; u < Layer->numberUnits; u++)
    {
        printf("******************************\n"
                "           Neuron %d          \n", u);
        printf("Computed value : %Lf\n", Layer->Units[u].computedValue);
        printf("Sumed value : %Lf\n", Layer->Units[u].sumedValue);
        printf("delta : %Lf\n", Layer->Units[u].delta);
        printf("bias : %Lf\n", Layer->Units[u].bias);
        for(w = 0; w < Layer->Units[u].numberWeights; w++)
            printf("Poids %d : %Lf\n", w, Layer->Units[u].weights[w]);
        for(w = 0; w < Layer->Units[u].numberWeights; w++)
            printf("Delta Weights %d : %Lf\n", w,
                    Layer->Units[u].deltaWeights[w]);
    }
}

int main(void)
{
    /*THIS IS JUST FOR TESTING*/
    /*NN with 3 layer, 1 input, 1 hidden 1 output*/
    /*No Learning for now*/

    //Variables declaration

    Layer Input;
    Layer Hidden;
    Layer Output;

    //double long **input;
    double long *input0;
    double long *input1;
    double long *input2;
    double long *input3;

    double long *expected0;
    double long *expected1;
    double long *expected2;
    double long *expected3;

    double long error = 0;

    double long *results;

    //Initialising neural network
    initializeLayer(&Input, 2, 2);
    initializeLayer(&Hidden, 2, 1);
    initializeLayer(&Output, 1, 1);

    //Set the starting weights
    Input.Units[0].weights[0] = 1.7;
    Input.Units[0].weights[1] = -1.2;

    Input.Units[1].weights[0] = -2.68;
    Input.Units[1].weights[1] = 1.3;

    Hidden.Units[0].weights[0] = 1.3;
    Hidden.Units[1].weights[0] = -1.3;

    //Initializing the inputs
    input0 = malloc(sizeof(long double) * NUMBER_INPUTS);
    input0[0] = 0;
    input0[1] = 0;
    input1 = malloc(sizeof(long double) * NUMBER_INPUTS);
    input1[0] = 0;
    input1[1] = 1;
    input2 = malloc(sizeof(long double) * NUMBER_INPUTS);
    input2[0] = 1;
    input2[1] = 0;
    input3 = malloc(sizeof(long double) * NUMBER_INPUTS);
    input3[0] = 1;
    input3[1] = 1;

    //Initializing the expected results
    expected0 = malloc(sizeof(long double) * NUMBER_OUTPUTS);
    expected0[0] = 0;
    expected1 = malloc(sizeof(long double) * NUMBER_OUTPUTS);
    expected1[0] = 1;
    expected2 = malloc(sizeof(long double) * NUMBER_OUTPUTS);
    expected2[0] = 1;
    expected3 = malloc(sizeof(long double) * NUMBER_OUTPUTS);
    expected3[0] = 0;

    //Initialising results tab
    results = malloc(sizeof(long double) * NUMBER_OUTPUTS);

    /*  Compute all the pattern for the beginning values
     *  will be used for compare the value after learning
     */

    computePattern(input0, &Input, &Hidden, &Output);
    printf("results for XOR 0 : %Lf\n", Output.Units[0].computedValue);
    computePattern(input1, &Input, &Hidden, &Output);
    printf("results for XOR 1 : %Lf\n", Output.Units[0].computedValue);
    // computePattern(input2, &Input, &Hidden, &Output);
    //printf("results for XOR 2 : %Lf\n", Output.Units[0].computedValue);
    // computePattern(input3, &Input, &Hidden, &Output);
    //printf("results for XOR 3 : %Lf\n", Output.Units[0].computedValue);

    unsigned i;
    for(i = 0; i < 5000; i++)
    {
        computePattern(input0, &Input, &Hidden, &Output);
        resultsToTab(&Output, &results);
        computeError(expected0, results, &error, 1);
        computeDeltaOutput(&Output, expected0, results);
        computeDeltaHidden(&Hidden, &Output);
        computeDeltaWeight(ETA, ALPHA, &Input, &Hidden);
        computeDeltaWeight(ETA, ALPHA, &Hidden, &Output);


        computePattern(input1, &Input, &Hidden, &Output);
        resultsToTab(&Output, &results);
        computeError(expected1, results, &error, 1);
        computeDeltaOutput(&Output, expected1, results);
        computeDeltaHidden(&Hidden, &Output);
        computeDeltaWeight(ETA, ALPHA, &Input, &Hidden);
        computeDeltaWeight(ETA, ALPHA, &Hidden, &Output);
        error = 0;

/*
        computePattern(input0, &Input, &Hidden, &Output);
        printf("results for XOR 0 : %Lf\n", Output.Units[0].computedValue);
        computePattern(input1, &Input, &Hidden, &Output);
        printf("results for XOR 1 : %Lf\n", Output.Units[0].computedValue);
*/
    }

    computePattern(input0, &Input, &Hidden, &Output);
    printf("results for XOR 0 : %Lf\n", Output.Units[0].computedValue);
    computePattern(input1, &Input, &Hidden, &Output);
    printf("results for XOR 1 : %Lf\n", Output.Units[0].computedValue);


    return 0;
}

