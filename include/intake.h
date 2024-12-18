// Intake Mech
bool intakeMech = 0;
bool intakeMechDirection = 0;
bool directionSwitch = 0;
int intakeSpeed = 0;
int intakeMaxSpeed = 100;

void ringRelease(){
    intakeMech = !intakeMech;
}

// AI Vision Intake
std::vector<double> intakePower;
double intakePowerAvg = 0.0;

// Intake Functions
void intakeIn(){
    intakeSpeed = intakeSpeed > 0 ? 0 : intakeMaxSpeed;
}

void intakeOut(){
    intakeSpeed = intakeSpeed < 0 ? 0 : -intakeMaxSpeed;
}