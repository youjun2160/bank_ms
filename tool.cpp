//
// Created by YUAN on 2024/4/9.
//

//tool.cpp

#include "tool.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;



//管理员类初始化
Administrators::Administrators() {
    string fp = "admin.txt";
    if (!filesystem::exists(fp)) {
        ofstream ofile("admin.txt");
        ofile << "123456";
        ofile.close();
    }

    ifstream ifile("admin.txt");
    if (ifile.is_open()) {
        ifile >> password;
        ifile.close();
    }

    string fp2 = "userNum.txt";
    if (!filesystem::exists(fp2)) {
        ofstream ofile("userNum.txt");
        ofile << "0";
        ofile.close();
    }

    ifstream ifile2("userNum.txt");
    if (ifile2.is_open()) {
        ifile2 >> userNum;
        ifile2.close();
    }

    cout << "管理员模式已启动" << endl;
    cout << "开始同步数据" << endl;
    if(importInfo()){
        cout << "同步完成" << endl;
    } else {
        cout << "同步失败" << endl;
    }
}

//管理员模式ui显示
void Administrators::uiShow() {
    cout << "===========管理员模式===========" << endl;
    cout << "1.用户信息录入" << endl;
    cout << "2.修改管理员密码" << endl;
    cout << "3.修改指定账户信息" << endl;
    cout << "4.信息管理业务" << endl;
    cout << "5.显示账户数量" << endl;
    cout << "0.退出管理员模式" << endl;
    cout << "==============================" << endl;
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

        cout << "当前用户数量:" << userNumber() << endl;
        cout << "===========用户信息录入===========" << endl;
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
        cout << "==============================" << endl;

        if(head == nullptr) {
            head = newUser;
            tail = newUser;
            head->pre = nullptr;
        } else {
            tail->next = newUser;
            newUser->pre = tail;
            tail = newUser;
        }
        newUser->next = nullptr;

        //将用户信息写入文件
        ofstream ofile("userInformation.txt", ios::app);
        if(ofile.is_open()) {
            ofile << newUser->account << " " << newUser->name << " " << newUser->password << " " << newUser->id << " " << newUser->phoneNumber << endl;
            ofile.close();
        }

        user *temp = head;
        userNum = 0;
        while(temp != nullptr) {
            userNum++;
            temp = temp->next;
        }
        ofstream ofile2("userNum.txt");
        if(ofile2.is_open()) {
            ofile2 << userNum;
            ofile2.close();
        }

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

//查询当前用户个数
int Administrators::userNumber() {
    return userNum;
}

//修改管理员密码
bool Administrators::changePassword() {
    cout << "请输入旧密码:" << endl;
    string oldPassword;
    cin >> oldPassword;
    if (oldPassword != password) {
        cout << "旧密码错误！" << endl;
        return false;
    }
    cout << "请输入新密码:" << endl;
    string newPassword;
    cin >> newPassword;
    password = newPassword;

    ofstream ofile("admin.txt");
    if(ofile.is_open()) {
        ofile << password;
        ofile.close();
    }

    cout << "密码修改成功！" << endl;
    return false;
}


//删除用户
void Administrators::deleteUser(user *delUser) {
            if (delUser == head) {
                head = delUser->next;
                if (head != nullptr) {
                    head->pre = nullptr;
                }
                delete delUser;
            } else if (delUser == tail) {
                tail = delUser->pre;
                tail->next = nullptr;
                delete delUser;
            } else {
                delUser = delUser->pre;
                user *temp2 = delUser->next;
                delUser->next = temp2->next;
                temp2->next->pre = delUser;
                delete temp2;
            }
            userNum--;
            cout << "用户删除成功！" << endl;

        ofstream ofile("userNumb.txt");
        if (ofile.is_open()){
            ofile << userNum;
            ofile.close();
        }

        ofile.open("userInformation2.txt");
        if (ofile.is_open()){
            user *temp = head;
            while(temp != nullptr) {
                ofile << temp->account << " " << temp->name << " " << temp->password << " " << temp->id << " " << temp->phoneNumber << endl;
                temp = temp->next;
            }
            ofile.close();
            remove("userInformation.txt");
            rename("userInformation2.txt", "userInformation.txt");
        }

}

//快速导入用户信息
bool Administrators::importInfo() {
    user *temp = head;

    ifstream ifile("userInformation.txt");
    if(!ifile.is_open()) {
        cout << "文件打开失败！" << endl;
    }

    string tempStr;
    while(std::getline(ifile, tempStr)) {
        user *newUser = new user;
        newUser->account = tempStr.substr(0, tempStr.find(' '));
        tempStr = tempStr.substr(tempStr.find(' ') + 1);
        newUser->name = tempStr.substr(0, tempStr.find(' '));
        tempStr = tempStr.substr(tempStr.find(' ') + 1);
        newUser->password = tempStr.substr(0, tempStr.find(' '));
        tempStr = tempStr.substr(tempStr.find(' ') + 1);
        newUser->id = tempStr.substr(0, tempStr.find(' '));
        tempStr = tempStr.substr(tempStr.find(' ') + 1);
        newUser->phoneNumber = tempStr.substr(0, tempStr.find(' '));
        tempStr = tempStr.substr(tempStr.find(' ') + 1);
        if (head == nullptr) {
            head = newUser;
            tail = newUser;
            head->pre = nullptr;
        } else {
            tail->next = newUser;
            newUser->pre = tail;
            tail = newUser;
        }
    }
    ifile.close();
    return true;
}

bool Administrators::showInfo() {
    user *temp = head;
    cout << "=========================" << endl;
    cout << "所有用户信息如下：" << endl;
    while(temp != nullptr) {
        cout << "账号：" << temp->account << endl;
        cout << "用户名：" << temp->name << endl;
        cout << "密码：" << temp->password << endl;
        cout << "身份证号：" << temp->id << endl;
        cout << "电话号码：" << temp->phoneNumber << endl;
        if (temp->next != nullptr){
            cout << "------------------------" << endl;
        }
        temp = temp->next;
    }
    cout << "=========================" << endl;
    return true;
}

//修改账户信息
bool Administrators::changeInfo() {
    cout << "请输入要修改的账号:" << endl;
    string account;
    cin >> account;

    //定位至指定账户
    user *temp = head;
    while(temp != nullptr) {
        if (temp->account == account) {
            break;
        }
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "用户不存在！" << endl;
        return false;
    }

    while(true) {
        cout << "1.修改用户名" << endl;
        cout << "2.修改密码" << endl;
        cout << "3.修改身份证号" << endl;
        cout << "4.修改电话号码" << endl;
        cout << "5.删除该用户" << endl;
        cout << "0.返回" << endl;
        cout << "请输入您的选择:";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "请输入新用户名:" << endl;
                cin >> temp->name;
                break;
            case 2:
                cout << "请输入新密码:" << endl;
                cin >> temp->password;
                break;
            case 3:
                cout << "请输入新身份证号:" << endl;
                cin >> temp->id;
                break;
            case 4:
                cout << "请输入新电话号码:" << endl;
                cin >> temp->phoneNumber;
                break;
            case 5:
                deleteUser(temp);
            case 0:
                return true;
            default:
                cout << "输入有误，请重新输入" << endl;
                break;

        }
        if(choice != 5) {

        }
    }
}