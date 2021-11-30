#include "main.h"
#include "motor.hpp"


void drivetrain(pros::Controller master) {
  if(ARCADE_TANK) {
    pros::Motor leftBack (LEFT_BACK_MOTOR, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
    pros::Motor leftFront (LEFT_FRONT_MOTOR, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
    pros::Motor rightBack (RIGHT_BACK_MOTOR, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
    pros::Motor rightFront (LEFT_FRONT_MOTOR, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

    int leftStick, rightStick;

    leftStick = master.get_analog(ANALOG_LEFT_Y);
    rightStick = master.get_analog(ANALOG_RIGHT_Y);

    leftBack = leftStick;
    leftFront = leftStick;
    rightBack = rightStick;
    rightFront = rightStick;
  }
}
