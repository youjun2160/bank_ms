//
// Created by YUAN on 2024/4/9.
//

//tool.cpp

#include "tool.h"
#include <iostream>

using namespace std;



//����Ա���ʼ��
Administrators::Administrators() {
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
            head = new user;
        } else {
            head->next = newUser;
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