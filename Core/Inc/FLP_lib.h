
#ifndef FLP_DISPLAY_H_
#define FLP_DISPLAY_H_

#include "main.h" 

extern int offset;


void FLP_Draw_Rectangle (uint16_t* buffer, int x, int y, int width, int height, uint32_t color);
void FLP_Draw_Box (uint16_t* buffer, int x, int y, int width, int height, int border_width, uint32_t color);
void FLP_Draw_Symbol (uint16_t* buffer, int x, int y, uint32_t color, int intensity);
void FLP_Draw_String (uint16_t* buffer, char* string, int x, int y, uint32_t color);
void FLP_Draw_Upgrade (uint16_t* buffer, char* text, int x, int y, int height, int width, uint32_t color);


#endif
