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
        struct user *pre;
    } user;

    std::string password = "123456";
    Administrators();
    void uiShow();
    bool checkIn();
    bool inputInfo();
    int userNumber();

    //修改密码
    bool changePassword();

    //删除用户
    void deleteUser(user *delUser);

    //快速导入用户信息
    bool importInfo();

    //展示所有用户信息
    bool showInfo();

    //修改用户信息
    bool changeInfo();

    user *head = nullptr;
    user *tail = nullptr;
    int userNum;
};

class user {
public:
};

class bank {
public:
};

#endif //BANK_MS_TOOL_H

