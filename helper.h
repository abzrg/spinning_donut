#ifndef DONUT_H
#define DONUT_H

// ------------------------------------------------------------------------- //

#include "canvas.h"

void clear_screen(void);

void modify_buffer(float *z, Canvas *canvas, float A, float B);

void display_buffer(const Canvas canvas);

// ------------------------------------------------------------------------- //

#endif
