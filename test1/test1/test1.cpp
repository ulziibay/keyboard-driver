// test1.cpp : Defines the entry point for the application.
// This is a testing windows application for the touchscreen simulator
// First test: block all keyboard input

#include "stdafx.h"
#include "test1.h"
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <Windowsx.h>
#include <hash_map>
#include <utility>
#define MAX_LOADSTRING 100

using namespace std;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HHOOK hhkLowLevelKybd;  // the variable to handle the low level hook
BOOL lockState = TRUE; // setting whether to log or not log the key
ofstream out; // file output variable

INPUT mouse_input; // output to mouse
wifstream infile; 
wstring line;
std::hash_map<int, pair<float, float> > coordinate_mapping ;


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
   //SendInput(1,&mouse_input,sizeof(mouse_input));
   
   
   pair<float, float>  my_pair(0,0);
   coordinate_mapping[27] = my_pair;
   my_pair.first = 2.3;
   my_pair.second = 0;
   coordinate_mapping[112] = my_pair;
   my_pair.first = 4;
   my_pair.second = 0;
   coordinate_mapping[113] = my_pair;
   my_pair.first = 5.6;
   my_pair.second = 0;
   coordinate_mapping[114] = my_pair;
   my_pair.first = 7.3;
   my_pair.second = 0;
   coordinate_mapping[115] = my_pair;
    my_pair.first = 9.5;
   my_pair.second = 0;
   coordinate_mapping[116] = my_pair;
   my_pair.first = 11.2;
   my_pair.second = 0;
   coordinate_mapping[117] = my_pair;
   my_pair.first = 14.5;
   my_pair.second = 0;
   coordinate_mapping[118] = my_pair;
   my_pair.first = 12.9;
   my_pair.second = 0;
   coordinate_mapping[119] = my_pair;
   my_pair.first = 14.5;
   my_pair.second = 0;
   coordinate_mapping[119] = my_pair;
   my_pair.first = 16.7;
   my_pair.second = 0;
   coordinate_mapping[120] = my_pair;
   my_pair.first = 18.4;
   my_pair.second = 0;
   coordinate_mapping[121] = my_pair;
   my_pair.first = 20.1;
   my_pair.second = 0;
   coordinate_mapping[122] = my_pair;
   my_pair.first = 21.7;
   my_pair.second = 0;
   coordinate_mapping[123] = my_pair;
   my_pair.first = 24;
   my_pair.second = 0;
   coordinate_mapping[45] = my_pair;
   my_pair.first = 26;
   my_pair.second = 0;
   coordinate_mapping[46] = my_pair;
   my_pair.first = 0.1;
   my_pair.second = 1.5;
   coordinate_mapping[192] = my_pair;
   my_pair.first = 1.9;
   my_pair.second = 1.5;
   coordinate_mapping[49] = my_pair;
   my_pair.first = 3.8;
   my_pair.second = 1.5;
   coordinate_mapping[50] = my_pair;	
   my_pair.first = 5.7;
   my_pair.second = 1.5;
   coordinate_mapping[51] = my_pair;
   my_pair.first = 3.8;
   my_pair.second = 1.5;
   coordinate_mapping[50] = my_pair;
   my_pair.first = 5.7;
   my_pair.second = 1.5;
   coordinate_mapping[51] = my_pair;
   my_pair.first = 7.6;
   my_pair.second = 1.5;
   coordinate_mapping[52] = my_pair;
   my_pair.first = 9.5;
   my_pair.second = 1.5;
   coordinate_mapping[53] = my_pair;
   my_pair.first = 11.4;
   my_pair.second = 1.5;
   coordinate_mapping[54] = my_pair;
   my_pair.first = 13,3;
   my_pair.second = 1.5;
   coordinate_mapping[55] = my_pair;
   my_pair.first = 15.2;
   my_pair.second = 1.5;
   coordinate_mapping[56] = my_pair;
   my_pair.first = 17.1;
   my_pair.second = 1.5;
   coordinate_mapping[57] = my_pair;
   my_pair.first = 19;
   my_pair.second = 1.5;
   coordinate_mapping[48] = my_pair;
   my_pair.first = 21.9;
   my_pair.second = 1.5;
   coordinate_mapping[189] = my_pair;
   my_pair.first = 23.8;
   my_pair.second = 1.5;
   coordinate_mapping[187] = my_pair;
   my_pair.first = 25.3;
   my_pair.second = 1.5;
   coordinate_mapping[8] = my_pair;
   my_pair.first = 0.5;
   my_pair.second = 3.4;
   coordinate_mapping[9] = my_pair;
   my_pair.first = 2.4;
   my_pair.second = 3.4;
   coordinate_mapping[81] = my_pair;
   my_pair.first = 4.3;
   my_pair.second = 3.4;
   coordinate_mapping[87] = my_pair;
   my_pair.first = 6.2;
   my_pair.second = 3.4;
   coordinate_mapping[69] = my_pair;
   my_pair.first = 8.1;
   my_pair.second = 3.4;
   coordinate_mapping[82] = my_pair;
   my_pair.first = 10;
   my_pair.second = 3.4;
   coordinate_mapping[84] = my_pair;
   my_pair.first = 11.9;
   my_pair.second = 3.4;
   coordinate_mapping[89] = my_pair;
   my_pair.first = 13.8;
   my_pair.second = 3.4;
   coordinate_mapping[85] = my_pair;
   my_pair.first = 15.7;
   my_pair.second = 3.4;
   coordinate_mapping[73] = my_pair;
   my_pair.first = 17.6;
   my_pair.second = 3.4;
   coordinate_mapping[79] = my_pair;
   my_pair.first = 19.5;
   my_pair.second = 3.4;
   coordinate_mapping[80] = my_pair;
   my_pair.first = 21.4;
   my_pair.second = 3.4;
   coordinate_mapping[219] = my_pair;
   my_pair.first = 23.3;
   my_pair.second = 3.4;
   coordinate_mapping[221] = my_pair;
   my_pair.first = 25.4;
   my_pair.second = 3.4;
   coordinate_mapping[220] = my_pair;
   my_pair.first = 0.7;
   my_pair.second = 5.3;
   coordinate_mapping[20] = my_pair;
   my_pair.first = 2.6;
   my_pair.second = 5.3;
   coordinate_mapping[65] = my_pair;
   my_pair.first = 4,5;
   my_pair.second = 5.3;
   coordinate_mapping[83] = my_pair;
   my_pair.first = 6.4;
   my_pair.second = 5.3;
   coordinate_mapping[68] = my_pair;
   my_pair.first = 8.3;
   my_pair.second = 5.3;
   coordinate_mapping[70] = my_pair;
   my_pair.first = 10.2;
   my_pair.second = 5.3;
   coordinate_mapping[71] = my_pair;
   my_pair.first = 12.1;
   my_pair.second = 5.3;
   coordinate_mapping[72] = my_pair;
   my_pair.first = 14;
   my_pair.second = 5.3;
   coordinate_mapping[74] = my_pair;
   my_pair.first = 16.9;
   my_pair.second = 5.3;
   coordinate_mapping[75] = my_pair;
   my_pair.first = 18.8;
   my_pair.second = 5.3;
   coordinate_mapping[76] = my_pair;
   my_pair.first = 19.7;
   my_pair.second = 5.3;
   coordinate_mapping[186] = my_pair;
   my_pair.first = 21.6;
   my_pair.second = 5.3;
   coordinate_mapping[222] = my_pair;
   my_pair.first = 24.5;
   my_pair.second = 5.3;
   coordinate_mapping[13] = my_pair;
   my_pair.first = 1.2;
   my_pair.second = 7.2;
   coordinate_mapping[160] = my_pair;
   my_pair.first = 3.1;
   my_pair.second = 7.2;
   coordinate_mapping[90] = my_pair;
   my_pair.first = 5;
   my_pair.second = 7.2;
   coordinate_mapping[88] = my_pair;
   my_pair.first = 10.7;
   my_pair.second = 7.2;
   coordinate_mapping[66] = my_pair;
   my_pair.first = 12.6;
   my_pair.second = 7.2;
   coordinate_mapping[78] = my_pair;
   my_pair.first = 14.5;
   my_pair.second = 7.2;
   coordinate_mapping[77] = my_pair;
   my_pair.first = 16.4;
   my_pair.second = 7.2;
   coordinate_mapping[188] = my_pair;
   my_pair.first = 18.3;
   my_pair.second = 7.2;
   coordinate_mapping[190] = my_pair;
   my_pair.first = 20.2;
   my_pair.second = 7.2;
   coordinate_mapping[191] = my_pair;
   my_pair.first = 23.7;
   my_pair.second = 7.2;
   coordinate_mapping[161] = my_pair;
   my_pair.first = 0.5;
   my_pair.second = 9.1;
   coordinate_mapping[162] = my_pair;
   my_pair.first = 4.3;
   my_pair.second = 9.1;
   coordinate_mapping[91] = my_pair;
   my_pair.first = 6.2;
   my_pair.second = 9.1;
   coordinate_mapping[164] = my_pair;
   my_pair.first = 11.4;
   my_pair.second = 9.1;
   coordinate_mapping[32] = my_pair;
   my_pair.first = 16;
   my_pair.second = 9.1;
   coordinate_mapping[165] = my_pair;
   my_pair.first = 17.9;
   my_pair.second = 9.1;
   coordinate_mapping[93] = my_pair;
   my_pair.first = 19.8;
   my_pair.second = 9.1;
   coordinate_mapping[163] = my_pair;


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
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
		   wstring s = std::to_wstring(p->vkCode);
		   OutputDebugString (s.c_str());
		   
		   /*
		   s = L"keyboard status:" + std::to_wstring(infile.good()) + L"\n";
		   OutputDebugString (s.c_str());
		   while (infile.good()) {
				//getline ( infile, line, '\n' );
				infile >> line;
				//std::cout << "Line is " << line << endl;
				OutputDebugString (line.c_str());
				out << "Line is " << line.c_str() <<endl;
				//printf ("%s \n", line);
			}*/


		   
		   //infile >> line;
				//std::cout << "Line is " << line << endl;
			//OutputDebugString (line.c_str());

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
				   mouse_input.mi.dy -=  50 ;
			       SendInput(1,&mouse_input,sizeof(mouse_input));
				   break;
			case 40: 
				   mouse_input.mi.dy += 50 ;
			       SendInput(1,&mouse_input,sizeof(mouse_input));
				   break;
			case 37: 
				   mouse_input.mi.dx -= 50 ;
			       SendInput(1,&mouse_input,sizeof(mouse_input));
				   break;
			case 39: 
				   mouse_input.mi.dx +=  50 ;
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
		infile.open( "KeyBoardPhysicalLayout.txt");

		out.open("out.txt", ios_base::app);
	    hhkLowLevelKybd  = SetWindowsHookEx( WH_KEYBOARD_LL,
                                              LowLevelKeyboardProc,
                                              hInst,
                                              0 );
		
	} else {
		out.close();

		infile.close();

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
