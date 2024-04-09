//
// Created by YUAN on 2024/4/9.
//

//tool.h

#ifndef BANK_MS_TOOL_H
#define BANK_MS_TOOL_H

#include <string>

class Administrators {
public:
    std::string password = "123456";
    void uiShow();
    bool checkPassword(std::string password);
};

class user {
public:
};

class bank {
public:
};

#endif //BANK_MS_TOOL_H

