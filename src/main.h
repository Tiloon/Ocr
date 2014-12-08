#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "redef.h"

#include "picture/copy_binarized.h"
#include "picture/binarypic.h"
#include "picture/loader.h"
#include "filters/filters.h"
#include "picture/convert_pic.h"

#include "perform_ocr.h"

#include "help/help.h"

<<<<<<< HEAD
#include "improvements/dictionary.h"
int segment_and_save(GdkPixbuf *origin);



=======
>>>>>>> aff467cb61727f3faef7f124dd00a6e0c57d1fa3
#ifndef NOGUI
#include "gui/gui.h"
#endif

#define FLAG_ALREADY_SET    0x01
#define FLAG_UNDEFINED      0x02
#define FLAG_MISSING_ARG    0x04
#define FLAG_INVALID_ARG    0x08

// Test if it works on target
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"

struct s_flags {
    char verbosity;
    char gui;
    char kerning_segm;
    char rules;
    char *filename;
    char *filteroutput;
    char *segmentation_output;
    // Other flags
};

#define FLAGS flags()
struct s_flags *flags(void);

#endif
