#include "vex.h"
#include "intake.h"
#include "aivision.h"
#include "driverControl.h"
#include "movementFunctions.h"


int main() 
{
    // Controller.ButtonA.pressed(toggleDriverControl);
    
    Gyro.calibrate();
    Brain.Screen.printAt(10, 20, "Gyro Calibrating");
    wait(3000, msec);
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(10, 20, "Calibration Complete");
    
    
    moveDistance(16);
    turnRight();
    turnLeft();
    
}
