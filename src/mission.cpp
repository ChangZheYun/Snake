#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "mission.h"
using namespace std;

fstream miss;
fstream play;
fstream ranks;

mission::mission()
{
    /**  先將hit和second設為0
    * \return
    */
    hit=0;
    second=0;
}

void mission::missionshow()
{
    /** 將玩家任務完成表中設為2的相對應任務顯示出，並把2改為1以表示把該次完成任務改為已完成任務
    * \return void
    */
    int name_num=0;
    for(int i=0;i<all_player.size();i++)
    {
        if(all_player[i]==name)
        {
            completed=all_player[i+1];
            name_num=i+1;
        }
    }
    for(int i=0;i<30;i++)
    {
        if(completed[i]=='2')
        {
            cout<<"▉    ▲"<<all_mission[i];

            int count_size=58-all_mission[i].length();
            while(count_size--)
                cout<<" ";
            cout<<"▉"<<endl;

            completed[i]='1';
        }
    }

    all_player[name_num]=completed;
    play.open("./note/player.txt",ios::out);
    for(int i=0;i<all_player.size();i++)
    {
        play<<all_player[i]<<endl;
    }
    play.close();

}

void mission::establish_player(string user_name) ///player建立玩家資料
{
    /** 先以名字尋找其任務完成表，若找不到名字則新增玩家資料
     * \return
     */

    name=user_name;
    play.open("./note/player.txt",ios::in);  ///檢查該筆玩家是否已建立
    string str;
    int check_name=0;
    while(getline(play,str))
    {
        all_player.push_back(str);
    }
    play.close();

    for(int i=0;i<all_player.size();i++)
    {
        if(all_player[i]==name)
        {
            completed=all_player[i+1];
            check_name=1;
            break;
        }
        else
            check_name=0;
    }
    if(check_name==0)  ///player內無該玩家資料，建立玩家資料
    {
        completed="0000000000000000000000";
        all_player.push_back(name);
        all_player.push_back(completed);

        play.open("./note/player.txt",ios::out|ios::app);
        play<<name<<endl<<completed<<endl;

        play.close();
    }
}

void mission::establish_mission()
{
    /** 將任務傳到all_mission以存之
     * \return void
     */
    string str;
    miss.open("./note/mission_list.txt",ios::in); ///建立all_mission
    while(getline(miss,str))
    {
        all_mission.push_back(str);
    }
    miss.close();
}


void mission::endagame(int modedif,int snakelong)  ///判斷有無達成成就
{
    /** 找出成就表，並在遊戲結束時把符合條件的從0(未完成)改成2(該次完成)
     * \return void
     */
    int person_mission_num=0;
    for(int i=0;i<all_player.size();i++)
    {
        if(all_player[i]==name)
        {
            person_mission_num=i+1;
            break;
        }
    }
    times(modedif);
    if(modedif==1)
    {
        if(snakelong>=10&&completed[0]=='0')
            completed[0]='2';
        if(snakelong>=30&&completed[4]=='0')
            completed[4]='2';
        if(snakelong>100&&completed[8]=='0')
            completed[8]='2';
    }
    if(modedif==2)
    {
        if(snakelong>=10&&completed[1]=='0')
            completed[1]='2';
        if(snakelong>=25&&completed[5]=='0')
            completed[5]='2';
        if(snakelong==87&&completed[9]=='0')
            completed[9]='2';
    }
    if(modedif==3)
    {
        if(snakelong>=10&&completed[2]=='0')
            completed[2]='2';
        if(snakelong>=20&&completed[6]=='0')
            completed[6]='2';
        if(snakelong==69&&completed[10]=='0')
            completed[10]='2';
        if(hit==3&&completed[21]=='0')
            completed[21]='2';
        hit=0;
    }
    if(modedif==4)
    {
        if(snakelong>=10&&completed[3]=='0')
            completed[3]='2';
        if(snakelong>=20&&completed[7]=='0')
            completed[7]='2';
        if(snakelong>=100&&completed[11]=='0')
            completed[11]='2';
        if(hit==0&&completed[20]=='0')
            completed[20]='2';
        hit=0;
    }
    if(snakelong==4&&completed[12]=='0')
        completed[12]='2';
    if(second>=300 && completed[19]=='0')
        completed[19]='2';


    all_player[person_mission_num]=completed;

    play.open("./note/player.txt",ios::out);
    for(int i=0;i<all_player.size();i++)
    {
        play<<all_player[i]<<endl;
    }
    play.close();
    return;
}


void mission::times(int modedif)
{
    /** \brief 在排行榜找出相同名字並記錄所需資訊，並把符合條件的從0(未完成)改成2(該次完成)
     * \return void
     */
    int score;
    string str;
    int timess=0,all_time=0,all_score=0;

    ranks.open("./note/easy_score.txt",ios::in);
    while(ranks>>score)
    {
        ranks.get();
        ranks.get();
        getline(ranks,str);
        if(name==str && modedif==1)
        {
            timess+=1;
        }
        if(name==str)
        {
            all_time+=1;
            all_score+=score;
        }
    }
    ranks.close();
    if(timess>=10&&completed[13]=='0')
        completed[13]='2';

    timess=0;
    ranks.open("./note/normal_score.txt",ios::in);
    while(ranks>>score)
    {
        ranks.get();
        ranks.get();
        getline(ranks,str);
        if(name==str && modedif==2)
        {
            timess+=1;
        }
        if(name==str)
        {
            all_time+=1;
            all_score+=score;
        }
    }
    ranks.close();
    if(timess>=10&&completed[14]=='0')
        completed[14]='2';

    timess=0;
    ranks.open("./note/hard_score.txt",ios::in);
    while(ranks>>score)
    {
        ranks.get();
        ranks.get();
        getline(ranks,str);
        if(name==str && modedif==3)
        {
            timess+=1;
        }
        if(name==str)
        {
            all_time+=1;
            all_score+=score;
        }
    }
    ranks.close();
    if(timess>=10&&completed[15]=='0')
        completed[15]='2';

    timess=0;
    ranks.open("./note/challenge_score.txt",ios::in);
    while(ranks>>score)
    {
        ranks.get();
        ranks.get();
        getline(ranks,str);
        if(name==str && modedif==4)
        {
            timess+=1;
        }
        if(name==str)
        {
            all_time+=1;
            all_score+=score;
        }
    }
    ranks.close();

    if(timess>=20&&completed[16]=='0')
        completed[16]='2';
    if(all_time>=50&&completed[17]=='0')
        completed[17]='2';
    if(all_score>=1000&&completed[18]=='0')
        completed[18]='2';
}

void mission::listshow(int completednoi)
{
/**
 *  所有成就分類成有完成和未完成
 * \param completednoi int
 * \return void
 */
    string str;
    for(int i=0;i<all_player.size();i++)
    {
        if(all_player[i]==name)
        {
            for(int j=0;j<all_player[i+1].length();j++)
            {
                if(all_player[i+1][j]=='1' && completednoi==1)
                {
                    cout<<"▉  ▲"<<all_mission[j];
                    int count_size=60-all_mission[j].length();
                    while(count_size--)
                        cout<<" ";
                    cout<<"▉"<<endl;
                }
                else if(all_player[i+1][j]=='0' && completednoi==2)
                {
                    cout<<"▉  ▲"<<all_mission[j];
                    int count_size=60-all_mission[j].length();
                    while(count_size--)
                        cout<<" ";
                    cout<<"▉"<<endl;
                }
            }
            break;
        }
    }
}


void mission::missionhit(int behaviorwa)
{
    /**改變hit數值
     * \return void
     */
    hit=behaviorwa;
}


void mission::missionsecond(double sec)
{
    /**紀錄時間，放入second
     * \return void
     */
    second=sec;
}
