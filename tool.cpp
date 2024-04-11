//
// Created by YUAN on 2024/4/9.
//

//tool.cpp

#include "tool.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;



//����Ա���ʼ��
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

//����Աģʽui��ʾ
void Administrators::uiShow() {
    cout << "==========����Աģʽ==========" << endl;
    cout << "1.�û���Ϣ¼��" << endl;
    cout << "2.�޸Ĺ���Ա����" << endl;
    cout << "3.�޸�ָ���˻���Ϣ" << endl;
    cout << "4.��Ϣ����ҵ��" << endl;
    cout << "5.��ʾ�˻�����" << endl;
    cout << "0.�˳�����Աģʽ" << endl;
    cout << "============================" << endl;
    cout << "����������ѡ��:";
}

//�ж�����������Ƿ���ȷ
bool Administrators::checkIn() {
    cout << "���������Ա���룺" << endl;
    string password;
    cin >> password;
    //�ж������Ƿ���ȷ������ȷ���˳�����Աϵͳ
    if (password != this->password) {
        cout << "�������" << endl;
        return false;
    }
    return true;
}

//�û���Ϣ¼��
bool Administrators::inputInfo() {
    while (true) {
        user *newUser = new user;

        if (newUser == nullptr) {
            cout << "�ڴ����ʧ��" << endl;
            return false;
        }

        cout << "��ǰ�û�����:" << userNumber() << endl;
        cout << "==========�û���Ϣ¼��==========" << endl;
        cout << "�������û���Ϣ:" << endl;
        cout << "�˺�:" << endl;
        cin >> newUser->account;
        cout << "����:" << endl;
        cin >> newUser->name;
        cout << "����:" << endl;
        cin >> newUser->password;
        cout << "���֤��:" << endl;
        cin >> newUser->id;
        cout << "�绰����:" << endl;
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

        //���û���Ϣд���ļ�
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

        cout << "-----------¼��ɹ�------------" << endl;

        while(true){
            cout << "�Ƿ�Ҫ����¼���û���Ϣ(y/n):" << endl;
            char choice;
            cin >> choice;
            if (choice == 'n' || choice == 'N') {
                return false;
            } else if (choice == 'y' || choice == 'Y') {
                break;
            } else {
                cout << "��������,����������" << endl;
            }
        }

    }
}

//��ѯ��ǰ�û�����
int Administrators::userNumber() {
    return userNum;
}

//�޸Ĺ���Ա����
bool Administrators::changePassword() {
    cout << "�����������:" << endl;
    string oldPassword;
    cin >> oldPassword;
    if (oldPassword != password) {
        cout << "���������" << endl;
        return false;
    }
    cout << "������������:" << endl;
    string newPassword;
    cin >> newPassword;
    password = newPassword;

    ofstream ofile("admin.txt");
    if(ofile.is_open()) {
        ofile << password;
        ofile.close();
    }

    cout << "�����޸ĳɹ���" << endl;
    return false;
}


//ɾ���û�
bool Administrators::deleteUser() {
    cout << "������Ҫɾ�����˺�:" << endl;
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
            cout << "�û�ɾ���ɹ���" << endl;
            break;
        } else {
            temp = temp->next;
        }
    }

    if (x == 0) {
        cout << "�û������ڣ�" << endl;
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