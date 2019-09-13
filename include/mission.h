#ifndef MISSION_H
#define MISSION_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class mission
{
    private:

        /** \brief  玩家名稱  */
        string name;

        /** \brief  任務完成與否個人列表  */
        string completed;

        /** \brief 玩家與任務完成與否列表  */
        vector<string> all_player;

        /** \brief 任務列表 */
        vector<string> all_mission;

        /** \brief 碰撞紀錄 */
        int hit;

        /** \brief 遊玩一場時間紀錄 */
        double second;
    public:

        /** \brief 先將hit和second設為0 */
        mission();

        /** \brief 該場遊戲任務完成顯示
         * \return void
         */
        void missionshow();

        /** \brief 找出玩家或建立新玩家資料
         * \return void
         */
        void establish_player(string user_name);

        /** \brief 將任務放入all_mission
         * \return void
         */
        void establish_mission();

        /** \brief 單場類任務判定
         * \return void
         */
        void endagame(int modedif,int snakelong);

        /** \brief 累積類任務判定
         * \return void
         */
        void times(int modedif);

        /** \brief 所有任務及完成與否顯示
         * \return void
         */
        void listshow(int completednoi);

        /** \brief 更改碰撞紀錄
         * \return void
         */
        void missionhit(int behaviorwa);

        /** \brief 記錄一場遊玩時間
         * \return void
         */
        void missionsecond(double sec);
};


#endif // MISSION_H
