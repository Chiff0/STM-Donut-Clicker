#ifndef FLP_LIB_CHARS_H_
#define FLP_LIB_CHARS_H_

#include <stdint.h>

extern int offset;

// Helper function for pixel filling
void fill_pixel(uint16_t* buffer, int x_base, int y_base, int x, int y, uint32_t color);

// Symbol drawing functions
void copy_dot(uint16_t* buffer, int x, int y, uint32_t color);
void copy_comma(uint16_t* buffer, int x, int y, uint32_t color);
void copy_dash(uint16_t* buffer, int x, int y, uint32_t color);
void copy_plus(uint16_t* buffer, int x, int y, uint32_t color);
void copy_hashtag(uint16_t* buffer, int x, int y, uint32_t color);
void copy_at(uint16_t* buffer, int x, int y, uint32_t color);
void copy_dollar(uint16_t* buffer, int x, int y, uint32_t color);
void copy_equals(uint16_t* buffer, int x, int y, uint32_t color);
void copy_slash(uint16_t* buffer, int x, int y, uint32_t color);
void copy_star(uint16_t* buffer, int x, int y, uint32_t color);
void copy_tilde(uint16_t* buffer, int x, int y, uint32_t color);
void copy_semicolon(uint16_t* buffer, int x, int y, uint32_t color);
void copy_colon(uint16_t* buffer, int x, int y, uint32_t color);

// Letter drawing functions (uppercase A-Z)
void copy_A(uint16_t* buffer, int x, int y, uint32_t color);
void copy_B(uint16_t* buffer, int x, int y, uint32_t color);
void copy_C(uint16_t* buffer, int x, int y, uint32_t color);
void copy_D(uint16_t* buffer, int x, int y, uint32_t color);
void copy_E(uint16_t* buffer, int x, int y, uint32_t color);
void copy_F(uint16_t* buffer, int x, int y, uint32_t color);
void copy_G(uint16_t* buffer, int x, int y, uint32_t color);
void copy_H(uint16_t* buffer, int x, int y, uint32_t color);
void copy_I(uint16_t* buffer, int x, int y, uint32_t color);
void copy_J(uint16_t* buffer, int x, int y, uint32_t color);
void copy_K(uint16_t* buffer, int x, int y, uint32_t color);
void copy_L(uint16_t* buffer, int x, int y, uint32_t color);
void copy_M(uint16_t* buffer, int x, int y, uint32_t color);
void copy_N(uint16_t* buffer, int x, int y, uint32_t color);
void copy_O(uint16_t* buffer, int x, int y, uint32_t color);
void copy_P(uint16_t* buffer, int x, int y, uint32_t color);
void copy_Q(uint16_t* buffer, int x, int y, uint32_t color);
void copy_R(uint16_t* buffer, int x, int y, uint32_t color);
void copy_S(uint16_t* buffer, int x, int y, uint32_t color);
void copy_T(uint16_t* buffer, int x, int y, uint32_t color);
void copy_U(uint16_t* buffer, int x, int y, uint32_t color);
void copy_V(uint16_t* buffer, int x, int y, uint32_t color);
void copy_W(uint16_t* buffer, int x, int y, uint32_t color);
void copy_X(uint16_t* buffer, int x, int y, uint32_t color);
void copy_Y(uint16_t* buffer, int x, int y, uint32_t color);
void copy_Z(uint16_t* buffer, int x, int y, uint32_t color);
void copy_space(uint16_t* buffer, int x, int y, uint32_t color);

// Number drawing functions (0-9)
void copy_0(uint16_t* buffer, int x, int y, uint32_t color);
void copy_1(uint16_t* buffer, int x, int y, uint32_t color);
void copy_2(uint16_t* buffer, int x, int y, uint32_t color);
void copy_3(uint16_t* buffer, int x, int y, uint32_t color);
void copy_4(uint16_t* buffer, int x, int y, uint32_t color);
void copy_5(uint16_t* buffer, int x, int y, uint32_t color);
void copy_6(uint16_t* buffer, int x, int y, uint32_t color);
void copy_7(uint16_t* buffer, int x, int y, uint32_t color);
void copy_8(uint16_t* buffer, int x, int y, uint32_t color);
void copy_9(uint16_t* buffer, int x, int y, uint32_t color);

// External offset variable for string drawing
extern int offset;

#endif /* FLP_LIB_CHARS_H_ */
