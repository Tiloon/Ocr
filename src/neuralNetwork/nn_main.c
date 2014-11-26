#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "network.h"
#include "layer.h"
#include "nn_main.h"
#include "structure.h"
#include "learning.h"
#include "serialization.h"

/*
 * CHECKING FUNCTIONS
 */

static void serialization(struct s_network *network)
{
    FILE *file = NULL;
    file = fopen("serialized", "w+");
    if(file == NULL)
    {
        printf("File not opened\n");
        return;
    }
    network_to_text(file, network);
    fclose(file);
}

static void get_data(struct s_network *network)
{
    FILE *file = NULL;
    file = fopen("serialized", "r+");
    if(file == NULL)
    {
        printf("File not opened\n");
        return;
    }
    text_to_network(file, network);
    fclose(file);
}

void printMatrix (long double ***matrix, int x, int y)
{
    int x1, y1;
    for(x1 = 0; x1 < x; x1++)
    {
        for(y1 = 0; y1 < y; y1++)
        {
            printf("Matrix[%d][%d] = (%Lf)\n", x1, y1,
                    (*matrix)[x1][y1]);
        }
    }
}

void printVector(long double *vector, size_t size)
{
    size_t u;
    for(u = 0; u < size; u++)
        printf(" |%Lf", vector[u]);
}

void printInputVector(long double *vector, size_t size)
{
    size_t u;
    for(u = 0; u < size; u++)
    {
        if(u != 0 && u % 16 == 0)
            printf("\n");
        printf("%Lf", vector[u]);
    }
}

static void printOutput(struct s_network *network)
{
    int u;
    for(u = 0; u < network->output->nbUnits; u++)
    {
        printf("\n %Lf", network->output->outputs[u]);
    }
    printf("\n");
}

/*
 *  testing functions
 */

static int checkFlags(int argc, char* argv[], struct s_flags_nn *flags);
static int print_flag_error();
static void print_nn_help();

int nn_main(int argc, char *argv[])
{
    //*******************************************//
    //             VARIABLES DECLARATIONS        //
    //*******************************************//

    struct s_layer input;
    struct s_layer hidden;
    struct s_layer output;
    struct s_network network;
    struct s_flags_nn flags;

    int NUMBER_PATTERNS = 52;
    int NUMBER_PIXELS_CHARACTER = 256;
    int NUMBER_INPUT_NEURONS = NUMBER_PIXELS_CHARACTER;
    int NUMBER_HIDDEN_NEURONS = 0.2 * NUMBER_INPUT_NEURONS;
    int NUMBER_OUTPUT_NEURONS = NUMBER_PATTERNS;
    int iterations, i;


    flags.inputsFlag = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));

    //inputsUser is used so as to debug/check the NN
    long double *inputsUser = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    /*
     * *inputs is a matrix with NB_PATTERNS vector
     * contains all the inputs of the NN i-e
     * all the vector of each character recognizable
     * vectors are size of NUMBER_PIXELS_CHARACTER as size
     */

    long double **inputs = calloc(NUMBER_PATTERNS,
            sizeof(long double));

    /*
     * targets is a matrix of NUM_PATTERNS vector
     * contains all the expected results for each patterns
     * size of vector of each expected results NUM_PATTERN
     */
    long double **targets = calloc(NUMBER_PATTERNS,
            sizeof(long double));
    /*
     * results is a matrix of NUM_PATTERNS vector
     * contains the results of each patterns
     * Will be compared to targets
     * each vector are size of NUM_PATTERNS
     */
    long double **results = calloc(NUMBER_PATTERNS,
            sizeof(long double));

    /*
     * Here are all the vector for each PATTERNS (= nb characters)
     * Will fill the **inputs matrix
     * Vectors are size of NUM_PIXELS_CHARACTERS (=256)
     */

    /*
     * Here are min letters
     */
    long double *inputs_a = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_b = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_c = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_d = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_e = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_f = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_g = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_h = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_i = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_j = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_k = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_l = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_m = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_n = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_o = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_p = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_q = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_r = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_s = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_t = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_u = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_v = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_w = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_x = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_y = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_z = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));

    /*
     * Here are CAPS letters
     */

    long double *inputs_A = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_B = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_C = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_D = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_E = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_F = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_G = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_H = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_I = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_J = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_K = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_L = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_M = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_N = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_O = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_P = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_Q = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_R = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_S = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_T = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_U = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_V = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_W = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_X = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_Y = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));
    long double *inputs_Z = calloc(NUMBER_PIXELS_CHARACTER,
            sizeof(long double));






    long double error;

    /*
     * calloc all the matrix (malloc are for weak people parait-il)
     * **inputs && targets && results
     */

    for(i = 0; i < NUMBER_PATTERNS; i++)
    {
        inputs[i] = calloc(NUMBER_PIXELS_CHARACTER,
                sizeof(long double));
        targets[i] = calloc(NUMBER_PATTERNS,
                sizeof(long double));
        results[i] = calloc(NUMBER_PATTERNS,
                sizeof(long double));
    }

    //Set the inputs
    stat_to_dyn(CHAR_a, NUMBER_PIXELS_CHARACTER, inputs_a);
    stat_to_dyn(CHAR_b, NUMBER_PIXELS_CHARACTER, inputs_b);
    stat_to_dyn(CHAR_c, NUMBER_PIXELS_CHARACTER, inputs_c);
    stat_to_dyn(CHAR_d, NUMBER_PIXELS_CHARACTER, inputs_d);
    stat_to_dyn(CHAR_e, NUMBER_PIXELS_CHARACTER, inputs_e);
    stat_to_dyn(CHAR_f, NUMBER_PIXELS_CHARACTER, inputs_f);
    stat_to_dyn(CHAR_g, NUMBER_PIXELS_CHARACTER, inputs_g);
    stat_to_dyn(CHAR_h, NUMBER_PIXELS_CHARACTER, inputs_h);
    stat_to_dyn(CHAR_i, NUMBER_PIXELS_CHARACTER, inputs_i);
    stat_to_dyn(CHAR_j, NUMBER_PIXELS_CHARACTER, inputs_j);
    stat_to_dyn(CHAR_k, NUMBER_PIXELS_CHARACTER, inputs_k);
    stat_to_dyn(CHAR_l, NUMBER_PIXELS_CHARACTER, inputs_l);
    stat_to_dyn(CHAR_m, NUMBER_PIXELS_CHARACTER, inputs_m);
    stat_to_dyn(CHAR_n, NUMBER_PIXELS_CHARACTER, inputs_n);
    stat_to_dyn(CHAR_o, NUMBER_PIXELS_CHARACTER, inputs_o);
    stat_to_dyn(CHAR_p, NUMBER_PIXELS_CHARACTER, inputs_p);
    stat_to_dyn(CHAR_q, NUMBER_PIXELS_CHARACTER, inputs_q);
    stat_to_dyn(CHAR_r, NUMBER_PIXELS_CHARACTER, inputs_r);
    stat_to_dyn(CHAR_s, NUMBER_PIXELS_CHARACTER, inputs_s);
    stat_to_dyn(CHAR_t, NUMBER_PIXELS_CHARACTER, inputs_t);
    stat_to_dyn(CHAR_u, NUMBER_PIXELS_CHARACTER, inputs_u);
    stat_to_dyn(CHAR_v, NUMBER_PIXELS_CHARACTER, inputs_v);
    stat_to_dyn(CHAR_w, NUMBER_PIXELS_CHARACTER, inputs_w);
    stat_to_dyn(CHAR_x, NUMBER_PIXELS_CHARACTER, inputs_x);
    stat_to_dyn(CHAR_y, NUMBER_PIXELS_CHARACTER, inputs_y);
    stat_to_dyn(CHAR_z, NUMBER_PIXELS_CHARACTER, inputs_z);

    stat_to_dyn(CHAR_A, NUMBER_PIXELS_CHARACTER, inputs_A);
    stat_to_dyn(CHAR_B, NUMBER_PIXELS_CHARACTER, inputs_B);
    stat_to_dyn(CHAR_C, NUMBER_PIXELS_CHARACTER, inputs_C);
    stat_to_dyn(CHAR_D, NUMBER_PIXELS_CHARACTER, inputs_D);
    stat_to_dyn(CHAR_E, NUMBER_PIXELS_CHARACTER, inputs_E);
    stat_to_dyn(CHAR_F, NUMBER_PIXELS_CHARACTER, inputs_F);
    stat_to_dyn(CHAR_G, NUMBER_PIXELS_CHARACTER, inputs_G);
    stat_to_dyn(CHAR_H, NUMBER_PIXELS_CHARACTER, inputs_H);
    stat_to_dyn(CHAR_I, NUMBER_PIXELS_CHARACTER, inputs_I);
    stat_to_dyn(CHAR_J, NUMBER_PIXELS_CHARACTER, inputs_J);
    stat_to_dyn(CHAR_K, NUMBER_PIXELS_CHARACTER, inputs_K);
    stat_to_dyn(CHAR_L, NUMBER_PIXELS_CHARACTER, inputs_L);
    stat_to_dyn(CHAR_M, NUMBER_PIXELS_CHARACTER, inputs_M);
    stat_to_dyn(CHAR_N, NUMBER_PIXELS_CHARACTER, inputs_N);
    stat_to_dyn(CHAR_O, NUMBER_PIXELS_CHARACTER, inputs_O);
    stat_to_dyn(CHAR_P, NUMBER_PIXELS_CHARACTER, inputs_P);
    stat_to_dyn(CHAR_Q, NUMBER_PIXELS_CHARACTER, inputs_Q);
    stat_to_dyn(CHAR_R, NUMBER_PIXELS_CHARACTER, inputs_R);
    stat_to_dyn(CHAR_S, NUMBER_PIXELS_CHARACTER, inputs_S);
    stat_to_dyn(CHAR_T, NUMBER_PIXELS_CHARACTER, inputs_T);
    stat_to_dyn(CHAR_U, NUMBER_PIXELS_CHARACTER, inputs_U);
    stat_to_dyn(CHAR_V, NUMBER_PIXELS_CHARACTER, inputs_V);
    stat_to_dyn(CHAR_W, NUMBER_PIXELS_CHARACTER, inputs_W);
    stat_to_dyn(CHAR_X, NUMBER_PIXELS_CHARACTER, inputs_X);
    stat_to_dyn(CHAR_Y, NUMBER_PIXELS_CHARACTER, inputs_Y);
    stat_to_dyn(CHAR_Z, NUMBER_PIXELS_CHARACTER, inputs_Z);

    inputs[0] = inputs_a;
    inputs[1] = inputs_b;
    inputs[2] = inputs_c;
    inputs[3] = inputs_d;
    inputs[4] = inputs_e;
    inputs[5] = inputs_f;
    inputs[6] = inputs_g;
    inputs[7] = inputs_h;
    inputs[8] = inputs_i;
    inputs[9] = inputs_j;
    inputs[10] = inputs_k;
    inputs[11] = inputs_l;
    inputs[12] = inputs_m;
    inputs[13] = inputs_n;
    inputs[14] = inputs_o;
    inputs[15] = inputs_p;
    inputs[16] = inputs_q;
    inputs[17] = inputs_r;
    inputs[18] = inputs_s;
    inputs[19] = inputs_t;
    inputs[20] = inputs_u;
    inputs[21] = inputs_v;
    inputs[22] = inputs_w;
    inputs[23] = inputs_x;
    inputs[24] = inputs_y;
    inputs[25] = inputs_z;

    inputs[26] = inputs_A;
    inputs[27] = inputs_B;
    inputs[28] = inputs_C;
    inputs[29] = inputs_D;
    inputs[30] = inputs_E;
    inputs[31] = inputs_F;
    inputs[32] = inputs_G;
    inputs[33] = inputs_H;
    inputs[34] = inputs_I;
    inputs[35] = inputs_J;
    inputs[36] = inputs_K;
    inputs[37] = inputs_L;
    inputs[38] = inputs_M;
    inputs[39] = inputs_N;
    inputs[40] = inputs_O;
    inputs[41] = inputs_P;
    inputs[42] = inputs_Q;
    inputs[43] = inputs_R;
    inputs[44] = inputs_S;
    inputs[45] = inputs_T;
    inputs[46] = inputs_U;
    inputs[47] = inputs_V;
    inputs[48] = inputs_W;
    inputs[49] = inputs_X;
    inputs[50] = inputs_Y;
    inputs[51] = inputs_Z;

    //*******************************************//
    //          VARIABLES AFFECTATIONS           //
    //*******************************************//

    //Initialize the flags structs
    flags.inputsSet = 0;
    flags.learning = 0;
    flags.iterations = -1;
    flags.text_to_data = 0;
    flags.serialize = 0;
    iterations = 0;
    error = 100;

    //Set the targets
    for(i = 0; i < NUMBER_PATTERNS; i++)
        targets[i][i] = 1;


    if(checkFlags(argc, argv, &flags))
        return 1;
    else
    {
        if(flags.inputsSet == 0)
            return 1;
        else
        {
            initialize_layer(&input, NUMBER_INPUT_NEURONS,
                    NUMBER_HIDDEN_NEURONS, BIAS);
            initialize_layer(&hidden, NUMBER_HIDDEN_NEURONS,
                    NUMBER_OUTPUT_NEURONS, BIAS);
            initialize_layer(&output, NUMBER_OUTPUT_NEURONS,
                    0, BIAS);

            initialize_network(&network, &input, &hidden, &output);

            if(flags.text_to_data == 1)
                get_data(&network);
            if(flags.learning == 0)
            {
                inputsUser = flags.inputsFlag;
                set_inputs(&network, inputsUser);
                feedforward(&network);
                printOutput(&network);
                if(flags.serialize)
                    serialization(&network);
            }
            else
            {
                inputsUser = flags.inputsFlag;
                if(flags.iterations == -1)
                    learning(&network, NUMBER_PATTERNS, &iterations,
                            &inputs, &targets, &results, &error,
                            ETA, ALPHA, 0.01);
                else
                {
                    learning2(&network, NUMBER_PATTERNS, flags.iterations,
                            &inputs, &targets, &results, &error,
                            ETA, ALPHA);
                }
                set_inputs(&network, inputsUser);
                feedforward(&network);
                printOutput(&network);
                if(flags.serialize)
                    serialization(&network);
            }
        }
    }
    printf("\n\n");
    return 0;
}

static int checkFlags(int argc, char *argv[], struct s_flags_nn *flags)
{
    int i;
    if(argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        print_nn_help();
        return 1;
    }
    for (i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-learning") == 0)
        {
            if(flags->learning)
                return print_flag_error();
            flags->learning = 1;
        }
        else if(strcmp(argv[i], "-serialize") == 0)
        {
            if(flags->serialize)
                return print_flag_error();
            flags->serialize = 1;
        }
        else if(strcmp(argv[i], "-fromtext") == 0)
        {
            if(flags->text_to_data)
                return print_flag_error();
            flags->text_to_data = 1;
        }
        else if(strcmp(argv[i], "-iterations") == 0)
        {
            if(i + 1 >= argc)
                return print_flag_error();
            else
            {
                i++;
                flags->iterations = atoi(argv[i]);
            }
        }
        else if(strcmp(argv[i], "-inputs:a") == 0)
        {
            if(flags->inputsSet)
                return print_flag_error();
            flags->inputsSet = 1;
            stat_to_dyn(CHAR_a, PIXELS, flags->inputsFlag);
        }
        else if(strcmp(argv[i], "-inputs:b") == 0)
        {
            if(flags->inputsSet)
                return print_flag_error();
            flags->inputsSet = 1;
            stat_to_dyn(CHAR_b, PIXELS, flags->inputsFlag);
        }
        else if(strcmp(argv[i], "-inputs:c") == 0)
        {
            if(flags->inputsSet)
                return print_flag_error();
            flags->inputsSet = 1;
            stat_to_dyn(CHAR_c, PIXELS, flags->inputsFlag);
        }
        else
            return print_flag_error();
    }
    return 0;
}


static int print_flag_error(void)
{
    printf("Flag ERROR : type -h for help\n");
    return 1;
}

static void print_nn_help(void)
{
    printf("\n\n./main then -\"your arguments\"\n");
    printf("Here is the list of available args : \n"
            "-inputs:a -> set the inputs with a matrix\n"
            "-inputs:b -> set the inputs with b matrix\n"
            "-inputs:c -> set the inputs with c matrix\n"
            "-learning -> start the learning process\n"
            "-iterations [white space] \"your number\"\n\n"
            "-serialize -> serialize the NN into serialize"
            "-fromtext to make a neural network with serialized data"
            "For example for inputs a matrix and for learning with 2500 "
            "iterations :\n"
            "--> .\\main -inputs:a -learning -iterations 2500\n\n");
}
