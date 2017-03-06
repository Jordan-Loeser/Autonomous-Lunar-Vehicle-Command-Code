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
    currentPosition.orientation = 90; // East
    int goalX = 135; // cm
    int goalY = 75;

    currentPosition.x = 0;
    currentPosition.y = 0;
    currentPosition.orientation = 90;

    // Enter Starting Position

    // TODO: Enable User Input
    writeDebugStream("\nEnter initial X coordinate: ");
    scanf("%f", &currentPosition.x);

    writeDebugStream("%s", "\nEnter initial Y coordinate: ");
    scanf("%f", &currentPosition.y);


    // Move to suitable y Position (40)
    moveVerticallyTo(40, currentPosition, 20);

    // Move to final x Position
    moveHorizontallyTo(goalX, currentPosition, 20);

    // Move to final y position
    moveVerticallyTo(goalY, currentPosition, 20);

}
