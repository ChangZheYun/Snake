#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<ctime>
#include<windows.h>
#include<conio.h>
#include "menu.h"
#include "board.h"
#include "snake.h"
#include "start_menu.h"
#include "mission.h"
#include "readfile.h"
#include "end_menu.h"
#include "for_use.h"
using namespace std;

///�Ʀr���:
///snake_walk_to/direction: 1.�W 2.�k 3.�� 4.�U
///difficult: 1.Easy 2.Normal 3.Hard 4.Challenge
///Map[x][y]: 0.�i�樫�� -1.��� -2.ī�G -3.��ê�� other:�D��
///situation/behavior: 1.�樫 2.�Yī�G 3.����ê�� 4.���D�� 5.�����

void ConsoleFullScreen()
{
/** \brief ������ù�
 * \return void
 */
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0);
    keybd_event(VK_RETURN,0x9c,KEYEVENTF_KEYUP,0);
}

void SetColor(int color=7)
{
/** \brief �����C��
 * \param color=7 int
 * \return void
 */
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,color);
}

/** \brief ����ù�DOS�����j�p */
console con(100, 50 );

int main()
{
    ///ConsoleFullScreen(); Windows10�H�U�L�k���ù�
    int endchoose=4;
    int row=10;
    string name;

    do
    {
        system("cls");

        srand(time(NULL)); ///�ü�
        menu control;

        if(endchoose==4)
        {
            cout<<endl;
            SetColor(207);
            cout<<"                                                                     "<<endl;
            cout<<" If the window is too small , please adjust to the appropriate size. "<<endl;
            cout<<"                                                                     "<<endl;

            while(1)   ///��J�m�W
            {
                SetColor(14); ///����
                cout<<endl;
                cout<<" Input your name : ";
                getline(cin,name);
                if(name.length()>12)
                {
                    SetColor(252);
                    cout<<endl<<" Warning ";
                    SetColor(12);
                    cout<<" Your name is more than 12 characters."<<endl;
                    cout<<"          Please input again."<<endl;
                }
                else if(name.length()==0)
                {
                    SetColor(252);
                    cout<<endl<<" Warning ";
                    SetColor(12);
                    cout<<" Your name is at least 0 character."<<endl;
                    cout<<"          Please input again."<<endl;
                }
                else
                    break;
            }
            SetColor(7); ///�^�_����C��
            system("cls");
            start_menu(endchoose); ///�I�s�e��

        }
        control.set_name(name);
        if(endchoose==2)
        {
            row=10;
            readfile(endchoose,row);
            if(row==12)     ///Easy
                control.mode(1);
            else if(row==14) ///Normal
                control.mode(2);
            else if(row==16) ///Hard
                control.mode(3);
            else if(row==18) ///Challenge
                control.mode(4);
        }
        if(endchoose==6)
        {
            row=12;
            readfile(endchoose,row);
            if(row==12)     ///Easy
                control.ranking(1);
            else if(row==14) ///Normal
                control.ranking(2);
            else if(row==16) ///Hard
                control.ranking(3);
            else if(row==18) ///Challenge
                control.ranking(4);
        }
        if(endchoose==8)
        {
            control.output_mission();
        }
        if(endchoose==10)
        {
            row=18;
            readfile(endchoose,row);
        }
        if(endchoose==12)
        {
            row=20;
            readfile(endchoose,row);
            if(row==8)
                control.develop(1);
            else if(row==10)
                control.develop(2);
            else if(row==12)
                control.develop(3);
            else if(row==14)
                control.develop(4);
            else if(row==16)
                control.develop(5);
        }
        cout<<endl;
        system("pause");
        system("cls");

        endchoose=2;
        end_menu(endchoose);

    }while(endchoose!=14);

    return 0;
}
