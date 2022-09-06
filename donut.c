// src: https://www.a1k0n.net/2006/09/15/obfuscated-c-donut.html

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    float A = 0;
    float B = 0;
    const size_t kBuffer_size = 1760;
    float z[kBuffer_size];
    char b[kBuffer_size];
    const float kJ_step = 0.07;
    const float kI_step = 0.02;
    const int kWidth = 80;
    const int kHeight = 22;
    const char *kShade_chars = ".,-~:;=!*#$@";
    const char kNew_line = '\n';
    const float kTwo_pi = 2 * M_PI;
    printf("\x1b[2J");
    for (;;)
    {
        memset(b, ' ', kBuffer_size);
        memset(z, 0, kBuffer_size * sizeof(float));
        for (float j = 0; kTwo_pi > j; j += kJ_step)
        {
            for (float i = 0; kTwo_pi > i; i += kI_step)
            {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x   = (float)(kWidth / 2) + 30 * D * (l * h * m - t * n);
                int y = (float)(kHeight / 2 + 1) + 15 * D * (l * h * n + t * m), o = x + kWidth * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if (kHeight > y && y > 0 && x > 0 && kWidth > x && D > z[o])
                {
                    z[o] = D;
                    b[o] = kShade_chars[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[H");
        for (size_t k = 0; kBuffer_size >= k; k++)
            putchar(k % kWidth ? b[k] : kNew_line);
        A += 0.04;
        B += 0.02;
    }
}
