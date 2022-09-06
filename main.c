// ------------------------------------------------------------------------- //
// De-obfuscated spinning donut                                              //
//  - src: https://www.a1k0n.net/2006/09/15/obfuscated-c-donut.html          //
//                                                                           //
// Author: Ali Bororgzadeh                                                   //
//  - with help of https://www.youtube.com/watch?v=BXSZ4_DKCBw               //
// ------------------------------------------------------------------------- //

#include "globals.h"
#include "helper.h"
#include <stdbool.h>

int main()
{
    float A = 0;
    float B = 0;

    Canvas canvas;
    float z[kCanvas_size];

    while (true)
    {
        modify_buffer(z, &canvas, A, B);
        display_buffer(canvas);

        A += 0.04;
        B += 0.02;
    }
}

// ------------------------------------------------------------------------- //
