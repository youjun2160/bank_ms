
//main.cpp

#include <iostream>
#include "tool.h"

using namespace std;

void administratorMode() {
    Administrators ad;
    if (!ad.checkIn()) {
        return;
    }
    int adminChoice;
    do {
        ad.uiShow();
        cin >> adminChoice;
        switch (adminChoice) {
            case 1:
                // 用户信息录入
                ad.inputInfo();
                break;
            case 2:
                // 修改管理员密码
                ad.changePassword();
                break;
            case 3:
                // 修改指定账户信息
                ad.changeInfo();
                break;
            case 4:
                // 信息管理业务
                ad.showInfo();
                break;
            case 5:
                // 显示账户数量
                cout << "用户数量：" << ad.userNumber() << endl;
                break;
            case 0:
                // 退出管理员模式
                break;
            default:
                cout << "输入有误,请重新输入" << endl;
                break;
        }
    } while (adminChoice != 0);
}

void userMode() {
    User user;
    if(!user.login()){
        return;
    }
    int userChoice;
    do {
        user.uiShow();
        cin >> userChoice;
        switch(userChoice) {
            case 1:
                // 存款
                user.save();
                break;
            case 2:
                // 取款
                user.take();
                break;
            case 3:
                // 余额查询
                user.balance();
                break;
            case 4:
                // 转账
                user.transfer();
                break;
            case 5:
                // 修改信息
                user.changeInfo();
                break;
            case 6:
                // 展示用户信息
                user.showInfo();
                break;
            case 0:
                // 退出用户模式
                break;
            default:
                cout << "输入有误,请重新输入" << endl;
                break;
        }
    } while (userChoice != 0);
}

int main() {
    int choice;
    do {
        cout << "=========欢迎来到银行系统=========" << endl;
        cout << "---1.管理员模式---2.普通用户模式---" << endl;
        cout << "-----------0.退出系统-----------" << endl;
        cout << "===============================" << endl;
        cout << "请输入您的选择:";
        cin >> choice;
        switch (choice) {
            case 1:
                administratorMode();
                break;
            case 2:
                userMode();
                break;
            case 0:
                // 退出系统
                cout << "感谢使用银行系统，再见!" << endl;
                break;
            default:
                cout << "输入有误，请重新输入" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
