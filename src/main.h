#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>

#include "picture/binarypic.h"
#include "picture/loader.h"
#include "filters/filters.h"
#include "segmentation/text_picture_segmentation.h"
#include "segmentation/split_lines.h"
#include "picture/convert_pic.h"
#include "segmentation/draw_rectangle.h"
#include "segmentation/morphology.h"

#ifndef NOGUI
#include "gui/gui.h"
#endif

#define FLAG_ALREADY_SET    0x01
#define FLAG_UNDEFINED      0x02
#define FLAG_MISSING_ARG    0x04
#define FLAG_INVALID_ARG    0x08

struct s_flags {
    char gui;
    char* filename;
    char* filteroutput;
    // Other flags
};

#endif
