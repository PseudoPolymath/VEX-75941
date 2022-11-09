#ifndef Odometry_H
#define Odometry_H

class Odometry {
    private:
    double xPos = 10; //global x position
    double yPos = 10; //global y position
    double orientation = 0; //global orientation
    
    public:
    Odometry(double x, double y, double theta);
    void tracking();
    void turn(double degrees);
    void turnToPoint(double targetX, double targetY);
};

#endif