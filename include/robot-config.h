using namespace vex;

// Global Variables

// Brain used for printing to the V5 brain screen
brain Brain;

// Initializes controller
controller Controller(primary);

// Initializes motors
motor leftBack = motor(PORT13, ratio18_1, true);
motor leftMid = motor(PORT12, ratio18_1, true);
motor leftFront = motor(PORT11, ratio18_1, true);
motor rightBack = motor(PORT18, ratio18_1, false);
motor rightMid = motor(PORT19, ratio18_1, false);
motor rightFront = motor(PORT20, ratio18_1, false);
//motor arm = motor(PORT13, ratio18_1, false);
//motor intake = motor(PORT10, ratio18_1, true);

// Initializes gyro
inertial Gyro(PORT15);

