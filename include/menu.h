#ifndef MENU_H
#define MENU_H

#include<iostream>
#include<string>
#include<ctime>
#include "board.h"
#include "snake.h"
#include "scoreboard.h"
#include "mission.h"
using namespace std;


/** \brief menu控制整個遊戲*/
class menu
{
    private:
        /** \brief 存每次遊戲的難度*/
        int difficult;
        /** \brief 判斷每次行走時的情況  */
        int behavior;
        /** \brief 使用者名稱 */
        string name;
        board The_Map;
        snake greedy;
        scoreboard score;
        mission achieve;
        /** \brief 計時器  */
        clock_t on,off;
    public:
        /** \brief constructor預設最大地圖、蛇的位置、行走狀況 */
        menu();
        /** \brief 儲存現在使用者名稱
         * \param user_name string
         * \return void
         */
        void set_name(string user_name);
        /** \brief 依照選擇的模式設定遊戲
         * \param hard_choose int
         * \return void
         */
        void mode(int hard_choose);
        /** \brief 依照選擇的模式呼叫排行榜
         * \param hard_choose int
         * \return void
         */
        void ranking(int hard_choose);
        /** \brief 依照選擇的模式刪除記事本內資料
         * \param setting int
         * \return void
         */
        void develop(int setting);
        /** \brief 讓board的snakeinmap紀錄蛇身
         * \return void
         */
        void combine();
        /** \brief 依照難度設定地圖大小
         * \return void
         */
        void start();
        /** \brief 遊戲運作
         * \return void
         */
        void in_running();
        /** \brief 輸出地圖邊框
         * \return void
         */
        void first_output_map();
        /** \brief 輸出整個地圖
         * \param time int
         * \return void
         */
        void output_map(int time);
        /** \brief 輸出結束後的成績及該局完成的成就
         * \return void
         */
        void output_score();
        /** \brief 依照ranking呼叫的難度呼叫排行榜
         * \param hard int
         * \return void
         */
        void output_scoreboard(int hard);
        /** \brief 輸出個人所有的成就
         * \return void
         */
        void output_mission();
};


#endif // MENU_H
