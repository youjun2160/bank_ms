//
// Created by YUAN on 2024/4/9.
//

//tool.h

#ifndef BANK_MS_TOOL_H
#define BANK_MS_TOOL_H

#include <string>

class Administrators {
public:
    typedef struct user {
        std::string account;
        std::string name;
        std::string password;
        std::string id;
        std::string phoneNumber;
        struct user *next;
    } user;

    std::string password = "123456";
    Administrators();
    void uiShow();
    bool checkIn();
    bool inputInfo();
    int userNumber();

    //修改密码
    bool changePassword();

    user *head = nullptr;
    user *tail = nullptr;
};

class user {
public:
};

class bank {
public:
};

#endif //BANK_MS_TOOL_H

