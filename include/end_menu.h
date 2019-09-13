#ifndef END_MENU_H_INCLUDED
#define END_MENU_H_INCLUDED

#include<fstream>
#include<string>
#include<vector>
#include "for_use.h"

/** \brief 遊戲結束後出現的選單 */
void end_menu(int &endchoose)
{
/**
 *  先開啟檔案後，將檔案內容存入str內，再依使用者輸入的上或下更改str，最後輸出，
 *  並利用call by reference 更改endchoose的值
 * \param endchoose int&    儲存最後使用者選何種模式
 * \return void
 */
    fstream fin;
    string read_str;
    string str[30];
    int i=0,choose;
    fin.open("./note/end_menu.txt",ios::in);
    while(getline(fin,read_str))
    {
        str[i]=read_str;
        i++;
    }
    fin.close();
    for(int j=0;j<i;j++)
    {
        cout<<str[j]<<endl;
    }
    while(choose=getch())
    {
        if(choose==224)
        {
            choose=getch();
            if(choose==80)
            {
                if(endchoose<14)
                    endchoose+=2;
                else
                    endchoose=2;

                str[endchoose].replace(12,2,"->"); ///換成->

                for(int j=2;j<=14;j++)
                {
                    if(j!=endchoose)
                        str[j].replace(12,2,"  ");
                }
            }
            else if(choose==72)
            {
                if(endchoose>2)
                    endchoose-=2;
                else
                    endchoose=14;

                str[endchoose].replace(12,2,"->"); ///換成->

                for(int j=2;j<=14;j++)
                {
                    if(j!=endchoose)
                        str[j].replace(12,2,"  ");
                }
            }
        }
        else if(choose==13) ///輸入Enter鍵跳出
            break;

        for(int j=0;j<i;j++)
        {
            gotoxy(0,j);
            cout<<str[j]<<endl;
        }
    }
}

#endif // END_MENU_H_INCLUDED
