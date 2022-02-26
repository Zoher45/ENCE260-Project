/*
 * File:    displayscreen.c
 * Author:  Ryan Wang, Zoher Hussein
 * Date:    19/10/2021
 * Brief:   This has the display methods that will be used in the game
 */

#include "system.h"
#include "navswitch.h"
#include "pacer.h"
#include "tinygl.h"
#include "timer.h"
#include "../fonts/font5x7_1.h"
#include "displayscreen.h"
#include <stdio.h>

#define PACER_RATE 500
#define MESSAGE_RATE 15

/* displays the end screen with the player score */
void endscreen(uint8_t score)
{
    
    char end_message[20];

    /* concatenate the end message with the gotten player score*/
    sprintf(end_message, "GAME OVER: %d", score);
    tinygl_text(end_message);

    while (1) {
        pacer_wait();
        tinygl_update ();
    }
    
}

/* displays the game title. Player can use NORTH (up) or SOUTH (down) to scroll levels and PUSH to select. Returns the enemy speed.*/
uint8_t startscreen (void) 
{
    uint8_t level_counter= 0;
    char levels[3][4] =  {"LV1", "LV2", "LV3"};
    uint8_t level_select[3] = {85, 70, 50};

    pacer_init (PACER_RATE);

    tinygl_text("CATCH IT");

    
    while (1) {

        pacer_wait();       
        tinygl_update ();
        navswitch_update ();
      
        /* scroll up the level using the levels array*/
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            
            level_counter++;

            /* if at the max level leave level_counter*/
            if (level_counter >= 2) {
                level_counter = 2;
            }
            tinygl_clear();

             /* display the level given the level_counter*/
            tinygl_text(levels[level_counter]);
             
        }

        /* scroll down the level using the levels array*/
        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            
            /* if not at the min level level_counter is minused by one*/
            if (level_counter - 1 >= 0) {
                level_counter--;
            }
            tinygl_clear();
            tinygl_text(levels[level_counter]);
        }
        
        /* the player has selected the level - break out of the while*/
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            break;
        }
     
    }
    
    /* returns the enemy speed according to the level*/
    return level_select[level_counter];

}


/* initializes tinygl and configures the required modes*/
void displayscreen_init (void) 
{

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

}


