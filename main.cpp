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

enum{
    IDB_1, IDB_2, IDB_3, IDB_4, IDB_5, IDB_6, IDB_7, IDB_8, IDB_9,
    IDS_TURN,
    IDB_RESTART,
    IDB_RESET,
    IDB_SCORE,
    IDS_TITLE,
    IDS_XSCORE, IDS_OSCORE, IDS_DRAW_SCORE,
    IDS_XVALUE, IDS_OVALUE, IDS_DRAW_VALUE,

    };

HINSTANCE hInstance;
HWND hwnd1;
HWND hwnd2;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
LRESULT CALLBACK MyWndProc1(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Windows Procedure for the game

LRESULT CALLBACK MyWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
