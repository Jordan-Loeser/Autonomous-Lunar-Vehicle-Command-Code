// Define Dimentions (cm)
#define PI 4 * atan(1.0)
#define diameter 8
#define circumference (diameter * PI)

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
void turnLeftDeg(int degrees, int power) {

    // Initialize Variables
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorB] = 0;

    // Determine Tickgoal
    float ticksPerDeg = 1.758;
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

    return;
}
