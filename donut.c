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
    const int kWidth = 80;
    const int kHeight = 22;
    const size_t kBuffer_size = kWidth * kHeight;
    float z[kBuffer_size];
    char buffer[kBuffer_size];
    const float kPhi_step = 0.07;
    const float kTheta_step = 0.02;
    const char *kShade_chars = ".,-~:;=!*#$@";
    const char kNew_line = '\n';
    const float kTwo_pi = 2 * M_PI;
    printf("\x1b[2J");
    for (;;)
    {
        memset(buffer, ' ', kBuffer_size);
        memset(z, 0, kBuffer_size * sizeof(float));
        for (float phi = 0; phi < kTwo_pi; phi += kPhi_step)
        {
            for (float theta = 0; theta < kTwo_pi; theta += kTheta_step)
            {
                float sin_theta = sin(theta);
                float cos_phi = cos(phi);
                float sin_A = sin(A);
                float sin_phi = sin(phi);
                float cos_A = cos(A);
                float h = cos_phi + 2;
                float D = 1 / (sin_theta * h * sin_A + sin_phi * cos_A + 5);
                float cos_theta = cos(theta);
                float cos_B = cos(B);
                float sin_B = sin(B);
                float t = sin_theta * h * cos_A - sin_phi * sin_A;
                int x   = (float)(kWidth / 2) + 30 * D * (cos_theta * h * cos_B - t * sin_B);
                int y = (float)(kHeight / 2 + 1) + 15 * D * (cos_theta * h * sin_B + t * cos_B), o = x + kWidth * y;
                int N = 8 * ((sin_phi * sin_A - sin_theta * cos_phi * cos_A) * cos_B - sin_theta * cos_phi * sin_A - sin_phi * cos_A - cos_theta * cos_phi * sin_B);
                if (0 < y && y < kHeight && 0 < x && x < kWidth && D > z[o])
                {
                    z[o] = D;
                    buffer[o] = kShade_chars[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[H");
        for (size_t k = 0; k <= kBuffer_size; k++)
            putchar(k % kWidth ? buffer[k] : kNew_line);
        A += 0.04;
        B += 0.02;
    }
}
