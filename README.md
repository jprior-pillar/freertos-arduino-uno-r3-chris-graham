
Test to get an example project using arduino and FreeRtos to compile and flash without the arduino ide


This project is primarily based on Jim Prior's arduino-cli on his gitlabs: https://gitlab.com/james-prior/arduino-cli
### Caveats
- The project is currently reliant on using an Arduino Uno R3
- The project is not yet clean (as of initial commit) and has plenty of ugly commented out/superfluous code
- Majority of the commands in the build_uno file is taken directly from Arduino's compilation commands you can see when it is running in verbose mode
### To Run

use ./build_uno