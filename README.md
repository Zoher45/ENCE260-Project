# ENCE260-Project
This project is done as a part of a course (ENCE260) offered at the University of Canterbury. The game utilizes a microcontroller (UC Funt Kit).

Group 346 ENCE260 Assignment

Author: Ryan Wang, Zoher Hussein

Catch it is a game where the player is trying to time the incoming lights. The player has control of row six. The aim is to press the according button when the light is at row six. If timed as expected there is a beep and a point is added to the score. If the player misses the light it will reach the end of the column and minus a live point.

Player controls;

NAVSWITCH_NORTH: UP (C1, R6)

NAVSWITCH_SOUTH: DOWN (C5, R6)

NAVSWITCH_PUSH: ENTER (C3, R6)

NAVSWITCH_EAST: RIGHT (C4, R6)

NAVSWITCH_WEST: LEFT (C2, R6)

                            C1      C2      C3      C4      C5                  

                    R1      0       0       0       0       0                   | 

                    R2      0       0       0       0       0                   | Incoming light direction

                    R3      0       0       0       0       0                   |

                    R4      0       0       0       0       0                  \ /   

                    R5      0       0       0       0       0                   

                    R6      UP     LEFT    ENTER   RIGHT   DOWN

                    R7      0       0       0       0       0
The game starts with the title. By pressing the NORTH (increase level) or SOUTH (decrease level) the player can scroll through the levels (level 1 - 3). To select the level press PUSH (ENTER). The level detemines the speed of the incoming lights. As the game begins try to time the lights and press the button accordingly. There are five lives. When the game is over, the end screen will display the score.
