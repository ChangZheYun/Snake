#ifndef START_MENU_H_INCLUDED
#define START_MENU_H_INCLUDED

#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include "for_use.h"
using namespace std;

/** \brief 遊戲一開始出現的選單 */
void start_menu(int &endchoose)
{
/**
 *  先開啟檔案後，將檔案內容存入str內，再依使用者輸入的上或下更改str，最後輸出，
 *  並利用call by reference 更改endchoose的值
 * \param endchoose int&
 * \return void
 */
    int choose;
    int num=0;
    int row=12;
    fstream fin;
    string str[200];
    string readfile;
    fin.open("./note/start_menu.txt",ios::in);

    while(getline(fin,readfile))
    {
        str[num]=readfile;
        num++;
    }
    fin.close();

    for(int j=0;j<num;j++)
    {
        for(int k=0;k<str[j].length();k++)
        {
            if(j>2 && j<8 && k>2 && k<str[j].length()-2)
                SetColor(14);
            cout<<str[j][k];
            SetColor(7);
        }
        cout<<endl;
    }

    while(choose=getch())
    {
        if(choose==224)
        {
            choose=getch();
            if(choose==80)
            {
                if(row<20)
                    row+=2;
                else
                    row=12;
                str[row].replace(19,2,"->"); ///換成->
                for(int j=12;j<=20;j++)
                {
                    if(j!=row)
                        str[j].replace(19,2,"  ");
                }
            }
            else if(choose==72)
            {
                if(row>12)
                    row-=2;
                else
                    row=20;

                str[row].replace(19,2,"->"); ///換成->
                for(int j=12;j<=20;j++)
                {
                    if(j!=row)
                        str[j].replace(19,2,"  ");
                }
            }
        }
        else if(choose==13)
            break;

        for(int j=11;j<num;j++)
        {
            gotoxy(0,j);
            cout<<str[j]<<endl;
        }
    }
    system("cls");

    if(row==12) ///mode
        endchoose=2;
    else if(row==14)
        endchoose=6;
    else if(row==16) ///rank
        endchoose=8;
    else if(row==18)
        endchoose=10;
    else if(row==20)
        endchoose=12;

    return;
}


#endif // START_MENU_H_INCLUDED
