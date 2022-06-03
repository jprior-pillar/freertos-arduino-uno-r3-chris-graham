Define registers without using <avr/io.h>
=========================================

atmega328.h shows the nitty-gritty details
of how hardware registers are defined
for the ATmega328 microcontroller.

This might be as good as it gets
if I do not have a standard header file
that defines the registers for a chip.

(compared with 06-using-avr-gcc-without-own-headers-without-avr-headers)

Good:
-   Improved modularity and file structure.
-   Code is easier to understand because more meaningful names are used.
-   Shows the nitty-gritty details of how hardware registers are defined.
-   Done on command line.
-   Does not rely on Arduino development environment.

Bad:
-   Is less portable and maintainable by not using <avr/io.h>.
-   wait() is uncalibrated.
-   Does not use TDD.
