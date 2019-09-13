#ifndef READ_H_INCLUDED
#define READ_H_INCLUDED

#include<string>
#include "for_use.h"

/** \brief 選單，讓使用者選擇模式(mode、rank、developer)  */
void read(string *str,int &row,int num,int endchoose)
{
/**
 * 依照readfile送進來start_menu使用者選擇的資料，輸出選單讓使用者選擇。
 * \param str string*    儲存txt檔內資料
 * \param row int&       判斷選單內使用者是選擇甚麼模式(第二層)
 * \param num int        txt檔內有幾行資料
 * \param endchoose int  判斷是選擇mode、rank、developer(第一層)
 * \return void
 */
    if(row<=12)
    {
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
        row=12;
    }
    else
    {
        for(int j=0;j<num;j++)
        {
            cout<<str[j]<<endl;
        }
        row=8;
    }
    int choose;
    while(choose=getch())
    {
        if(choose==224)
        {
            choose=getch();
            if(endchoose<=6)
            {
                if(choose==80)
                {
                    if(row<18)
                        row+=2;
                    else
                        row=12;
                    str[row].replace(20,2,"->");
                    for(int j=12;j<=18;j++)
                    {
                        if(j!=row)
                            str[j].replace(20,2,"  ");
                    }
                }
                else if(choose==72)
                {
                    if(row>12)
                        row-=2;
                    else
                        row=18;
                    str[row].replace(20,2,"->");
                    for(int j=12;j<=18;j++)
                    {
                        if(j!=row)
                            str[j].replace(20,2,"  ");
                    }
                }

                for(int j=11;j<num;j++)
                {
                    gotoxy(0,j);
                    cout<<str[j];
                }
            }
            else if(endchoose==12)
            {
                if(choose==80)
                {
                    if(row<16)
                        row+=2;
                    else
                        row=8;
                    str[row].replace(20,2,"->");
                    for(int j=8;j<=16;j++)
                    {
                        if(j!=row)
                            str[j].replace(20,2,"  ");
                    }
                }
                else if(choose==72)
                {
                    if(row>8)
                        row-=2;
                    else
                        row=16;
                    str[row].replace(20,2,"->");
                    for(int j=8;j<=16;j++)
                    {
                        if(j!=row)
                            str[j].replace(20,2,"  ");
                    }
                }
                for(int j=0;j<num;j++)
                {
                    gotoxy(0,j);
                    cout<<str[j]<<endl;
                }
            }
        }
        else if(choose==13)
            break;

    }
    system("cls");
}
#endif // READ_H_INCLUDED
