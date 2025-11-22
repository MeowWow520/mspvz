#pragma once

#ifndef LOGOUTPUT_H
#define LOGOUTPUT_H
#include <iostream>
#include <string>
#include <ctime>



class LogOutput {
public:
    static void PrintfCurrentTime() {
        time_t CurrentTime;
        time(&CurrentTime);
        std::string String_CurrentTime = ctime(&CurrentTime);
        String_CurrentTime.erase(std::remove(String_CurrentTime.begin(), String_CurrentTime.end(), '\n'), String_CurrentTime.end());
        std::cout << "[" + String_CurrentTime + "]  ";
    }
protected:
    LogOutput() = default;
    ~LogOutput() = default;
private:
};
#endif // !LOGOUTPUT_H
