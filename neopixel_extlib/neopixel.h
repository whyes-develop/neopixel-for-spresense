// SPDX-FileCopyrightText: 2023 whyes-develop
// SPDX-License-Identifier: MIT

/***************************************************************************/
/* Included Files                                                          */
/***************************************************************************/

#include <stdint.h>

/***************************************************************************/
/* Pre-processor Definitions                                               */
/***************************************************************************/

#define NEOPIXEL_RESULT_OK (0)
#define NEOPIXEL_RESULT_NG (-1)

/***************************************************************************/
/* Public Types                                                            */
/***************************************************************************/

/* client structure for control.
 * Please initialize it using neopixel_initialize(). */

typedef struct
{
  /* This is a control member,
   * so do not change the value directly. */

  uint32_t  pin;
  uint32_t  pixel_num;
  uint8_t  *pixels;
  uint32_t *reg_addr;
  uint32_t  reg_val;
} neopixel_client_t;

/* Color structure */

typedef struct
{
  uint8_t r;  /* Red (0-255)   */
  uint8_t g;  /* Green (0-255) */
  uint8_t b;  /* Blue (0-255)  */
} neopixel_color_t;

/***************************************************************************/
/* Public Function Prototypes                                              */
/***************************************************************************/

neopixel_client_t* neopixel_inizialize(uint32_t pin,
                                       uint32_t pixel_num);
void neopixel_finalize(neopixel_client_t *client);
int neopixel_set(neopixel_client_t *client,
                 uint32_t n,
                 neopixel_color_t *color);
int neopixel_setall(neopixel_client_t *client,
                    neopixel_color_t *color);
int neopixel_clear(neopixel_client_t *client);
int neopixel_show(neopixel_client_t *client);
