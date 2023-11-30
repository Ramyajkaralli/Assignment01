Articulus Surgical - Assignment 01

Basic Motor Position Control

**Problem Statement:** Consider an Arduino Mega. It is connected to a single DC motor (through a standard Motor driver - one pin for PWM to motor, one for direction) and an encoder (standard encoder with 2 PWM outputs shifted by 90 degrees). Write a script for the following.

The Arduino receives a number ranging from -255 to 255 through serial communication. Once the number is received, the Arduino has to move the motor by the number of count received. Example. If 40 is received, the motor moves in one direction by 40 counts of the encoder. If -123 is received, the motor is moved in the other direction by 123 counts of the encoder.
