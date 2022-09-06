// src: https://www.a1k0n.net/2006/09/15/obfuscated-c-donut.html

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// -- Global Variables ----------------------------------------------------- //
const char kNew_line     = '\n';
const char *kShade_chars = ".,-~:;=!*#$@";
const float kTwo_pi      = 2 * M_PI;
const float kPhi_step    = 0.07;
const float kTheta_step  = 0.02;


// -- Function headers ----------------------------------------------------- //
static void clear_screen(void);

static void
modify_buffer(float *z, char *buffer, const size_t width, const size_t height, float A, float B);

static void display_buffer(char *buffer, const size_t width, const size_t height);


// ------------------------------------------------------------------------- //
// -- Main ----------------------------------------------------------------- //

int main()
{
    float A                   = 0;
    float B                   = 0;
    const size_t kWidth       = 80;
    const size_t kHeight      = 22;
    const size_t kBuffer_size = kWidth * kHeight;
    float z[kBuffer_size];
    char buffer[kBuffer_size];

    for (;;)
    {
        modify_buffer(z, buffer, kWidth, kHeight, A, B);
        display_buffer(buffer, kWidth, kHeight);

        A += 0.04;
        B += 0.02;
    }
}


// -- Function definitions ----------------------------------------------------

static void clear_screen(void)
{
    printf("\x1b[2J\x1b[H");
}

static void
modify_buffer(float *z, char *buffer, const size_t width, const size_t height, float A, float B)
{
    const size_t buffer_size = width * height;
    memset(buffer, ' ', buffer_size);
    memset(z, 0, buffer_size * sizeof(float));

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
            size_t x = fabs(width / 2.0) + 30 * D * (cos_theta * h * cos_B - t * sin_B);
            size_t y = fabs(height / 2.0) + 15 * D * (cos_theta * h * sin_B + t * cos_B);
            size_t o = x + width * y;
            int N    = 8 *
            ((sin_phi * sin_A - sin_theta * cos_phi * cos_A) * cos_B -
             sin_theta * cos_phi * sin_A - sin_phi * cos_A - cos_theta * cos_phi * sin_B);

            if (0 < y && y < height && 0 < x && x < width && D > z[o])
            {
                z[o]      = D;
                buffer[o] = kShade_chars[N > 0 ? N : 0];
            }
        }
    }
}

static void display_buffer(char *buffer, size_t width, size_t height)
{
    clear_screen();
    const size_t buffer_size = width * height;
    for (size_t k = 0; k <= buffer_size; k++)
        putchar(k % width ? buffer[k] : kNew_line);
}
