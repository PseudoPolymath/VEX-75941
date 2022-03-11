#include "main.h"

bool clampState = true; // Clamp starts up
pros::Motor m_lift (20, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);
pros::Motor m_clamp (19, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);

int i = 0;
bool HT = false;

void dual_lift_control() {
    // Clamp is written as normal
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        clampState = !clampState;
        pros::delay(100);
        std::cout << "Clamp State: " << clampState << std::endl;
    }

    if(clampState) {
        m_clamp.move_absolute(0, 127);
    } else {
        m_clamp.move_absolute(-150, 127);
    }


    // Lift is written with torque hold code
    int current = m_lift.get_current_draw();
    int eff = m_lift.get_efficiency();
    int volt = m_lift.get_voltage();
    float torq = m_lift.get_torque();
    int temp = m_lift.get_temperature();

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        m_lift.move_velocity(255);
    } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
        m_lift.move_velocity(-255);
        HT = false;
     } else { m_lift.move_velocity(0); }

    std::cout << " \tCurrent: " << current << std::endl;
}