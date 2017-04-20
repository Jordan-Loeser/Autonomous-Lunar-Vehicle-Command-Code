/* Project 3 Control Code
 * File:    Project3_Team09.c
 * Date:    22 January 2017
 * By:      Klaire Fosnaugh
 *          kfosnau?
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

	// Define Variables
	Position currentPosition;
  int goalX = 135; // cm
  int goalY = 75;

  wait1Msec(3000); // RobotC Quirk

  nxtDisplayCenteredTextLine(1, "%s", "Initialized...");

  // Send Initial LSTS Request
  ClearMessage();
  sendMessage(10); // Height of Marker in mm
  nxtDisplayCenteredTextLine(1, "%s", "Message Sent...");
  wait1Msec(5000);
  eraseDisplay();

  // Interpret Message
  word error = messageParm[0];
  if(error == 1){
      nxtDisplayCenteredTextLine(3, "%s", "No error.");
    }
  else if(error == 2) {
        nxtDisplayCenteredTextLine(3, "%s", "Manual override engaged.");
    }
  else if(error == 4) {
        nxtDisplayCenteredTextLine(3, "%s", "Out of bounds detected");
    }
  else if(error == 8) {
        nxtDisplayCenteredTextLine(3, "%s", "No ALV marker seen");
    }
  else if(error == 16) {
        nxtDisplayCenteredTextLine(3, "%s", "LSTS system error");
    }
  else if(error == 32) {
        nxtDisplayCenteredTextLine(3, "%s", "Busy, request again later");
    }
  else {
        nxtDisplayCenteredTextLine(3, "%s", "Error not recognized!");
    }


  // Interpret Coordinates
  word xCoord = messageParm[1];
  word yCoord = messageParm[2];
  nxtDisplayCenteredTextLine(4, "%d", messageParm[0]);
  nxtDisplayCenteredTextLine(5, "%d", messageParm[1]);
  nxtDisplayCenteredTextLine(6, "%d", messageParm[2]);

  // Initialize Starting Position
  currentPosition.x = (int) xCoord;
  currentPosition.y = (int) yCoord;
  currentPosition.orientation = 90; // THIS WONT BE TRUE FOR FINAL DEMO


  wait1Msec(3000);
  ClearMessage();
  ClearMessage();

  wait1Msec(20000);
  eraseDisplay();

  // Move to suitable y Position (30)
  if(yCoord > 30){
   moveVerticallyTo(30, currentPosition, 20);
  }
  wait10Msec(transitionDelay);

  // Move to final x Position
  moveHorizontallyTo(goalX, currentPosition, 20);
  wait10Msec(transitionDelay);

  // Move to final y position
  moveVerticallyTo(goalY, currentPosition, 20);
  wait10Msec(transitionDelay);

  // At Goal - Beep Thric
  motor[motorA] = 0; // Left
  motor[motorB] = 0;
  for(int i = 0; i < 3; i++){
    wait10Msec(100);
    playSound(soundBeepBeep);
  }
  wait10Msec(100);


}
