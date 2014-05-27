#include "ticTacToe.h"
#include "resource.h"

#define ID_BUTTON 100

#define X 1
#define O 2

//Global Windows
HWND BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4,
     BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8, BUTTON_9; //Main buttons
HWND BUTTON_RESTART;
HWND BUTTON_RESET;
HWND STATIC_TURN;
HWND STATIC_TITLE;
HWND STATIC_XSCORE,STATIC_SCORE, STATIC_OSCORE, STATIC_DRAW_SCORE;
HWND STATIC_XVALUE, STATIC_OVALUE, STATIC_DRAW_VALUE;

//Icons
HICON xIcon = NULL;
HICON oIcon = NULL;


//Misc
HBRUSH br_txt = NULL; //text coloring
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
LRESULT CALLBACK MyWndProc2(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
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
    HWND hwnd2;

    hInstance = hInst;

    // The Window  structure
    wnd2.cbSize=sizeof(WNDCLASSEX);
    wnd2.hInstance = hInstance;
    wnd2.lpfnWndProc = MyWndProc2;                  /* This function is called by windows */
    wnd2.style = CS_HREDRAW | CS_VREDRAW;           /* Redraw */
    wnd2.cbSize = sizeof (WNDCLASSEX);
    wnd2.hIcon = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
    wnd2.hCursor = LoadCursor (NULL, IDC_ARROW);
    wnd2.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);  /* Menu */
    wnd2.cbClsExtra = 0;                            /* No extra bytes after the window class */
    wnd2.cbWndExtra = 0;                            /* structure or the window instance */
    wnd2.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(56,176,222));//GetSysColorBrush(COLOR_3DFACE);
    wnd2.lpszClassName = "MyClass1";
    wnd2.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 0, 0, 0);


    /* Register the window class, and if it fails quit the program */
   if (!RegisterClassEx (&wnd2))
        {MessageBox(NULL,"Could not register class2","Window Class Failed",MB_ICONERROR);
        }


    hwnd1 = CreateWindowEx(
                        NULL,
                        "MyClass1",
                       "Tic-Tac-Toe",
                       WS_OVERLAPPED|WS_SYSMENU,        //basic window style
                       CW_USEDEFAULT,CW_USEDEFAULT,     //set starting point to default value
                       646, 625,                        //set all the dimensions to default value
                       NULL,                            //no parent window
                       NULL,                            //no menu
                       hInstance,
                       NULL);                           //no parameters to pass
    ShowWindow(hwnd1, SW_SHOW);              //display the window on the screen
    UpdateWindow(hwnd1);             //make sure the window is updated correctly
    // Place the Window in the center of the screen
    CenterWindow(hwnd1);

    while(GetMessage(&msg, NULL, 0, 0))      //message loop
    {
       TranslateMessage(&msg);
       DispatchMessage(&msg);
    }
    return msg.wParam;
    }

LRESULT CALLBACK MyWndProc1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND button;
    HDC hdc = GetDC(hwnd);
    HDC hdcMem;
    PAINTSTRUCT ps;
    BITMAP bitmap;
    HBITMAP hbmplogo = NULL;
    hbmplogo = (HBITMAP)LoadImage(hInstance, "logo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbmplogo, sizeof(bitmap), &bitmap);


    switch(msg)
    {

        case WM_PAINT:
              hdc = BeginPaint(hwnd, &ps);
              hdcMem = CreateCompatibleDC(hdc);
              SelectObject(hdcMem, hbmplogo);

            // Copy the bits from the memory DC into the current dc
                BitBlt(hdc,
                10,
                10,
                bitmap.bmWidth, bitmap.bmHeight,
                hdcMem, 0, 0, SRCCOPY);

            // Restore the old bitmap
                DeleteDC(hdcMem);

            EndPaint(hwnd, &ps);

             break;

         case WM_CLOSE:
            if(MessageBox(hwnd, "Are you sure? ", "Message", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
                {
                    DestroyWindow(hwnd);
                    PostQuitMessage(0);
                }

            break ;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK MyWndProc2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{  char *buf = new char;
	switch(msg)
	{
	    case WM_CTLCOLORSTATIC:

            hwndCtl = (HWND)lParam;
            hdcDisp = (HDC)wParam;

            if(hwndCtl == GetDlgItem(hwnd, IDS_TITLE))
            {
                    SetTextColor(hdcDisp, RGB(255, 165, 0));
                    SetBkColor(hdcDisp, RGB(255, 255, 255));
                    return (LONG)br_txt;
            }

            if(hwndCtl == GetDlgItem(hwnd, IDS_TURN))
            {
                    if(turnColor == 1) //Crosses turn
                    {
                            SetTextColor(hdcDisp, RGB(230, 30, 15));
                    }
                    else if(turnColor == 2) //Noughts turn
                    {
                            SetTextColor(hdcDisp, RGB(15, 30, 230));
                    }
                    else if(turnColor == 3) //draw wins
                    {
                            SetTextColor(hdcDisp, RGB(255, 255, 0));
                    }

                    SetBkColor(hdcDisp, RGB(255, 255, 255));
                    return (LONG)br_txt;
            }

            //Set X score colors
            if(hwndCtl == GetDlgItem(hwnd, IDS_XSCORE))
            {
                    SetTextColor(hdcDisp, RGB(15, 30, 230));
                    SetBkMode(hdcDisp, TRANSPARENT);
                    return (LONG)br_txt;
            }
            if(hwndCtl == GetDlgItem(hwnd, IDS_XVALUE))
            {
                    SetTextColor(hdcDisp, RGB(0, 0, 0));
                    SetBkColor(hdcDisp, RGB(255, 255, 255));
                    return (LONG)br_txt;
            }

            //Set Draw score colors
            if(hwndCtl == GetDlgItem(hwnd, IDS_DRAW_SCORE))
            {
                    SetTextColor(hdcDisp, RGB(0, 0, 0));
                    SetBkMode(hdcDisp, TRANSPARENT);
                    return (LONG)br_txt;
            }
            if(hwndCtl == GetDlgItem(hwnd, IDS_DRAW_VALUE))
            {
                    SetTextColor(hdcDisp, RGB(0, 0, 0));
                    SetBkColor(hdcDisp, RGB(255, 255, 255));
                    return (LONG)br_txt;
            }

            //Set O score colors
            if(hwndCtl == GetDlgItem(hwnd, IDS_OSCORE))
            {
                    SetTextColor(hdcDisp, RGB(230, 30, 15));
                    SetBkMode(hdcDisp, TRANSPARENT);
                    return (LONG)br_txt;
            }
            if(hwndCtl == GetDlgItem(hwnd, IDS_OVALUE))
            {
                    SetTextColor(hdcDisp, RGB(0, 0, 0));
                    SetBkColor(hdcDisp, RGB(255, 255, 255));
                    return (LONG)br_txt;
            }

                break;



        case WM_CREATE:

            br_txt = CreateSolidBrush(RGB(0, 0, 0));
            xIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_X));
            oIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_O));


            InitGUI(hwnd, reinterpret_cast<CREATESTRUCT*>(lParam));

            for(int i=0;i<9;i++)
            {
                    bStatus[i] = 0;
            }

                break;

        case WM_COMMAND:

            switch(LOWORD(wParam))
            {
                    case IDB_1: SetBox(0, BUTTON_1); break;

                    case IDB_2: SetBox(1, BUTTON_2); break;

                    case IDB_3: SetBox(2, BUTTON_3); break;

                    case IDB_4: SetBox(3, BUTTON_4); break;

                    case IDB_5: SetBox(4, BUTTON_5); break;

                    case IDB_6: SetBox(5, BUTTON_6); break;

                    case IDB_7: SetBox(6, BUTTON_7); break;

                    case IDB_8: SetBox(7, BUTTON_8); break;

                    case IDB_9: SetBox(8, BUTTON_9); break;

                    case IDB_RESTART:

                                RestartGame();
                        break;

                    case IDB_RESET:
                        xScore=0;
                        oScore=0;
                        DrawScore=0;
                        sprintf(buf, "%g", xScore);
                        SetWindowText(STATIC_XVALUE, buf);
                        sprintf(buf, "%g", oScore);
                        SetWindowText(STATIC_OVALUE, buf);
                        sprintf(buf, "%g", DrawScore);
                        SetWindowText(STATIC_DRAW_VALUE, buf);
                        delete buf;
                        buf = 0;

                        break;

                    //Menu items
                    case IDR_FILE_QUIT:
                        if(MessageBox(hwnd, "Do you really want to quit? ", "Message", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
                            {
                                DestroyWindow(hwnd);
                                PostQuitMessage(0);
                            }

                        break;

                    case IDR_OPTIONS_RESTART:

                        RestartGame();

                        break;
                    case IDR_OPTIONS_RESET:
                        xScore=0;
                        oScore=0;
                        DrawScore=0;
                        sprintf(buf, "%g", xScore);
                        SetWindowText(STATIC_XVALUE, buf);
                        sprintf(buf, "%g", oScore);
                        SetWindowText(STATIC_OVALUE, buf);
                        sprintf(buf, "%g", DrawScore);
                        SetWindowText(STATIC_DRAW_VALUE, buf);
                        delete buf;
                        buf = 0;

                        break;

                    case IDR_HELP_ABOUT:

                        DialogBox(GetModuleHandle(NULL),
                                MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);

                        break;

            }

            break;


        case WM_CLOSE:
            {
                    if(MessageBox(hwnd, "Are you sure? ", "Message", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
                    DestroyWindow(hwnd);
            }

            break;
	    case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void InitGUI(const HWND hwnd, CREATESTRUCT *cs)
{
       RECT rc = {45, 70, 150, 150};

       BUTTON_1 = CreateControl("BUTTON",       //Type of control
                                "",             //Caption for control
                                hwnd,           //Parent window
                                cs->hInstance,  //HINSTANCE
                                BS_ICON,        //dwStyle
                                0,              //dwExStyle
                                rc,             //RECT struct
                                IDB_1           //ID
                                );

        rc.left += 150;
        BUTTON_2 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_2
                                );

        rc.left += 150;
        BUTTON_3 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_3
                                );

        rc.left -= 300;
        rc.top += 150;
        BUTTON_4 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_4
                                );

        rc.left += 150;
        BUTTON_5 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_5
                                );

        rc.left += 150;
        BUTTON_6 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_6
                                );

        rc.left -= 300;
        rc.top += 150;
        BUTTON_7 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_7
                                );

        rc.left += 150;
        BUTTON_8 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_8
                                );

        rc.left += 150;
        BUTTON_9 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_9
                                );

        SetRect(&rc, 226, 20, 124, 18);

        STATIC_TURN = CreateControl("STATIC",
                                    "Crosses turn",
                                    hwnd,
                                    cs->hInstance,
                                    SS_SIMPLE,
                                    0,
                                    rc,
                                    IDS_TURN
                                    );

        SetRect(&rc, 510, 240, 90, 19);
        STATIC_SCORE = CreateControl("STATIC",
                                      "SCORE:",
                                      hwnd,
                                      cs->hInstance,
                                      SS_SIMPLE,
                                      0,
                                      rc,
                                      NULL
                                      );

        SetRect(&rc, 510, 93, 90, 30);
        BUTTON_RESTART = CreateControl("BUTTON",
                                       "Restart",
                                       hwnd,
                                       cs->hInstance,
                                       BS_PUSHBUTTON,
                                       WS_EX_CLIENTEDGE,
                                       rc,
                                       IDB_RESTART
                                       );

        SetRect(&rc, 510, 143, 70, 30);
        BUTTON_RESET = CreateControl("BUTTON",
                                       "Reset",
                                       hwnd,
                                       cs->hInstance,
                                       BS_PUSHBUTTON,
                                       WS_EX_CLIENTEDGE,
                                       rc,
                                       IDB_RESET
                                       );

        SetRect(&rc, 510, 270, 90, 19);
        STATIC_XSCORE = CreateControl("STATIC",
                                      "Crosses:",
                                      hwnd,
                                      cs->hInstance,
                                      SS_SIMPLE,
                                      0,
                                      rc,
                                      IDS_XSCORE
                                      );

        rc.left += 95;
        STATIC_XVALUE = CreateControl("STATIC",
                                      "0",
                                      hwnd,
                                      cs->hInstance,
                                      SS_SIMPLE,
                                      0,
                                      rc,
                                      IDS_XVALUE
                                      );

        SetRect(&rc, 515, 320, 90, 19);
        STATIC_DRAW_SCORE = CreateControl("STATIC",
                                        "Draws:",
                                        hwnd,
                                        cs->hInstance,
                                        SS_SIMPLE,
                                        0,
                                        rc,
                                        IDS_DRAW_SCORE
                                        );

        rc.left += 90;
        STATIC_DRAW_VALUE = CreateControl("STATIC",
                                        "0",
                                        hwnd,
                                        cs->hInstance,
                                        SS_SIMPLE,
                                        0,
                                        rc,
                                        IDS_DRAW_VALUE
                                        );

        SetRect(&rc, 511, 295, 90, 19);
        STATIC_OSCORE = CreateControl("STATIC",
                                      "Noughts:",
                                      hwnd,
                                      cs->hInstance,
                                      SS_SIMPLE,
                                      0,
                                      rc,
                                      IDS_OSCORE
                                      );

        rc.left += 94;
        STATIC_OVALUE = CreateControl("STATIC",
                                      "0",
                                      hwnd,
                                      cs->hInstance,
                                      SS_SIMPLE,
                                      0,
                                      rc,
                                      IDS_OVALUE
                                      );
}


void SetBox(int b, HWND hwnd)
{
        if(bStatus[b] == 0)
        {
        counter++;

        if(turn == 0) // if Crosses turn
        {
                bStatus[b] = X;
                turn = 1;
                SetTurn();
                CheckWinner();
                if(draw == false)
                    SendMessage(hwnd, BM_SETIMAGE, IMAGE_ICON, reinterpret_cast<LPARAM>(xIcon));

        }
        else if(turn == 1) // if Noughts turn
        {
                bStatus[b] = O;
                turn = 0;
                SetTurn();
                CheckWinner();
                if(draw == false)
                    SendMessage(hwnd, BM_SETIMAGE, IMAGE_ICON, reinterpret_cast<LPARAM>(oIcon));
        }
        }
}

void SetTurn()
{
        if(turn == 0)
        {
                SetWindowText(STATIC_TURN, "Crosses Turn  ");
                turnColor = 1;
        }
        else if(turn == 1)
        {
                SetWindowText(STATIC_TURN, "Noughts Turn    ");
                turnColor = 2;
        }
}

void CheckWinner()
{

        /* Check Crosses Victory */
        //Check Rows
        if(bStatus[0] == X && bStatus[1] == X && bStatus[2] == X)
        {
                ShowWinner("x");


        }

        if(bStatus[3] == X && bStatus[4] == X && bStatus[5] == X)
        {
                ShowWinner("x");
        }

        if(bStatus[6] == X && bStatus[7] == X && bStatus[8] == X)
        {
                ShowWinner("x");
        }

        //Check Collums
        if(bStatus[0] == X && bStatus[3] == X && bStatus[6] == X)
        {
                ShowWinner("x");
        }

        if(bStatus[1] == X && bStatus[4] == X && bStatus[7] == X)
        {
                ShowWinner("x");
        }

        if(bStatus[2] == X && bStatus[5] == X && bStatus[8] == X)
        {
                ShowWinner("x");
        }

        //Check Diagonals
        if(bStatus[0] == X && bStatus[4] == X && bStatus[8] == X)
        {
                ShowWinner("x");
        }

        if(bStatus[2] == X && bStatus[4] == X && bStatus[6] == X)
        {
                ShowWinner("x");
        }


        //-------------------------------------------------------


        /* Check noughts Victory */
        //Check Rows
        if(bStatus[0] == O && bStatus[1] == O && bStatus[2] == O)
        {
                ShowWinner("o");
        }

        if(bStatus[3] == O && bStatus[4] == O && bStatus[5] == O)
        {
                ShowWinner("o");
        }

        if(bStatus[6] == O && bStatus[7] == O && bStatus[8] == O)
        {
                ShowWinner("o");
        }

        //Check Collums
        if(bStatus[0] == O && bStatus[3] == O && bStatus[6] == O)
        {
                ShowWinner("o");
        }

        if(bStatus[1] == O && bStatus[4] == O && bStatus[7] == O)
        {
                ShowWinner("o");
        }

        if(bStatus[2] == O && bStatus[5] == O && bStatus[8] == O)
        {
                ShowWinner("o");
        }

        //Check Diagonals
        if(bStatus[0] == O && bStatus[4] == O && bStatus[8] == O)
        {
                ShowWinner("o");
        }

        if(bStatus[2] == O && bStatus[4] == O && bStatus[6] == O)
        {
                ShowWinner("o");
        }


        else if(counter >= 9 && over == false)
        {
                ShowWinner("draw");
        }
}

void ShowWinner(LPCSTR winner)
{
        if(winner == "x")
        {
                SetWindowText(STATIC_TURN, "Crosses Win!    ");
                MessageBox(hwnd1, "Crosses Win", "Message", MB_ICONASTERISK);
        }
        else if(winner == "o")
        {
                SetWindowText(STATIC_TURN, "Noughts Win!      ");
                MessageBox(hwnd1, "Noughts Win", "Message", MB_ICONASTERISK);
        }
        else if(winner == "draw")
        {
                turnColor = 0;
                SetWindowText(STATIC_TURN, "          DRAW            ");
                MessageBox(hwnd1, "DRAW !", "Message", MB_ICONASTERISK);

        }

        for(int i=0;i<9;i++)
        {
                bStatus[i] = -1; //Lock every tile
        }

        UpdateScores(winner);
        over = true;
}

void UpdateScores(LPCSTR winner)
{
        char *buf = new char;

        if(winner == "x")
        {
                xScore++;
                sprintf(buf, "%g", xScore);
                SetWindowText(STATIC_XVALUE, buf);
        }
        if(winner == "o")
        {
                oScore++;
                sprintf(buf, "%g", oScore);
                SetWindowText(STATIC_OVALUE, buf);
        }
        if(winner == "draw")
        {
                DrawScore++;
                sprintf(buf, "%g", DrawScore);
                SetWindowText(STATIC_DRAW_VALUE, buf);

        }

        delete buf;
        buf = 0;
}

void RestartGame()
{
            for(int i=0;i<9;i++)
            {
                bStatus[i] = 0;
            }

            // Reset all the icons
            SendMessage(BUTTON_1, BM_SETIMAGE, IMAGE_ICON, 0);
            SendMessage(BUTTON_2, BM_SETIMAGE, IMAGE_ICON, 0);
            SendMessage(BUTTON_3, BM_SETIMAGE, IMAGE_ICON, 0);
            SendMessage(BUTTON_4, BM_SETIMAGE, IMAGE_ICON, 0);
            SendMessage(BUTTON_5, BM_SETIMAGE, IMAGE_ICON, 0);
            SendMessage(BUTTON_6, BM_SETIMAGE, IMAGE_ICON, 0);
            SendMessage(BUTTON_7, BM_SETIMAGE, IMAGE_ICON, 0);
            SendMessage(BUTTON_8, BM_SETIMAGE, IMAGE_ICON, 0);
            SendMessage(BUTTON_9, BM_SETIMAGE, IMAGE_ICON, 0);

            turn = 0;
            turnColor = 1;
            SetTurn();
            over = false;
            draw = false;
            counter = 0;
}

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
        switch(msg)
        {
                case WM_COMMAND:

                    switch(LOWORD(wParam))
                    {
                            case IDOK:

                                EndDialog(hwnd, IDOK);

                                break;

                            case IDCANCEL:

                                EndDialog(hwnd, IDCANCEL);

                                break;
                    }

                    break;

                default:

                    return FALSE;

                    break;
        }

        return TRUE;
}
