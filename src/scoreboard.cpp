#include "scoreboard.h"
#include<string>
#include<fstream>

using namespace std;

fstream fin;

void scoreboard::into_easy(int score, string name)
{
/**
 *  開檔加入
 * \param score int
 * \param name string
 * \return void
 */
    fin.open("./note/easy_score.txt",ios::out|ios::app);
    fin<<score<<"  "<<name<<endl;
    fin.close();
}

void scoreboard::into_normal(int score, string name)
{
/**
 *  開檔加入
 * \param score int
 * \param name string
 * \return void
 */
    fin.open("./note/normal_score.txt",ios::out|ios::app);
    fin<<score<<"  "<<name<<endl;
    fin.close();
}

void scoreboard::into_hard(int score, string name)
{
/**
 *  開檔加入
 * \param score int
 * \param name string
 * \return void
 */
    fin.open("./note/hard_score.txt",ios::out|ios::app);
    fin<<score<<"  "<<name<<endl;
    fin.close();
}

void scoreboard::into_challenge(int score, string name)
{
/**
 *  開檔加入
 * \param score int
 * \param name string
 * \return void
 */
    fin.open("./note/challenge_score.txt",ios::out|ios::app);
    fin<<score<<"  "<<name<<endl;
    fin.close();
}
