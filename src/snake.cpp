#include "snake.h"
#include<iostream>
#include<vector>
using namespace std;



snake::snake(int start_x, int start_y, int head_num)
{
    /**
     *  蛇初始化
     * \param start_x int   傳入蛇頭的X座標
     * \param start_y int   傳入蛇頭的y座標
     * \param head_num int  傳入蛇的長度
     */
    for(int i=head_num-1;i>=0;i--)  ///將蛇身的x,y,數字加入身體
    {
        dot a={start_x,start_y-i,head_num-i};
        insect.push_back(a);
    }
    snake_head_x=start_x;           ///頭座標x定位
    snake_head_y=start_y;           ///頭座標y定位
    snakelong=head_num;             ///蛇長定位
    snake_walk_to=2;                ///蛇方向定位
}


int snake::direction_change(int direction)
{
    /**
     *  傳入輸入的方向,改變並回傳蛇走的方向
     * \param direction int 傳入輸入的方向
     * \return int  回傳改變後的方向
     */
    if(snake_walk_to==1)        ///若原來蛇走的方向為 up
    {
        if(direction==1||direction==4)      ///若輸入的方向為up或down 不變
            return snake_walk_to;
        else                                ///否則將蛇走的方向改為輸入的方向
        {
            snake_walk_to=direction;
            return direction;
        }
    }
    else if(snake_walk_to==2)   ///若原來蛇走的方向為 right
    {
        if(direction==3||direction==2)      ///若輸入的方向為left或right 不變
            return snake_walk_to;
        else                                ///否則將蛇走的方向改為輸入的方向
        {
            snake_walk_to=direction;
            return direction;
        }
    }
    else if(snake_walk_to==3)   ///若原來蛇走的方向為 left
    {
        if(direction==2||direction==3)      ///若輸入的方向為left或right 不變
            return snake_walk_to;
        else                                ///否則將蛇走的方向改為輸入的方向
        {
            snake_walk_to=direction;
            return direction;
        }
    }
    else if(snake_walk_to==4)   ///若原來蛇走的方向為 down
    {
        if(direction==1||direction==4)      ///若輸入的方向為up或down 不變
            return snake_walk_to;
        else                                ///否則將蛇走的方向改為輸入的方向
        {
            snake_walk_to=direction;
            return direction;
        }
    }
}

int snake::motion(int difficult,int situation)
{
    /**
     *   傳入情況和難度,改變蛇的位置或長度
     * \param difficult int 遊戲難度
     * \param situation int 現在蛇遇到的情況
     * \return int          回傳情況
     */
    if(situation==1 || situation==3 || situation==4)    ///若情形為行走中,撞到障礙物,撞到身體
    {
        if(snake_walk_to==1)        ///若蛇現在為往上走
        {
            snake_head_x--;         ///將蛇頭往上移
        }

        else if(snake_walk_to==2)   ///若蛇現在為往右走
        {
            snake_head_y++;         ///將蛇頭往右移
        }

        else if(snake_walk_to==3)   ///若蛇現在為往左走
        {
            snake_head_y--;         ///將蛇頭往左移
        }

        else if(snake_walk_to==4)   ///若蛇現在為往下走
        {
            snake_head_x++;         ///將蛇頭往下移
        }
        for(int i=0;i<snakelong-1;i++)///將蛇身的位置往前更新
        {
            insect[i].x=insect[i+1].x;
            insect[i].y=insect[i+1].y;
        }
        insect[insect.size()-1].x=snake_head_x;///將蛇身陣列最後面變成頭的座標
        insect[insect.size()-1].y=snake_head_y;///將蛇身陣列最後面變成頭的座標
    }
    else if(situation==2)   ///若吃到蘋果
    {
        if(snake_walk_to==1)        ///若蛇現在為往上走
        {
            snake_head_x--;         ///將蛇頭往上移
        }

        else if(snake_walk_to==2)   ///若蛇現在為往右走
        {
            snake_head_y++;         ///將蛇頭往右移
        }

        else if(snake_walk_to==3)   ///若蛇現在為往左走
        {
            snake_head_y--;         ///將蛇頭往左移
        }

        else if(snake_walk_to==4)   ///若蛇現在為往下走
        {
            snake_head_x++;         ///將蛇頭往下移
        }
        snakelong++;                ///加長蛇長
        dot a={snake_head_x,snake_head_y,snakelong};///在蛇身中加入蛇頭

        insect.push_back(a);
    }


    if(situation==5 && difficult==4)   ///若撞到牆且難度為challenge
    {
        if(snake_walk_to==1)        ///若蛇現在為往上走
        {
            if(snake_head_y==38)        ///若蛇在最右方,將蛇頭向左移 否則向右移
                snake_head_y--;
            else
                snake_head_y++;
        }
        else if(snake_walk_to==2)   ///若蛇現在為往右走
        {
            if(snake_head_x==38)       ///若蛇在最下方,將蛇頭向上移 否則向下移
                snake_head_x--;
            else
                snake_head_x++;
        }
        else if(snake_walk_to==3)   ///若蛇現在為往左走
        {
            if(snake_head_x==38)        ///若蛇在最下方,將蛇頭向上移 否則向下移
                snake_head_x--;
            else
                snake_head_x++;
        }
        else if(snake_walk_to==4)   ///若蛇現在為往下走
        {
            if(snake_head_y==38)       ///若蛇在最右方,將蛇頭向左移 否則向右移
                snake_head_y--;
            else
                snake_head_y++;
        }
        for(int i=0;i<snakelong-1;i++)  ///將蛇身的位置往前更新
        {
            insect[i].x=insect[i+1].x;
            insect[i].y=insect[i+1].y;
        }
        insect[insect.size()-1].x=snake_head_x;///將蛇身陣列最後面變成頭的座標
        insect[insect.size()-1].y=snake_head_y;///將蛇身陣列最後面變成頭的座標
    }
    return situation;   ///回傳情況
}


void snake::set_snake_walk_to()
{
    /**
     *  challenge模式時的撞牆自動轉彎
     * \return void
     */
    if(snake_walk_to==1 && snake_head_y==37)    ///若在右上角往上走 左轉
    {
        snake_walk_to=3;
    }
    else if(snake_walk_to==1)                   ///若在其他地方往上走 右轉
    {
        snake_walk_to=2;
    }
    else if(snake_walk_to==2 && snake_head_x==37)///若在右下角往右走 改為往上走
    {
        snake_walk_to=1;
    }
    else if(snake_walk_to==2)                   ///若在其他地方往右走 改為往下走
    {
        snake_walk_to=4;
    }
    else if(snake_walk_to==3 && snake_head_x==37)///若在左下角往左走 改為往上走
    {
        snake_walk_to=1;
    }
    else if(snake_walk_to==3)                   ///若在其他地方往左走 改為往下走
    {
        snake_walk_to=4;
    }
    else if(snake_walk_to==4 && snake_head_y==37)///若在右下角往下走 左轉
    {
        snake_walk_to=3;
    }
    else if(snake_walk_to==4)                   ///若在其他地方往下走 右轉
    {
        snake_walk_to=2;
    }
}


int snake::get_snake_walk_to()
{
    /**
    *   回傳蛇走的方向
    * \return int
    */
    return snake_walk_to;
}


int snake::get_snakelong()
{
    /**
     *  回傳蛇長
     * \return int
     */
    return snakelong;
}


vector<dot>* snake::getsnakepoint()
{
    /**
     *  回傳蛇的指標
     * \return vector<dot>*
     */
    vector<dot>* a;
    a=&insect;
    return a;
}
