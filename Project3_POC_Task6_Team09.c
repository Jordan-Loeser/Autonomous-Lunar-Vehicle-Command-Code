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

    wait1Msec(1000); // RobotC Quirk

    nxtDisplayCenteredTextLine(1, "%s", "WE OUT HERE");

    // Send Initial LSTS Request
    ClearMessage();
    sendMessage(10); // Height of Marker in mm
    wait1Msec(1000);
    //writeDebugStream("\nInitial LSTS Request: Sent\n");

    // See if message has been returned
    /*
    int firstMessage = 0;
    while(!firstMessage){
    	if(bQueuedMsgAvailable()){
    		firstMessage = 1;
    		nxtDisplayClearTextLine(5);
    		nxtDisplayCenteredTextLine(5, "%s", "Message recieved!");
    	}
    	else {
    		nxtDisplayClearTextLine(5);
    		//nxtDisplayCenteredTextLine(5, "%s", "Well we'll just wait...\n");
    	}
    }
    */

    // We got a message
    int error = messageParm[0];
    if(error == 1){
        nxtDisplayCenteredTextLine(7, "%s", "No error.");
        // Initialize Starting Position
        currentPosition.x = messageParm[1];
        currentPosition.y = messageParm[2];
        currentPosition.orientation = 90;
        ClearMessage();

        // Move to suitable y Position (40)
   			moveVerticallyTo(40, currentPosition, 20);

    		// Move to final x Position
    		moveHorizontallyTo(goalX, currentPosition, 20);

   	 		// Move to final y position
    		moveVerticallyTo(goalY, currentPosition, 20);
    }
    else {
        nxtDisplayCenteredTextLine(4, "%s", "error");
    }



}
