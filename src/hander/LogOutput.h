#pragma once

#ifndef LOGOUTPUT_H
#define LOGOUTPUT_H
#include <iostream>
#include <string>
#include <ctime>



class LogOutput {

public:
    LogOutput() = default;
    ~LogOutput() = default;

    static void PrintfCurrentTime() {
        time_t CurrentTime;
        time(&CurrentTime);
        std::string StringCurrentTime = ctime(&CurrentTime);
        StringCurrentTime.erase(
            std::remove(
                StringCurrentTime.begin(),
                StringCurrentTime.end(),
                '\n'
            ),
            StringCurrentTime.end()
        );
        std::cout << "[" + StringCurrentTime + "]  ";
    }

protected:

private:
    
};
#endif // !LOGOUTPUT_H
