
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
                // �û���Ϣ¼��
                ad.inputInfo();
                break;
            case 2:
                // �޸Ĺ���Ա����
                ad.changePassword();
                break;
            case 3:
                // �޸�ָ���˻���Ϣ
                ad.changeInfo();
                break;
            case 4:
                // ��Ϣ����ҵ��
                ad.showInfo();
                break;
            case 5:
                // ��ʾ�˻�����
                cout << "�û�������" << ad.userNumber() << endl;
                break;
            case 0:
                // �˳�����Աģʽ
                break;
            default:
                cout << "��������,����������" << endl;
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
                // ���
                user.save();
                break;
            case 2:
                // ȡ��
                user.take();
                break;
            case 3:
                // ����ѯ
                user.balance();
                break;
            case 4:
                // ת��
                user.transfer();
                break;
            case 5:
                // �޸���Ϣ
                user.changeInfo();
                break;
            case 6:
                // չʾ�û���Ϣ
                user.showInfo();
                break;
            case 0:
                // �˳��û�ģʽ
                break;
            default:
                cout << "��������,����������" << endl;
                break;
        }
    } while (userChoice != 0);
}

int main() {
    int choice;
    do {
        cout << "=========��ӭ��������ϵͳ=========" << endl;
        cout << "---1.����Աģʽ---2.��ͨ�û�ģʽ---" << endl;
        cout << "-----------0.�˳�ϵͳ-----------" << endl;
        cout << "===============================" << endl;
        cout << "����������ѡ��:";
        cin >> choice;
        switch (choice) {
            case 1:
                administratorMode();
                break;
            case 2:
                userMode();
                break;
            case 0:
                // �˳�ϵͳ
                cout << "��лʹ������ϵͳ���ټ�!" << endl;
                break;
            default:
                cout << "������������������" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
