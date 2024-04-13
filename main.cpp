
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
                        ad.changeInfo();
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
                if (choice2 == 0){
                    break;
                }
            }

        } else if (choice == 2) {
            User user;
            if(!user.login()){
                continue;
            }
                while(true){
                    user.uiShow();
                    cin >> choice;
                    switch(choice){
                        case 1:
                            //存款
                            user.save();
                            break;
                        case 2:
                            //取款
                            user.take();
                            break;
                        case 3:
                            //余额查询
                            user.balance();
                            break;
                        case 4:
                            //转账
                            user.transfer();
                            break;
                        case 5:
                            //修改信息
                            user.changeInfo();
                            break;
                        case 6:
                            //展示用户信息
                            user.showInfo();
                            break;
                        case 0:
                            break;
                        default:
                            cout << "输入有误,请重新输入" << endl;
                            break;
                    }
                    if(choice == 0){
                        break;
                    }
                }


        } else if (choice == 0) {
            break;
        } else {
            cout << "输入有误,请重新输入" << endl;
        }
    }

    return 0;
}
