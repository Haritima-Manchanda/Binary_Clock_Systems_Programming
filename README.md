# BINARY-CLOCK
## DESCRIPTION

This project is for system's programming in C language.

A binary clock is a clock which displays the time in 24 hour notation in binary. Since the screen on the Raspberry pi is 8 pixels wide, we can easily display an 8 bit number across one row of the display. The program displays the current time (updating once a second) on the display in binary by turning on and off the led's in a row to represent the 8 bit binary number for that component of the time. 

In other words for 14:26:34 (14 hours, 26 minutes, 34 seconds) The display would look like this:

1. row1: 0 0 0 0 0 0 0 0
2. row2: 0 0 0 0 1 1 1 0 (14 in binary.  Should display hours in blue.  Each 1 would be a blue led turned on, each 0 would be an led turned off)
3. row3: 0 0 0 0 0 0 0 0
4. row4: 0 0 0 1 1 0 1 0 (26 in binary display in green)
5. row5: 0 0 0 0 0 0 0 0
6. row6: 0 0 1 0 0 0 1 0 (34 in binary display in red)

Main.c initializes the frame buffer, then periodically gets the current time, and then displays it as described above on the led matrix.  The program exits when the user types ctrl-c on the keyboard.
