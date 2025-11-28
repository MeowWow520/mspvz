#pragma once

#ifndef LOGOUTPUT_H
#define LOGOUTPUT_H
#include <iostream>
#include <string>
#include <ctime>



/** LogOutPut.h 提供输出日志的函数
 * 
 *  保存日志到文件等功能
 */
class LogOutput {

public:
    LogOutput() = default;
    ~LogOutput() = default;
    // 函数 -- 输出当前时间
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
        std::cout << '[' + StringCurrentTime + "]  ";
    }

protected:

private:
    
};
#endif // !LOGOUTPUT_H
