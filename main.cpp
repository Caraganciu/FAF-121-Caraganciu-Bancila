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
void InitGUI(const HWND hwnd, CREATESTRUCT *cs);
void SetBox(int, HWND);
void SetTurn();
void CheckWinner();
void ShowWinner(LPCSTR);
void UpdateScores(LPCSTR);
void RestartGame();

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSEX wnd;
    WNDCLASSEX wnd2;
    memset(&wnd,0,sizeof(WNDCLASSEX));
	memset(&wnd2,0,sizeof(WNDCLASSEX));
    MSG msg;
    HWND hwnd1;

    hInstance = hInst;

    // The Window  structure

    wnd2.cbSize=sizeof(WNDCLASSEX);
    wnd2.hInstance = hInstance;
    wnd2.lpfnWndProc = MyWndProc;                                                 // This function is called by windows
    wnd2.style = CS_HREDRAW | CS_VREDRAW;                                          // Redraw
    wnd2.cbSize = sizeof (WNDCLASSEX);
    wnd2.hIcon = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
    wnd2.hCursor = LoadCursor (NULL, IDC_ARROW);
    wnd2.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);                                 // Menu
    wnd2.cbClsExtra = 0;                                                           // No extra bytes after the window class
    wnd2.cbWndExtra = 0;                                                           // Structure or the window instance
    wnd2.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(56,176,222));                // GetSysColorBrush(COLOR_3DFACE);
    wnd2.lpszClassName = "MyClass1";
    wnd2.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 0, 0, 0);


   // Register the window class, and if it fails quit the program

   if (!RegisterClassEx (&wnd2))
        {MessageBox(NULL,"Could not register class2","Window Class Failed",MB_ICONERROR);
        }


    hwnd1 = CreateWindowEx(
                        NULL,
                        "MyClass1",
                       "Tic-Tac-Toe",
                       WS_OVERLAPPED|WS_SYSMENU,                         //basic window style
                       CW_USEDEFAULT,CW_USEDEFAULT,                      //set starting point to default value
                       646, 625,                                         //set all the dimensions to default value
                       NULL,                                             //no parent window
                       NULL,                                             //no menu
                       hInstance,
                       NULL);                                            //no parameters to pass
    ShowWindow(hwnd1, SW_SHOW);                                          //display the window on the screen
    UpdateWindow(hwnd1);                                                 //make sure the window is updated correctly

    // Place the Window in the center of the screen

    CenterWindow(hwnd1);

    while(GetMessage(&msg, NULL, 0, 0))                                  //message loop
    {
       TranslateMessage(&msg);
       DispatchMessage(&msg);
    }
    return msg.wParam;
    }
