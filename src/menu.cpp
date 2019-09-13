#include "menu.h"
#include "board.h"
#include "snake.h"
#include "scoreboard.h"
#include "for_use.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<conio.h>
#include<stdio.h>
#include<ctime>
#include<windows.h>
#include<fstream>
#include<vector>

using namespace std;


void gotoxy(int xpos, int ypos)
{
/**
 *  gotoxy讓游標移動到x,y位置繪製
 * \param xpos int
 * \param ypos int
 * \return void
 */
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}

menu::menu():The_Map(40,40),greedy(4,4,3)
{
/**
 *  設定最大地圖及蛇的預設位置
 */
    behavior=1;
}

void menu::set_name(string user_name)
{
/**
 *  設定使用者名稱、成就系統建立玩家資料、成就系統建立那筆玩家的所有成就
 * \param user_name string 傳入使用者輸入的名字
 * \return void
 */
    name=user_name;
    achieve.establish_player(name);
    achieve.establish_mission();
}

void menu::mode(int hard_choose)
{
/**
 *  依照選擇更動difficult，並更改地圖大小(start)，呼叫combine讓board擁有蛇身位置，
 *  再呼叫in_running開始遊戲，遊戲結束後將該玩家成績紀錄至排行榜，並判斷該場完成哪些成就，
 *  最後呼叫output_score輸出成績及該場完成的成就
 * \param hard_choose int 傳入選擇的模式
 * \return void
 */
    switch(hard_choose)
    {
        case 1:
            difficult=1;
            break;
        case 2:
            difficult=2;
            break;
        case 3:
            difficult=3;
            break;
        case 4:
            difficult=4;
            break;
    }
    start();
    combine();
    in_running();

    switch(difficult)
    {
        case 1:
            score.into_easy(greedy.get_snakelong(),name);
            break;
        case 2:
            score.into_normal(greedy.get_snakelong(),name);
            break;
        case 3:
            score.into_hard(greedy.get_snakelong(),name);
            break;
        case 4:
            score.into_challenge(greedy.get_snakelong(),name);
            break;
    }
    achieve.endagame(difficult,greedy.get_snakelong());
    output_score();
}

void menu::ranking(int hard_choose)
{
/**
 *  依照選擇呼叫output_scoreboard輸出排行榜
 * \param hard_choose int 傳入選擇的模式
 * \return void
 */
    switch(hard_choose)
    {
        case 1:
            output_scoreboard(1);
            break;
        case 2:
            output_scoreboard(2);
            break;
        case 3:
            output_scoreboard(3);
            break;
        case 4:
            output_scoreboard(4);
            break;
    }
}

void menu::develop(int setting)
{
/**
 *  依照選擇刪除記事本內資料
 * \param setting int 傳入選擇
 * \return void
 */
    fstream fin;
    if(setting==1)
        fin.open("./note/easy_score.txt",ios::out);
    else if(setting==2)
        fin.open("./note/normal_score.txt",ios::out);
    else if(setting==3)
        fin.open("./note/hard_score.txt",ios::out);
    else if(setting==4)
        fin.open("./note/challenge_score.txt",ios::out);
    else if(setting==5)
        fin.open("./note/player.txt",ios::out);
    fin.close();
    cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉              ";
    SetColor(10);
    cout<<"Your data was successfully deleted.";
    SetColor(7);
    cout<<"               ▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉"<<endl;
}


void menu::start()
{
/**
 *  設定地圖大小
 * \return void
 */
    switch(difficult)
    {
        case 1:
        case 4:
            The_Map=board(40,40);
            break;
        case 2:
        case 3:
            The_Map=board(30,30);
            break;
    }
}

void menu::in_running()
{
/**
 *  on為開始計時，並在開始前就呼叫蘋果和障礙物及輸出地圖邊框，
 *  在每步開始前紀錄位置給premap，依照輸入方向傳給direction_change檢查(避免反方向行走時當機)，
 *  先check前一步情形後再傳給motion移動，將移動情形紀錄給confirm_direction，若是在Easy,Normal,Hard模式下
 *  撞牆、蛇身、障礙物立刻死，Challenge模式不會死。off為該階段停止計時。最後輸出地圖。
 * \return void
 */
    on=clock();
    int confirm_direction;
    int time=0;

    The_Map.apple_point();  ///一開始
    if(difficult==3)
        The_Map.barrier_point();
    first_output_map();

    while(1)
    {
        The_Map.premapupdate();
        if(kbhit())
        {
            int input=getch();
            switch(input)
            {
                case 72: ///up
                    confirm_direction=greedy.direction_change(1);
                    behavior=greedy.motion(difficult,The_Map.check(confirm_direction));
                    break;
                case 75: ///Left
                    confirm_direction=greedy.direction_change(3);
                    behavior=greedy.motion(difficult,The_Map.check(confirm_direction));
                    break;
                case 77: ///Right
                    confirm_direction=greedy.direction_change(2);
                    behavior=greedy.motion(difficult,The_Map.check(confirm_direction));
                    break;
                case 80: ///Down
                    confirm_direction=greedy.direction_change(4);
                    behavior=greedy.motion(difficult,The_Map.check(confirm_direction));
                    break;
            }
        }
        else
        {
            behavior=greedy.motion(difficult,The_Map.check(greedy.get_snake_walk_to()));
        }

        The_Map.combine_snake_map();
        off=clock();
        double countdown=(off-on)/(double)(CLOCKS_PER_SEC);
        achieve.missionsecond(countdown);  ///不停紀錄現在時間判斷有無達成玩300秒成就

        if(behavior==2 && difficult==4)
        {
            time+=2;                       ///Challenge模式下每次吃到蘋果加2秒
            behavior=1;
            achieve.missionhit(1);
        }
        else if(behavior>2 && difficult==4)
        {
            time-=10;                     ///Challenge模式下撞到障礙物,牆壁,蛇身扣10秒
            if(behavior==5)               ///Challenge模式下撞到牆壁轉彎，避免連續扣分
                greedy.set_snake_walk_to();
            behavior=1;
            achieve.missionhit(1);
        }
        else if(behavior==1 && difficult==4)
        {
            int minute=(61-countdown+time)/60;
            int second=abs((60-(int)countdown+time))%60;

            if((60-countdown+time)<=0)  ///Challenge模式下時間到就跳出
                break;

            int r=rand()%100;
            if(r%10==0)                 /// 10/100機率產生一個新蘋果
                The_Map.apple_point();
            if(r%15==0)                 /// 6/100機率產生一個障礙物
                The_Map.barrier_point();
            if(r%30==0)                 /// 3/100機率清除東西
                The_Map.clear_object(difficult);

            int check_x,check_y;
            for(check_x=0;check_x<40;check_x++) ///防止一個蘋果也沒有
            {
                for(check_y=0;check_y<40;check_y++)
                {
                    int N=The_Map.return_map(check_x,check_y);
                    if(N==-2)
                        break;
                }
                if(check_y!=40)
                    break;
            }
            if(check_x==40)
                The_Map.apple_point();

        }
        else if(behavior==2 && difficult<4) ///吃到蘋果時重新產生一個蘋果和障礙物
        {
            The_Map.clear_object(difficult);
            The_Map.apple_point();

            if(difficult==3)
                The_Map.barrier_point();
            behavior=1;
        }
        else if(behavior>2 && difficult<4)
        {
            if(difficult==3&&behavior==3)
            {
                achieve.missionhit(3);
            }
            break;
        }
        output_map(time);

        if(difficult==1)
            Sleep(80);
        else if(difficult==2 || difficult==4)
            Sleep(60);
        else if(difficult==3)
            Sleep(40);
    }
    system("cls");
}

void menu::first_output_map()
{
/**
 *  一開始輸出邊框
 * \param
 * \param
 * \return
 *
 */
    The_Map.combine_snake_map();

    int x,y;
    if(difficult==1 || difficult==4)
    {
        x=40;
        y=40;
    }
    else if(difficult==2 || difficult==3)
    {
        x=30;
        y=30;
    }

    for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
            int N=The_Map.return_map(i,j);
            if(N==-1)
            {
                gotoxy(2*j,i);
                cout<<"■";
            }
        }
        cout<<endl;
    }
}

void menu::output_map(int time)
{
/**
 *  輸出地圖，和premap同時比較，若前一步和這一步object相同就不輸出(避免刷新過快)
 *  並在右側輸出名字、模式、成績、時間(Easy、Normal、Hard模式為正計時，到達整數分鐘會閃爍4秒，
 *  Challenge模式為倒計時，剩10秒會閃爍並出現警告)
 * \param time int
 * \return void
 */
    int x,y;
    The_Map.combine_snake_map();
    if(difficult==1 || difficult==4)
    {
        x=40;
        y=40;
    }
    else if(difficult==2 || difficult==3)
    {
        x=30;
        y=30;
    }

    gotoxy(0,0);

    off=clock();
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
            if(j<y)
            {
                int N=The_Map.return_map(i,j);
                int M=The_Map.return_premap(i,j);
                if(N==0&&M!=0)
                {
                    gotoxy(2*j,i);
                    cout<<"　";///walk
                }
                else if(N==-2)
                {
                    SetColor(12);
                    gotoxy(2*j,i);
                    cout<<"★";///apple
                }
                else if(N==-3)
                {
                    SetColor(11);
                    gotoxy(2*j,i);
                    cout<<"☆";///barrier
                }
                else if(N>0&&M<=0)
                {
                    SetColor(14);
                    gotoxy(2*j,i);
                    cout<<"●";///body
                }
                else;
            }
        }
    }
    SetColor(7);
    gotoxy(y*2,6);
    {
        cout<<"   Hi, ";
        SetColor(14);
        cout<<name;
        SetColor(7);
    }
    gotoxy(y*2,8);
    {
        cout<<"   Mode : ";
        if(difficult==1)
        {
            cout<<"Easy";
        }
        else if(difficult==2)
        {
            cout<<"Normal";
        }
        else if(difficult==3)
        {
            cout<<"Hard";
        }
        else if(difficult==4)
        {
            cout<<"Challenge";
        }
    }
    gotoxy(y*2,10);
    cout<<"   Score: "<<greedy.get_snakelong();

    if(difficult==4)
    {
        double countdown=(off-on)/(double)(CLOCKS_PER_SEC);
        int minute=(61-countdown+time)/60;
        int second=abs((60-(int)countdown+time))%60;


        gotoxy(y*2,12);
        cout<<"   Time : ";

        if(second<=10 && second%2==0 && minute<1)
        {
            SetColor(12);
        }
        else if(second<=10 && second%2==1 && minute<1)
        {
            SetColor(7);
        }

        cout<<setfill('0')<<setw(2)<<minute<<":"<<setw(2)<<second;
        SetColor(7);

        if(second<=10 && second>7 && minute<1)
        {
            gotoxy(y*2,14);
            SetColor(12);
            cout<<"  Left 10 seconds !"<<endl;
            SetColor(7);
        }
        else
        {
            gotoxy(y*2,14);
            cout<<"                    ";
        }
    }
    else
    {
        double countdown=(off-on)/(double)(CLOCKS_PER_SEC);
        int minute=countdown/60;
        int second=(int)countdown%60;

        gotoxy(y*2,12);
        cout<<"   Time : ";
        if(minute>0 && (second==1 || second==3))
        {
            SetColor(12);
        }
        else if(minute>0 && (second==2 || second==4))
        {
            SetColor(7);
        }
        cout<<setfill('0')<<setw(2)<<minute<<":"<<setw(2)<<second;
        SetColor(7);
    }
    gotoxy(0,0);
}

void menu::output_score()
{
/**
 *  輸出成績(要算成績幾位數避免超出框界)及此局完成的成就
 * \return void
 */
    cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉    Ｓｃｏｒｅ：　"<<greedy.get_snakelong();

    int y=greedy.get_snakelong(),count=1;
    while(y!=0)
    {
        y/=10;
        count++;
    }
    int z=47-count;
    while(z--)
        cout<<" ";
    cout<<"▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉    Ｍｉｓｓｉｏｎ：                                            ▉"<<endl;
    cout<<"▉  ";
    SetColor(10);
    cout<<"【Ｙｏｕ　ｆｉｎｉｓｈｅｄ】";
    SetColor(7);
    cout<<"                                  ▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    achieve.missionshow();
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉"<<endl;
}

void menu::output_scoreboard(int hard)
{
/**
 *  依照選擇的模式開檔輸出排行榜
 * \param hard int
 * \return void
 */
    fstream fin;
    system("cls");
    int j;
    string s;
    vector<int> num;
    vector<string> str;
    cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉                            Ｒａｎｋ                            ▉"<<endl;

    if(hard==1)
    {
        cout<<"▉                            Ｅａｓｙ                            ▉"<<endl;
        fin.open("./note/easy_score.txt",ios::in);
    }
    else if(hard==2)
    {
        cout<<"▉                          Ｎｏｒｍａｌ                          ▉"<<endl;
        fin.open("./note/normal_score.txt",ios::in);
    }
    else if(hard==3)
    {
        cout<<"▉                            Ｈａｒｄ                            ▉"<<endl;
        fin.open("./note/hard_score.txt",ios::in);
    }
    else if(hard==4)
    {
        cout<<"▉                       Ｃｈａｌｌｅｎｇｅ                       ▉"<<endl;
        fin.open("./note/challenge_score.txt",ios::in);
    }

    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉       Rank           Score                     Name            ▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    while(fin>>j)
    {
        fin.get();
        getline(fin,s);
        num.push_back(j);
        str.push_back(s);
    }
    for(int a=0;a<num.size();a++)   ///bubble sort
    {
        for(int b=0;b<num.size()-a;b++)
        {
            if(num[b]<num[b+1] && b+1<num.size())
            {
                swap(num[b],num[b+1]);
                swap(str[b],str[b+1]);
            }
        }
    }
    for(int a=0;a<num.size() && a<10 ;a++)   ///輸出前10名
    {
        int x=num[a],count=1;
        while(x!=0)  ///算成績幾位數
        {
            x/=10;
            count++;
        }

        cout<<"▉";

        if(a==0)
        {
            SetColor(12); ///紅色
        }
        else if(a==1)
        {
            SetColor(10); ///綠色
        }
        else if(a==2)
        {
            SetColor(11); ///青色
        }

        int w=8;
        if(a==9)      ///排名第10名往前一格(對齊)
            w--;
        while(w--)
            cout<<" ";
        cout<<a+1;

        int y=17-count;  ///排名和成績間的空格
        while(y--)
            cout<<" ";
        cout<<num[a]<<"             "<<str[a];

        int z=26-str[a].length();
        while(z--)
            cout<<" ";
        SetColor(7);
        cout<<"▉"<<endl;
    }
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉"<<endl;
    fin.close();
}

void menu::output_mission()
{
/**
 *  開檔輸出這個使用者的所有成就
 * \return void
 */
    cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉                        Ｍｉｓｓｉｏｎ                          ▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉  Hi, ";
    SetColor(14);
    cout<<name;
    SetColor(7);
    cout<<":";
    int space_size=57-name.length();
    while(space_size--)
        cout<<" ";
    cout<<"▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉  ";
    SetColor(10);
    cout<<"【Ｙｏｕ　ｆｉｎｉｓｈｅｄ】";
    SetColor(7);
    cout<<"                                  ▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    achieve.listshow(1);
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉  ";
    SetColor(12);
    cout<<"【Ｙｏｕ　ｕｎｆｉｎｉｓｈ】";
    SetColor(7);
    cout<<"                                  ▉"<<endl;
    cout<<"▉                                                                ▉"<<endl;
    achieve.listshow(2);
    cout<<"▉                                                                ▉"<<endl;
    cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉"<<endl;
}

void menu::combine()
{
/**
 *  讓board的snakeinmap指向snake的insect紀錄蛇身
 * \return void
 */
    The_Map.setsnakepoint(greedy.getsnakepoint());
}
