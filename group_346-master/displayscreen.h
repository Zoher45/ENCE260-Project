/*
 * File:    displayscreen.h
 * Author:  Ryan Wang, Zoher Hussein
 * Date:    19/10/2021
 * Brief:   This has the display methods for the game
 */

#ifndef DISPLAYSCREEN_H
#define DISPLAYSCREEN_H

//end screen display
void endscreen(uint8_t score);

//start screen display - displays the game name and the level select
uint8_t startscreen (void);

//initializes tinygl and configures the required modes
void displayscreen_init (void);


#endif //DISPLAYSCREEN_H
