/*
 * File:    gaming.c
 * Author:  Ryan Wang, Zoher Hussein
 * Date:    19/10/2021
 * Brief:   This has the game methods that will be used in the game
 */

#include "system.h"
#include "navswitch.h"
#include "pio.h"
#include "pacer.h"
#include "timer.h"
#include "gaming.h"
#include "ledmat.h"
#include <stdlib.h>

#define PACER_RATE 500

#define PIEZO1_PIO PIO_DEFINE (PORT_D, 4)
#define PIEZO2_PIO PIO_DEFINE (PORT_D, 6)

/* Define PIO pins driving LED matrix rows*/
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/* Define PIO pins driving LED matrix columns*/
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

/* bitmap for the player control - row 6*/
static uint8_t bitmap[] =
{
    0x01, 0x01, 0x01, 0x01, 0x01
};

/*used to clear the display screen */
void ledmat_clear (void)
{
    uint8_t row;
    uint8_t col;

    for (row = 0; row < LEDMAT_ROWS_NUM; row++) {
        /* The rows are active low so configure PIO as an initially
           high output*/
        pio_output_high(rows[row]);
    }

    for (col = 0; col < LEDMAT_COLS_NUM; col++) {
        /* The columns are active low so configure PIO as an initially
           high output*/
        pio_output_high(cols[col]);
    }
}

/* takes the enemy_speed which decides the speed of the incoming led lights. 
    This is were main functionality comes from.
    After the game is over it returns the player score*/
uint32_t gaming(uint8_t enemy_speed)
{
    uint8_t button_value = 10;
    uint8_t player_speed = 10;
    uint8_t miss = 0;
    uint32_t kill = 0;
    uint8_t level_speed = enemy_speed;

    pio_config_set (PIEZO1_PIO, PIO_OUTPUT_LOW);
    pio_config_set (PIEZO2_PIO, PIO_OUTPUT_HIGH);

    /* picks the enemy at to appear at a random column */
    int enemy = rand() % 5;

    while (1)
    {
        pacer_wait();
        navswitch_update ();
    
        /* players led display control - EAST*/
        if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            ledmat_display_column (0x20, 3);
            /* remembers the player input*/
            button_value = 3;

            while (player_speed > 1) {
                pacer_wait();
                player_speed--;
            }

            ledmat_clear();
        }

        /* West control (pressed)*/
        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            ledmat_display_column (0x20, 1);
            button_value = 1;

            while (player_speed > 1) {
                pacer_wait();
                player_speed--;
            }

            ledmat_clear();
        }

        /* North control (pressed)*/
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            ledmat_display_column (0x20, 0);
            button_value = 0;

            while (player_speed > 1) {
                pacer_wait();
                player_speed--;
            }

            ledmat_clear();
        }

        /* SOUTH control (pressed)*/
        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            ledmat_display_column (0x20, 4);
            button_value = 4;

            while (player_speed > 1) {
                pacer_wait();
                player_speed--;
            }

            ledmat_clear();
        }

        /* PUSH control (pressed)*/
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ledmat_display_column (0x20, 2);
            button_value = 2;

            while (player_speed  > 1) {
                pacer_wait();
                player_speed--;
            } 

            ledmat_clear();
        }

        /* enemy running leds - (incoming lights)*/
        ledmat_display_column (bitmap[enemy], enemy);

         /* loop pacer_wait many times to control the enemy moving speed*/
        while (enemy_speed > 1) {
            pacer_wait();
            enemy_speed--;
        }

        /* check if we hit the enemy or enemy keep moving*/
        if (bitmap[enemy] < 32) {
            bitmap[enemy] = bitmap[enemy]*2;
        } else {
            if (bitmap[enemy] == 32) {
                /* the player timed the press*/
                if (button_value == enemy) {

                    pacer_wait();
                
                    /* make a beep when you kill the enemy*/
                    pio_output_toggle (PIEZO1_PIO);
                    pio_output_toggle (PIEZO2_PIO);
                    pacer_wait();

                    /* add to the score*/
                    kill += 1;

                    /* reset the col for next coming enemy*/
                    bitmap[enemy] = 0x01;
                    enemy = rand() % 5;

                } else {
                    miss += 1; 
                }
            }

            if (bitmap[enemy] != 0x01) {

                bitmap[enemy] = bitmap[enemy]*2;

            }

        
            /* enemy passes the defence and reaches the bottom row (miss)*/
            if (bitmap[enemy] > 64) {

                bitmap[enemy] = 0x01;
                enemy = rand() % 5;

            }

        }

        ledmat_clear();

        /* if miss 5 enemy, game over*/
        if (miss > 5) {

            break;

        }

        /* reset the speed values*/
        enemy_speed = level_speed;

        player_speed = 10;

        /* reset button value*/
        button_value = 10;

    }

    /* turn the pio output low to remove any noise (pull up)*/
    pio_output_low (PIEZO1_PIO);
    pio_output_low (PIEZO2_PIO);

    /* game over, return the score*/
    return kill;
}
