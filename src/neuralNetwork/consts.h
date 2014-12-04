#ifndef NN_CONSTS_H
#define NN_CONSTS_H

#define CHAR_WIDTH 16
#define CHAR_HEIGHT 16
#define NUMBER_PATTERNS             98
#define NUMBER_PIXELS_CHARACTER     (CHAR_WIDTH * CHAR_HEIGHT)
#define NUMBER_INPUT_NEURONS        NUMBER_PIXELS_CHARACTER
#define NUMBER_HIDDEN_NEURONS       0.1 * NUMBER_INPUT_NEURONS
#define ETA     0.1
#define ALPHA   0.8
#define BIAS    0.5
#define ERROR   0.10 


#endif
