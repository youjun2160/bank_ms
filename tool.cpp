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


}

//管理员模式ui显示
void Administrators::uiShow() {
    cout << "==========管理员模式==========" << endl;
    cout << "1.用户信息录入" << endl;
    cout << "2.修改管理员密码" << endl;
    cout << "3.修改指定账户信息" << endl;
    cout << "4.信息管理业务" << endl;
    cout << "5.显示账户数量" << endl;
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

        cout << "当前用户数量:" << userNumber() << endl;
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
bool Administrators::deleteUser() {
    cout << "请输入要删除的账号:" << endl;
    string account;
    cin >> account;
    user *temp = head;
    int x = 0;
    while(temp != nullptr) {
        if (temp->account == account) {
            x = 1;
            if (temp == head) {
                head = temp->next;
                if (head != nullptr) {
                    head->pre = nullptr;
                }
                delete temp;
            } else if (temp == tail) {
                tail = temp->pre;
                tail->next = nullptr;
                delete temp;
            } else {
                temp = temp->pre;
                user *temp2 = temp->next;
                temp->next = temp2->next;
                temp2->next->pre = temp;
                delete temp2;
            }
            userNum--;
            cout << "用户删除成功！" << endl;
            break;
        } else {
            temp = temp->next;
        }
    }

    if (x == 0) {
        cout << "用户不存在！" << endl;
    } else {
        ofstream ofile("userNumber.txt");
        if (ofile.is_open()){
            ofile << userNum;
            ofile.close();
        }

        ofile.open("userInformation2.txt");
        if (ofile.is_open()){
            temp = head;
            while(temp != nullptr) {
                ofile << temp->account << " " << temp->name << " " << temp->password << " " << temp->id << " " << temp->phoneNumber << endl;
                temp = temp->next;
            }
            ofile.close();
            remove("userInformation.txt");
            rename("userInformation2.txt", "userInformation.txt");
        }
    }
    return true;
}