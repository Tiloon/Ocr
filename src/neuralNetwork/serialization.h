#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

//Gather all the setter methods
void network_to_text(FILE *file, struct s_network *network);
//Gather bias and weights setter methods
void set_specific_data(FILE *file, struct s_network *network);
//Gather nb_units and nb weights setter methods
void set_general_data(FILE *file, struct s_network *network);

/* ------------------ SPECIFIC DATA ------------------
 * Will set the weights and the bias on this way
 * INPUT (or HIDDEN or OUTPUT)
 * WEIGHTS
 * VALUE0 \n
 * VALUE1 \n
 * ...
 * BIAIS
 * VALUE0 \n
 * VALUE1 \n
 *...
 */
void set_weights(FILE *file, struct s_network *network);
void set_bias(FILE *file, struct s_network *network);

/* ------------------ GENERAL DATA ------------------
 * Set on the first line 6 integers on this way :
 * nb_inputs_units nb_weights_input_to_hidden ...
 * with a space between each value *
 */
void set_number_units(FILE *file, struct s_network *network);
void set_number_weights(FILE *file, struct s_network *network);