#ifndef PERFORM_OCR_H
#define PERFORM_OCR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "picture/copy_binarized.h"
#include "picture/binarypic.h"
#include "segmentation/text_picture_segmentation.h"
#include "segmentation/split_lines.h"
#include "segmentation/split_chars.h"
#include "segmentation/split_blocs.h"
#include "segmentation/draw_rectangle.h"
#include "segmentation/morphology.h"
#include "segmentation/vectorize_char.h"
#include "neuralNetwork/nn_main.h"
#include "neuralNetwork/learn_from_pics.h"
#include "neuralNetwork/consts.h"
#include "improvements/dictionary.h"

GdkPixbuf * perform_ocr(GdkPixbuf *origin);

#endif
