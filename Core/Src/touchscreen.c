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

bool third_impact = false;

uint32_t nums[6];
uint32_t inactivity_counter = 0;

// shoutout to a1k0n for the macro
#define R(mul,shift,x,y) \
  _=x; \
  x -= mul*y>>shift; \
  y += mul*_>>shift; \
  _ = 3145728-x*x-y*y>>11; \
  x = x*_>>10; \
  y = y*_>>10;



typedef struct
{
	char* name;
	float red;
	float green;
	float blue;
} Color_Filter;

Color_Filter rgb = {"RGB", 1, 1, 1};
Color_Filter eva_00 = {"REI", 1.7f, 0.1f, 4.0f};
Color_Filter eva_01 = {"SHINJI", 0.5f, 2.1f, 0.5f};
Color_Filter eva_02 = {"ASUKA", 2.1f, 0.1f, 0.1f};


typedef struct
{
	uint32_t donuts_count;        
    uint32_t donuts_per_tap;    
    uint32_t donuts_passive;

	int Spin_Rate;
	int multiplier;

	int r11, r12, r21, r22, framerate;

	Color_Filter* Colorway;

	bool RGB;
	bool ASCII;
	bool EVA;
	bool power_saving_mode;
	bool third_impact;
} Donut_Game;

Donut_Game Donut = {10000001, 1, 0, 0, 1, 8, 12, 8, 13, 16, &rgb, false, false, false, false, false};

typedef struct
{
	int x, y, width, height;
	uint32_t cost;
	char* label;
	bool purchased;

} Upgrade;
Upgrade upgrades[] = {
	{400, 0, SCREEN_WIDTH - 400, 30, 0, "STORE", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 100, "AUTO SPIN", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 1000, "RGB", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 2000, "ASCII", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 4000, "EVA-00", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 16000, "EVA-01", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 50000, "EVA-02", false},
	{400, 0, SCREEN_WIDTH - 400, 30, 10000000, "THIRD IMPACT", false}
};

int32_t calculate_dps ()
{
	int32_t dps = 6 * Donut.donuts_passive;
	for (int i = 0; i < 6; i++) dps += nums[i];

	return dps;
}


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

uint32_t color_filter_to_rgb565 (Color_Filter* filter)
{
	uint8_t intensity = 128;

    uint8_t r = (uint8_t)(intensity * filter -> red);
    uint8_t g = (uint8_t)(intensity * filter -> green);
    uint8_t b = (uint8_t)(intensity * filter -> blue);

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

    uint16_t red_565 = (r >> 3) << 11;
    uint16_t green_565 = (g >> 2) << 5;
    uint16_t blue_565 = (b >> 3);

    return red_565 | green_565 | blue_565;
}



void initiate_third_impact ()
{
	memset (b_1, 0xFF, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof (uint16_t));
    draw_donut ();

    HAL_Delay (3000);
    FLP_Draw_String (b_1, "A: Well, I guess you got what you wanted", 5, 5, 0x0000);
    draw_donut ();
    HAL_Delay (3000);
    FLP_Draw_String (b_1, "B: It's not about what I wanted, it had to be done.", 5, 35, 0x0000);
    draw_donut ();
    HAL_Delay (3000);
    FLP_Draw_String (b_1, "A: So... This is the end of the story... Our work here is done", 5, 65, 0x0000);
    draw_donut ();
    HAL_Delay (3000);
    FLP_Draw_String (b_1, "B: Humanity has just reached Neon Genesis.", 5, 95, 0x0000);
    draw_donut ();
    HAL_Delay (3000);
    FLP_Draw_String (b_1, "B: Our work here has just begun. We have a whole world to rebuild. ", 5, 125, 0x0000);
	draw_donut ();
	HAL_Delay (3000);

    memset (b_1, 0xFF, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof (uint16_t));
    HAL_Delay (3000);

    FLP_Draw_String (b_1, "Thanks for playing this demo. I hope you enjoyed it.", 10, 10, 0x0000);
    FLP_Draw_String (b_1, "Filip Dobnikar, Vgrajeni sistemi, 2025", 10, 40, 0x0000);
    FLP_Draw_String (b_1, "Se opravicujem da nicem uporabil nobenega rtosa.", 10, 70, 0x0000);
    draw_donut ();

	for (;;);
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
	Donut.donuts_count -= upgrade -> cost;
	
	if (!strcmp (upgrade -> label, "AUTO SPIN"))
	{
		if (Donut.r11 > 2)
		{
			Donut.r11--;
			Donut.r21--;
		}
		if (Donut.r12 > 2)
		{
			Donut.r12--;
			Donut.r22--;
		}

		if (!upgrade -> purchased) Donut.Spin_Rate = 100;
		else Donut.Spin_Rate -= 10;
		Donut.donuts_passive += 1;
		strcpy (upgrade -> label, "FASTER");
		upgrade -> cost *= 2;
	}
	else if (!strcmp (upgrade -> label, "RGB"))
	{
		if (!upgrade -> purchased) Donut.donuts_passive *= 10;
		Donut.EVA = false;
		Donut.RGB = !Donut.RGB;
		Donut.Colorway = &rgb;
		upgrade -> cost = 0;
	}
	else if (!strcmp (upgrade -> label, "ASCII"))
	{
		if (!upgrade -> purchased) Donut.donuts_per_tap *= 10;
		Donut.ASCII = !Donut.ASCII;
		upgrade -> cost = 0;
	}
	else if (!strcmp (upgrade -> label, "EVA-00"))
	{
		if (!upgrade -> purchased) Donut.donuts_per_tap *= 10;
		Donut.RGB = false;
		Donut.EVA = true;
		Donut.Colorway = &eva_00;
		upgrade -> cost = 0;
	}
	else if (!strcmp (upgrade -> label, "EVA-01"))
	{
		if (!upgrade -> purchased) Donut.donuts_passive *= 20;
		Donut.RGB = false;
		Donut.EVA = true;
		Donut.Colorway = &eva_01;
		upgrade -> cost = 0;
	}
	else if (!strcmp (upgrade -> label, "EVA-02"))
	{
		if (!upgrade -> purchased) Donut.Spin_Rate *= 5;
		Donut.RGB = false;
		Donut.EVA = true;
		Donut.Colorway = &eva_02;
		upgrade -> cost = 0;
	}
	else
	{
		Donut.third_impact = true;
	}



	FLP_Draw_Rectangle (b_1, upgrade -> x + 4, upgrade -> y + 4, upgrade -> width - 4, upgrade -> height - 4, UTIL_LCD_COLOR_WHITE);
	FLP_Draw_String (b_1, upgrade -> label, upgrade -> x, upgrade -> y, UTIL_LCD_COLOR_BLACK);

}

void check_if_upgrade_clicked (int x, int y)
{
	for (int i = 1; i < sizeof (upgrades) / sizeof (Upgrade); i++)
	{
		if 
		(
			x >= upgrades[i].x && 
			x < upgrades[i].x + upgrades[i].width &&
			y >= upgrades[i].y && 
			y < upgrades[i].y + upgrades[i].height
		)
        {
			if (Donut.donuts_count >= upgrades[i].cost)
			{
				apply_upgrade (&upgrades[i]);
				upgrades[i].purchased = true;
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
	int stack_offset = 30;
	int n = sizeof (upgrades) / sizeof (Upgrade);
	int y_offset = 0;


	for (int i = 0; i < n; i++)
	{
		if (upgrades[i].cost < Donut.donuts_count && !(i == 1 && Donut.r11 == 2))
		{
			upgrades[i].y = y_offset;

			FLP_Draw_Upgrade (b_1, upgrades[i].label, upgrades[i].x, upgrades[i].y, upgrades[i].width, upgrades[i].height, (upgrades[i].purchased) ? color_filter_to_rgb565 (Donut.Colorway) : UTIL_LCD_COLOR_WHITE);

			y_offset += 30;
		}
	}

}


void draw_UI ()
{
	if (!strcmp (Donut.Colorway -> name, "ASUKA")) FLP_Draw_String (b_1, "BAKA", 0, 200, UTIL_LCD_COLOR_WHITE);

	FLP_Draw_String (b_1, "DONUT TOUCH ME", 10, 260, color_filter_to_rgb565 (Donut.Colorway));

	char counter[32];
	if (Donut.donuts_count < 1000)
	{
		sprintf(counter, "%lu LCL COLLECTED", Donut.donuts_count);
	}
	else if (Donut.donuts_count < 1000000)
	{
		sprintf (counter, "%lu.%luK LCL COLLECTED", Donut.donuts_count / 1000, (Donut.donuts_count % 1000) / 10);
	}
	else
	{
		sprintf (counter, "%lu.%luM LCL COLLECTED", Donut.donuts_count / 1000000, (Donut.donuts_count % 1000000) / 10000);
	}
	FLP_Draw_String (b_1, counter, 10, 10, color_filter_to_rgb565 (Donut.Colorway));
	draw_upgrades ();
	

    char dps[32];
    sprintf(dps, "%lu DPS", calculate_dps ());
    FLP_Draw_String(b_1, dps, 10, 40, 0x07E0);

    if (Donut.Colorway && Donut.Colorway -> name)
    {
        sprintf (counter, "MODE: %s", Donut.Colorway -> name);
        FLP_Draw_String (b_1, counter, 10, 70, color_filter_to_rgb565 (Donut.Colorway));
    }






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

void draw_frame_low_power ()
{
    static int pulse = 0;
    pulse = (pulse + 1) % 60;


    reset_frame();


    uint16_t brightness = 128 + (sin(pulse * 0.1) * 127);
    uint16_t color = (brightness >> 3) << 11 | (brightness >> 2) << 5 | (brightness >> 3);

    FLP_Draw_String(b_1, "TOUCH TO WAKE", 150, 120, color);
    FLP_Draw_String(b_1, "POWER SAVE MODE", 145, 140, color);


	char counter[32];
	if (Donut.donuts_count < 1000)
	{
		sprintf(counter, "%lu LCL COLLECTED", Donut.donuts_count);
	}
	else if (Donut.donuts_count < 1000000)
	{
		sprintf (counter, "%lu.%luK LCL COLLECTED", Donut.donuts_count / 1000, (Donut.donuts_count % 1000) / 10);
	}
	else
	{
		sprintf (counter, "%lu.%luM LCL COLLECTED", Donut.donuts_count / 1000000, (Donut.donuts_count % 1000000) / 10000);
	}
    FLP_Draw_String(b_1, counter, 130, 160, color);
    SCB_CleanInvalidateDCache ();
    draw_donut ();
}




void check_for_inactivity ()
{
	if (inactivity_counter > 1000 && !Donut.power_saving_mode) Donut.power_saving_mode = true;
	if (!inactivity_counter && Donut.power_saving_mode) Donut.power_saving_mode = false;
}


void DonutRotatus ()
{
	TS_Init_t ts_init;
    ts_init.Width = SCREEN_WIDTH;
    ts_init.Height = SCREEN_HEIGHT;
    ts_init.Orientation = LCD_ORIENTATION_LANDSCAPE;
    ts_init.Accuracy = 5;

    if (BSP_TS_Init(0, &ts_init) != BSP_ERROR_NONE) Error_Handler();

    TS_State_t TS_State;
    uint8_t prev_touch_detected = 0;

    int counter = 0;

    memset (nums, 0, 6 * sizeof (int));

    for (;;)
    {
    	BSP_TS_GetState(0, &TS_State);

    	reset_frame ();

		if (Donut.RGB) change_RGB ();
		update_angle ();

		memset (z, 127, 1760);

		if (!Donut.power_saving_mode && !Donut.third_impact) get_donut_cords ();

		counter %= 6;

		if (TS_State.TouchDetected && !prev_touch_detected)
		{
			if (inactivity_counter > 0) inactivity_counter = 0;

			int x_corrected = TS_State.TouchY, y_corrected = TS_State.TouchX;
			if (x_corrected > 100 && x_corrected < 380 && y_corrected > 50 && y_corrected < 220)
			{
				Donut.donuts_count += Donut.donuts_per_tap;

				if (!Donut.Spin_Rate)
				{
                    R(Donut.r11, Donut.r12, c_A, s_A);
                    R(Donut.r21, Donut.r22, c_B, s_B);
				}
				nums[counter++] = Donut.donuts_per_tap++;
			}
			else
			{
				check_if_upgrade_clicked (x_corrected, y_corrected);
				nums[counter++] = 0;
			}


		    char debug[50];
		    sprintf(debug, "X:%d Y:%d", x_corrected, y_corrected);
		    FLP_Draw_String(b_1, debug, 0, 100, 0xFFFF);


		    FLP_Draw_Rectangle(b_1, x_corrected-2, y_corrected-2, 4, 4, 0xF800);
		}
		else
		{
			nums[counter++] = 0;
			inactivity_counter++;
		}

		prev_touch_detected = TS_State.TouchDetected;


        while (blockRendering);
        blockRendering = 1;

        check_for_inactivity ();

        if (Donut.power_saving_mode)
        {
        	HAL_Delay (100);
        	draw_frame_low_power ();
        }
        else if (Donut.third_impact)
        {
        	initiate_third_impact ();
        }
        else
        {
			HAL_Delay (16);
			draw_frame ();
        }

		if (Donut.Spin_Rate > 0)
		{
	        R(Donut.r11, Donut.r12, c_A, s_A);
	        R(Donut.r21, Donut.r22, c_B, s_B);
		}

		Donut.donuts_count += Donut.donuts_passive;



    }
}
