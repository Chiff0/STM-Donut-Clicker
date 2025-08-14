/*
 * FLP_lib_chars.c
 * Character and symbol rendering functions
 *
 *  Created on: Aug 13, 2025
 *      Author: flp
 */

#include "FLP_lib_chars.h"
#include "FLP_lib.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272


//=============================== HELPER FUNCTION ============================

void fill_pixel(uint16_t* buffer, int x_base, int y_base, int x, int y, uint32_t color)
{
    int pixel_x = x_base + x + offset;
    int pixel_y = y_base + y;
    
    if (pixel_x >= 0 && pixel_x < SCREEN_WIDTH && pixel_y >= 0 && pixel_y < SCREEN_HEIGHT)
    {
        buffer[pixel_x + pixel_y * SCREEN_WIDTH] = color;
    }
}

//================================ SYMBOL -> BUFFER =====================================================

void copy_dot(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 9; i < 12; i++)
    {
        for (int j = 0; j < 3; j++) 
            fill_pixel(buffer, x, y, j, i, color);    
    }
}

void copy_comma(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 7; i < 12; i++)
    {
        for (int j = 0; j < 3; j++) 
            fill_pixel(buffer, x, y, j, i, color);
    }
}

void copy_dash(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 5; i < 8; i++)
    {
        for (int j = 0; j < 6; j++) 
            fill_pixel(buffer, x, y, j, i, color);
    }
}

void copy_plus(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 2; i < 10; i++)
    {
        for (int j = 2; j < 4; j++) 
            fill_pixel(buffer, x, y, j, i, color);
    }
    for (int i = 5; i < 7; i++)
    {
        for (int j = 0; j < 6; j++) 
            fill_pixel(buffer, x, y, j, i, color);
    }
}

void copy_hashtag(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 2; i < 10; i++)
    {
        for (int j = 1; j < 2; j++) 
            fill_pixel(buffer, x, y, j, i, color);
        for (int j = 4; j < 5; j++) 
            fill_pixel(buffer, x, y, j, i, color);
    }
    
    for (int i = 0; i < 6; i++)
    {
        for (int j = 4; j < 5; j++) 
            fill_pixel(buffer, x, y, i, j, color);
        for (int j = 7; j < 8; j++) 
            fill_pixel(buffer, x, y, i, j, color);
    }
}

void copy_at(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++)
    {
        fill_pixel(buffer, x, y, i, 0, color);
        fill_pixel(buffer, x, y, i, 11, color);
    }
    for (int i = 1; i < 11; i++)
    {
        fill_pixel(buffer, x, y, 0, i, color);
        fill_pixel(buffer, x, y, 5, i, color);
    }
    for (int i = 3; i < 8; i++)
    {
        fill_pixel(buffer, x, y, 2, i, color);
        fill_pixel(buffer, x, y, 3, i, color);
    }
    fill_pixel(buffer, x, y, 2, 5, color);
    fill_pixel(buffer, x, y, 4, 6, color);
}

void copy_dollar(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++)
    {
        fill_pixel(buffer, x, y, 2, i, color);
    }
    
    for (int j = 1; j < 4; j++)
    {
        fill_pixel(buffer, x, y, j, 2, color);
        fill_pixel(buffer, x, y, j, 5, color);
        fill_pixel(buffer, x, y, j, 9, color);
    }
    fill_pixel(buffer, x, y, 0, 3, color);
    fill_pixel(buffer, x, y, 4, 7, color);
}

void copy_equals(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int j = 0; j < 6; j++)
    {
        fill_pixel(buffer, x, y, j, 4, color);
        fill_pixel(buffer, x, y, j, 7, color);
    }
}

void copy_slash(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++)
    {
        int x_pos = 5 - (i / 3);
        if (x_pos >= 0 && x_pos < 6)
            fill_pixel(buffer, x, y, x_pos, i, color);
    }
}

void copy_star(uint16_t* buffer, int x, int y, uint32_t color)
{
    fill_pixel(buffer, x, y, 2, 4, color);
    fill_pixel(buffer, x, y, 2, 5, color);
    fill_pixel(buffer, x, y, 2, 6, color);
    for (int j = 1; j < 4; j++)
        fill_pixel(buffer, x, y, j, 5, color);
    fill_pixel(buffer, x, y, 1, 4, color);
    fill_pixel(buffer, x, y, 3, 4, color);
    fill_pixel(buffer, x, y, 1, 6, color);
    fill_pixel(buffer, x, y, 3, 6, color);
}

void copy_tilde(uint16_t* buffer, int x, int y, uint32_t color)
{
    fill_pixel(buffer, x, y, 0, 5, color);
    fill_pixel(buffer, x, y, 1, 4, color);
    fill_pixel(buffer, x, y, 2, 4, color);
    fill_pixel(buffer, x, y, 3, 5, color);
    fill_pixel(buffer, x, y, 4, 5, color);
    fill_pixel(buffer, x, y, 5, 4, color);
}

void copy_semicolon(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 4; i < 6; i++)
    {
        for (int j = 1; j < 3; j++)
            fill_pixel(buffer, x, y, j, i, color);
    }
    for (int i = 8; i < 12; i++)
    {
        for (int j = 1; j < 3; j++)
            fill_pixel(buffer, x, y, j, i, color);
    }
}

void copy_colon(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 3; i < 5; i++)
    {
        for (int j = 2; j < 4; j++)
            fill_pixel(buffer, x, y, j, i, color);
    }
    for (int i = 7; i < 9; i++)
    {
        for (int j = 2; j < 4; j++)
            fill_pixel(buffer, x, y, j, i, color);
    }
}

//================================ LETTER -> BUFFER =====================================================

void copy_A(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 12; i++) fill_pixel(buffer, x, y, 5, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 6, color);
}

void copy_B(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 5, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, 5, i, color);
    for (int i = 6; i < 11; i++) fill_pixel(buffer, x, y, 5, i, color);
}

void copy_C(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 11; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
}

void copy_D(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 4; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 4; i++) fill_pixel(buffer, x, y, i, 11, color);
    for (int i = 1; i < 11; i++) fill_pixel(buffer, x, y, 4, i, color);
    fill_pixel(buffer, x, y, 5, 2, color);
    fill_pixel(buffer, x, y, 5, 9, color);
}

void copy_E(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 6; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 4; i++) fill_pixel(buffer, x, y, i, 5, color);
    for (int i = 1; i < 6; i++) fill_pixel(buffer, x, y, i, 11, color);
}

void copy_F(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 6; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 4; i++) fill_pixel(buffer, x, y, i, 5, color);
}

void copy_G(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 11; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
    for (int i = 6; i < 12; i++) fill_pixel(buffer, x, y, 5, i, color);
    for (int i = 3; i < 6; i++) fill_pixel(buffer, x, y, i, 6, color);
}

void copy_H(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 5, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 5, color);
}

void copy_I(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 6; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 0; i < 6; i++) fill_pixel(buffer, x, y, i, 11, color);
    for (int i = 1; i < 11; i++) fill_pixel(buffer, x, y, 2, i, color);
    for (int i = 1; i < 11; i++) fill_pixel(buffer, x, y, 3, i, color);
}

void copy_J(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 6; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 0; i < 10; i++) fill_pixel(buffer, x, y, 4, i, color);
    for (int i = 8; i < 11; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 4; i++) fill_pixel(buffer, x, y, i, 11, color);
}

void copy_K(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    fill_pixel(buffer, x, y, 1, 5, color);
    fill_pixel(buffer, x, y, 2, 4, color);
    fill_pixel(buffer, x, y, 3, 3, color);
    fill_pixel(buffer, x, y, 4, 2, color);
    fill_pixel(buffer, x, y, 5, 1, color);
    fill_pixel(buffer, x, y, 2, 6, color);
    fill_pixel(buffer, x, y, 3, 7, color);
    fill_pixel(buffer, x, y, 4, 8, color);
    fill_pixel(buffer, x, y, 5, 9, color);
    fill_pixel(buffer, x, y, 5, 10, color);
}

void copy_L(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 6; i++) fill_pixel(buffer, x, y, i, 11, color);
}

void copy_M(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 5, i, color);
    fill_pixel(buffer, x, y, 1, 1, color);
    fill_pixel(buffer, x, y, 2, 2, color);
    fill_pixel(buffer, x, y, 2, 3, color);
    fill_pixel(buffer, x, y, 3, 2, color);
    fill_pixel(buffer, x, y, 3, 3, color);
    fill_pixel(buffer, x, y, 4, 1, color);
}

void copy_N(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 5, i, color);
    fill_pixel(buffer, x, y, 1, 2, color);
    fill_pixel(buffer, x, y, 2, 3, color);
    fill_pixel(buffer, x, y, 2, 4, color);
    fill_pixel(buffer, x, y, 3, 5, color);
    fill_pixel(buffer, x, y, 3, 6, color);
    fill_pixel(buffer, x, y, 4, 7, color);
    fill_pixel(buffer, x, y, 4, 8, color);
}

void copy_O(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 11; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
    for (int i = 1; i < 11; i++) fill_pixel(buffer, x, y, 5, i, color);
}

void copy_P(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 6; i++) fill_pixel(buffer, x, y, 5, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 6, color);
}

void copy_Q(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 11; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
    for (int i = 1; i < 10; i++) fill_pixel(buffer, x, y, 5, i, color);
    fill_pixel(buffer, x, y, 3, 8, color);
    fill_pixel(buffer, x, y, 4, 9, color);
    fill_pixel(buffer, x, y, 5, 10, color);
    fill_pixel(buffer, x, y, 5, 11, color);
}

void copy_R(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 6; i++) fill_pixel(buffer, x, y, 5, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 6, color);
    fill_pixel(buffer, x, y, 2, 7, color);
    fill_pixel(buffer, x, y, 3, 8, color);
    fill_pixel(buffer, x, y, 4, 9, color);
    fill_pixel(buffer, x, y, 5, 10, color);
    fill_pixel(buffer, x, y, 5, 11, color);
}

void copy_S(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 5, color);
    for (int i = 6; i < 11; i++) fill_pixel(buffer, x, y, 5, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
}

void copy_T(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 6; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 12; i++) fill_pixel(buffer, x, y, 2, i, color);
    for (int i = 1; i < 12; i++) fill_pixel(buffer, x, y, 3, i, color);
}

void copy_U(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 11; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 0; i < 11; i++) fill_pixel(buffer, x, y, 5, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
}

void copy_V(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 8; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 0; i < 8; i++) fill_pixel(buffer, x, y, 5, i, color);
    fill_pixel(buffer, x, y, 1, 8, color);
    fill_pixel(buffer, x, y, 1, 9, color);
    fill_pixel(buffer, x, y, 4, 8, color);
    fill_pixel(buffer, x, y, 4, 9, color);
    fill_pixel(buffer, x, y, 2, 10, color);
    fill_pixel(buffer, x, y, 3, 10, color);
    fill_pixel(buffer, x, y, 2, 11, color);
    fill_pixel(buffer, x, y, 3, 11, color);
}

void copy_W(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 5, i, color);
    fill_pixel(buffer, x, y, 2, 8, color);
    fill_pixel(buffer, x, y, 2, 9, color);
    fill_pixel(buffer, x, y, 3, 8, color);
    fill_pixel(buffer, x, y, 3, 9, color);
    fill_pixel(buffer, x, y, 1, 10, color);
    fill_pixel(buffer, x, y, 4, 10, color);
}

void copy_X(uint16_t* buffer, int x, int y, uint32_t color)
{
    fill_pixel(buffer, x, y, 0, 0, color);
    fill_pixel(buffer, x, y, 0, 1, color);
    fill_pixel(buffer, x, y, 5, 0, color);
    fill_pixel(buffer, x, y, 5, 1, color);
    fill_pixel(buffer, x, y, 1, 2, color);
    fill_pixel(buffer, x, y, 1, 3, color);
    fill_pixel(buffer, x, y, 4, 2, color);
    fill_pixel(buffer, x, y, 4, 3, color);
    fill_pixel(buffer, x, y, 2, 4, color);
    fill_pixel(buffer, x, y, 2, 5, color);
    fill_pixel(buffer, x, y, 3, 4, color);
    fill_pixel(buffer, x, y, 3, 5, color);
    fill_pixel(buffer, x, y, 2, 6, color);
    fill_pixel(buffer, x, y, 2, 7, color);
    fill_pixel(buffer, x, y, 3, 6, color);
    fill_pixel(buffer, x, y, 3, 7, color);
    fill_pixel(buffer, x, y, 1, 8, color);
    fill_pixel(buffer, x, y, 1, 9, color);
    fill_pixel(buffer, x, y, 4, 8, color);
    fill_pixel(buffer, x, y, 4, 9, color);
    fill_pixel(buffer, x, y, 0, 10, color);
    fill_pixel(buffer, x, y, 0, 11, color);
    fill_pixel(buffer, x, y, 5, 10, color);
    fill_pixel(buffer, x, y, 5, 11, color);
}

void copy_Y(uint16_t* buffer, int x, int y, uint32_t color)
{
    fill_pixel(buffer, x, y, 0, 0, color);
    fill_pixel(buffer, x, y, 0, 1, color);
    fill_pixel(buffer, x, y, 5, 0, color);
    fill_pixel(buffer, x, y, 5, 1, color);
    fill_pixel(buffer, x, y, 1, 2, color);
    fill_pixel(buffer, x, y, 1, 3, color);
    fill_pixel(buffer, x, y, 4, 2, color);
    fill_pixel(buffer, x, y, 4, 3, color);
    fill_pixel(buffer, x, y, 2, 4, color);
    fill_pixel(buffer, x, y, 2, 5, color);
    fill_pixel(buffer, x, y, 3, 4, color);
    fill_pixel(buffer, x, y, 3, 5, color);
    for (int i = 6; i < 12; i++) fill_pixel(buffer, x, y, 2, i, color);
    for (int i = 6; i < 12; i++) fill_pixel(buffer, x, y, 3, i, color);
}

void copy_Z(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 6; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 0; i < 6; i++) fill_pixel(buffer, x, y, i, 11, color);
    fill_pixel(buffer, x, y, 5, 1, color);
    fill_pixel(buffer, x, y, 5, 2, color);
    fill_pixel(buffer, x, y, 4, 3, color);
    fill_pixel(buffer, x, y, 3, 4, color);
    fill_pixel(buffer, x, y, 3, 5, color);
    fill_pixel(buffer, x, y, 2, 6, color);
    fill_pixel(buffer, x, y, 2, 7, color);
    fill_pixel(buffer, x, y, 1, 8, color);
    fill_pixel(buffer, x, y, 0, 9, color);
    fill_pixel(buffer, x, y, 0, 10, color);
}

void copy_space(uint16_t* buffer, int x, int y, uint32_t color)
{
    // Space is just empty, no pixels to draw
    (void)buffer; (void)x; (void)y; (void)color; // Suppress unused parameter warnings
}

//================================ NUMBER -> BUFFER =====================================================

void copy_0(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 11; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
    for (int i = 1; i < 11; i++) fill_pixel(buffer, x, y, 5, i, color);
    // Diagonal line to distinguish from O
    fill_pixel(buffer, x, y, 4, 2, color);
    fill_pixel(buffer, x, y, 3, 3, color);
    fill_pixel(buffer, x, y, 2, 4, color);
    fill_pixel(buffer, x, y, 1, 5, color);
}

void copy_1(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 2, i, color);
    fill_pixel(buffer, x, y, 1, 1, color);
    fill_pixel(buffer, x, y, 0, 2, color);
    for (int i = 0; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
}

void copy_2(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    fill_pixel(buffer, x, y, 0, 1, color);
    fill_pixel(buffer, x, y, 5, 1, color);
    fill_pixel(buffer, x, y, 5, 2, color);
    fill_pixel(buffer, x, y, 5, 3, color);
    fill_pixel(buffer, x, y, 4, 4, color);
    fill_pixel(buffer, x, y, 3, 5, color);
    fill_pixel(buffer, x, y, 2, 6, color);
    fill_pixel(buffer, x, y, 1, 7, color);
    fill_pixel(buffer, x, y, 0, 8, color);
    fill_pixel(buffer, x, y, 0, 9, color);
    fill_pixel(buffer, x, y, 0, 10, color);
    for (int i = 0; i < 6; i++) fill_pixel(buffer, x, y, i, 11, color);
}

void copy_3(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    fill_pixel(buffer, x, y, 0, 1, color);
    fill_pixel(buffer, x, y, 5, 1, color);
    fill_pixel(buffer, x, y, 5, 2, color);
    fill_pixel(buffer, x, y, 5, 3, color);
    fill_pixel(buffer, x, y, 5, 4, color);
    for (int i = 2; i < 5; i++) fill_pixel(buffer, x, y, i, 5, color);
    fill_pixel(buffer, x, y, 5, 6, color);
    fill_pixel(buffer, x, y, 5, 7, color);
    fill_pixel(buffer, x, y, 5, 8, color);
    fill_pixel(buffer, x, y, 5, 9, color);
    fill_pixel(buffer, x, y, 5, 10, color);
    fill_pixel(buffer, x, y, 0, 10, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
}

void copy_4(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 7; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 0; i < 6; i++) fill_pixel(buffer, x, y, i, 6, color);
    for (int i = 0; i < 12; i++) fill_pixel(buffer, x, y, 4, i, color);
}

void copy_5(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 6; i++) fill_pixel(buffer, x, y, i, 0, color);
    fill_pixel(buffer, x, y, 0, 1, color);
    fill_pixel(buffer, x, y, 0, 2, color);
    fill_pixel(buffer, x, y, 0, 3, color);
    fill_pixel(buffer, x, y, 0, 4, color);
    for (int i = 0; i < 5; i++) fill_pixel(buffer, x, y, i, 5, color);
    fill_pixel(buffer, x, y, 5, 6, color);
    fill_pixel(buffer, x, y, 5, 7, color);
    fill_pixel(buffer, x, y, 5, 8, color);
    fill_pixel(buffer, x, y, 5, 9, color);
    fill_pixel(buffer, x, y, 5, 10, color);
    fill_pixel(buffer, x, y, 0, 10, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
}

void copy_6(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 11; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 5, color);
    for (int i = 6; i < 11; i++) fill_pixel(buffer, x, y, 5, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
}

void copy_7(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 0; i < 6; i++) fill_pixel(buffer, x, y, i, 0, color);
    fill_pixel(buffer, x, y, 5, 1, color);
    fill_pixel(buffer, x, y, 5, 2, color);
    fill_pixel(buffer, x, y, 4, 3, color);
    fill_pixel(buffer, x, y, 4, 4, color);
    fill_pixel(buffer, x, y, 3, 5, color);
    fill_pixel(buffer, x, y, 3, 6, color);
    fill_pixel(buffer, x, y, 2, 7, color);
    fill_pixel(buffer, x, y, 2, 8, color);
    fill_pixel(buffer, x, y, 1, 9, color);
    fill_pixel(buffer, x, y, 1, 10, color);
    fill_pixel(buffer, x, y, 1, 11, color);
}

void copy_8(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    fill_pixel(buffer, x, y, 0, 1, color);
    fill_pixel(buffer, x, y, 0, 2, color);
    fill_pixel(buffer, x, y, 0, 3, color);
    fill_pixel(buffer, x, y, 0, 4, color);
    fill_pixel(buffer, x, y, 5, 1, color);
    fill_pixel(buffer, x, y, 5, 2, color);
    fill_pixel(buffer, x, y, 5, 3, color);
    fill_pixel(buffer, x, y, 5, 4, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 5, color);
    fill_pixel(buffer, x, y, 0, 6, color);
    fill_pixel(buffer, x, y, 0, 7, color);
    fill_pixel(buffer, x, y, 0, 8, color);
    fill_pixel(buffer, x, y, 0, 9, color);
    fill_pixel(buffer, x, y, 0, 10, color);
    fill_pixel(buffer, x, y, 5, 6, color);
    fill_pixel(buffer, x, y, 5, 7, color);
    fill_pixel(buffer, x, y, 5, 8, color);
    fill_pixel(buffer, x, y, 5, 9, color);
    fill_pixel(buffer, x, y, 5, 10, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
}

void copy_9(uint16_t* buffer, int x, int y, uint32_t color)
{
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 0, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, 0, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 5, color);
    for (int i = 1; i < 11; i++) fill_pixel(buffer, x, y, 5, i, color);
    for (int i = 1; i < 5; i++) fill_pixel(buffer, x, y, i, 11, color);
}
