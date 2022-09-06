#ifndef HELPER_H
#define HELPER_H

// ------------------------------------------------------------------------- //

#include "helper.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

void clear_screen(void)
{
    printf("\x1b[2J\x1b[H");
}

void modify_buffer(float *z, Canvas *canvas, float A, float B)
{
    memset(canvas->buffer, ' ', kCanvas_size);
    memset(z, 0, kCanvas_size * sizeof(float));

    for (float phi = 0; phi < kTwo_pi; phi += kPhi_step)
    {
        for (float theta = 0; theta < kTwo_pi; theta += kTheta_step)
        {
            float sin_theta = sin(theta);
            float cos_phi   = cos(phi);
            float sin_A     = sin(A);
            float sin_phi   = sin(phi);
            float cos_A     = cos(A);
            float h         = cos_phi + 2;
            float D         = 1 / (sin_theta * h * sin_A + sin_phi * cos_A + 5);
            float cos_theta = cos(theta);
            float cos_B     = cos(B);
            float sin_B     = sin(B);
            float t         = sin_theta * h * cos_A - sin_phi * sin_A;
            size_t x        = fabs(kCanvas_width / 2.0) +
            30 * D * (cos_theta * h * cos_B - t * sin_B);
            size_t y = fabs(kCanvas_height / 2.0) +
            15 * D * (cos_theta * h * sin_B + t * cos_B);
            size_t o = x + kCanvas_width * y;
            int N    = 8 *
            ((sin_phi * sin_A - sin_theta * cos_phi * cos_A) * cos_B -
             sin_theta * cos_phi * sin_A - sin_phi * cos_A - cos_theta * cos_phi * sin_B);

            if (0 < y && y < kCanvas_height && 0 < x && x < kCanvas_width && D > z[o])
            {
                z[o]              = D;
                canvas->buffer[o] = kShade_chars[N > 0 ? N : 0];
            }
        }
    }
}

void display_buffer(const Canvas canvas)
{
    clear_screen();
    const size_t buffer_size = kCanvas_width * kCanvas_height;
    for (size_t k = 0; k <= buffer_size; k++)
        putchar(k % kCanvas_width ? canvas.buffer[k] : kNew_line);
}

// ------------------------------------------------------------------------- //

#endif
