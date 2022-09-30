#include "main.h"

class Odometry {
    public:
    double xPos = 10; //global x position
    double yPos = 10; //global y position
    double orientation = 0; //global orientation
    
    void tracking();
    void turn(double degrees);
    void turnToPoint(double targetX, double targetY);
};

void Odometry::tracking() {
    pros::ADIEncoder encoderLeft (1, 2, false);
    pros::ADIEncoder encoderRight (3, 4, false);
    pros::ADIEncoder encoderBack (5, 6, false);
    
    double distanceLeftEncoder = 7; //horizontal distance from the traking center to left encoder
    double distanceRightEncoder = 7; //horizontal distance from the traking center to right encoder
    double distanceBackEncoder = 7; //vertical distance from the traking center to horizontal encoder
    double radiusPos; //polar radius of position vector
    double thetaPos; //polar theta of position vector
    double radiusLeft = 7; //radius of left encoder
    double radiusRight = 7; //radius of right encoder
    double radiusBack = 7; //radius of horizontal encoder
    double orientationInitial = orientation; //previous global orientation
    double orientationFinal; //current global orientation
    double orientationReset = orientation; //global position at last reset
    double leftValueReset = encoderLeft.get_value(); //initial left encoder value
    double rightValueReset = encoderRight.get_value(); //initial left encoder value
    double leftValueInitial = encoderLeft.get_value(); //previous left encoder value
    double rightValueInitial = encoderRight.get_value(); //previous right encoder value
    double backValueInitial = encoderBack.get_value(); //previous horizontal encoder value
    double leftValueFinal; //current left encoder value
    double rightValueFinal; //current right encoder value
    double backValueFinal; //current horizonal encoder value
    double deltaOrientation; //change in orientation
    double averageOrientation; //average orientation
    double deltaXPos; //change in x position
    double deltaYPos; //change in y position
    double deltaRightValue; //change in right encoder distance
    double deltaBackValue; //change in horizontal encoder distance
    double deltaLeftValueReset; //change in left encoder distance since last reset
    double deltaRightValueReset; //change in right encoder distance since last reset
    
    while (true) {
        //get values
        leftValueFinal = encoderLeft.get_value();
        rightValueFinal = encoderRight.get_value();
        backValueFinal = encoderBack.get_value();
        //convert to radians and calculate arc length
        leftValueFinal = (leftValueFinal/180) * M_PI * radiusLeft;
        rightValueFinal = (rightValueFinal/180) * M_PI * radiusRight;
        backValueFinal = (backValueFinal/180) * M_PI * radiusBack;
        //calculate deltas
        deltaRightValue = rightValueFinal - rightValueInitial;
        deltaBackValue = backValueFinal - backValueInitial;
        //calculate deltas since last reset
        deltaLeftValueReset = leftValueFinal - leftValueReset;
        deltaRightValueReset = rightValueFinal - rightValueReset;
        //set final to initial
        leftValueInitial = leftValueFinal;
        rightValueInitial = rightValueFinal;
        backValueInitial = backValueFinal;
        //calculate current orientation
        orientationFinal = orientationReset - ((deltaLeftValueReset - deltaRightValueReset) / (distanceLeftEncoder + distanceRightEncoder));
        //calculate delta theta
        deltaOrientation = orientationFinal - orientationInitial;
        //calculate average orientation
        averageOrientation = orientationInitial - (deltaOrientation/2);
        //set orienationFinal to output
        orientation = orientationFinal;
        //set final to initial
        orientationInitial = orientationFinal;
        if (deltaOrientation = 0) {
            //no change in orientation
            deltaXPos = deltaBackValue;
            deltaYPos = deltaRightValue;
            //convert to polar coordinates
            thetaPos = atan2(deltaYPos, deltaXPos);
            radiusPos = sqrt(pow(deltaYPos, 2) + pow(deltaXPos, 2);
            //rotate local coordinates to global coordinates
            thetaPos = thetaPos - averageOrientation;
            //convert to cartestian coordinates
            deltaXPos = cos(thetad) * radiusPos;
            deltaYPos = sin(thetad) * radiusPos;
        } else {
            //change in orientation
            deltaXPos = 2 * sin(deltaOrientation / 2) * ((deltaBackValue / deltaOrientation) + distanceBackEncoder);
            deltaYPos = 2 * sin(deltaOrientation / 2) * ((deltaRightValue / deltaOrientation) + distanceRightEncoder);
            //convert to polar coordinates
            thetaPos = atan2(deltaYPos, deltaXPos);
            radiusPos = sqrt(pow(deltaYPos, 2) + pow(deltaXPos, 2);
            //rotate local coordinates to global coordinates
            thetaPos = thetaPos - averageOrientation;
            //convert to cartestian coordinates
            deltaXPos = cos(thetad) * radiusPos;
            deltaYPos = sin(thetad) * radiusPos;
        }
        xPos = xPos + deltaXPos;
        yPos = yPos + deltaYPos;
        
        /*Outputs:
        xPos = global x position
        yPos = global y position
        orientation = global orientation
        */
       pros::delay(20);
    }
}

void Odometry::turn(double degrees) {
    double Kp = 1; //proportional constant
    double Ki = 1; //integral constant
    double Kd = 1; //derivative constant
    bool targetOrientation;
    double error1;
    double error2;
    double lastError1;
    double derivative1;
    double integral1;
    double derivative2;
    double integral2;

    while (targetOrientation = false) {
        error1 = left_mtr_1.get_position() - right_mtr_1.get_position();
        error2 = left_mtr_2.get_position() - right_mtr_2.get_position();
        integral1 = integral1 + error1
        derivative1 = error - lasterror
        
    }
}

void Odometry::turnToPoint(double targetX, double targetY) {

}

void Odometry::moveToPoint() {
    //haha...no
}
