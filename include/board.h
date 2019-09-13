#ifndef BOARD_H
#define BOARD_H

#include<vector>
#include"for_use.h"
using namespace std;

/** \brief 控制地圖 */
class board
{
    private:
        /** \brief 地圖 */
        int Map[40][40];
        /** \brief 前一步地圖(避免刷新過快) */
        int premap[40][40];
         /** \brief 地圖的長寬 */
        int length,width;
        /** \brief 指向蛇身的座標 */
        vector<dot> *snakeinmap;
    public:
        /** \brief 設定地圖長寬及地圖牆壁、行走處
         * \param l int
         * \param w int
         */
        board(int l,int w);
        /** \brief 依照傳入的方向檢查前一個的情況
         * \param direction int
         * \return int
         */
        int check(int direction);
        /** \brief 結合蛇身與地圖
         * \return void
         */
        void combine_snake_map();
        /** \brief 一點一點回傳這一步地圖
         * \param x int
         * \param y int
         * \return int
         */
        int return_map(int x,int y);
        /** \brief 一點一點回傳前一步地圖
         * \param x int
         * \param y int
         * \return int
         */
        int return_premap(int x, int y);
        /** \brief 清除蘋果及障礙物
         * \param difficult int
         * \return void
         */
        void clear_object(int difficult);
        /** \brief 在地圖中隨機尋找適合的點讓蘋果出現
         * \return void
         */
        void apple_point();
        /** \brief 在地圖中隨機尋找適合的點讓障礙物出現
         * \return void
         */
        void barrier_point();
        /** \brief 讓board擁有蛇身位置
         * \param vector<dot>*
         * \return void
         */
        void setsnakepoint(vector<dot>*);
        /** \brief 更新premap地圖
         * \return void
         */
        void premapupdate();
};

#endif // BOARD_H
