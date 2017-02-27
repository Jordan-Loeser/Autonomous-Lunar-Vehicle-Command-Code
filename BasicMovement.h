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
