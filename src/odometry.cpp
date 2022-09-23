#include "main.h"

void tracking () {
    double sL = 7; //horizontal distance from the traking center to left encoder
    double sR = 7; //horizontal distance from the traking center to right encoder
    double sS = 7; //vertical distance from the traking center to horizontal encoder
    double x = 10; //initial/current global x position
    double y = 10; //initial/current global y position
    double rd; //polar radius of position vector
    double thetad; //polar theta of position vector
    double rL = 7; //radius of left encoder
    double rR = 7; //radius of right encoder
    double rS = 7; //radius of horizontal encoder
    double theta1 = 0; //previous global orientation
    double theta2; //current global orientation
    double thetaR = 0; //global position at last reset
    double LR = 0; //initial left encoder value
    double RR = 0; //initial right encoder value
    double SR = 0; //initial horizontal encoder value
    double L1 = 0; //previous left encoder value
    double R1 = 0; //previous right encoder value
    double S1 = 0; //previous horizontal encoder value
    double L2; //current left encoder value
    double R2; //current right encoder value
    double S2; //current horizonal encoder value
    double dTheta; //change in orientation
    double thetaM; //average orientation
    double dx; //change in x position
    double dy; //change in y position
    double dL; //change in left encoder distance
    double dR; //change in right encoder distance
    double dS; //change in horizontal encoder distance
    double dLR; //change in left encoder distance since last reset
    double dRR; //change in right encoder distance since last reset
    double dSR; //change in horizontal encoder distance since last reset
    

    pros::ADIEncoder encoderL (1, 2, false);
    pros::ADIEncoder encoderR (3, 4, false);
    pros::ADIEncoder encoderS (5, 6, false);

    while (true) {
        //get values
        L2 = encoderL.get_value();
        R2 = encoderR.get_value();
        S2 = encoderS.get_value();
        //convert to radians and calculate arc length
        L2 = (L2/180) * M_PI * rL;
        R2 = (R2/180) * M_PI * rR;
        S2 = (S2/180) * M_PI * rS;
        //calculate deltas
        dL = L2 - L1;
        dR = R2 - R1;
        dS = S2 - S1;
        //calculate deltas since last reset
        dLR = L2 - LR;
        dRR = R2 - RR;
        dSR = S2 - SR;
        //set final to initial
        L1 = L2;
        R1 = R2;
        S1 = S2;
        //calculate current orientation
        theta2 = thetaR - ((dLR - dRR) / (sL + sR));
        //calculate delta theta
        dTheta = theta2 - theta1;
        //calculate average orientation
        thetaM = theta1 - (dtheta/2);
        //set final to initial
        theta1 = theta2;
        if (dTheta = 0) {
            //no change in orientation
            dx = dS;
            dy = dR;
            //convert to polar coordinates
            thetad = atan2(dy, dx);
            rd = sqrt(pow(dy, 2) + pow(dx, 2);
            //rotate local coordinates to global coordinates
            thetad = thetad - thetaM;
            //convert to cartestian coordinates
            dx = cos(thetad) * rd;
            dy = sin(thetad) * rd;
        } else {
            //change in orientation
            dx = 2 * sin(dTheta / 2) * ((dS / dTheta) + sS);
            dy = 2 * sin(dTheta / 2) * ((dR / dTheta) + rS);
            //convert to polar coordinates
            thetad = atan2(dy, dx);
            rd = sqrt(pow(dy, 2) + pow(dx, 2);
            //rotate local coordinates to global coordinates
            thetad = thetad - thetaM;
            //convert to cartestian coordinates
            dx = cos(thetad) * rd;
            dy = sin(thetad) * rd;
        }
        x = x + dx;
        y = y + dy;
        /*Outputs:
        x = global x position
        y = global y position
        theta1 = global orientation
        */
    }
}