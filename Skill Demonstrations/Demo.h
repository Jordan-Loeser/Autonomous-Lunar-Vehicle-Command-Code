#define heightMarker 160

void interpretError(word error){
    // Interpret Message
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
}

/*
Update Position
*/
void getAccuratePosition(Position &currentPosition){

		eraseDisplay();

		wait1Msec(3000);

	  nxtDisplayCenteredTextLine(1, "%s", "Initialized...");

  	// Send Initial LSTS Request
  	ClearMessage();
  	ClearMessage();
  	sendMessage(heightMarker); // Height of Marker in mm
  	nxtDisplayCenteredTextLine(1, "%s", "Message Sent...");
  	wait1Msec(5000);
  	eraseDisplay();

  	// Interpret Coordinates
  	interpretError(messageParm[0]);
  	int xCoord = (int) messageParm[1] / 10;
  	int yCoord = (int) messageParm[2] / 10;
  	nxtDisplayCenteredTextLine(4, "Error: %d", messageParm[0]);
  	nxtDisplayCenteredTextLine(5, "X: %d", messageParm[1]);
  	nxtDisplayCenteredTextLine(6, "Y: %d", messageParm[2]);

  	wait1Msec(2000);
    ClearMessage();
    ClearMessage();

    wait1Msec(2000);
    eraseDisplay();

    currentPosition.x = xCoord;
    currentPosition.y = yCoord;

    return;
}

/*
Compare LSTS with Actual Position
*/
void altFixPositionError(Position &currentPosition, int inputPower, int magnetCalibrationValue){

		nxtDisplayCenteredTextLine(4, "%s", "Fixing Position!");
    // Initialize Variables
    int idealX = currentPosition.x;
    int idealY = currentPosition.y;
    int onTarget = false;
    int foundMagnet = false;
    int magnetValue = magnetCalibrationValue;
    int diff = magnetCalibrationValue - magnetValue;

    while(!onTarget && !foundMagnet) {
        // Get Actual Position
        getAccuratePosition(currentPosition);

        if( sqrt(pow(currentPosition.x - idealX, 2) + pow(currentPosition.y - idealY, 2)) < 10) { // TODO: Tolerance
            onTarget = true;
            return;
        }
        else {
            /*
             * Move Horizotally WHile Checking Magnet
             */
            // Initialize Variables
            nMotorEncoder[motorA] = 0;
            nMotorEncoder[motorB] = 0;
            int ticksPerMm = (360 / circumference) * LinearTextureGainFactor;
            int distanceMmX = abs(idealX - currentPosition.x) * 10;
            nxtDisplayCenteredTextLine(6, "MOVE X: %d cm", distanceMmX / 10);
            int tickGoalX = (ticksPerMm * distanceMmX) / 10;

            if(currentPosition.x > idealX) { // ALV must move west
                faceWest(currentPosition, turnPower);
                wait10Msec(transitionDelay);
            		// Move
            		nMotorEncoder[motorA] = 0;
            		nMotorEncoder[motorB] = 0;
            		while( (abs(nMotorEncoder[motorA]) < tickGoalX) ){
                        if((abs(diff) > 10)){
                            foundMagnet = true;
                            motor[motorA] = 0; // Left
                  		    	motor[motorB] = 0; // Right
                            return;
                        }
                        motor[motorA] = basePower; // Left
             		   	 		motor[motorB] = basePower; // Right
                        magnetValue = SensorRaw[S4];
                        diff = magnetCalibrationValue - magnetValue;
           			}
            		currentPosition.x -= (distanceMmX / 10);
           			displayPosition(currentPosition);
            }
            else { // ALV must move east
                faceEast(currentPosition, turnPower);
                wait10Msec(transitionDelay);
            		// Move
            		nMotorEncoder[motorA] = 0;
            		nMotorEncoder[motorB] = 0;
            		while( (abs(nMotorEncoder[motorA]) < tickGoalX) ){
                        if((abs(diff) > 10)){
                            foundMagnet = true;
                            motor[motorA] = 0; // Left
                  		    	motor[motorB] = 0; // Right
                            return;
                        }
                        motor[motorA] = basePower; // Left
             		    		motor[motorB] = basePower; // Right
                        magnetValue = SensorRaw[S4];
                        diff = magnetCalibrationValue - magnetValue;
           			}
            		currentPosition.x += (distanceMmX / 10);
           			displayPosition(currentPosition);
            		nxtDisplayCenteredTextLine(4, "FINAL X: %d", currentPosition.x);
            }
            wait10Msec(transitionDelay);

            // Stop Motors
            motor[motorA] = 0;
            motor[motorB] = 0;

            /*
             * Move Vertically WHile Checking Magnet
             */
             // Initialize Variables
             nMotorEncoder[motorA] = 0;
             nMotorEncoder[motorB] = 0;
             int distanceMmY = abs(idealY - currentPosition.y) * 10;
             nxtDisplayCenteredTextLine(6, "MOVE X: %d cm", distanceMmY / 10);
             int tickGoalY = (ticksPerMm * distanceMmY) / 10;

             if(currentPosition.y > idealY) { // ALV must move south
                 faceSouth(currentPosition, turnPower);
                 wait10Msec(transitionDelay);
                    // Move
                    nMotorEncoder[motorA] = 0;
                    nMotorEncoder[motorB] = 0;
                    while( (abs(nMotorEncoder[motorA]) < tickGoalY) ){
                         if((abs(diff) > 10)){
                             foundMagnet = true;
                             motor[motorA] = 0; // Left
                             motor[motorB] = 0; // Right
                             return;
                         }
                         motor[motorA] = basePower; // Left
                         motor[motorB] = basePower; // Right
                         magnetValue = SensorRaw[S4];
                         diff = magnetCalibrationValue - magnetValue;
                    }
                    currentPosition.y -= (distanceMmY / 10);
                    displayPosition(currentPosition);
             }
             else { // ALV must move north
                 faceNorth(currentPosition, turnPower);
                 wait10Msec(transitionDelay);
                    // Move
                    nMotorEncoder[motorA] = 0;
                    nMotorEncoder[motorB] = 0;
                    while( (abs(nMotorEncoder[motorA]) < tickGoalY) ){
                         if((abs(diff) > 10)){
                             foundMagnet = true;
                             motor[motorA] = 0; // Left
                             motor[motorB] = 0; // Right
                             return;
                         }
                         motor[motorA] = basePower; // Left
                         motor[motorB] = basePower; // Right
                         magnetValue = SensorRaw[S4];
                         diff = magnetCalibrationValue - magnetValue;
                        }
                    currentPosition.y += (distanceMmY / 10);
                    displayPosition(currentPosition);
                    nxtDisplayCenteredTextLine(4, "FINAL Y: %d", currentPosition.y);
             }
             wait10Msec(transitionDelay);

             // Stop Motors
             motor[motorA] = 0;
             motor[motorB] = 0;

         }
        // If you reach this point, check LSTS again
    }

	return;
}
