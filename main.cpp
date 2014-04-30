#include "ticTacToe.h"
#include "resource.h"
#define ID_BUTTON 100

#define X 1
#define O 2

//Global Windows

HWND BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4,BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8, BUTTON_9;       //Main buttons
HWND BUTTON_RESTART;
HWND BUTTON_RESET;
HWND STATIC_TURN;
HWND STATIC_TITLE;
HWND STATIC_XSCORE,STATIC_SCORE, STATIC_OSCORE, STATIC_DRAW_SCORE;
HWND STATIC_XVALUE, STATIC_OVALUE, STATIC_DRAW_VALUE;

//Icons

HICON xIcon = NULL;
HICON oIcon = NULL;


HBRUSH br_txt = NULL;          //text coloring
HWND hwndCtl;
HDC  hdcDisp;

//Game control variables

float xScore = 0, oScore = 0, DrawScore = 0;
bool over = false, draw = false;
short turnColor =1;
short turn = 0, counter = 0;
int bStatus[9] = {0};
