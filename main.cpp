
//main.cpp

#include <iostream>
#include "tool.h"

using namespace std;

int main() {
    int choice = -1;
    while(true) {
        cout << "=========欢迎来到银行系统=========" << endl;
        cout << "---1.管理员模式---2.普通用户模式---" << endl;
        cout << "-----------0.退出系统-----------" << endl;
        cout << "===============================" << endl;
        cout << "请输入您的选择:";
        cin >> choice;
        if (choice == 1) {
            while(true) {
                Administrators ad;
                cout << "请输入管理员密码：" << endl;
                string password;
                cin >> password;
                //判断密码是否正确，不正确则退出管理员系统
                if (!ad.checkPassword(password)) {
                    cout << "密码错误！" << endl;
                    break;
                }
                int choice2 = -1;
                while(true) {
                    ad.uiShow();
                    cin >> choice2;
                    if (choice2 == 1) {
                        //用户信息录入
                    } else if (choice2 == 2) {
                        //修改管理员密码
                    } else if (choice2 == 3) {
                        //修改指定账户信息
                    } else if (choice2 == 4) {
                        //信息管理业务
                    } else if (choice2 == 0) {
                        break;
                    } else {
                        cout << "输入有误,请重新输入" << endl;
                    }
                }


            }

        } else if (choice == 2) {

        } else if (choice == 0) {
            break;
        } else {
            cout << "输入有误,请重新输入" << endl;
        }
    }

    return 0;
}
