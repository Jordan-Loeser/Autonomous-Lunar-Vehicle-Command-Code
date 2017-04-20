/* Project 3 POC Task2 Code
 * File:    Project3_POC_Task2_Team09.c
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

    // Define Variables
    Position currentPosition;
    int goalX = 135; // cm
    int goalY = 75;
    int startX = 35;
    int startY = 35;

   	// Initialize Starting Position
    currentPosition.x = startX;
    currentPosition.y = startY;
    currentPosition.orientation = 90;

    // Move to suitable y Position (30)
    if(startY > 30){
   		moveVerticallyTo(30, currentPosition, 20);
   	}
   	wait10Msec(transitionDelay);

    // Move to final x Position
    moveHorizontallyTo(goalX, currentPosition, 20);
    wait10Msec(transitionDelay);

   	// Move to final y position
    moveVerticallyTo(goalY, currentPosition, 20);
    wait10Msec(transitionDelay);

    // At Goal - Beep Thrice
    motor[motorA] = 0; // Left
    motor[motorB] = 0;
    for(int i = 0; i < 3; i++){
    	wait10Msec(100);
      playSound(soundBeepBeep);
    }
    wait10Msec(100);

    // Move to suitable y Position (30)
    if(startY > 30){
   		moveVerticallyTo(30, currentPosition, 20);
   	}
   	else {
   		moveVerticallyTo(startY, currentPosition, 20);
   	}
   	wait10Msec(transitionDelay);

    // Move to home x Position
    moveHorizontallyTo(startX, currentPosition, 20);
    wait10Msec(transitionDelay);

   	// Move to home y position
    moveVerticallyTo(startY, currentPosition, 20);
    wait10Msec(transitionDelay);
    faceEast(currentPosition, 20);

}
