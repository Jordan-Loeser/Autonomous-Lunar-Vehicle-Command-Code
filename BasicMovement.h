// Define Dimentions (cm)
#define PI 4 * atan(1.0)
#define diameter 8
#define circumference (diameter * PI)
#define RotationalTextureGainFactorLeft 2.05
#define RotationalTextureGainFactorRight 1.43
#define LinearTextureGainFactor 1.0
#define transitionDelay 50

#define basePower 20
#define turnPower 30

/*
Struct for robot's current position.
*/
typedef struct Position_struct{
    int x;
    int y;
    int orientation;
} Position;

/*
Display current position coordinates.
*/
void displayPosition(Position currentPosition){
	eraseDisplay();
	nxtDisplayCenteredTextLine(1, "(%d, %d)", currentPosition.x, currentPosition.y);
	nxtDisplayCenteredTextLine(2, "%d degrees", currentPosition.orientation);
	return;
}

/*
Move forwards a set distance in mm.
*/
void moveDistanceMm(int distanceMm, int power) {

    // Initialize Variables
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;
    int ticksPerMm = (360 / circumference) * LinearTextureGainFactor;
    int tickGoal = (ticksPerMm * distanceMm) / 10;

    // Move
    while(abs(nMotorEncoder[motorA]) < tickGoal){
        // TODO: Update to sync motors digitally?
        motor[motorA] = power; // Left
        motor[motorB] = power; // Right
    }

    // Stop Motors
    motor[motorA] = 0;
    motor[motorB] = 0;
    return;
}

/*
Move forwards a set distance in cm.
*/
void moveDistanceCm(int distanceCm, int power) {
    moveDistanceMm(distanceCm * 10, power);
    return;
}

/*
Rotate a specific amount of degrees.
*/
int turnLeftDeg(Position &currentPosition, int degrees, int power) {

    // Initialize Variables
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;

    // Determine Tickgoal
    float ticksPerDeg = 1.758 * RotationalTextureGainFactorLeft;
    int tickGoal = (ticksPerDeg * degrees);

    // Run Motors
    motor[motorA] = -1 * power;
    motor[motorB] = power;

    // Turn
    while(nMotorEncoder[motorA] > -1 * tickGoal || nMotorEncoder[motorB] < tickGoal) {
    	if(nMotorEncoder[motorA] < -1 * tickGoal) { motor[motorA] = 0;}
    	if(nMotorEncoder[motorB] > tickGoal) { motor[motorB] = 0;}
    }

    // Stop
    motor[motorA] = 0;
    motor[motorB] = 0;

    // Update Orientation
    currentPosition.orientation = (currentPosition.orientation - degrees) % 360;

    return -1 * degrees;
}
int turnRightDeg(Position &currentPosition, int degrees, int power) {

    // Initialize Variables
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;

    // Determine Tickgoal
    float ticksPerDeg = 1.758 * RotationalTextureGainFactorRight;
    int tickGoal = (ticksPerDeg * degrees);

    // Run Motors
    motor[motorB] = -1 * power;
    motor[motorA] = power;

    // Turn
    while(nMotorEncoder[motorB] > -1 * tickGoal || nMotorEncoder[motorA] < tickGoal) {
    	if(nMotorEncoder[motorB] < -1 * tickGoal) { motor[motorB] = 0;}
    	if(nMotorEncoder[motorA] > tickGoal) { motor[motorA] = 0;}
    }

    // Stop
    motor[motorA] = 0;
    motor[motorB] = 0;

    // Update Orientation
    currentPosition.orientation = (currentPosition.orientation + degrees) % 360;

    return degrees;
}

/*
Face Compass Direction
*/
void faceNorth(Position &currentPosition, int power){

    int initialOrientation = currentPosition.orientation;

    // Readjust angle to vertical
    if((initialOrientation % 360) < 180){
        turnLeftDeg(currentPosition, (initialOrientation % 360), power);
    }
    else {
        turnRightDeg(currentPosition, 360 - (initialOrientation % 360), power);
    }

    currentPosition.orientation = 0;

    return; // Degrees
}
void faceSouth(Position &currentPosition, int power){

    int initialOrientation = currentPosition.orientation;

    // Readjust angle to vertical
    if((initialOrientation % 360) < 180){
        turnRightDeg(currentPosition, 180 - (initialOrientation % 360), power);
    }
    else {
        turnLeftDeg(currentPosition, (initialOrientation % 360) - 180, power);
    }

    currentPosition.orientation = 180;

    return; // Degrees
}
void faceEast(Position &currentPosition, int power){

    int initialOrientation = currentPosition.orientation;

    // Readjust angle to vertical
    if((initialOrientation % 360) < 90){
        turnRightDeg(currentPosition, 90 - (initialOrientation % 360), power);
    }
    else {
        turnLeftDeg(currentPosition, (initialOrientation % 360) - 90, power);
    }

    currentPosition.orientation = 90;

    return; // Degrees
}
void faceWest(Position &currentPosition, int power){

    int initialOrientation = currentPosition.orientation;

    // Readjust angle to vertical
    if((initialOrientation % 360) < 270){
        turnRightDeg(currentPosition, 270 - (initialOrientation % 360), power);
    }
    else {
        turnLeftDeg(currentPosition, (initialOrientation % 360) - 270, power);
    }

    currentPosition.orientation = 270;

    return; // Degrees
}


/*
Move Vertically To a specific Y coord
*/
void moveVerticallyTo(int goalYPos, Position &currentPosition, int power, int magnetCalibrationValue){

    // Initialize Variables
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;
    int initialYPos = currentPosition.y;
    int ticksPerMm = (360 / circumference) * LinearTextureGainFactor;
    int distanceMm = abs(goalYPos - currentPosition.y) * 10;
    nxtDisplayCenteredTextLine(6, "MOVE Y: %d cm", distanceMm / 10);
    int tickGoal = (ticksPerMm * distanceMm) / 10;

    int magnetValue = magnetCalibrationValue;
    int diff = magnetCalibrationValue - magnetValue;

    if(currentPosition.y > goalYPos) { // ALV must move down
        faceSouth(currentPosition, turnPower);
        wait10Msec(transitionDelay);
    		// Move
    		nMotorEncoder[motorA] = 0;
    		nMotorEncoder[motorB] = 0;
    		while(abs(nMotorEncoder[motorA]) < tickGoal){
    			if((abs(diff) > 10)){
          		motor[motorA] = 0; // Left
              motor[motorB] = 0; // Right
              nxtDisplayCenteredTextLine(4, "%s", "MAGNET DETECTED");
              return;
           }
     		   motor[motorA] = power; // Left
     		   motor[motorB] = power; // Right
     		   magnetValue = SensorRaw[S4];
           diff = magnetCalibrationValue - magnetValue;
   			}
   			currentPosition.y = initialYPos - (distanceMm / 10);
   			displayPosition(currentPosition);
    		nxtDisplayCenteredTextLine(4, "FINAL Y: %d", currentPosition.y);
    }
    else { // ALV must move up
        faceNorth(currentPosition, turnPower);
        wait10Msec(transitionDelay);
    		// Move
    		nMotorEncoder[motorA] = 0;
    		nMotorEncoder[motorB] = 0;
    		while(abs(nMotorEncoder[motorA]) < tickGoal){
    			if((abs(diff) > 10)){
          		motor[motorA] = 0; // Left
              motor[motorB] = 0; // Right
              nxtDisplayCenteredTextLine(4, "%s", "MAGNET DETECTED");
              return;
           }
     		   motor[motorA] = power; // Left
     		   motor[motorB] = power; // Right
     		   magnetValue = SensorRaw[S4];
           diff = magnetCalibrationValue - magnetValue;
   			}
    		currentPosition.y = initialYPos + (distanceMm / 10);
   			displayPosition(currentPosition);
    		nxtDisplayCenteredTextLine(4, "FINAL Y: %d", currentPosition.y);
    }

    // Stop Motors
    motor[motorA] = 0; // Left
    motor[motorB] = 0; // Right

    return;
}

/*
Move Horizontally To a specific X coord
*/
void moveHorizontallyTo(int goalXPos, Position &currentPosition, int power, int magnetCalibrationValue){

    // Initialize Variables
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;
    int ticksPerMm = (360 / circumference) * LinearTextureGainFactor;
    int initialXPos = currentPosition.x;
    int distanceMm = abs(goalXPos - currentPosition.x) * 10;
    nxtDisplayCenteredTextLine(6, "MOVE X: %d cm", distanceMm / 10);
    int tickGoal = (ticksPerMm * distanceMm) / 10;

    int magnetValue = magnetCalibrationValue;
    int diff = magnetCalibrationValue - magnetValue;

    if(currentPosition.x > goalXPos) { // ALV must move west
        faceWest(currentPosition, turnPower);
        wait10Msec(transitionDelay);
    		// Move
    		nMotorEncoder[motorA] = 0;
    		nMotorEncoder[motorB] = 0;
    		while(abs(nMotorEncoder[motorA]) < tickGoal){
    		   if((abs(diff) > 10)){
          		motor[motorA] = 0; // Left
              motor[motorB] = 0; // Right
              nxtDisplayCenteredTextLine(4, "%s", "MAGNET DETECTED");
              return;
           }
     		   motor[motorA] = power; // Left
     		   motor[motorB] = power; // Right
     		   magnetValue = SensorRaw[S4];
           diff = magnetCalibrationValue - magnetValue;
   			}
    		currentPosition.x = initialXPos - (distanceMm / 10);
   			displayPosition(currentPosition);
    		nxtDisplayCenteredTextLine(4, "FINAL X: %d", currentPosition.y);
    }
    else { // ALV must move east
        faceEast(currentPosition, turnPower);
        wait10Msec(transitionDelay);
    		// Move
    		nMotorEncoder[motorA] = 0;
    		nMotorEncoder[motorB] = 0;
    		while(abs(nMotorEncoder[motorA]) < tickGoal){
    		   if((abs(diff) > 10)){
          		motor[motorA] = 0; // Left
              motor[motorB] = 0; // Right
              nxtDisplayCenteredTextLine(4, "%s", "MAGNET DETECTED");
              return;
           }
     		   motor[motorA] = power; // Left
     		   motor[motorB] = power; // Right
     		   magnetValue = SensorRaw[S4];
           diff = magnetCalibrationValue - magnetValue;
   			}
    		currentPosition.x = initialXPos + (distanceMm / 10);
   			displayPosition(currentPosition);
    		nxtDisplayCenteredTextLine(4, "FINAL X: %d", currentPosition.y);
    }
    wait10Msec(transitionDelay);

    // Stop Motors
    motor[motorA] = 0;
    motor[motorB] = 0;

    return;
}

/*
Drop off Bin
*/
void dropOffBin() {

    // Initialize Variables
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;
    nMotorEncoder[motorC] = 0;
    int treadDiameterMm = 30;
    int ticksPerMm = 360 / (treadDiameterMm * PI);
    int binWidthMm = 40.5;
    int tickGoal = (ticksPerMm * binWidthMm);

    // Move
    while(abs(nMotorEncoder[motorC]) < tickGoal){
        motor[motorC] = 15;
    }

    // Stop Motors
    motor[motorC] = 0;

    return;
}
