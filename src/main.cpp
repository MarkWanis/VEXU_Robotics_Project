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
    
<<<<<<< HEAD
    startMotors(20);
=======
    
    startMotors(20);
    //wait(5, sec);
>>>>>>> f7c6cc55271544f0cfb963b48c42f862e1632609
    //moveDistance(16);
    //turnRight();
    //turnLeft();
    
}
