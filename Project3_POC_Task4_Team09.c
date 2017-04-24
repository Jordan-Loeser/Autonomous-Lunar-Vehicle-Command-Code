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
    int magnetCalibrationValue = 473; // Default

    // Move to search area
    //moveDistanceCm(50, 20);

    // Start searching
    magnetCalibrationValue = SensorRaw[S4];
    int magnetValue = magnetCalibrationValue;
    int diff = magnetCalibrationValue - magnetValue;
    while(abs(diff) < 10){
    	motor[motorA] = 10;
    	motor[motorB] = 10;
    	magnetValue = SensorRaw[S4];
    	diff = magnetCalibrationValue - magnetValue;
    	nxtDisplayCenteredTextLine(1, "MAGNET: %d", magnetValue);
    	nxtDisplayCenteredTextLine(3, "DIFF: %d", diff);
    	wait1Msec(500);
    }

    motor[motorA] = 0;
    motor[motorB] = 0;

    // Go over Beacon
    //moveDistanceCm(5, 20);

    // Beacon was found
    for(int i = 0; i < 3; i++){
        playSound(soundDownwardTones);
        wait10Msec(100);
    }

   	sleep(1000);
}
