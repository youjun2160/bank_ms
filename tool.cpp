//
// Created by YUAN on 2024/4/9.
//

//tool.cpp

#include "tool.h"
#include <iostream>

using namespace std;



//管理员类初始化
Administrators::Administrators() {
}

//管理员模式ui显示
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

//判断输入的密码是否正确
bool Administrators::checkIn() {
    cout << "请输入管理员密码：" << endl;
    string password;
    cin >> password;
    //判断密码是否正确，不正确则退出管理员系统
    if (password != this->password) {
        cout << "密码错误！" << endl;
        return false;
    }
    return true;
}

//用户信息录入
bool Administrators::inputInfo() {
    while (true) {
        user *newUser = new user;

        if (newUser == nullptr) {
            cout << "内存分配失败" << endl;
            return false;
        }

        cout << "==========用户信息录入==========" << endl;
        cout << "请输入用户信息:" << endl;
        cout << "账号:" << endl;
        cin >> newUser->account;
        cout << "姓名:" << endl;
        cin >> newUser->name;
        cout << "密码:" << endl;
        cin >> newUser->password;
        cout << "身份证号:" << endl;
        cin >> newUser->id;
        cout << "电话号码:" << endl;
        cin >> newUser->phoneNumber;
        cout << "============================" << endl;

        if(head == nullptr) {
            head = new user;
        } else {
            head->next = newUser;
        }
        newUser->next = nullptr;

        cout << "-----------录入成功------------" << endl;

        while(true){
            cout << "是否要继续录入用户信息(y/n):" << endl;
            char choice;
            cin >> choice;
            if (choice == 'n' || choice == 'N') {
                return false;
            } else if (choice == 'y' || choice == 'Y') {
                break;
            } else {
                cout << "输入有误,请重新输入" << endl;
            }
        }

    }
}