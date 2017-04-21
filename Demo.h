#define basePower 20

/*
Compare LSTS with Actual Position
*/
/*
void fixPositionError(Position &currentPosition, int inputPower){

    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;

    // Initialize Variables
    int idealX = currentPosition.x;
    int idealY = currentPosition.y;
    int initialOrientation = currentPosition.orientation;

    SEND MESSAGE
    GET ACTUAL COORDINATES

    int actualX = ;
    int actualY = ;

    if(actualY > idealY){ // Too high
        faceSouth(currentPosition, inputPower);
        moveDistanceCm(actualY - idealY, inputPower);
    }
    else { // Too low
        faceNorth(currentPosition, inputPower);
        moveDistanceCm(idealY - actualY, inputPower);
    }

    if(actualX > idealX){ // Too right
        faceWest(currentPosition, inputPower);
        moveDistanceCm(actualX - idealX, inputPower);
    }
    else { // Too left
        faceEast(currentPosition, inputPower);
        moveDistanceCm(idealX - actualX, inputPower);
    }

    // Face back to starting position
    int degreesToTurn = (currentPosition.orientation - initialOrientation) % 360;
    if (degreesToTurn > 0) {
        turnLeftDeg(degreesToTurn, inputPower);
    }
    else {
        turnRightDeg(degreesToTurn, inputPower);
    }

	return;
}
*/

/*
Compare LSTS with Actual Position
*/
void altFixPositionError(Position &currentPosition, int inputPower){

    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;

    // Initialize Variables
    int idealX = currentPosition.x;
    int idealY = currentPosition.y;
    int initialOrientation = currentPosition.orientation;
    int onTarget = FALSE;

    /*
    SEND MESSAGE
    GET ACTUAL COORDINATES

    int actualX = ;
    int actualY = ;
    */
    currentPosition.x = actualX;
    currentPosition.y = actualY;

    while(!onTarget){
        if((currentPosition.x == idealX) && (currentPosition.y == idealY)){
            onTarget = TRUE:
        }
        else {
            moveHorizontallyTo(idealX, currentPosition, inputPower);
            wait10Msec(transitionDelay);
            moveVerticallyTo(idealY, currentPosition, inputPower);
            wait10Msec(transitionDelay);

            /*
            SEND MESSAGE
            GET ACTUAL COORDINATES

            currentPosition.x = messageParms[];
            currentPosition.y = messageParms[];
            */
            wait10Msec(1000);
        }
        displayPosition();
    }

    // TODO: Face correct orientation?

	return;
}

/*
Move Forward to detect magnet in search zone
*/
void findBeacon(Position &currentPosition, int inputPower){
    int magnetCalibrationValue = 473; // Default

    // Start searching

    // TODO: HOW WAS IT MOVING???
    // TODO: Cap at 10cm
    magnetCalibrationValue = SensorRaw[S4];
    int magnetValue = magnetCalibrationValue;
    int diff = magnetCalibrationValue - magnetValue;
    while(abs(diff) < 10){
    	magnetValue = SensorRaw[S4];
    	diff = magnetCalibrationValue - magnetValue;
    	nxtDisplayCenteredTextLine(1, "MAGNET: %d", magnetValue);
    	nxtDisplayCenteredTextLine(3, "DIFF: %d", diff);
    	wait1Msec(500);
    }

    motor[motorA] = 0;
    motor[motorB] = 0;

    // Beacon was found
    for(int i = 0; i < 3; i++){
        playSound(soundDownwardTones);
        wait10Msec(100);
    }

    return;
}
