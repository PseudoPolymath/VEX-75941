#include "main.h"

bool clampState = true; // Clamp starts up
pros::Motor m_lift (20, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
pros::Motor m_clamp (19, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

int i = 0;
bool HT = false;

void dual_lift_control() {
    // Clamp is written as normal
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


    // Lift is written with torque hold code
    int current = m_lift.get_current_draw();
    int eff = m_lift.get_efficiency();
    int volt = m_lift.get_voltage();
    float torq = m_lift.get_torque();
    int temp = m_lift.get_temperature();

    
    
    i++;
    if(i > 3) {
        //std::cout << "Curr: \t" << current << " Eff: \t" << eff << " Volt: \t" << volt << " Torque: \t" << torq << " Temp: \t" << temp << std::endl;
        if(current > 2000) {
            //std::cout << "HIGH TORQUE MODE" << std::endl;
            HT = true;
        }
        i = 0;
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
        m_lift.move_velocity(255);
    } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        m_lift.move_velocity(-255);
        HT = false;
     } else { m_lift.move_velocity(0); }

    if(HT) {
        m_lift.move_velocity(255);
    }

    std::cout << "HT: " << HT << " \tCurrent: " << current << std::endl;
}