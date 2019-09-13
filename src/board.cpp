#include<vector>
#include<cstdlib>
#include<iostream>
#include"board.h"
using namespace std;


board::board(int l, int w)
{
/**
 * 設定地圖最外面的邊框為-1並把其他設為0(可行走)
 * \param l int 地圖長
 * \param w int 地圖寬
 */
    length=l;
    width=w;
    for(int i=0;i<length;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(i==0 || i==length-1 || j==0 || j==width-1)
                Map[i][j]=-1;
            else
                Map[i][j]=0;
        }
    }
}

int board::check(int direction)
{
/**
 *  蛇頭在snakeinmap是最後一個，取出蛇頭的x和y值後，
 *  依照方向判斷前一個可能的情形(正常、吃蘋果、撞障礙物、撞牆、撞蛇身)
 * \param direction int z; 方向
 * \return int 回傳判定情況
 */
    int situation;
    int x=(*snakeinmap)[(*snakeinmap).size()-1].x;
    int y=(*snakeinmap)[(*snakeinmap).size()-1].y;
    switch(direction)
    {
        case 1:
            x--;
            break;
        case 2:
            y++;
            break;
        case 3:
            y--;
            break;
        case 4:
            x++;
            break;
    }
    if(Map[x][y]==0)
        situation=1;
    else if(Map[x][y]==-1)
        situation=5;
    else if(Map[x][y]==-2)
        situation=2;
    else if(Map[x][y]==-3)
        situation=3;
    else
        situation=4;
    return situation;
}

void board::combine_snake_map()
{
/**
 *  把上一步的蛇身地圖歸0(設成可行走)，再把蛇身位置結合進地圖
 * \return void
 */
    for(int map_x=0;map_x<length;map_x++)
    {
        for(int map_y=0;map_y<width;map_y++)
        {
            if(Map[map_x][map_y]>=0)
                Map[map_x][map_y]=0;
        }
    }

    for(int i=0;i<(*snakeinmap).size();i++)
    {
        Map[(*snakeinmap)[i].x][(*snakeinmap)[i].y]=(*snakeinmap)[i].num;
    }
}

int board::return_map(int x, int y)
{
/**
 * \param x int 地圖長
 * \param y int 地圖寬
 * \return int  回傳該地圖數值(情況)
 */
    return Map[x][y];
}

int board::return_premap(int x, int y)
{
/**
 *  這個函數是"前一步地圖"
 * \param x int 地圖長
 * \param y int 地圖寬
 * \return int 回傳該地圖數值(情況)
 */
    return premap[x][y];
}

void board::clear_object(int difficult)
{
/**
 *  Easy、Normal、Hard(difficult<4)在出現蘋果/障礙物之前都必須清空，避免重複出現。
 *  n為Challenge模式在用的，有3/1000(1/10*3/100)機率消失"全部"障礙物，3/500(2/10*3/100)機率"全部"消失蘋果，
 *  其他也有可能"個別"消失障礙物或蘋果
 * \param difficult int 傳入難度(不同難度有不同清除設定)
 * \return void
 */
    int n=rand()%10;

    if(difficult<4)
    {
        for(int i=0;i<length;i++)
        {
            for(int j=0;j<width;j++)
            {
                if(Map[i][j]<-1)
                    Map[i][j]=0;
            }
        }
    }
    else if(n==2)
    {
        for(int i=0;i<length;i++)
        {
            for(int j=0;j<width;j++)
            {
                if(Map[i][j]==-3)
                    Map[i][j]=0;
            }
        }
    }
    else if(n<2)
    {
        for(int i=0;i<length;i++)
        {
            for(int j=0;j<width;j++)
            {
                if(Map[i][j]==-2)
                    Map[i][j]=0;
            }
        }
    }
    else
    {
        while(n>0)
        {
            int i=rand()%length;
            int j=rand()%width;
            if(Map[i][j]<-1)
            {
                Map[i][j]=0;
            }
            n--;
        }
    }
}

void board::apple_point()
{
/**
 *  利用rand隨機在地圖可行走處出現蘋果
 * \return void
 */
    while(1)
    {
        int i=rand()%length;
        int j=rand()%width;
        if(Map[i][j]==0)
        {
            Map[i][j]=-2;
            break;
        }
    }
}

void board::barrier_point()
{
/**
 *  利用rand隨機在地圖可行走處出現障礙物(Hard、Challenge模式)
 * \return void
 */
    while(1)
    {
        int i=rand()%length;
        int j=rand()%width;
        if(Map[i][j]==0)
        {
            Map[i][j]=-3;
            break;
        }
    }
}

void board::setsnakepoint(vector<dot>* a)
{
/**
 *  讓指標setsnakepoint擁有蛇身
 * \param a vector<dot>* 傳入蛇身
 * \return void
 */
    snakeinmap=a;
}

void board::premapupdate()
{
/**
 *  更新"前一步"地圖
 * \return void
 */
    for(int map_x=0;map_x<length;map_x++)
    {
        for(int map_y=0;map_y<width;map_y++)
        {
            premap[map_x][map_y]=Map[map_x][map_y];
        }
    }
}
