// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#include "stdafx.h"

/******************************************************************
*                                                                 *
*  WinMain                                                        *
*                                                                 *
*  Application entrypoint                                         *
*                                                                 *
******************************************************************/


int
WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
 
    POINTER_TOUCH_INFO contact;
    BOOL bRet = TRUE;
	return 0;

    //
    // assume a maximum of 10 contacts and turn touch feedback off
    //
    InitializeTouchInjection(10, TOUCH_FEEDBACK_NONE);

    //
    // initialize the touch info structure
    //
    memset(&contact, 0, sizeof(POINTER_TOUCH_INFO));

	//contact.pointerInfo.pointerType = ; 
	keybd_event(0x5b ,0xb8,0 , 0); //Alt Press
	keybd_event(0x5b,0xb8,KEYEVENTF_KEYUP,0); // Alt Release

	Sleep(10);
	//tagPOINTER_INPUT_TYPE::PT_MOUSE

    contact.pointerInfo.pointerType = PT_TOUCH; //we're sending touch input
    contact.pointerInfo.pointerId = 0;          //contact 0
    contact.pointerInfo.ptPixelLocation.x = 300;
    contact.pointerInfo.ptPixelLocation.y = 300;
    contact.pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact.touchFlags = TOUCH_FLAG_NONE;
    contact.touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact.orientation = 90;
    contact.pressure = 64000;
    //
    // set the contact area depending on thickness
    //
    contact.rcContact.top = 300 - 10;
    contact.rcContact.bottom = 300 + 10;
    contact.rcContact.left = 300 - 10;
    contact.rcContact.right = 300 + 10;

    //
    // inject a touch down
    //
    //bRet = InjectTouchInput(1, &contact);

    //
    // if touch down was succesfull, send a touch up
    //
    if (bRet) {
        //contact.pointerInfo.pointerFlags = POINTER_FLAG_UP;

        //
        // inject a touch up
        //
        //InjectTouchInput(1, &contact);
    }


	//Setting the Pointer Flag to Drag

	//contact.pointerInfo.pointerFlags = POINTER_FLAG_UP | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
	//for(int i=0;i<1000;i++){
	//	contact.pointerInfo.ptPixelLocation.x--; // updating the X Co-ordinate to x-100 pixels
	//	InjectTouchInput(1, &contact);
	//	Sleep(10);
	//}
	// Lifts the touch input UP
	contact.pointerInfo.pointerFlags = POINTER_FLAG_UP;
	InjectTouchInput(1, &contact);


	DWORD dx = 0;
	DWORD dy = 0;
	for (int i=0; i< 1000; i++, dx++, dy++){
		mouse_event(MOUSEEVENTF_MOVE , dx, dy, 0, 0 );
	}
}

