// SPDX-FileCopyrightText: 2023 whyes-develop
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <nuttx/config.h>
#include <arch/board/board.h>

#include "neopixel.h"

/***************************************************************************/
/* Included Files                                                          */
/***************************************************************************/

/***************************************************************************/
/* Pre-processor Definitions                                               */
/***************************************************************************/

#define LOW  (0)
#define HIGH (1)

#define n_wait_cycles_t0h_t1l (2)
#define n_wait_cycles_t1h_t0l (28)
#define n_wait_cycles_reset   (1)

/* Refer to
 * spresense-nuttx/arch/arm/src/cxd56xx/hardware/cxd5602_memorymap.h */
#define CXD56_SYS_MIRROR         0x04000000
#define CXD56_TOPREG_BASE        (CXD56_SYS_MIRROR + 0x00100000)

/* Refer to
 * spresense-nuttx/arch/arm/src/cxd56xx/hardware/cxd5602_topreg.h */
#define CXD56_TOPREG_GP_I2C4_BCK (CXD56_TOPREG_BASE + 0x2000)

/***************************************************************************/
/* Private Functions                                                       */
/***************************************************************************/

uint32_t get_gpio_regaddr(uint32_t pin)
{
  uint32_t base;
  base = (pin < PIN_IS_CLK) ? 1 : 7;
  return CXD56_TOPREG_GP_I2C4_BCK + ((pin - base) * 4);
}

void bit_write(neopixel_client_t *client, uint8_t value)
{
#define GPIO_OUTPUT_SHIFT (8)
  if (value == HIGH)
    {
      client->reg_val |= (1UL << GPIO_OUTPUT_SHIFT);
    }
  else
    {
      client->reg_val &= ~(1UL << GPIO_OUTPUT_SHIFT);
    }
  *(volatile uint32_t*)client->reg_addr = client->reg_val;
}

void wait_cycles(uint32_t n) // 4 clocks per cycle
{
  asm volatile
  (
      "0:" "SUBS %[count], 1;"
      "BNE 0b;"
      : [count] "+r" (n)
  );
}

void zero(neopixel_client_t *client)
{
  bit_write(client, HIGH);
  wait_cycles(n_wait_cycles_t0h_t1l);
  bit_write(client, LOW);
  wait_cycles(n_wait_cycles_t1h_t0l);
}

void one(neopixel_client_t *client)
{
  bit_write(client, HIGH);
  wait_cycles(n_wait_cycles_t1h_t0l);
  bit_write(client, LOW);
  wait_cycles(n_wait_cycles_t0h_t1l);
}

/***************************************************************************/
/* Public Functions                                                        */
/***************************************************************************/

neopixel_client_t* neopixel_inizialize(uint32_t pin,
                                       uint32_t pixel_num)
{
#define SETUP_PIN_OUTPUT(pin) do{ \
  board_gpio_write(pin, -1); \
  board_gpio_config(pin, 0, false, true, PIN_FLOAT); \
}while(0)

  neopixel_client_t *client = NULL;
  client = (neopixel_client_t *)calloc(1, sizeof(neopixel_client_t));
  if (!client)
    {
      return NULL;
    }

  client->pin       = pin;
  client->pixel_num = pixel_num;
  client->pixels    = (uint8_t *)calloc(pixel_num * 3, sizeof(uint8_t));

  SETUP_PIN_OUTPUT(pin);
  board_gpio_write(pin, LOW);
  client->reg_addr = (uint32_t *)get_gpio_regaddr(pin);
  client->reg_val = *((volatile uint32_t *)client->reg_addr);
  return client;
}

void neopixel_finalize(neopixel_client_t *client)
{
  if (!client)
    {
      return;
    }

  /* turn off the LED */
  neopixel_clear(client);
  neopixel_show(client);

  free(client->pixels);
  memset(client, 0, sizeof(neopixel_client_t));
  free(client);
}

int neopixel_set(neopixel_client_t *client,
                 uint32_t n,
                 neopixel_color_t *color)
{
#define R (1)
#define G (0)
#define B (2)

  if (!client || !color)
    {
      return NEOPIXEL_RESULT_NG;
    }
  if (n >= client->pixel_num)
    {
      return NEOPIXEL_RESULT_NG;
    }
  client->pixels[n * 3 + R] = color->r;
  client->pixels[n * 3 + G] = color->g;
  client->pixels[n * 3 + B] = color->b;
  return NEOPIXEL_RESULT_OK;
}

int neopixel_setall(neopixel_client_t *client, neopixel_color_t *color)
{
  int i;
  int result = NEOPIXEL_RESULT_OK;

  if (!client || !color)
    {
      return NEOPIXEL_RESULT_NG;
    }

  for (i = 0; i < client->pixel_num; i++)
    {
      result = neopixel_set(client, i, color);
      if (NEOPIXEL_RESULT_NG == result)
        {
          break;
        }
    }
  return result;
}

int neopixel_clear(neopixel_client_t *client)
{
  if (!client)
    {
      return NEOPIXEL_RESULT_NG;
    }
  memset(client->pixels, 0,
    sizeof(client->pixels[0]) * (client->pixel_num * 3));
  return NEOPIXEL_RESULT_OK;
}

int neopixel_show(neopixel_client_t *client)
{
  if (!client)
    {
      return NEOPIXEL_RESULT_NG;
    }
  board_gpio_int(client->pin, false);
  for (uint8_t pixel = 0; pixel < client->pixel_num; pixel++)
    {
      bit_write(client, LOW);
      wait_cycles(n_wait_cycles_reset);
      for (uint8_t rgb = 0; rgb < 3; rgb++)
        {
          uint8_t i = pixel * 3 + rgb;
          (client->pixels[i] & 0x80) ? one(client) : zero(client);
          (client->pixels[i] & 0x40) ? one(client) : zero(client);
          (client->pixels[i] & 0x20) ? one(client) : zero(client);
          (client->pixels[i] & 0x10) ? one(client) : zero(client);
          (client->pixels[i] & 0x08) ? one(client) : zero(client);
          (client->pixels[i] & 0x04) ? one(client) : zero(client);
          (client->pixels[i] & 0x02) ? one(client) : zero(client);
          (client->pixels[i] & 0x01) ? one(client) : zero(client);
      }
    }
  board_gpio_int(client->pin, true);
  return NEOPIXEL_RESULT_OK;
}
