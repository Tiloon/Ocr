#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "../main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "../redef.h"
#include "../picture/copy_binarized.h"
#include "../picture/binarypic.h"
#include "../picture/loader.h"
#include "../filters/filters.h"
#include "../picture/convert_pic.h"
#include "../perform_ocr.h"
#include "../help/help.h"
#include "../char_to_wchar.h"


int gui_main(int argc, char **argv);
void load_image();
void binarize();
void apply_gaussian_filter();
void check_rotation();
void segmentation();
void all_filters();
void start_recognition();
void save_text();
void clean();
void quit();
GtkTextBuffer** get_text_buffer();
