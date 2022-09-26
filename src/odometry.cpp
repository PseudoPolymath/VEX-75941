#include "main.h"

void tracking() {
    double distanceLeftEncoder = 7; //horizontal distance from the traking center to left encoder
    double distanceRightEncoder = 7; //horizontal distance from the traking center to right encoder
    double distanceBackEncoder = 7; //vertical distance from the traking center to horizontal encoder
    double xPos = 10; //initial/current global x position
    double yPos = 10; //initial/current global y position
    double radiusPos; //polar radius of position vector
    double thetaPos; //polar theta of position vector
    double radiusLeft = 7; //radius of left encoder
    double radiusRight = 7; //radius of right encoder
    double radiusBack = 7; //radius of horizontal encoder
    double orientation; //global orientation
    double orientationInitial = 0; //previous global orientation
    double orientationFinal; //current global orientation
    double orientationReset = 0; //global position at last reset
    double leftValueReset = 0; //initial left encoder value
    double rightValueReset = 0; //initial left encoder value
    double leftValueInitial = 0; //previous left encoder value
    double rightValueInitial = 0; //previous right encoder value
    double backValueInitial = 0; //previous horizontal encoder value
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
    

    pros::ADIEncoder encoderL (1, 2, false);
    pros::ADIEncoder encoderR (3, 4, false);
    pros::ADIEncoder encoderS (5, 6, false);

    while (true) {
        //get values
        leftValueFinal = encoderL.get_value();
        rightValueFinal = encoderR.get_value();
        backValueFinal = encoderS.get_value();
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
    }
}

void turn(double degrees) {

}

void turnToPoint() {

}

void moveToPoint() {
    //haha...no
}