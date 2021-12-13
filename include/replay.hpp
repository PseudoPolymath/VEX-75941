#include "main.h"
#include <string>     // std::string, std::stoi

class VirtualController {
    public:
        int leftStick;
        int rightStick;
        int digLeft1;
        int digLeft2;
        int digRight;
};

class Record {
    public:
        FILE* writeFile;

    void init() {
        std::cout << "Initializing record..." << std::endl;
    }

    void record(pros::Controller master) {
        writeFile = fopen("/usd/recording1.txt", "a");
        std::string al = std::to_string(master.get_analog(ANALOG_LEFT_Y));
        std::string ar = std::to_string(master.get_analog(ANALOG_RIGHT_Y));

        std::string dr1 = std::to_string(master.get_digital(DIGITAL_R1));
        std::string dl1 = std::to_string(master.get_digital(DIGITAL_L1));
        std::string dl2 = std::to_string(master.get_digital(DIGITAL_L2));

        //Combine
        std::string lineOut = al + " " + ar + " " + dr1 + " " + dl1 + " " + dl2 + " ";
        std::cout << "Recorded: " << lineOut << std::endl;
        const char* pchar = lineOut.c_str();

        fputs(pchar, writeFile);
        fputs("\n", writeFile);
        fclose(writeFile);
    }

    void stopRecord() {
        
    }
};

class Replay {
    public:
        FILE* readFile;
        char buf[50000];
        char* lines[5000];
        std::string motorStrings[15000];
        VirtualController vc;

    int lineSplit(char *sentence) {
        std::string s = sentence;
        std::string delim = " ";

        size_t pos = 0;
        std::string token;
        int i = 0;

        while(pos = s.find(delim) != std::string::npos) {
            token = s.substr(0, pos);
            s.erase(0, pos + delim.length());
            i++;
        }

        return 0;
    }

    void start() {
        readFile = fopen("/usd/recording3.txt", "r");
        fread(buf, 1, 5000, readFile);
        fclose(readFile);

        std::cout << "File read" << std::endl;

        lineSplit(buf);

        int j = 0;
        while(true) {
            std::cout << motorStrings[j] << " " << motorStrings[j + 1] << std::endl;
            std::cout << motorStrings[j + 2] << " " << motorStrings[j + 3] << " " << motorStrings[j + 4] << std::endl;
        }

        vc.leftStick = std::stoi(motorStrings[j]);
        vc.rightStick = stoi(motorStrings[j + 1]);

        vc.digLeft1 = stoi(motorStrings[j + 2]);
        vc.digLeft2 = stoi(motorStrings[j + 3]);
        vc.digRight = stoi(motorStrings[j + 4]);
    }
};  