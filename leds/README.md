[Back to components README](../README.md)

# LEDs :bulb:

The LEDs are luminous landmarks used as beacon for locating the robot
by triangularisation.

<img src="assets/led1.jpg" width="280"><img src="assets/led2.jpg" width="280"><img src="assets/led3.jpg" width="280">

## How it's made

A single luminous landmark is made from:
- 4 RGB LEDs.
- Plastic support taken from a commercial solar beacons kit.
- An interruptor.
- A metal square support.
- An Arduino pro mini.
- A battery support.

Here is how the different elements are linked:

![electrical diagram](assets/el-diagram.png)

## Code on the Arduino card

The arduino card is flashed with the code from `leds.ino`.
This code lights up the leds with a random color.
The colors available are:
- red
- green
- blue
- yellow
- purple
- orange
- white

Depending on the quality of the leds the RGB values for these colors have
to be adjusted.

## Tutorial in images to build your own beacon


