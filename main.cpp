
//main.cpp

#include <iostream>
#include "tool.h"

using namespace std;

int main() {
    int choice = -1;
    while(true) {
        cout << "=========��ӭ��������ϵͳ=========" << endl;
        cout << "---1.����Աģʽ---2.��ͨ�û�ģʽ---" << endl;
        cout << "-----------0.�˳�ϵͳ-----------" << endl;
        cout << "===============================" << endl;
        cout << "����������ѡ��:";
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
                        //�û���Ϣ¼��
                        if (ad.inputInfo()) {
                            break;
                        }
                    } else if (choice2 == 2) {
                        //�޸Ĺ���Ա����
                        if (ad.changePassword()) {
                            break;
                        }
                    } else if (choice2 == 3) {
                        //�޸�ָ���˻���Ϣ
                        ad.deleteUser();
                    } else if (choice2 == 4) {
                        //��Ϣ����ҵ��
                        ad.showInfo();
                    }else if(choice2 == 5) {
                        //��ʾ�˻�����
                        cout << "�û�������" << ad.userNumber() << endl;
                    }else if (choice2 == 0) {
                        break;
                    } else {
                        cout << "��������,����������" << endl;
                    }
                }


            }

        } else if (choice == 2) {

        } else if (choice == 0) {
            break;
        } else {
            cout << "��������,����������" << endl;
        }
    }

    return 0;
}
