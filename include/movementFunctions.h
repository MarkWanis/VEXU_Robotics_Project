#include <algorithm>
#include <cstdlib>

const double inPerDeg = 0.0489; // Inches traversed per degree of motor rotation
int targetDistIn = 10; 


// Returns lower value
int min(int num1, int num2)
{
    return (num1 < num2) ? (num1) : (num2);
}


// Returns higher value
int max(int num1, int num2)
{
    return (num1 > num2) ? (num1) : (num2);
}


// Calculates how far the robot has traveled in inches
double distTraveled()
{
    return rightFront.position(degrees) * inPerDeg; 
}


// Calculates degrees rotated from start angle
double degreesRotated(double start = 180)
{
    return Gyro.heading() - start;
}


// Changes gyro heading while keeping it in the range 0 <= "newHeading" < 360
double changeHeading(double newHeading)
{
    if (newHeading >= 360)
        return newHeading - 360;
    else if (newHeading < 0)
        return newHeading + 360;
    return newHeading;
}


// Resets the degrees counter for each motor
void resetMotorPos()
{
    leftFront.resetPosition();
    leftMid.resetPosition();
    leftBack.resetPosition();
    rightFront.resetPosition();
    rightMid.resetPosition();
    rightBack.resetPosition();
}


// Starts all the motors at the given percentage "speed", with default parameters "leftMotors" and "rightMotors" to control which side moves
void startMotors(int speed, bool leftMotors = true, bool rightMotors = true)
{
    // Starts left motors
    if (leftMotors)
    {
        leftFront.spin(forward, speed, percent);
        leftMid.spin(forward, speed, percent);
        leftBack.spin(forward, speed, percent); 
    }
    // Starts right motors
    if (rightMotors)
    {
        rightFront.spin(forward, speed, percent);
        rightMid.spin(forward, speed, percent);
        rightBack.spin(forward, speed, percent);
    }
}


// Stops all the motors, checking "hardStop" to see if it brakes or coasts
void stopMotors(bool hardStop = true)
{
    if (hardStop)
    {
        leftBack.stop(brake);
        leftMid.stop(brake);
        leftFront.stop(brake);
        rightBack.stop(brake);
        rightMid.stop(brake);
        rightFront.stop(brake);
    }
    else
    {
        leftBack.stop(coast);
        leftMid.stop(coast);
        leftFront.stop(coast);
        rightBack.stop(coast);
        rightMid.stop(coast);
        rightFront.stop(coast);
    }
}

/*
// Moves robot x inches in one direction, speeding up and slowing down at the start and end
void moveXDistance(double x) // 16
{
    int acc = 2,
        currVel = acc,
        delay = 50;
    double rampUpDist;

    resetMotorPos(); 

    // Speeds up robot to full speed or half distance
    while (currVel < 100 && distTraveled() < 0.5 * x) // < 8
    {
        startMotors(currVel);

        wait(delay, msec); 

        currVel = min(currVel + acc, 100); // Keeps velocity below or at 100 
    }

    rampUpDist = distTraveled(); // Records in inches how long it took to speed up 8

    waitUntil(distTraveled() > x - rampUpDist); // Coasts until it needs to brake >= 8

    // Slows down to stop or forces stop at x inches
    while (currVel > 0 && distTraveled() < x) // 
    {
        startMotors(currVel);

        wait(delay, msec); 

        currVel = max(currVel - acc, 0); // Keeps velocity above or at 0
    }

    stopMotors();


}
*/

// Moves robot endDist inches in one direction, speeding up and slowing down at the start and end
void moveDistance(double endDist) // 16
{
    double delay = 5,
        accelEnd = 0.25 * endDist;

    resetMotorPos(); 

    startMotors(5);
    wait(.3, sec);
    
    while (distTraveled() < accelEnd)
    {
        startMotors( 100 * ( distTraveled() / accelEnd ) );
        wait(delay, msec); 
    }

    while (distTraveled() < endDist)
    {
        startMotors( -100 * ( distTraveled() - endDist ) / (endDist-accelEnd) );
        wait(delay, msec); 
    }
}


// Rotates robot right 90 degrees CW
void turnRight(double endDegrees = 90)
{
    double delay = 10,
        startHeading = 180,
        endHeading = startHeading - endDegrees, // 90
        accelEnd = startHeading - 0.5 * endDegrees; // 135

    resetMotorPos(); 
    Gyro.setHeading(startHeading, degrees);

    startMotors(5, true, false);
    startMotors(-5, false, true);
    wait(.3, sec);

    while (Gyro.heading() > accelEnd) // 160 > 135
    {
        startMotors(100 * ( degreesRotated() / accelEnd ), true, false);
        startMotors(-100 * ( degreesRotated() / accelEnd ), false, true);
        wait(delay, msec); 
    }

    while (Gyro.heading() > endHeading) // 100 > 90
    {
        startMotors(-100 * ( degreesRotated() - endDegrees ) / (endDegrees-accelEnd), true, false);
        startMotors(100 * ( degreesRotated() - endDegrees ) / (endDegrees-accelEnd), false, true);
        wait(delay, msec); 
    }

    stopMotors();
}


void turnLeft(double endDegrees = 90)
{
    double delay = 10,
        accelEnd = 0.5 * endDegrees;

    resetMotorPos(); 
    //Gyro.setHeading() = 180;

    startMotors(5, false, true);
    startMotors(-5, true, false);
    wait(.3, sec);

    while (degreesRotated() < accelEnd) // 40 < 45
    {
        startMotors(100 * ( degreesRotated() / accelEnd ), false, true);
        startMotors(-100 * ( degreesRotated() / accelEnd ), true, false);
        wait(delay, msec); 
    }

    while (degreesRotated() < endDegrees)
    {
        startMotors(-100 * ( degreesRotated() - endDegrees ) / (endDegrees-accelEnd), false, true);
        startMotors(100 * ( degreesRotated() - endDegrees ) / (endDegrees-accelEnd), true, false);
        wait(delay, msec);
    }

    stopMotors();
}

/*
// Rotates robot right 90 degrees CW
void turnRight()
{
    
    Overview:
    Set heading to 180 degrees
    Increase rotation speed until max speed or half way
    Record x, where x is degree at which speed stopped increasing
    Coast until degree is at 180 + 90 - x
    Slow rotation until at 180 + 90 degrees
    Stop motors
    

    int acc = 2,
        currVel = acc,
        delay = 50;
    double rampUpAngle,
        startHeading = 180,
        endHeading = changeHeading(startHeading + 90); // 270 // Sets CW 90 degrees from the initial heading

    Gyro.setHeading(startHeading, degrees); // Sets Gyro heading to 180
    Controller.Screen.setCursor(10, 1);

    // Speeds up robot to full speed or half angle
    while (currVel < 100 && degreesRotated(startHeading) < 0.5 * (endHeading - startHeading)) // Ex: 30 < 0.5 * (270-180)
    {
        // Turns on motors 
        startMotors(currVel, true, false); 
        startMotors(-1*currVel, false, true);

        wait(delay, msec); 

        currVel = min(currVel + acc, 100); // Keeps velocity below or at 100 

        // printf("Current Velocity: ");
        // print("Gyro Heading: %f", Gyro.heading());

        Controller.Screen.clearScreen(); 
        Controller.Screen.print("Current Velocity:");
        //Brain.Screen.printAt(10, 20, "Gyro Heading: %f", Gyro.heading());
        
    }

    rampUpAngle = degreesRotated(startHeading); // Records in degrees how long it took to speed up

    //waitUntil(degreesRotated(startHeading) >= endHeading - rampUpAngle * .95); // Coasts until it needs to brake

    // Slows down to stop or forces stop at 90 degrees
    while (currVel > 0 && degreesRotated(startHeading) < (endHeading - startHeading)) // Ex: 90 < (270-180)
    {
        startMotors(currVel, true, false);
        startMotors(-1*currVel, false, true);

        wait(delay, msec); 

        currVel = max(currVel - acc, 0); // Keeps velocity above or at 0
        Brain.Screen.printAt(10, 20, "Gyro Heading: %f", Gyro.heading());
    }

    stopMotors();
}


// Rotates robot left 90 degrees CCW
void turnLeft()
{
    int acc = 2,
        currVel = acc,
        delay = 50;
    double rampUpAngle,
        startHeading = 180,
        endHeading = changeHeading(startHeading - 90); // Sets CW 90 degrees from the initial heading

    Gyro.setHeading(startHeading, degrees); 

    // Speeds up robot to full speed or half angle
    while (currVel < 100 && degreesRotated(startHeading) > 0.5 * (endHeading - startHeading))
    {
        startMotors(currVel, false, true);
        startMotors(-1*currVel, true, false);

        wait(delay, msec); 

        currVel = min(currVel + acc, 100); // Keeps velocity below or at 100 
    }

    rampUpAngle = degreesRotated(startHeading); // Records in degrees how long it took to speed up

    waitUntil(degreesRotated(startHeading) >= endHeading - rampUpAngle * .95); // Coasts until it needs to brake

    // Slows down to stop or forces stop at 90 degrees
    while (currVel > 0 && degreesRotated(startHeading) > (endHeading - startHeading))
    {
        startMotors(currVel, false, true);
        startMotors(-1*currVel, true, false);

        wait(delay, msec); 

        currVel = max(currVel - acc, 0); // Keeps velocity above or at 0
    }

    stopMotors();
}
*/

// Rotates robot 180 degrees CW directly behind
void turnAround()
{
    turnRight();
    turnRight();
}


void basicBackAndForth() 
{
    resetMotorPos();
    while(leftFront.position(degrees) < targetDistIn / inPerDeg){
        Brain.Screen.clearScreen();
        Brain.Screen.printAt(10, 20, "%f", rightBack.position(degrees));
        startMotors(10);
        wait(20, msec);
    }
    waitUntil(false);
}


void displayGyro()
{
    while (1) {
        Brain.Screen.clearScreen();
        Brain.Screen.printAt(10, 40, "Gyro: %f", Gyro.heading());
        wait(20, msec);
    }
}