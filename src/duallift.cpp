#include "main.h"

bool clampState = true; // Clamp starts up
pros::Motor m_lift (20, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);
pros::Motor m_clamp (19, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

void dual_lift_control() {
    
    

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        clampState = !clampState;
        pros::delay(200);
        std::cout << "Clamp State: " << clampState << std::endl;
    }

    if(clampState) {
        m_clamp.move_absolute(0, 127);
    } else {
        m_clamp.move_absolute(-130, 127);
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        m_lift.move_velocity(127);
    } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        m_lift.move_velocity(-127);
     } else { m_lift.move_velocity(0); }


}