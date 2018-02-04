# turntable-model-railroad-serial
Simple code for Stepper 28BYJ-48 + ULN2003 to operate a Model Railroad turntable



Turntable V1 20180204 MCR
based on the idea from Ray on rmweb.co.uk forum
http://www.rmweb.co.uk/community/index.php?/topic/78578-dcc-controlled-peco-turntable-project-using-a-arduino-uno/

The idea was having a sensor determine and calibrate de stepper motor on startup of the system.
From there all the positions are relative to position (0) the sensor.

Works fine but, for the moment, only interact with Arduino serial monitor commands
0 - Go to home position
1, 2, 3 & 4 - Go to position 1, 2, 3 & 4
9 - Calibrate the turntable again

This is a work in progress. The goal is to make a DDC Accessory Decoder

Works with the very cheap Stepper Motor DC 5V 28BYJ-48 + ULN2003 Stepper Motor Driver Module
The sensor is an Hall Effect Magnetic sensor, also very cheap

