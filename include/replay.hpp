#include "main.h"
#include <string> // std::string, std::stoi

struct VirtualController
    {
        int leftTank = 0;
        int rightTank = 0;
        int suck = 0;
        int spit = 0;
        int lift = 0;
    };

class Record
{
public:
    FILE *writeFile;

    void init()
    {
        std::cout << "Initializing record..." << std::endl;
    }

    void record(pros::Controller master)
    {
        writeFile = fopen("/usd/fancy34.txt", "a");
        std::string al = std::to_string(master.get_analog(ANALOG_LEFT_Y));
        std::string ar = std::to_string(master.get_analog(ANALOG_RIGHT_Y));

        std::string dr1 = std::to_string(master.get_digital(DIGITAL_R1));
        std::string dl1 = std::to_string(master.get_digital(DIGITAL_L1));
        std::string dl2 = std::to_string(master.get_digital(DIGITAL_L2));

        //Combine
        std::string lineOut = al + " " + ar + " " + dr1 + " " + dl1 + " " + dl2 + " ";
        std::cout << lineOut << std::endl;
        const char *pchar = lineOut.c_str();

        fputs(pchar, writeFile);
        fputs("\n", writeFile);
        fclose(writeFile);
    }

    void stopRecord()
    {
    }
};

class Replay
{
public:
    FILE *readFile;
    char buf[100000];
    std::string bufStr;
    std::vector<VirtualController> bufVec;
    int index = 0;

    std::vector<std::string> split_string(const std::string &str,
                                          const std::string &delimiter)
    {
        std::vector<std::string> strings;

        std::string::size_type pos = 0;
        std::string::size_type prev = 0;
        while ((pos = str.find(delimiter, prev)) != std::string::npos)
        {
            strings.push_back(str.substr(prev, pos - prev));
            prev = pos + 1;
        }

        // To get the last substring (or only, if delimiter is not found)
        strings.push_back(str.substr(prev));

        return strings;
    }

    std::vector<VirtualController> parse_input(const std::string &input)
    {
        std::vector<VirtualController> controllers;
        std::vector<std::string> lines = split_string(input, "\n");

        for (int i = 0; i < lines.size(); i++)
        {
            std::vector<std::string> tokens = split_string(lines[i], " ");
            VirtualController controller;
            if (tokens.size() == 6)
            {
                controller.leftTank = std::stoi(tokens[0]);
                controller.rightTank = std::stoi(tokens[1]);
                controller.suck = std::stoi(tokens[2]);
                controller.spit = std::stoi(tokens[3]);
                controller.lift = std::stoi(tokens[4]);
                controllers.push_back(controller);

                std::cout << "Parsed frame: " << i << std::endl;
            }
        }

        return controllers;
    }

    void init()
    {
        std::cout << "Initializing replay..." << std::endl;

        readFile = fopen("/usd/fancy34.txt", "r");
        fread(buf, sizeof(char), 100000, readFile);

        bufStr = std::string(buf);

        bufVec = parse_input(bufStr);

        std::cout << "Replay initialized" << std::endl;
    }

    void replay()
    {
        if (index > bufVec.size())
        {
            std::cout << "Replay ended" << std::endl;
        }
        else
        {
            std::cout << "Replaying tank: Left: " << bufVec.at(index).leftTank << " Right: " << bufVec.at(index).rightTank << std::endl;
            set_tank(bufVec.at(index).leftTank, bufVec.at(index).rightTank);

            if(bufVec.at(index).spit == 1)
            {
                tilter_in();
            }

            if(bufVec.at(index).lift == 1)
            {
                tilter_out();
            }
            
        }

        index++;
    }
};