/* Project 3 POC Task1 Code
 * File:    Project3_POC_Task1_Team09.c
 * Date:    22 January 2017
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
    nMotorEncoder[motorC] = 0;

    // Move Forward
   	moveDistanceCm(45, 20);
   	turnRightDeg(90, 20);
   	moveDistanceCm(35, 20);
   	turnLeftDeg(90, 20);
   	moveDistanceCm(30, 20);
   	turnRightDeg(180, 20);

   	// Drop Off
   	dropOffBin();
   	wait10Msec(100);
   	dropOffBin();
   	wait10Msec(100);
   	dropOffBin();
   	wait10Msec(100);
   	dropOffBin();
   	wait10Msec(100);
   	dropOffBin();

   	// Move Away
   	moveDistanceCm(30, 20);

}
