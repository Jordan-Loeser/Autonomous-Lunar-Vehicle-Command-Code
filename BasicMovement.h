// Define Dimentions (cm)
#define PI 4 * atan(1.0)
#define diameter 8
#define circumference (diameter * PI)
#define RotationalTextureGainFactor 1.1
#define LinearTextureGainFactor 1.1

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
	nxtDisplayCenteredTextLine(1, "\n(%d, %d)\n", currentPosition.x, currentPosition.y);
	return;
}

/*
Move forwards a set distance in mm.
*/
void moveDistanceMm(int distanceMm, int power) {
    // Initialize Variables
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;
    int ticksPerMm = 360 / circumference;
    int tickGoal = (ticksPerMm * distanceMm) / 10;

    // Move
    while(abs(nMotorEncoder[motorA]) < tickGoal){
        // TODO: Update to sync motors digitally?
        motor[motorA] = power; // Left
        motor[motorB] = power; // Right
    }

    // Stop Motors
    motor[motorA] = power;
    motor[motorB] = power;
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
int turnLeftDeg(int degrees, int power) {

    // Initialize Variables
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;

    // Determine Tickgoal
    float ticksPerDeg = 1.758 * RotationalTextureGainFactor;
    int tickGoal = (ticksPerDeg * degrees);
    //printf("%d", tickGoal);

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

    return -1 * degrees;
}
int turnRightDeg(int degrees, int power) {

    // Initialize Variables
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;

    // Determine Tickgoal
    float ticksPerDeg = 1.758 * RotationalTextureGainFactor;
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

    return degrees;
}

/*
Face Compass Direction
*/
void faceNorth(Position &currentPosition, int power){

    int initialOrientation = currentPosition.orientation;

    // Readjust angle to vertical
    if((initialOrientation % 360) < 180){
        turnLeftDeg((initialOrientation % 360), power);
    }
    else {
        turnRightDeg(360 - (initialOrientation % 360), power);
    }

    currentPosition.orientation = 0;

    return; // Degrees
}
void faceSouth(Position &currentPosition, int power){

    int initialOrientation = currentPosition.orientation;

    // Readjust angle to vertical
    if((initialOrientation % 360) < 180){
        turnRightDeg(180 - (initialOrientation % 360), power);
    }
    else {
        turnLeftDeg((initialOrientation % 360) - 180, power);
    }

    currentPosition.orientation = 180;

    return; // Degrees
}
void faceEast(Position &currentPosition, int power){

    int initialOrientation = currentPosition.orientation;

    // Readjust angle to vertical
    if((initialOrientation % 360) < 90){
        turnRightDeg(90 - (initialOrientation % 360), power);
    }
    else {
        turnLeftDeg((initialOrientation % 360) - 90, power);
    }

    currentPosition.orientation = 90;

    return; // Degrees
}
void faceWest(Position &currentPosition, int power){

    int initialOrientation = currentPosition.orientation;

    // Readjust angle to vertical
    if((initialOrientation % 360) < 270){
        turnRightDeg(270 - (initialOrientation % 360), power);
    }
    else {
        turnLeftDeg((initialOrientation % 360) - 270, power);
    }

    currentPosition.orientation = 270;

    return; // Degrees
}


/*
Move Vertically To a specific Y coord
*/
void moveVerticallyTo(int goalYPos, Position &currentPosition, int power){

    if(currentPosition.y > goalYPos) { // ALV must move down
        faceSouth(currentPosition, power);
        while(currentPosition.y > goalYPos){
            moveDistanceCm(1, power);
            currentPosition.y -= 1;
            displayPosition(currentPosition);
        }
    }
    else { // ALV must move up
        faceNorth(currentPosition, power);
        while(currentPosition.y < goalYPos){
            moveDistanceCm(1, power);
            currentPosition.y += 1;
            displayPosition(currentPosition);
        }
    }

    return;
}

/*
Move Vertically To a specific Y coord
*/
void moveHorizontallyTo(int goalXPos, Position &currentPosition, int power){

    if(currentPosition.x > goalXPos) { // ALV must move west
        faceWest(currentPosition, power);
        while(currentPosition.x > goalXPos){
            moveDistanceCm(1, power);
            currentPosition.x -= 1;
            displayPosition(currentPosition);
        }
    }
    else { // ALV must move east
        faceEast(currentPosition, power);
        while(currentPosition.x < goalXPos){
            moveDistanceCm(1, power);
            currentPosition.x += 1;
            displayPosition(currentPosition);
        }
    }

    return;
}
