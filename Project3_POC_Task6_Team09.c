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

    wait1Msec(1000); // RobotC Quirk

    nxtDisplayCenteredTextLine(1, "%s", "Initialized...");

    // Send Initial LSTS Request
    ClearMessage();
    sendMessage(10); // Height of Marker in mm
    nxtDisplayCenteredTextLine(1, "%s", "Message Sent...");
    wait1Msec(1000);

    // Interpret Message
    word error = messageParm[0];
    if(error == 1){
        nxtDisplayCenteredTextLine(7, "%s", "No error.");
    }
    else {
        nxtDisplayCenteredTextLine(4, "%s", "error");
    }

    wait10Msec(500);
    ClearMessage();
    eraseDisplay();
}
