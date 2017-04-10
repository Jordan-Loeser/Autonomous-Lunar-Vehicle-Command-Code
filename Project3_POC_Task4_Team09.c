/* Project 3 POC Task4 Code
 * File:    Project3_POC_Task4_Team09.c
 * Date:    07 April 2017
 * By:      Klaire Fosnaugh
 *          kfosnau
 *          Bailey Hayes
 *          hayes121
 *          Jordan Loeser
 *          jloeser
 *          Michael Porter
 *          porte109
 * Section: 1
 * Team:    9
 *
 * ELECTRONIC SIGNATURE
 * Klaire Fosnaugh
 * Bailey Hayes
 * Jordan Loeser
 * Michael Porter
 *
 * The electronic signatures above indicate that the program
 * submitted for evaluation is the combined effort of all
 * team members and that each member of the team was an
 * equal participant in its creation. In addition, each
 * member of the team has a general understanding of
 * all aspects of the program development and execution.
 *
 * Commands Autonomous Lunar Vehicle (ALV).
 */

#include "BasicMovement.h"

task main() {
    // Clean Slate
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;

    // Move to search area
    moveDistanceCm(50, 20);

    // Start searching
    magetValue = sensorRaw[A] / 1023;
    while(magnetValue < .75){
    	moveDistanceMm(1);
    	magetValue = sensorRaw[A] / 1023;
    }

    // Beacon was found
    playSound(soundBeepBeepBeep);
   	sleep(1000);
}
