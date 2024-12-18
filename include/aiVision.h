// AIVision Rotation
double maxRotationSpeed = 30.0;
int rotationTolerance = 4;
int rotationSpeed = 0;
double rotationTargetValue = 202.0;

// AIVision Movement
double maxBackwardSpeed = 50.0;
double maxForwardSpeed = 60.0;
int movementTolerance = 5;
int movementSpeed = 0;
double movementTargetValue = 45;

// Alignment variables
bool alignment = false;

// Speed Formulas
double rotationSpeedFormula(int x){
    double distance = (double)abs(x - (int)rotationTargetValue);
    //printf("%f\n", pow(distance, 2));
    return pow(distance, 2) * (maxRotationSpeed / pow(rotationTargetValue, 2));
}

double movementSpeedFormula(int x, bool close){
    double distance = (double)abs(x - (int)movementTargetValue);
    if (close){
        return pow(distance, 2) * (maxBackwardSpeed / pow(100 - movementTargetValue, 2)) > maxBackwardSpeed ? maxBackwardSpeed :
        pow(distance, 2) * (maxBackwardSpeed / pow(100 - movementTargetValue, 2));
    }
    return pow(distance, 2) * (maxForwardSpeed / pow(movementTargetValue - 10, 2));
    //return distance * (maxForwardSpeed / (double)(movementTargetValue - 10));
}