#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED

#include<string>
#include<fstream>
#include "read.h"

/** \brief 讀取檔案 */
void readfile(int &endchoose,int &row)
{
/**
 *  依照選擇讀取檔案，將資料輸進str內再傳給read。
 * \param endchoose int&  儲存使用者輸入何種模式(mode、rank、menual、developer)送給read使用
 * \param row int&        判斷要開啟何種檔案(這裡也可用endchoose判斷，只是row比較方便一點)
 * \return void
 */
    string readfile;
    fstream fin;
    string str[200];
    int num=0;

    if(row==10)
        fin.open("./note/mode_menu.txt",ios::in);
    else if(row==12)
        fin.open("./note/rank_menu.txt",ios::in);
    else if(row==18)
        fin.open("./note/manual.txt",ios::in);
    else if(row==20)
        fin.open("./note/developer.txt",ios::in);

    while(getline(fin,readfile))
    {
        if(endchoose==10)
        {
            cout<<readfile<<endl;
        }
        str[num]=readfile;
        num++;
    }
    fin.close();

    if(row<=12 || row==20)
        read(str,row,num,endchoose);
}

#endif // READFILE_H_INCLUDED
