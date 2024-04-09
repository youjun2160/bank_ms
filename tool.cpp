//
// Created by YUAN on 2024/4/9.
//

//tool.cpp

#include "tool.h"
#include <iostream>

using namespace std;

void Administrators::uiShow() {
    cout << "==========管理员模式==========" << endl;
    cout << "1.用户信息录入" << endl;
    cout << "2.修改管理员密码" << endl;
    cout << "3.修改指定账户信息" << endl;
    cout << "4.信息管理业务" << endl;
    cout << "0.退出管理员模式" << endl;
    cout << "============================" << endl;
    cout << "请输入您的选择:";
}

bool Administrators::checkPassword(std::string password) {
    if (password == this->password) {
        return true;
    } else {
        return false;
    }
}