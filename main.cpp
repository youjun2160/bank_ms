
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
                if (!ad.checkIn()) {
                    break;
                }
                int choice2 = -1;
                while(true) {
                    ad.uiShow();
                    cin >> choice2;
                    if (choice2 == 1) {
                        //用户信息录入
                        if (ad.inputInfo()) {
                            break;
                        }
                    } else if (choice2 == 2) {
                        //修改管理员密码
                        if (ad.changePassword()) {
                            break;
                        }
                    } else if (choice2 == 3) {
                        //修改指定账户信息
                        ad.deleteUser();
                    } else if (choice2 == 4) {
                        //信息管理业务
                        ad.showInfo();
                    }else if(choice2 == 5) {
                        //显示账户数量
                        cout << "用户数量：" << ad.userNumber() << endl;
                    }else if (choice2 == 0) {
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
