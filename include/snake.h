#ifndef SNAKE_H
#define SNAKE_H

#include<iostream>
#include<vector>
#include"for_use.h"

using namespace std;

/** \brief  蛇 */
class snake
{
    private:
        /** \brief 紀錄蛇身*/
        vector<dot> insect;
        /** \brief 紀錄蛇頭*/
        int snake_head_x,snake_head_y;
        /** \brief 紀錄蛇長*/
        int snakelong;
        /** \brief 蛇走的方向*/
        int snake_walk_to;
    public:
        /** \brief 蛇初始化
         * \param start_x int   蛇頭的X座標
         * \param start_y int   蛇頭的y座標
         * \param head_num int  蛇的長度
         */
        snake(int start_x,int start_y,int head_num);
        /** \brief 傳入輸入的方向,改變並回傳蛇走的方向
         * \param direction int 輸入的方向
         * \return int 蛇走的方向
         */
        int direction_change(int direction);
        /** \brief 傳入情況和難度,改變蛇的位置或長度
         * \param difficult int 難度
         * \param situation int 情況
         * \return int 情況
         */
        int motion(int difficult,int situation);
        /** \brief 回傳蛇走的方向
         * \return int 蛇走的方向
         */
        int get_snake_walk_to();
        /** \brief 自動判定撞牆時的轉向
         * \return void
         */
        void set_snake_walk_to();
        /** \brief 回傳蛇長
         * \return int 蛇長
         */
        int get_snakelong();
        /** \brief 回傳蛇身的指標
         * \return vector<dot>* 蛇身的指標
         */
        vector<dot>* getsnakepoint();
};

#endif // SNAKE_H
