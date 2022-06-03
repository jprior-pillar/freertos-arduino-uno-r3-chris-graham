/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdint.h>
#include <stdbool.h>

#include "Arduino.h"
#include "Arduino_FreeRTOS.h"
#include "arduino-uno-r3.h"

// Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/ )()) { return 0; }
// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));

void initVariant() { }
void setupUSB() __attribute__((weak));

void setupUSB() { }
int led = 13;

//void digitalWrite(int led, bool isHigh)
//{
//    //No idea
//    if (isHigh == 1) {
//        PORTC = 0xff;        // Turn ON all the Leds connected to PORTC
//        PORTB = 0xff;
////        PORTB |= (1U << led);
//    }
//    else {
//        PORTC = 0x00;        // Turn OFF all the Leds connected to PORTC
//        PORTB = 0x00;
////        PORTB &= ~(1U << led);
//    }
//}


void TaskAnalogRead(void *pvParameters)  // This is a task.
{
    (void) pvParameters;

    for (;;)
    {
        // read the input on analog pin 0:
        int sensorValue = analogRead(A0);
        // print out the value you read:
        Serial.println(sensorValue);
        vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
    }
}

void TaskBlink(void *pvParameters)  // This is a task.
{
    // initialize digital LED_BUILTIN on pin 13 as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    for (;;) // A Task shall never return or exit.
    {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    }
}

void setup() {

    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);

    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
    }

    // Now set up two tasks to run independently.
    xTaskCreate(
            TaskBlink
            ,  "Blink"   // A name just for humans
            ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
            ,  NULL
            ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
            ,  NULL );

    xTaskCreate(
            TaskAnalogRead
            ,  "AnalogRead"
            ,  128  // Stack size
            ,  NULL
            ,  1  // Priority
            ,  NULL );

    // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}


int main(void)
{
    init();

    initVariant();

#if defined(USBCON)
    USBDevice.attach();
#endif

    setup();

    for (;;) {
        loop();
        if (serialEventRun) serialEventRun();
    }

    return 0;
}

void loop() {}
