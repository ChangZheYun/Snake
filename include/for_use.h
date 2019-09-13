#ifndef FOR_USE_H_INCLUDED
#define FOR_USE_H_INCLUDED

#include<windows.h>

/** \brief 蛇，包含蛇頭x,y、蛇長 */
struct dot
{
    int x,y;
    int num;
};

/** \brief 控制視窗大小 */
struct console
{
    console( unsigned width, unsigned height )
    {
        SMALL_RECT r;
        COORD      c;
        hConOut = GetStdHandle( STD_OUTPUT_HANDLE );

        r.Left   =
        r.Top    = 0;
        r.Right  = width -1;
        r.Bottom = height -1;
        SetConsoleWindowInfo( hConOut, TRUE, &r );

        c.X = width;
        c.Y = height;
        SetConsoleScreenBufferSize( hConOut, c );
    }

    ~console()
    {
        SetConsoleTextAttribute(    hConOut,        csbi.wAttributes );
        SetConsoleScreenBufferSize( hConOut,        csbi.dwSize      );
        SetConsoleWindowInfo(       hConOut, TRUE, &csbi.srWindow    );
    }

    void color( WORD color = 0x07 )
    {
        SetConsoleTextAttribute( hConOut, color );
    }

    HANDLE                     hConOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
};

/** \brief 控制顏色 */
void SetColor(int);

/** \brief 控制全螢幕 */
void ConsoleFullScreen();

/** \brief 控制游標 */
void gotoxy(int xpos, int ypos);

#endif // FOR_USE_H_INCLUDED
