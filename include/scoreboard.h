#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/** \brief 排行榜  */
class scoreboard
{
    public:
        /** \brief 將成績及名字加入Easy排行榜
         * \param score int
         * \param name string
         * \return void
         */
        void into_easy(int score,string name);
        /** \brief 將成績及名字加入Normal排行榜
         * \param score int
         * \param name string
         * \return void
         */
        void into_normal(int score,string name);
        /** \brief 將成績及名字加入Hard排行榜
         * \param score int
         * \param name string
         * \return void
         */
        void into_hard(int score,string name);
        /** \brief 將成績及名字加入Challenge排行榜
         * \param score int
         * \param name string
         * \return void
         */
        void into_challenge(int score,string name);
};
#endif // SCOREBOARD_H
