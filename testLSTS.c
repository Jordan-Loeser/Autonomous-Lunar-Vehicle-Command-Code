/* Project 3 Final Demo Code
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
#include "Demo.h"

task main() {
    // Clean Slate
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;

    // Define Variables
	Position currentPosition;
	int magnetCalibrationValue = SensorRaw[S4];

    // Beacon Positions
    // A: (55, 2basePower)
    Position testPos;
    beaconA.x = 20;
    beaconA.y = 30;

    getAccuratePosition(currentPosition);
    currentPosition.orientation = 0; // CHANGE BEFORE DEMO

    // Go To Beacon A
    moveHorizontallyTo(testPos.x, currentPosition, basePower, magnetCalibrationValue);
    wait10Msec(transitionDelay);
    moveVerticallyTo(testPos.y, currentPosition, basePower, magnetCalibrationValue);
    wait10Msec(transitionDelay);

    altFixPositionError(currentPosition, basePower, magnetCalibrationValue);

    getAccuratePosition(currentPosition);
    displayPosition(currentPosition);

}
