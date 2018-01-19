[Back to components README](../README.md)

# Motors

The robot has 4 motors, each equipped with an odometry sensor which enables us to get the number of turns per wheels.
The Arduino card controls 4 motors and the servomotor.
The motor module can receive a speed between -255 and 255, with -255 meaning the fastest speed possible going backward and +255 the fastest speed possible to go forward.
The Servo is configured with a commang GPIO and can recieve an angle in radians.
The odometry module is also loaded. It should be plugged with the STM8 tx pin and will
exchange the informations coming from the STM8 to the raspberry pi.

![The Motors](../odometry/assets/below-robot.png)

## Build instructions

Download the sources and follow the instructions on the [official repository's wiki](https://github.com/arduino/arduino/wiki/building-arduino).
Complete the Arduino sources with the libraries and flash the `motors.ino` on the
main arduino responsible to control the motors.

