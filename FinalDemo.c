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

task main() {
    // Clean Slate
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;

    // Define Variables
    Position currentPosition;

    // Beacon Positions
    // A: (55, 2basePower)
    Position beaconA;
    beaconA.x = 55;
    beaconA.y = 220;
    // B: (250, 163)
    Position beaconB;
    beaconB.x = 250;
    beaconB.y = 163;
    // C: (298, 71)
    Position beaconC;
    beaconC.x = 298;
    beaconC.y = 71;

   	// TODO: LSTS Initialize Starting Position
    int startX = 0;
    int startY = 0;
    currentPosition.x = startX;
    currentPosition.y = startY;
    currentPosition.orientation = 90;

    // Go To Beacon A
    moveVerticallyTo(beaconA.y, currentPosition, basePower);
    wait10Msec(transitionDelay);
    moveHorizontallyTo(beaconA.x - 5, currentPosition, basePower);
    wait10Msec(transitionDelay);
    fixPositionError(currentPosition, basePower);
    // TODO: Magnet sensor

    faceEast(currentPosition, basePower);
    dropOffBin();

    // Go To Beacon C
    moveVerticallyTo(beaconC.y, currentPosition, basePower);
    wait10Msec(transitionDelay);
    moveHorizontallyTo(beaconC.x - 5, currentPosition, basePower);
    wait10Msec(transitionDelay);
    fixPositionError(currentPosition, basePower);
    // TODO: Magnet sensor

    faceWest(currentPosition, basePower);
    dropOffBin();

    // Go To Beacon B
    moveVerticallyTo(beaconB.y, currentPosition, basePower);
    wait10Msec(transitionDelay);
    moveHorizontallyTo(beaconB.x - 5, currentPosition, basePower);
    wait10Msec(transitionDelay);
    fixPositionError(currentPosition, basePower);
    // TODO: Magnet sensor

    faceSouth(currentPosition, basePower);
    dropOffBin();

    moveVerticallyTo(startY, currentPosition, basePower);
    wait10Msec(transitionDelay);
    moveHorizontallyTo(startX, currentPosition, basePower);
    wait10Msec(transitionDelay);
    // TODO: Check LSTS position & Fix

}
