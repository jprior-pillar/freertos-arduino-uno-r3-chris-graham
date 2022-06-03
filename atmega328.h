/*
* register definitions for AVR ATmega328P microcontroller from
* http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf
*
* $ ll ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf
* -rw--w----@ 1 jep  staff  34343538 Nov  1  2018 ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf
* $ md5sum ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf
* 9936a914b2398ce4c9deb076627fda28 ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf
* $
*/

#define IO_BASE_ADDRESS (0x20)
#define SFR_8(io_address) ( \
    *(volatile uint8_t *)((io_address) + IO_BASE_ADDRESS))

/* use lower-case names for mutable and volatile things */

#define ddrb SFR_8(0x04)
#define portb SFR_8(0x05)
#define pinb SFR_8(0x03)

/* more meaningful names that are not standard */

#define portb_output_direction (ddrb)
#define portb_output (portb)
#define portb_input (pinb)
