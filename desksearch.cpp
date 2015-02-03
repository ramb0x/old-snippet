// desksearch.cpp : Defines the entry point for the console application.
//
/*

#include "stdafx.h"
#include <omp.h>
#include <stdio.h>
#include <boost/filesystem.hpp>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

bool find_file( const path & dir_path,         // in this directory,
            const std::string & file_name, // search for this name,
            path & path_found ) {
				// placing path here if found
if ( !exists( dir_path ) ) return false;
directory_iterator end_itr; // default construction yields past-the-end
try {
#pragma omp parallel for
for ( directory_iterator itr( dir_path );  itr != end_itr;  ++itr ) {
    if ( is_directory(itr->path()) && itr->path().filename().string() != "$Recycle.Bin" )
       find_file( itr->path(), file_name, path_found ) ;
	//else
		//cout << itr->path() << "\n";//filename().string();
}
} catch(...) {return true;};
return false;
}*/


#include "screenopps.hpp"
#define SAVE_PATH "C:/screenshots/"
#include <iostream>
#include <windows.h>
bool once=false;
HWND HW;



long __stdcall WindowProcedure ( HWND window, unsigned int msg, WPARAM wp, LPARAM lp )
{
	
			 RECT mappedRect, tmpRect, myRect;
    HBRUSH myBrush;
    BITMAP bm;
    PAINTSTRUCT ps;
    HDC mDC;
    HBITMAP tmpBmp;
	
	switch ( msg )
		{


    
    case WM_LBUTTONDOWN:
        if (bMouseSelectionEnabled)
        {
            bRubberBanding = true;
            mouseClickDownPos.x = LOWORD(lParam);
            mouseClickDownPos.y = HIWORD(lParam);

            cmp = mouseClickDownPos;
            rectRegion.left = min(cmp.x, mouseClickDownPos.x);
            rectRegion.right = max(cmp.x, mouseClickDownPos.x);
            rectRegion.top = min(cmp.y, mouseClickDownPos.y);
            rectRegion.bottom = max(cmp.y, mouseClickDownPos.y);
            normalizeSelRect();
            InvalidateRect(mHwnd, NULL, isBkgTransparent);
            PostMessage(GetParent(hWnd),  WM_COMMAND, GetDlgCtrlID(hWnd), (LPARAM)hWnd);
        }
        return 1;

    case WM_LBUTTONUP:
        if (bMouseSelectionEnabled)
            if (bRubberBanding)
            {
                bRubberBanding = false;
                mouseClickUpPos.x = LOWORD(lParam);
                mouseClickUpPos.y = HIWORD(lParam);

                rectRegion.left = min(mouseClickUpPos.x, mouseClickDownPos.x);
                rectRegion.right = max(mouseClickUpPos.x, mouseClickDownPos.x);
                rectRegion.top = min(mouseClickUpPos.y, mouseClickDownPos.y);
                rectRegion.bottom = max(mouseClickUpPos.y, mouseClickDownPos.y);

                normalizeSelRect();
                InvalidateRect(mHwnd, NULL, isBkgTransparent);
                PostMessage(GetParent(hWnd),  WM_COMMAND, GetDlgCtrlID(hWnd), (LPARAM)hWnd);
            }
        return 1;

    case WM_MOUSEMOVE:
        if (bMouseSelectionEnabled)
            if (bRubberBanding)
            {
                cmp.x = LOWORD(lParam);
                cmp.y = HIWORD(lParam);

                rectRegion.left = min(cmp.x, mouseClickDownPos.x);
                rectRegion.right = max(cmp.x, mouseClickDownPos.x);
                rectRegion.top = min(cmp.y, mouseClickDownPos.y);
                rectRegion.bottom = max(cmp.y, mouseClickDownPos.y);
                //                UpdateWindow(hWnd);
                //RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW);
                normalizeSelRect();
                InvalidateRect(hWnd, NULL, false);
                PostMessage(GetParent(hWnd),  WM_COMMAND, GetDlgCtrlID(hWnd), (LPARAM)hWnd);
                //       printf("Message posted\n");
            }
        return 0;


    case WM_ERASEBKGND:
        if (isBkgTransparent)
        {
            GetClientRect(hWnd, &myRect);
            myBrush = (HBRUSH) GetWindowLong(hWnd, GCL_HBRBACKGROUND);
            FillRect((HDC)wParam, &myRect, myBrush);
            printf("background cleared\n");
        }
        return true;

    case WM_SETCURSOR:
        SetCursor(mCursor);
        return true;
 
			////
		case WM_LBUTTONDOWN:
			std::cout << "\nmouse left button down at (" << LOWORD ( lp )
			          << ',' << HIWORD ( lp ) << ")\n" ;
			break;

		// fall thru
		case WM_PAINT:
		{

			if (!once) {
				once=true;
			int x, y, w, h;
			// get screen dimensions
			x  = GetSystemMetrics ( SM_XVIRTUALSCREEN );
			y  = GetSystemMetrics ( SM_YVIRTUALSCREEN );
			w   = GetSystemMetrics ( SM_CXVIRTUALSCREEN ) - x;
			h   = GetSystemMetrics ( SM_CYVIRTUALSCREEN ) - y;
			// copy screen to bitmap
			HDC     hScreen = GetDC ( NULL );
			HDC     hDC     = CreateCompatibleDC ( hScreen );
			HBITMAP hBitmap = CreateCompatibleBitmap ( hScreen, w, h );
			HGDIOBJ old_obj = SelectObject ( hDC, hBitmap );
			BOOL    bRet    = BitBlt ( hDC, 0, 0, w, h, hScreen, x, y, SRCCOPY );
			// clean up
			SelectObject ( hDC, old_obj );
			DeleteDC ( hDC );
			ReleaseDC ( NULL, hScreen );
			PAINTSTRUCT 	ps;
			HDC 			hdc;
			BITMAP bitmap;
			HDC 			hdcMem;
			HGDIOBJ 		oldBitmap;
			hdc = BeginPaint ( window, &ps );
			hdcMem = CreateCompatibleDC ( hdc );
			oldBitmap = SelectObject ( hdcMem, hBitmap );
			GetObject ( hBitmap, sizeof ( bitmap ), &bitmap );
			BitBlt ( hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY );
			SelectObject ( hdcMem, oldBitmap );
			DeleteDC ( hdcMem );
			EndPaint ( window, &ps );
			DeleteObject ( hBitmap );
			}
			
        mDC = BeginPaint(hWnd, &ps);

        GetClientRect(hWnd, &tmpRect);
    //        GetObject(mBmp, sizeof(bm), &bm);
        mappedRect.left = mLeft * tmpRect.right;
        mappedRect.right = mRight * tmpRect.right;
        mappedRect.top = mTop * tmpRect.bottom;
        mappedRect.bottom = mBottom * tmpRect.bottom;

        redraw();
        if  (mBmp) drawRect(mDC, mappedRect, RGB(0,0,255));
        DeleteObject(tmpBmp);
        EndPaint(hWnd, &ps);
			break;
		}

		case WM_DESTROY:
		{
			std::cout << "\ndestroying window\n" ;
			PostQuitMessage ( 0 );
			return 0L;
		}

		default:
			std::cout << '.' ;
			return DefWindowProc ( window, msg, wp, lp ) ;
		}
}
LRESULT CALLBACK keyboardHookProc ( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( nCode < 0 )
		return CallNextHookEx ( NULL, nCode, wParam, lParam );

	KBDLLHOOKSTRUCT *p = ( KBDLLHOOKSTRUCT * ) lParam;

	if ( nCode == HC_ACTION )
		{
			/*
			        
			        if(p->vkCode == VK_LSHIFT || p->vkCode == VK_RSHIFT){
			                if(wParam == WM_KEYDOWN)			                
			                        shift = true;
			                else
								   shift = false;
			                } 
		}

	// Check if F12 + CTRL is pressed, if yes -> exit
	
	if ( wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN ) // If key has been pressed
		{
			
			// Virtual key codes reference:
			http://msdn.microsoft.com/en-us/library/dd375731%28v=VS.85%29.aspx
			switch ( p->vkCode ) 
				{
			case VK_ESCAPE:
				if (HW != NULL)
					DestroyWindow(HW);
				break;
				case VK_F12:
				{
					LPCWSTR  myclass = ( LPCWSTR ) "myclass" ;
					WNDCLASSEX wndclass = { sizeof ( WNDCLASSEX ), CS_DBLCLKS, WindowProcedure,
					                        0, 0, GetModuleHandle ( 0 ), LoadIcon ( 0, IDI_APPLICATION ),
					                        LoadCursor ( 0, IDC_ARROW ), HBRUSH ( COLOR_WINDOW + 1 ),
					                        0, myclass, LoadIcon ( 0, IDI_APPLICATION )
					                      } ;

					if ( RegisterClassEx ( &wndclass ) )
						{
							HWND window = CreateWindowEx ( 0, myclass, L"title",
							                               /*WS_OVERLAPPEDWINDOW*/WS_BORDER, CW_USEDEFAULT, CW_USEDEFAULT,
							                               CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle ( 0 ), 0 ) ;
							HW = window;
							//SetWindowLong(window, GWL_STYLE, 0);
							MSG msg;

							if ( window )
								ShowWindow ( window, SW_MAXIMIZE ) ;

							
						}

					//Number keys
				}
				}
		}

	return CallNextHookEx ( NULL, nCode, wParam, lParam );
}
int CALLBACK WinMain (
    _In_  HINSTANCE hInstance,
    _In_  HINSTANCE hPrevInstance,
    _In_  LPSTR lpCmdLine,
    _In_  int nCmdShow
)
{
	HHOOK KeyboardHook = SetWindowsHookEx ( WH_KEYBOARD_LL, keyboardHookProc, hInstance, 0 );
	MSG msg;
	//std::cout << "hello world!\n" ;

	while ( GetMessage ( &msg, 0, 0, 0 ) )
		{
			TranslateMessage ( &msg );
			DispatchMessage ( &msg ) ;
		}
}
/*
int main(void) {

            screenops::crossCursor(); //change cursor to +
            while (!screenops::isMouseDown()) //Don't need to sample so fast.
                Sleep(200);
            POINT initialPos;
            GetCursorPos(&initialPos);
            POINT currentPos;
            GetCursorPos(&currentPos);
            screenops::pixelRect * PR = new screenops::pixelRect(); //cacheing previous selection region pixels
            while(screenops::isMouseDown()) {
                GetCursorPos(&currentPos);
                drawRect(initialPos,currentPos,PR);
                //Must invalidate previous selection rectangles
                //Either by forcing lower Z-order components to redraw OR
                //cacheing previous pixels of selection region. (pixelRect)
            }
            // negative width/height is ok.
            HBITMAP imageRegion = screenops::getImageAt(initialPos,currentPos.x-initialPos.x,currentPos.y-initialPos.y);
            CImage image;
            image.Attach(imageRegion);
            time_t result = time(nullptr);
            string fp= SAVE_PATH  "screenshot" + to_string(result)+".png";
            image.Save((LPCTSTR)fp.c_str(),Gdiplus::ImageFormatPNG);


}*/