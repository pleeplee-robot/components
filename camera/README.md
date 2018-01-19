[Back to components README](../README.md)

# Camera :video_camera:

The camera complements the beacons (leds) in supporting the location.
The camera takes pictures of the leds and from these pictures the angle of the
leds on the picture is calculated.
We get the adequate angle for the localisation by additionning the found angle with the angle of the servomotor.

## Requirements

To install requirements simply run `pip install -r requirements.txt`, or run the `make init` command.

## Code

In short the code we use to recognize the beacons is in the `capture_beacons.py` file. The other scripts are legacy.

The `get_focal.py` is an attempt to get the distance to a beacon from a picture.
The `get_angle_from_image` computes the angle between a beacon and the centre of the image.
As we did not get good enough results with the previous methods, we decided to use an additionnal library `imutils` to handle multiple beacons in a single picture.

