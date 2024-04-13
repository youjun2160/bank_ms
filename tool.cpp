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

    cout << "����Աģʽ������" << endl;
    cout << "��ʼͬ������" << endl;
    if(importInfo()){
        cout << "ͬ�����" << endl;
    } else {
        cout << "ͬ��ʧ��" << endl;
    }

    //���û��userInformation.txt�ļ����ʹ���
    string fp3 = "userInformation.txt";
    if (!filesystem::exists(fp3)) {
        ofstream ofile("userInformation.txt");
        ofile.close();
    }
}

//����Աģʽui��ʾ
void Administrators::uiShow() {
    cout << "===========����Աģʽ===========" << endl;
    cout << "1.�û���Ϣ¼��" << endl;
    cout << "2.�޸Ĺ���Ա����" << endl;
    cout << "3.�޸�ָ���˻���Ϣ" << endl;
    cout << "4.��ʾ�����û���Ϣ" << endl;
    cout << "5.��ʾ�˻�����" << endl;
    cout << "0.�˳�����Աģʽ" << endl;
    cout << "==============================" << endl;
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
        newUser->balance = 0;
        cout << "=============================" << endl;

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
            ofile << newUser->account << " " << newUser->name << " " << newUser->password << " " << newUser->id << " " << newUser->phoneNumber << " " << newUser->balance << endl;
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
            cout << "�û�ɾ���ɹ���" << endl;

        ofstream ofile("userNum.txt");
        if (ofile.is_open()){
            ofile << userNum;
            ofile.close();
        }

        ofile.open("userInformation2.txt");
        if (ofile.is_open()){
            user *temp = head;
            while(temp != nullptr) {
                ofile << temp->account << " " << temp->name << " " << temp->password << " " << temp->id << " " << temp->phoneNumber << " " << temp->balance << endl;
                temp = temp->next;
            }
            ofile.close();
            remove("userInformation.txt");
            rename("userInformation2.txt", "userInformation.txt");
        }

}

//���ٵ����û���Ϣ
bool Administrators::importInfo() {
    user *temp = head;

    ifstream ifile("userInformation.txt");
    if(!ifile.is_open()) {
        cout << "�ļ���ʧ�ܣ�" << endl;
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
        newUser->balance = stoi(tempStr.substr(0, tempStr.find(' ')));
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

//չʾ�����û���Ϣ
bool Administrators::showInfo() {
    if (userNum == 0) {
        cout << "�����û���Ϣ" << endl;
        return true;
    }
    user *temp = head;
    cout << "=========================" << endl;
    cout << "�����û���Ϣ���£�" << endl;
    while(temp != nullptr) {
        cout << "�˺ţ�" << temp->account << endl;
        cout << "�û�����" << temp->name << endl;
        cout << "���룺" << temp->password << endl;
        cout << "���֤�ţ�" << temp->id << endl;
        cout << "�绰���룺" << temp->phoneNumber << endl;
        cout << "��" << temp->balance << endl;
        if (temp->next != nullptr){
            cout << "------------------------" << endl;
        }
        temp = temp->next;
    }
    cout << "=========================" << endl;
    return true;
}

//�޸��˻���Ϣ
bool Administrators::changeInfo() {
    cout << "������Ҫ�޸ĵ��˺�:" << endl;
    string account;
    cin >> account;

    //��λ��ָ���˻�
    user *temp = head;
    while(temp != nullptr) {
        if (temp->account == account) {
            break;
        }
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "�û������ڣ�" << endl;
        return false;
    }

    while(true) {
        cout << "=========================" << endl;
        cout << "��ѡ��Ҫ�޸ĵ�����:" << endl;
        cout << "1.�޸��û���" << endl;
        cout << "2.�޸�����" << endl;
        cout << "3.�޸����֤��" << endl;
        cout << "4.�޸ĵ绰����" << endl;
        cout << "5.ɾ�����û�" << endl;
        cout << "0.����" << endl;
        cout << "����������ѡ��:";
        int choice;
        cin >> choice;
        cout << "=========================" << endl;
        switch (choice) {
            case 1:
                cout << "���������û���:" << endl;
                cin >> temp->name;
                break;
            case 2:
                cout << "������������:" << endl;
                cin >> temp->password;
                break;
            case 3:
                cout << "�����������֤��:" << endl;
                cin >> temp->id;
                break;
            case 4:
                cout << "�������µ绰����:" << endl;
                cin >> temp->phoneNumber;
                break;
            case 5:
                deleteUser(temp);
            case 0:
                return true;
            default:
                cout << "������������������" << endl;
                break;

        }
        if(choice != 5) {
            ofstream ofile("userInformation2.txt");
            if(!ofile.is_open()) {
                cout << "�ļ���ʧ�ܣ�" << endl;
                return true;
            }

            while(temp != nullptr) {
                ofile << temp->account << " " << temp->name << " " << temp->password << " " << temp->id << " " << temp->phoneNumber << endl;
                temp = temp->next;
            }
            ofile.close();

            remove("userInformation.txt");
            rename("userInformation2.txt", "userInformation.txt");

            return true;
        }
    }
}

//��������
Administrators::~Administrators() {
    //������Ϣ
    ofstream ofile("userInformation.txt");
    if(!ofile.is_open()) {
        cout << "�ļ���ʧ�ܣ�" << endl;
        return;
    }
    user *temp = head;
    while(temp != nullptr) {
        ofile << temp->account << " " << temp->name << " " << temp->password << " " << temp->id << " " << temp->phoneNumber << " " << temp->balance << endl;
        temp = temp->next;
    }
    ofile.close();

    //�ͷ��ڴ�
    user *temp2 = head;
    while(temp2 != nullptr) {
        head = temp2->next;
        delete temp2;
        temp2 = head;
    }
}

//==================================================================================================================================================

//���캯��
User::User() {
    head = nullptr;
    tail = nullptr;

    if (importInfo()) {
        cout << "�û���Ϣ����ɹ���" << endl;
    }
}

//���ٵ����û���Ϣ
bool User::importInfo() {
    ifstream ifile;
    ifile.open("userInformation.txt");
    if (!ifile) {
        cout << "�ļ���ʧ�ܣ�" << endl;
        return false;
    }
    string tempStr;
    while(getline(ifile, tempStr)) {
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
        newUser->balance = stoi(tempStr.substr(0, tempStr.find(' ')));
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

//���ٵ����û���Ϣ
bool User::exportInfo() {
    ofstream ofile("userInformation.txt");
    if (!ofile.is_open()) {
        cout << "�ļ���ʧ�ܣ�" << endl;
        return false;
    }
    user *temp = head;
    while(temp != nullptr) {
        ofile << temp->account << " " << temp->name << " " << temp->password << " " << temp->id << " " << temp->phoneNumber << " " << temp->balance << endl;
        temp = temp->next;
    }
    ofile.close();
    return true;
}

//��¼
bool User::login() {
    //�ж��Ƿ����û�
    if (head == nullptr) {
        cout << "û���û���Ϣ����������û���Ϣ" << endl;
        return false;
    }


    cout << "�������˺�:" << endl;
    string account;
    cin >> account;
    cout << "����������:" << endl;
    string password;
    cin >> password;
    user *temp = head;
    while(temp != nullptr) {
        if (account == temp->account && password == temp->password) {
            cout << "��¼�ɹ���" << endl;
            curAccount = temp;
            return true;
        } else if(account == temp->account && password != temp->password) {
            cout << "������������������" << endl;
            return false;
        }
        temp = temp->next;
    }
    cout << "���˺Ų�����" << endl;
    return false;
}

//uiչʾ
void User::uiShow() {
    cout << "=========��ӭ��������ϵͳ=========" << endl;
    cout << "1.���" << endl;
    cout << "2.ȡ��" << endl;
    cout << "3.����ѯ" << endl;
    cout << "4.ת��" << endl;
    cout << "5.�޸���Ϣ" << endl;
    cout << "6.չʾ�û���Ϣ" << endl;
    cout << "0.�˳�" << endl;
    cout << "===============================" << endl;
    cout << "����������ѡ��:";
}

//���
bool User::save() {
    cout << "����������:" << endl;
    int money;
    cin >> money;
    curAccount->balance += money;
    cout << "���ɹ���" << endl;
    return true;
}

//ȡ��
bool User::take() {
    cout << "������ȡ����:" << endl;
    int money;
    cin >> money;
    if (money > curAccount->balance) {
        cout << "���㣬����������" << endl;
        return false;
    }
    curAccount->balance -= money;
    cout << "ȡ��ɹ���" << endl;
    return true;
}

//����ѯ
bool User::balance() {
    cout << "��ǰ��" << curAccount->balance << endl;
    return true;
}

//ת��
bool User::transfer() {
    cout << "������ת�˽��:" << endl;
    int money;
    cin >> money;
    if (money > curAccount->balance) {
        cout << "���㣬����������" << endl;
        return false;
    }
    cout << "������Է��˺�:" << endl;
    string account;
    cin >> account;
    user *temp = head;
    while(temp != nullptr) {
        if (account == temp->account) {
            temp->balance += money;
            curAccount->balance -= money;
            cout << "ת�˳ɹ���" << endl;
            return true;
        }
        temp = temp->next;
    }
    cout << "���˺Ų�����" << endl;
    return false;
}

//�޸���Ϣ
bool User::changeInfo() {
    cout << "�������޸ĺ����Ϣ" << endl;
    cout << "������" << endl;
    string name;
    cin >> name;
    cout << "���룺" << endl;
    string password;
    cin >> password;
    cout << "���֤�ţ�" << endl;
    string id;
    cin >> id;
    cout << "�ֻ����룺" << endl;
    string phoneNumber;
    cin >> phoneNumber;
    curAccount->name = name;
    curAccount->password = password;
    curAccount->id = id;
    curAccount->phoneNumber = phoneNumber;
    cout << "�޸ĳɹ���" << endl;
    return true;
}

//չʾ���û�������Ϣ
bool User::showInfo() {
    user *temp = head;
    while(temp != nullptr) {
        if (temp->account == curAccount->account) {
            cout << "�˺ţ�" << temp->account << endl;
            cout << "������" << temp->name << endl;
            cout << "���룺" << temp->password << endl;
            cout << "���֤�ţ�" << temp->id << endl;
            cout << "�ֻ����룺" << temp->phoneNumber << endl;
            cout << "��" << temp->balance << endl;
            return true;
        }
        temp = temp->next;
    }
    return true;
}

//��������
User::~User() {

    //���û���Ϣ������ļ�
    if(exportInfo()) {
        cout << "�û���Ϣ����ɹ���" << endl;
    }

    //�ͷ��ڴ�
    user *temp = head;
    while(temp != nullptr) {
        user *delUser = temp;
        temp = temp->next;
        delete delUser;
    }
}