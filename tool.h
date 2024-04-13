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
        int balance;
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

    //析构函数
    ~Administrators();

    user *head = nullptr;
    user *tail = nullptr;
    int userNum;
};

class User {
public:
    typedef struct user {
        std::string account;
        std::string name;
        std::string password;
        std::string id;
        std::string phoneNumber;
        int balance;
        struct user *next;
        struct user *pre;
    } user;

    user *head = nullptr;
    user *tail = nullptr;
    user *curAccount = nullptr;

    //构造函数
    User();

    //快速导入用户信息
    bool importInfo();

    //快速导出用户信息
    bool exportInfo() const;

    //登录
    bool login();

    //ui展示
    void uiShow();

    //存款
    bool save();

    //取款
    bool take();

    //余额查询
    bool balance();

    //转账
    bool transfer();

    //修改信息
    bool changeInfo();

    //展示该用户所有信息
    bool showInfo();

    //析构函数
    ~User();
};

class bank {
public:
};

#endif //BANK_MS_TOOL_H

