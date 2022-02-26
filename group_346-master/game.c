/*
 * File:    game.c
 * Author:  Ryan Wang, Zoher Hussein
 * Date:    19/10/2021
 * Brief:   This is the main. It is used to initialize important modules and provide the flow of the game.
 */

#include "system.h"
#include "displayscreen.h"
#include "gaming.h"
#include "pacer.h"
#include "navswitch.h"
#include "ledmat.h"

#define PACER_RATE 500

int main (void)
{
    system_init ();
    navswitch_init();
    pacer_init (PACER_RATE);
    ledmat_init ();
    
    /* initialize the displayscreen*/
    displayscreen_init();

    /* gets the level speed from the selected level */
    uint8_t level_speed = startscreen();

    /* start the game passing it the level speed*/
    uint32_t kill = gaming(level_speed);

    /*display the game over screen with the player score*/
    endscreen(kill);
}
