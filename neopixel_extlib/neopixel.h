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

/** Client structure for control.
 * Please initialize it using neopixel_initialize().
 */
typedef struct
{
  /* This is a control member,
   * so do not change the value directly.
   */

  uint32_t  pin;
  uint32_t  pixel_num;
  uint8_t  *pixels;
  uint32_t *reg_addr;
  uint32_t  reg_val;
} neopixel_client_t;

/** Color structure */
typedef struct
{
  uint8_t r;  /** Red (0-255)   */
  uint8_t g;  /** Green (0-255) */
  uint8_t b;  /** Blue (0-255)  */
} neopixel_color_t;

/***************************************************************************/
/* Public Function Prototypes                                              */
/***************************************************************************/

/**
 * Initialize neopixel client
 *
 * @param[in] pin GPIO pin no to use.
 * @param[in] pixel_num NeoPixel LED cell count.
 * @return neopixel_client_t* Pointer to client if success.
 *                            otherwise NULL.
 */
neopixel_client_t* neopixel_inizialize(uint32_t pin,
                                       uint32_t pixel_num);
/**
 * Free the neopixel client's resources
 *
 * @param[in] client Pointer to neopixel client.
 * @return void
 */
void neopixel_finalize(neopixel_client_t *client);

/**
 * Set the color for the specified pixel
 *
 * @param[in] client Pointer to neopixel client.
 * @param[in] n Pixel number.
 * @param[in] color Pointer to color structure.
 * @return int NEOPIXEL_RESULT_OK if success.
 *             otherwise NEOPIXEL_RESULT_NG.
 */
int neopixel_set(neopixel_client_t *client,
                 uint32_t n,
                 neopixel_color_t *color);

/**
 * Set the color for the all pixel
 *
 * @param[in] client Pointer to neopixel client.
 * @param[in] color Pointer to color structure.
 * @return int NEOPIXEL_RESULT_OK if success.
 *             otherwise NEOPIXEL_RESULT_NG.
 */
int neopixel_setall(neopixel_client_t *client,
                    neopixel_color_t *color);

/**
 * Clear the color set for the pixel
 *
 * @param[in] client Pointer to neopixel client.
 * @return int NEOPIXEL_RESULT_OK if success.
 *             otherwise NEOPIXEL_RESULT_NG.
 */
int neopixel_clear(neopixel_client_t *client);

/**
 * Reflect the set color to NeoPixel
 *
 * @param[in] client Pointer to neopixel client.
 * @return int NEOPIXEL_RESULT_OK if success.
 *             otherwise NEOPIXEL_RESULT_NG.
 */
int neopixel_show(neopixel_client_t *client);
