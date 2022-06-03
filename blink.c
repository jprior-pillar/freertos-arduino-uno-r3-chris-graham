#include <stdint.h>
#include <stdbool.h>
#include "arduino-uno-r3.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>             // provides PORT* and DDR* registers
#include <util/delay.h>         // provides _delay_ms(), and needs F_CPU

#include "./deps/src/Arduino_FreeRTOS.h"
int led = 13;

void digitalWrite(int led, bool isHigh)
{
    //No idea
    if (isHigh == 1) {
        PORTC = 0xff;        // Turn ON all the Leds connected to PORTC
        PORTB = 0xff;
//        PORTB |= (1U << led);
//        PORTB5 |= (1U << led);
    }
    else {
        PORTC = 0x00;        // Turn OFF all the Leds connected to PORTC
        PORTB = 0x00;
//        PORTB &= ~(1U << led);
//        PORTB5 &= ~(1U << led);
    }
}

void TaskBlink(void *pvParameters)  // This is a task.
{
    for (;;) // A Task shall never return or exit.
    {
        digitalWrite(led_output_port, 1);   // turn the LED on (HIGH is the voltage level)
        vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one second
        digitalWrite(led_output_port, 0);    // turn the LED off by making the voltage LOW
        vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one second
    }
}
void setup()
{
    led_output_direction |= led_output_direction_mask;
//    DDRC = 0xff;           // Configure PORTC as output
//    DDRB |= (1U << led); //I doubt this is right
    xTaskCreate(
            TaskBlink
            ,  "Blink"   // A name just for humans
            ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
            ,  NULL
            ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
            ,  NULL );
}

int main(void)
{
// Original code
//    led_output_direction |= led_output_direction_mask;
    setup();

//    for (;;) {
//        led_output_port |=  led_on_mask;
////        wait(100000U);
//        _delay_ms(1000);
//
//        led_output_port &= ~led_on_mask;
////        wait(100000U);
//        _delay_ms(1000);
//
//    }
//Mega2560 code
//    DDRC = 0xff;           // Configure PORTC as output
//    DDRB |= (1U << led); //I doubt this is right
//    for (;;) {
//        digitalWrite(led, true);
//        _delay_ms(1000);
//        digitalWrite(led, false);
//        _delay_ms(1000);
//    }
        return 0;
}



