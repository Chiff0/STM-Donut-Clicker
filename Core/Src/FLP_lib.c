/*
 * FLP_lib.c
 *
 *  Created on: Aug 13, 2025
 *      Author: flp
 */

#include "FLP_lib.h"
#include "FLP_lib_chars.h"

#define SCREEN_HEIGHT 272
#define SCREEN_WIDTH 480

int offset = 0;



//=============================== HELPER FUNCTIONS ============================

char get_ASCII (int intensity)
{
    const char ascii_map[] = " .,-~:;=/*#$@";
    int index = (intensity * (sizeof(ascii_map) - 2)) / 255;
    if (index < 0) index = 0;
    if (index >= sizeof(ascii_map) - 1) index = sizeof(ascii_map) - 2;
    return ascii_map[index];
}



//=============================== FLP DRAW FUNCTIONS (used in touchscreen.c) ============================


void FLP_Draw_Rectangle (uint16_t* buffer, int x, int y, int width, int height, uint32_t color)
{
	for (int row = y; row < y + height; row++)
	{
		for (int col = x; col < x + width; col++)
		{
			buffer[col + row * SCREEN_WIDTH] = color;
		}
	}
}

void FLP_Draw_Box (uint16_t* buffer, int x, int y, int border, int height, int width, uint32_t color)
{
	FLP_Draw_Rectangle (buffer, x, y, height, width, color);
	FLP_Draw_Rectangle (buffer, x + border / 2, y + border / 2, height - border, width - border, 0x0000);
}

void FLP_Draw_Symbol (uint16_t* buffer, int x, int y, uint32_t color, int intensity)
{
    offset = 0;

	char c = get_ASCII (intensity);

    switch(c)
    {
        case '.': copy_dot (buffer, x, y, color); break;
        case ',': copy_comma (buffer, x, y, color); break;
        case '-': copy_dash (buffer, x, y, color); break;
        case '~': copy_tilde (buffer, x, y, color); break;
        case ':': copy_colon (buffer, x, y, color); break;
        case ';': copy_semicolon (buffer, x, y, color); break;
        case '=': copy_equals (buffer, x, y, color); break;
        case '/': copy_slash (buffer, x, y, color); break;
        case '*': copy_star (buffer, x, y, color); break;
        case '#': copy_hashtag (buffer, x, y, color); break;
        case '$': copy_dollar (buffer, x, y, color); break;
        case '@': copy_at (buffer, x, y, color); break;
        default: break;
    }
}


void FLP_Draw_String (uint16_t* buffer, char* string, int x, int y, uint32_t color)
{
    offset = 0;
    char c;
    int i = 0;
    
    while ((c = string[i]) != '\0')
    {
        switch (c)
        {
            case 'A': copy_A (buffer, x, y, color); break;
            case 'B': copy_B (buffer, x, y, color); break;
            case 'C': copy_C (buffer, x, y, color); break;
            case 'D': copy_D (buffer, x, y, color); break;
            case 'E': copy_E (buffer, x, y, color); break;
            case 'F': copy_F (buffer, x, y, color); break;
            case 'G': copy_G (buffer, x, y, color); break;
            case 'H': copy_H (buffer, x, y, color); break;
            case 'I': copy_I (buffer, x, y, color); break;
            case 'J': copy_J (buffer, x, y, color); break;
            case 'K': copy_K (buffer, x, y, color); break;
            case 'L': copy_L (buffer, x, y, color); break;
            case 'M': copy_M (buffer, x, y, color); break;
            case 'N': copy_N (buffer, x, y, color); break;
            case 'O': copy_O (buffer, x, y, color); break;
            case 'P': copy_P (buffer, x, y, color); break;
            case 'Q': copy_Q (buffer, x, y, color); break;
            case 'R': copy_R (buffer, x, y, color); break;
            case 'S': copy_S (buffer, x, y, color); break;
            case 'T': copy_T (buffer, x, y, color); break;
            case 'U': copy_U (buffer, x, y, color); break;
            case 'V': copy_V (buffer, x, y, color); break;
            case 'W': copy_W (buffer, x, y, color); break;
            case 'X': copy_X (buffer, x, y, color); break;
            case 'Y': copy_Y (buffer, x, y, color); break;
            case 'Z': copy_Z (buffer, x, y, color); break;
            case 'a': copy_A (buffer, x, y, color); break;
            case 'b': copy_B (buffer, x, y, color); break;
            case 'c': copy_C (buffer, x, y, color); break;
            case 'd': copy_D (buffer, x, y, color); break;
            case 'e': copy_E (buffer, x, y, color); break;
            case 'f': copy_F (buffer, x, y, color); break;
            case 'g': copy_G (buffer, x, y, color); break;
            case 'h': copy_H (buffer, x, y, color); break;
            case 'i': copy_I (buffer, x, y, color); break;
            case 'j': copy_J (buffer, x, y, color); break;
            case 'k': copy_K (buffer, x, y, color); break;
            case 'l': copy_L (buffer, x, y, color); break;
            case 'm': copy_M (buffer, x, y, color); break;
            case 'n': copy_N (buffer, x, y, color); break;
            case 'o': copy_O (buffer, x, y, color); break;
            case 'p': copy_P (buffer, x, y, color); break;
            case 'q': copy_Q (buffer, x, y, color); break;
            case 'r': copy_R (buffer, x, y, color); break;
            case 's': copy_S (buffer, x, y, color); break;
            case 't': copy_T (buffer, x, y, color); break;
            case 'u': copy_U (buffer, x, y, color); break;
            case 'v': copy_V (buffer, x, y, color); break;
            case 'w': copy_W (buffer, x, y, color); break;
            case 'x': copy_X (buffer, x, y, color); break;
            case 'y': copy_Y (buffer, x, y, color); break;
            case 'z': copy_Z (buffer, x, y, color); break;
            case '0': copy_0 (buffer, x, y, color); break;
            case '1': copy_1 (buffer, x, y, color); break;
            case '2': copy_2 (buffer, x, y, color); break;
            case '3': copy_3 (buffer, x, y, color); break;
            case '4': copy_4 (buffer, x, y, color); break;
            case '5': copy_5 (buffer, x, y, color); break;
            case '6': copy_6 (buffer, x, y, color); break;
            case '7': copy_7 (buffer, x, y, color); break;
            case '8': copy_8 (buffer, x, y, color); break;
            case '9': copy_9 (buffer, x, y, color); break;
            case '.': copy_dot (buffer, x, y, color); break;
            case ',': copy_comma (buffer, x, y, color); break;
            default: break;
        }
        
        offset += 7;  // Move to next character position
        i++;          // Move to next character in string
    }
}


void FLP_Draw_Upgrade (uint16_t* buffer, char* text, int x, int y, int height, int width, uint32_t color)
{
    FLP_Draw_Box (buffer, x, y, 4, height, width, color);
    FLP_Draw_String (buffer, text, x + 9, y + 9, color);
}









