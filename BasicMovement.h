// Define Dimentions (cm)
#define diameter 8
#define circumference (diameter * 3.14159)

/*
Move forwards a set distance in mm.
*/
task moveDistanceMm(int distanceMm, int power) {
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
}

/*
Move forwards a set distance in cm.
*/
task moveDistanceCm(int distanceCm, int power) {
    moveDistanceCm(distance * 10, power);
}
