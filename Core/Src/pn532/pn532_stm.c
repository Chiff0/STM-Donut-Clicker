/**************************************************************************
 *  @file     pn532_stm32f1.c
 *  @author   Yehui from Waveshare
 *  @license  BSD
 *
 *  This implements the peripheral interfaces.
 *
 *  Check out the links above for our tutorials and wiring diagrams
 *  These chips use SPI communicate.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **************************************************************************/

#include "stm32h750xx.h"
#include "../../Drivers/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal.h"
#include "../../Drivers/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal_i2c.h"
#include "../../Drivers/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal_gpio.h"
#include "main.h"
#include "pn532_stm.h"

// This indicates if the bits read/write should be reversed
#define _SPI_HARDWARE_LSB

#define _I2C_ADDRESS 0x48
#define _I2C_TIMEOUT 10

#define PN_RST_Pin GPIO_PIN_3
#define PN_RST_GPIO_Port GPIOA

extern I2C_HandleTypeDef hi2c4;

/**************************************************************************
 * Reset and Log implements
 **************************************************************************/
int PN532_Reset(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = PN_RST_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PN_RST_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(PN_RST_GPIO_Port, PN_RST_Pin, 1);
    HAL_Delay(100);
    HAL_GPIO_WritePin(PN_RST_GPIO_Port, PN_RST_Pin, 0);
    HAL_Delay(500);
    HAL_GPIO_WritePin(PN_RST_GPIO_Port, PN_RST_Pin, 1);
    HAL_Delay(100);
    return PN532_STATUS_OK;
}

void PN532_Log(const char *log)
{
    printf("%s\r\n", log);
}

void PN532_Init(PN532 *pn532)
{
    PN532_I2C_Init(pn532);
}
/**************************************************************************
 * End: Reset and Log implements
 **************************************************************************/
/**************************************************************************
 * I2C
 **************************************************************************/
void i2c_read(uint8_t *data, uint16_t count)
{
    HAL_I2C_Master_Receive(&hi2c4, _I2C_ADDRESS, data, count, _I2C_TIMEOUT);
}

void i2c_write(uint8_t *data, uint16_t count)
{
    HAL_I2C_Master_Transmit(&hi2c4, _I2C_ADDRESS, data, count, _I2C_TIMEOUT);
}

int PN532_I2C_ReadData(uint8_t *data, uint16_t count)
{
    uint8_t status[] = {0x00};
    uint8_t frame[count + 1];
    i2c_read(status, sizeof(status));
    if (status[0] != PN532_I2C_READY)
    {
        return PN532_STATUS_ERROR;
    }
    i2c_read(frame, count + 1);
    for (uint8_t i = 0; i < count; i++)
    {
        data[i] = frame[i + 1];
    }
    return PN532_STATUS_OK;
}

int PN532_I2C_WriteData(uint8_t *data, uint16_t count)
{
    i2c_write(data, count);
    return PN532_STATUS_OK;
}

bool PN532_I2C_WaitReady(uint32_t timeout)
{
    uint8_t status[] = {0x00};
    uint32_t tickstart = HAL_GetTick();
    while (HAL_GetTick() - tickstart < timeout)
    {
        i2c_read(status, sizeof(status));
        if (status[0] == PN532_I2C_READY)
        {
            return true;
        }
        else
        {
            HAL_Delay(5);
        }
    }
    return false;
}

int PN532_I2C_Wakeup(void)
{
    return PN532_STATUS_OK;
}

void PN532_I2C_Init(PN532 *pn532)
{
    // init the pn532 functions
    pn532->reset = PN532_Reset;
    pn532->read_data = PN532_I2C_ReadData;
    pn532->write_data = PN532_I2C_WriteData;
    pn532->wait_ready = PN532_I2C_WaitReady;
    pn532->wakeup = PN532_I2C_Wakeup;
    pn532->log = PN532_Log;

    // hardware wakeup
    pn532->wakeup();
}
/**************************************************************************
 * End: I2C
 **************************************************************************/
