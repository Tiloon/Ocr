#include "structure.h"

/*
 * All this part is dedicated to convert the neural network
 * from DATA to a text file
 */

//Gather all the setter methods
void network_to_text(FILE *file, struct s_network *network, FILE *file2);
//Gather bias and weights setter methods
void set_specific_data(FILE *file, struct s_network *network);
//Gather nb_units and nb weights setter methods
void set_general_data(FILE *file, struct s_network *network);

/* ------------------ GENERAL DATA ------------------
 * Set on the first line 6 integers on this way :
 * nb_inputs_units (+others layers) nb_weights_input_to_hidden (+others layer)
 * with a space between each value
 */
void set_header_file(FILE *file);
void set_number_units(FILE *file, struct s_network *network);
void set_number_weights(FILE *file, struct s_network *network);


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
void set_weights_bias(FILE *file, struct s_network *network);
void set_charset(FILE *file);
void set_weights_layer(FILE *file, struct s_layer *layer);
void set_bias_layer(FILE *file, struct s_layer *layer);


/*
 * All this part is dedicated to convert a text file
 * into a working neural network
 */

void text_to_network(FILE *file, struct s_network *network, FILE *file2);
void get_general_data(FILE *file, struct s_network *network);
void get_specific_data(FILE *file, struct s_network *network);
void get_charset(FILE *file, struct s_network *network);
void get_number_units(FILE *file, struct s_network *network);
void get_number_weights(FILE *file, struct s_network *network);
void get_bias(FILE *file, struct s_network *network);
void get_weights(FILE *file, struct s_network *network);
void get_bias_layer(FILE *file, struct s_layer *layer);
void get_weights_layer(FILE *file, struct s_layer *layer);
void get_weights_bias(FILE *file, struct s_network *network);
