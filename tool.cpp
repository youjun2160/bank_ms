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

}

//����Աģʽui��ʾ
void Administrators::uiShow() {
    cout << "==========����Աģʽ==========" << endl;
    cout << "1.�û���Ϣ¼��" << endl;
    cout << "2.�޸Ĺ���Ա����" << endl;
    cout << "3.�޸�ָ���˻���Ϣ" << endl;
    cout << "4.��Ϣ����ҵ��" << endl;
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
        } else {
            tail->next = newUser;
        }
        newUser->next = nullptr;

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
    int number = 0;
    user *temp = head;
    while(temp != nullptr) {
        number++;
        temp = temp->next;
    }
    return number;
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