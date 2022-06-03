/* register definitions for Arduino UNO r3 */

#include "atmega328.h"

#define led_bit_index (5)
#define led_output_direction (portb_output_direction)
#define led_output_direction_mask (1 << led_bit_index)
#define led_output_port (portb_output)
#define led_on_mask (1 << led_bit_index)
