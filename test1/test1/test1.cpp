// test1.cpp : Defines the entry point for the application.
// This is a testing windows application for the touchscreen simulator
// First test: block all keyboard input

#include "stdafx.h"
#include "test1.h"
#include <string>
#include <fstream>
#include <vector>
#define MAX_LOADSTRING 100

using namespace std;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HHOOK hhkLowLevelKybd;  // the variable to handle the low level hook
BOOL lockState = TRUE; // setting whether to log or not log the key
vector<PKBDLLHOOKSTRUCT> buffer;

const int MOUSESTATE = 0;
const int TOUCHSTATE = 1;

// state of the keyboard
int state = MOUSESTATE;

ofstream out; // file output variable

INPUT mouse_input; // output to mouse


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TEST1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TEST1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   mouse_input.type = INPUT_MOUSE;
   mouse_input.mi.mouseData=0;
   mouse_input.mi.dx =  300*(65536/GetSystemMetrics(SM_CXSCREEN));//x being coord in pixels
   mouse_input.mi.dy =  300*(65536/GetSystemMetrics(SM_CYSCREEN));//y being coord in pixels
   mouse_input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
   SendInput(1,&mouse_input,sizeof(mouse_input));

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

bool isAdjacent(PKBDLLHOOKSTRUCT prevKey, PKBDLLHOOKSTRUCT currentKey)
{
	return false;
}

LRESULT CALLBACK LowLevelKeyboardProc( int nCode,
                                       WPARAM wParam,
                                       LPARAM lParam)
{
 
  BOOL fEatKeystroke = FALSE;
  if (nCode == HC_ACTION)
  {
	  OutputDebugString (L"seeing some actions here\n");
     switch (wParam)
     {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
 
           // Get hook struct
           PKBDLLHOOKSTRUCT p = ( PKBDLLHOOKSTRUCT ) lParam;
		   
		   // adding the key to the buffer
		   buffer.push_back (p);
		   // keeping the buffer size constant
		   if (buffer.size() > 100) {
			   buffer.erase(buffer.begin());
		   }

		   if (state == MOUSESTATE && buffer.size() >= 40)
		   {
			   bool dragState = true;
			   int dragNum = 40;
			   for (int i = 0; i < dragNum; i++)
			   {
				   if (p->vkCode != buffer[0]->vkCode )
				   {
					   dragState = false;
				   }
			   }

			   // if detecting drag, change state to touch
			   if (dragState == true) state = TOUCHSTATE ;
		   }

		   if (state == MOUSESTATE)
		   {
			   if (isAdjacent(buffer[0], p))
			   {
			   } else {
			   }
		   }
		   else
		   {
			   if (isAdjacent(buffer[0], p))
			   {
			   } else {
			   }
		   }

		   wstring s = std::to_wstring(p->vkCode);
		   OutputDebugString (s.c_str());
		   OutputDebugString (L"\n");

		   OutputDebugString(to_wstring(buffer.size()).c_str());
		   OutputDebugString (L"\n");

		   OutputDebugString((L"state:" + to_wstring(state)).c_str());
		   OutputDebugString (L"\n");

		   OutputDebugString((L"time:" + to_wstring(p->time)).c_str());
		   OutputDebugString (L"\n");

		   out << p->vkCode << " " << p->time << endl;

           /*fEatKeystroke = (( p->vkCode == VK_TAB ) &&
                           (( p->flags & LLKHF_ALTDOWN ) != 0 )) ||
                           (( p->vkCode == VK_ESCAPE ) &&
                           (( p->flags & LLKHF_ALTDOWN ) != 0 )) ||
                           (( p->vkCode == VK_ESCAPE ) &&
                           (( GetKeyState( VK_CONTROL ) & 0x8000) != 0 ));*/
			switch (p->vkCode)
			{
			case 38: 
				   mouse_input.mi.dy -= 50;
			       SendInput(1,&mouse_input,sizeof(mouse_input));
				   break;
			case 40: 
				   mouse_input.mi.dy += 50;
			       SendInput(1,&mouse_input,sizeof(mouse_input));
				   break;
			case 37: 
				   mouse_input.mi.dx -= 50;
			       SendInput(1,&mouse_input,sizeof(mouse_input));
				   break;
			case 39: 
				   mouse_input.mi.dx += 50;
			       SendInput(1,&mouse_input,sizeof(mouse_input));
				   break;
			}
 
     }// End switch
  }// End if
 
   // Did we trap a key??
   //return( fEatKeystroke ? 1 : CallNextHookEx( NULL, nCode, wParam, lParam ));
  return 1;
}// End LowLevelKeyboardProc
 
// This function attaches a low level keyboard hook to the system and logs key strokes
// using Win32 API
void BlockKeyboardInput()
{
	if (lockState)
	{
		out.open("out.txt", ios_base::app);
	    hhkLowLevelKybd  = SetWindowsHookEx( WH_KEYBOARD_LL,
                                              LowLevelKeyboardProc,
                                              hInst,
                                              0 );
	} else {
		out.close();
		UnhookWindowsHookEx(hhkLowLevelKybd);
	}
	lockState = !(lockState);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_BLOCK:
			BlockKeyboardInput();
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
