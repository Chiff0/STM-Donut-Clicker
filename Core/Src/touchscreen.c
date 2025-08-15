#include "main.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stm32h7xx_hal_dma2d.h" 
#include "stm32h750b_discovery_lcd.h"
#include "FLP_lib.h"

#define PI 3.14159265359
#define H 22
#define W 80
#define SCREEN_HEIGHT 272
#define SCREEN_WIDTH 480
#define THETA_INCREMENT 0.02
#define OMEGA_INCREMENT 0.006



extern DMA2D_HandleTypeDef hdma2d;
extern volatile uint32_t blockRendering;

static uint16_t b_1[SCREEN_WIDTH * SCREEN_HEIGHT];
static int8_t z[W * H];
static int s_A = 1024, c_A = 0, s_B = 1024, c_B = 0, _;
static int K2 = 5120 * 1024;

double RGB_angle = 0.0;


// shoutout a1k0n for the macro
#define R(mul,shift,x,y) \
  _=x; \
  x -= mul*y>>shift; \
  y += mul*_>>shift; \
  _ = 3145728-x*x-y*y>>11; \
  x = x*_>>10; \
  y = y*_>>10;



typedef struct
{
	float red;
	float green;
	float blue;
} Color_Filter;

Color_Filter rgb = {1, 1, 1};

typedef struct
{
	uint32_t donuts_count;        
    uint32_t donuts_per_tap;    
    uint32_t donuts_passive;

	int Spin_Rate;
	int multiplier;

	Color_Filter* Colorway;

	bool RGB;
	bool ASCII;
} Donut_Game;

Donut_Game Donut = {42690, 1, 0, 0, 1, &rgb, false, false};

typedef struct
{
	int x, y, width, height;
	uint32_t cost;
	char* label;
	bool purchased;

} Upgrade;
Upgrade upgrades[] = {
	{400, 0, SCREEN_WIDTH - 400, 30, 100, "AUTO SPIN", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 200, "FASTER", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 1000, "RGB", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 2000, "ASCII", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 300, "EVA-00", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 4000, "EVA-01", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 5000, "EVA-02", false}
};


int32_t pick_color
	(
			uint8_t r, uint8_t g, uint8_t b,
			Color_Filter filter
	)
{
	r *= filter.red;
	g *= filter.green;
	b *= filter.blue;

	uint16_t red_565   = (r >> 3) << 11;
	uint16_t green_565 = (g >> 2) << 5;
	uint16_t blue_565  = (b >> 3);

	return red_565 | green_565 | blue_565;
}



void set_pixel
	(
			int R1, int R2,
			int s_i, int s_j,
			int c_i, int c_j,
			int s_A, int s_B,
			int c_A, int c_B,
			int K2,
			int8_t* z
	)
{

	int x0 = R1 * c_j + R2,
	x1 = c_i * x0 >> 10,
	x2 = c_A * s_j >> 10,
	x3 = s_i * x0 >> 10,
    x4 = R1 * x2 - (s_A * x3 >> 10),
    x5 = s_A * s_j >> 10,
    x6 = K2 + R1 * 1024 * x5 + c_A * x3,
    x7 = c_j * s_i >> 10,
    x = 40 + 30 * (c_B * x1 - s_B * x4) / x6,
    y = 12 + 15 * (c_B * x4 + s_B * x1) / x6,
    N = (-c_A * x7 - c_B * ((-s_A * x7 >> 10) + x2) - c_i * (c_j * s_B >> 10) >> 10) - x5 >> 7;


	int8_t zz = (x6 - K2) >> 15;
	int pixel_position = x + y * 80;

	if (y < 22 && y >= 0 && x >= 0 && x < 80 && zz < z[pixel_position])
	{
		uint8_t intensity = N * 21;
		uint32_t pixel_color = pick_color (intensity, intensity, intensity, *Donut.Colorway);
        const int char_block_width = 6;
        const int char_block_height = 12;
        int screen_x_start = x * char_block_width;
        int screen_y_start = y * char_block_height;

		z[pixel_position] = zz;



		if (Donut.ASCII) FLP_Draw_Symbol (b_1, screen_x_start, screen_y_start, pixel_color, intensity);
		else
		{
			for (int c_y = 0; c_y < char_block_height; c_y++)
			{
				for (int c_x = 0; c_x < char_block_width; c_x++)
				{
					b_1[(screen_x_start + c_x) + (screen_y_start + c_y) * SCREEN_WIDTH] = pixel_color;
				}
			}

		}

	}
}

void apply_upgrade (Upgrade* upgrade)
{
	Donut.donuts_count -= upgrade.cost;
	
	if (!strcmp (upgrade.label, "AUTO SPIN"))
	{
		Donut.Spin_Rate = 100;
		Donut.donuts_passive += 1;
	}
	else if (!strcmp (upgrade.label, "FASTER"))
	{
		Donut.Spin_Rate -= 10;
		Donut.donuts_passive += 1;
	}
	else if (!strcmp (upgrade.label, "RGB"))
	{
		Donut.RGB = true;
	}
	else if (!strcmp (upgrade.label, "ASCII"))
	{
		Donut.ASCII = true;
	}
	else if (!strcmp (upgrade.label, "EVA 00"))
	{
		//TODO: apply rei color theme
	}
	else if (!strcmp (upgrade.label, "EVA 01"))
	{
		//TODO: apply shinji color theme
	}
	else if (!strcmp (upgrade.label, "EVA 02"))
	{
		//TODO: apply asuka color theme
	}

}

void check_if_upgrade_clicked (int x, int y)
{
	for (int i = 0; i < sizeof(upgrades)/sizeof(Upgrade); i++)
	{
		if 
		(
			!upgrades[i].purchased && 
			touch_x >= upgrades[i].x && 
			touch_x < upgrades[i].x + upgrades[i].width &&
			touch_y >= upgrades[i].y && 
			touch_y < upgrades[i].y + upgrades[i].height
		)
        {
			if (Donut.donuts_count >= upgrades[i].cost)
			{
				upgrades[i].purchased = true;
				apply_upgrade (upgrades[i]);
			}
		}
	}
}


void change_RGB ()
{
	rgb.red = (sin (RGB_angle) * 0.5) + 0.5;
	rgb.green = (sin (RGB_angle + 2.0944) * 0.5) + 0.5;
	rgb.blue = (sin (RGB_angle + 4.18888) * 0.5) + 0.5;
}


void update_angle ()
{
	RGB_angle += 0.05;

	if (RGB_angle > 2 * PI) RGB_angle -= 2 * PI;
}

void draw_donut ()
{
	hdma2d.Init.Mode = DMA2D_M2M;
	if (HAL_DMA2D_Init(&hdma2d) != HAL_OK) Error_Handler ();
	SCB_CleanInvalidateDCache ();
	HAL_DMA2D_Start (&hdma2d, (uint32_t) b_1, 0xD0000000, SCREEN_WIDTH, SCREEN_HEIGHT);
	HAL_DMA2D_PollForTransfer (&hdma2d, 100);
}

void draw_upgrades ()
{
	int stack_offset = 0;
	int n = sizeof (upgrades) / sizeof (Upgrade);
	int y_offset;

	for (int i = 0; i < n; i++)
	{
		if (upgrades[i].cost < Donut.donuts_count && !upgrades[i].purchased) 
		{
			FLP_Draw_Upgrade (b_1, upgrades[i].label, upgrades[i].x, upgrades[i].y + y_offset, upgrades[i].width, upgrades[i].height, UTIL_LCD_COLOR_WHITE);
			y_offset += 30;
		}
		else if (upgrades[i].cost > Donut.donuts_count) break; // cuz they ascending in price
	}

}


void draw_UI ()
{
	FLP_Draw_Box (b_1, 20, 200, 4, 50, 50, UTIL_LCD_COLOR_WHITE);

	FLP_Draw_String (b_1, "DONUT TOUCH ME", 5, 5, UTIL_LCD_COLOR_WHITE);

    char counter[32];
    sprintf(counter, "%lu DONUTS TOUCHED", Donut.donuts_count);
	FLP_Draw_String (b_1, counter, 5, 50, UTIL_LCD_COLOR_WHITE);
	draw_upgrades ();
}

void draw_frame ()
{
	draw_UI ();
	draw_donut ();
}

void reset_frame ()
{
	hdma2d.Init.Mode = DMA2D_R2M;
	if(HAL_DMA2D_Init (&hdma2d) != HAL_OK) Error_Handler();
	HAL_DMA2D_Start (&hdma2d, 0x0000, (uint32_t) b_1, SCREEN_WIDTH, SCREEN_HEIGHT);
	HAL_DMA2D_PollForTransfer (&hdma2d, 10);
}

void get_donut_cords ()
{
	int s_i = 0, c_i = 1024;

	for (int i = 0; i < 90; i++)
	{
		int s_j = 0, c_j = 1024;

		for (int j = 0; j < 324; j++)
		{
			set_pixel (1, 2048, s_j, s_i, c_j, c_i, s_A, s_B, c_A, c_B, K2, z);

			R(5, 8, c_j, s_j);
		}
		R(9, 7, c_i, s_i);
	}
}


void AppMain()
{
	TS_Init_t ts_init;
    ts_init.Width = SCREEN_WIDTH;
    ts_init.Height = SCREEN_HEIGHT;
    ts_init.Orientation = LCD_ORIENTATION_LANDSCAPE;
    ts_init.Accuracy = 5;

    if (BSP_TS_Init(0, &ts_init) != BSP_ERROR_NONE) Error_Handler();

    TS_State_t TS_State;
    uint8_t prev_touch_detected = 0;


    for (;;)
    {
    	BSP_TS_GetState(0, &TS_State);

    	reset_frame ();

		if (Donut.RGB) change_RGB ();
		update_angle ();

		memset (z, 127, 1760);

		get_donut_cords ();


		if (TS_State.TouchDetected && !prev_touch_detected)
		{
			if (TS_State.TouchX > 100 && TS_State.TouchX < 380 && TS_State.TouchY > 50 && TS_State.TouchY < 220)
			{
				Donut.donuts_count += Donut.donuts_per_tap;

				if (!Donut.Spin_Rate)
				{
                    R(5, 7, c_A, s_A);
                    R(5, 8, c_B, s_B);
				}
			}
		}

		prev_touch_detected = TS_State.TouchDetected;


        while (blockRendering);
        blockRendering = 1;

		HAL_Delay (Donut.Spin_Rate);

		if (Donut.Spin_Rate > 0)
		{
	        R(5, 7, c_A, s_A);
	        R(5, 8, c_B, s_B);
		}

		Donut.donuts_count += Donut.donuts_passive;
		draw_frame ();



    }
}
