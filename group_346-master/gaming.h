/*
 * File:    gaming.h
 * Author:  Ryan Wang, Zoher Hussein
 * Date:    19/10/2021
 * Brief:   This has the main functionality of the game 
 */

#ifndef GAMING_H
#define GAMING_H

/* for the 'beep' sound when you hit an enemy*/
#define PIEZO1_PIO PIO_DEFINE (PORT_D, 4)
#define PIEZO2_PIO PIO_DEFINE (PORT_D, 6)

/* the main method that has the functionality of the game*/
uint32_t gaming(uint8_t enemy_speed);

#endif //Gaming_H


