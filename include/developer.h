#ifndef DEVELOPER_H_INCLUDED
#define DEVELOPER_H_INCLUDED

#include<fstream>
#include<string>
#include<vector>
#include "for_use.h"

void developer()
{
    fstream fin;
    string read_str;
    string origin_str[30],str[30];
    int i=0,choose;
    fin.open("./note/develop.txt",ios::in);
    while(getline(fin,read_str))
    {
        origin_str[i]=read_str;
        str[i]=read_str;
        i++;
    }
    fin.close();
    for(int j=0;j<i;j++)
    {
        cout<<origin_str[j]<<endl;
    }
    while(choose=getch())
    {
        if(choose==224)
        {
            choose=getch();
            if(choose==80)
            {
                if(endchoose<12)
                    endchoose+=2;
                else
                    endchoose=2;

                str[endchoose].replace(12,2,"->"); ///換成->

                for(int j=2;j<=12;j++)
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
                    endchoose=12;

                str[endchoose].replace(12,2,"->"); ///換成->

                for(int j=2;j<=12;j++)
                {
                    if(j!=endchoose)
                        str[j].replace(12,2,"  ");
                }
            }
        }
        for(int j=0;j<i;j++)
        {
            gotoxy(0,j);
            cout<<str[j]<<endl;
        }
        for(int j=0;j<i;j++)
        {
            str[j]=origin_str[j];
        }
        if(choose==13)
            break;
    }
}

#endif // DEVELOPER_H_INCLUDED
