
#include "main.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "stm32h750xx.h"
#include "pn532/pn532.h"
#include "pn532/pn532_stm.h"


#define PI 3.14159265359
#define H 100
#define W 200
#define SCREEN_HEIGHT 272
#define SCREEN_WIDTH 480
#define THETA_INCREMENT 0.02
#define OMEGA_INCREMENT 0.006



extern I2C_HandleTypeDef hi2c4;
extern DMA2D_HandleTypeDef hdma2d;
extern volatile uint32_t blockRendering;

static uint16_t back_buffer[SCREEN_HEIGHT * SCREEN_WIDTH];

typedef struct
{
    double x;
    double y;
    double z;
} Donut_cords;

typedef struct
{
    int x_p;
    int y_p;

} Donut_cords_projected;


uint16_t convert_8bit_to_RGB565 (uint8_t r, uint8_t g, uint8_t b)
{
	uint16_t red_565   = (r >> 3) << 11;
	uint16_t green_565 = (g >> 2) << 5;
	uint16_t blue_565  = (b >> 3);

	return red_565 | green_565 | blue_565;
}



Donut_cords_projected project_cords (
    double x, double y, double z,
    double K1, double K2
    )
{
    Donut_cords_projected temp;

    double ooz = 1 / (z + K2);

    temp.x_p = (int) (W / 2 + K1 * ooz * x);
    temp.y_p = (int)(H / 2 - K1 * ooz * y);

    return temp;
}




Donut_cords calculate_pixel (
    double r1, double r2,
    double theta, double omega,
    double A, double B
    )
{
    Donut_cords temp;

    double sin_A = sin (A);
    double sin_B = sin (B);
    double sin_theta = sin (theta);
    double sin_omega = sin (omega);
    double cos_A = cos (A);
    double cos_B = cos (B);
    double cos_theta = cos (theta);
    double cos_omega = cos (omega);

    temp.x = (r2 + r1 * cos_theta) * (cos_B * cos_omega + sin_A * sin_B * sin_omega) - r1 * cos_A * sin_B * sin_theta;
    temp.y = (r2 + r1 * cos_theta) * (cos_theta * sin_B - cos_B * sin_A * sin_omega) + r1 * cos_A * cos_B * sin_theta;
    temp.z = cos_A * (r2 + r1 * cos_theta) * sin_omega + r1 * sin_A * sin_theta;

    return temp;
}

double luminance (
    double theta, double omega,
    double A, double B
    )
{
    double sin_A = sin (A);
    double sin_B = sin (B);
    double sin_theta = sin (theta);
    double sin_omega = sin (omega);
    double cos_A = cos (A);
    double cos_B = cos (B);
    double cos_theta = cos (theta);
    double cos_omega = cos (omega);

    return cos_omega * cos_theta * sin_B - cos_A * cos_theta * sin_omega - sin_A * sin_theta + cos_B * (cos_A * sin_theta - cos_theta * sin_A * sin_omega);
}



extern DMA2D_HandleTypeDef hdma2d;

void DonutOld ()
{
	UTIL_LCD_Clear (UTIL_LCD_COLOR_WHITE);

	double r1 = 2, r2 = 4;
	double A = 0, B = 0;
	double K2 = 15, K1 = W;


	double z_buffer[H * W];

    Donut_cords curr;
    Donut_cords_projected curr_p;
    double curr_L;
	HAL_DMA2D_ConfigLayer (&hdma2d, 1);



    for (;;)
    {

    	hdma2d.Init.Mode = DMA2D_R2M;
    	if(HAL_DMA2D_Init (&hdma2d) != HAL_OK) { Error_Handler(); }
    	HAL_DMA2D_Start(&hdma2d, 0x0000, (uint32_t)back_buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
    	HAL_DMA2D_PollForTransfer(&hdma2d, 10);

    	memset (z_buffer, 0, sizeof (double) * H * W);

    	for (double theta = 0; theta < PI * 2; theta += THETA_INCREMENT)
    	{
    		for (double omega = 0; omega < PI * 2; omega += OMEGA_INCREMENT)
    		{
    			curr = calculate_pixel (r1, r2, theta, omega, A, B);
    			curr_L = luminance (theta, omega, A, B);
    			curr_p = project_cords (curr.x, curr.y, curr.z , K1, K2);

    			double ooz = 1 / (curr.z + K2);

    			int idx = curr_p.x_p + curr_p.y_p * W;

    			if (idx >= 0 && idx < W * H && ooz > z_buffer[idx])
    			{
    				z_buffer[idx] = ooz;

    				if (curr_L > 0)
    				{
                        int luminance_idx = curr_L * 8;

                        if (luminance_idx < 0) luminance_idx = 0;
                        if (luminance_idx > 11) luminance_idx = 11;

                        uint8_t intensity = luminance_idx * 21;

    					uint16_t pixel_color = convert_8bit_to_RGB565 (intensity, intensity, intensity);

                        int screen_x = curr_p.x_p + (SCREEN_WIDTH / 2 - W / 2);
                        int screen_y = curr_p.y_p + (SCREEN_HEIGHT / 2 - H / 2);


						uint32_t pixel_index = screen_x + screen_y * SCREEN_WIDTH;
						back_buffer[pixel_index] = pixel_color;


    				}
    			}

    		}
    	}


		SCB_CleanInvalidateDCache();

		hdma2d.Init.Mode = DMA2D_M2M;
		if(HAL_DMA2D_Init(&hdma2d) != HAL_OK) { Error_Handler(); }
		HAL_DMA2D_Start(&hdma2d, (uint32_t)back_buffer, 0xD0000000, SCREEN_WIDTH, SCREEN_HEIGHT);
		HAL_DMA2D_PollForTransfer(&hdma2d, 100);


        A += 0.04;
        B += 0.02;


        //HAL_Delay (1);
    }

}












































