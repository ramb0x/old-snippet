/****Ram Bhakta | http://hira.us****/
								

#include "screenopps.hpp"
namespace screenops {

    void pixelRect::clean() {
        delete[] top;
        delete[] bot;
        delete[] left;
        delete[] right;
    }

    pixelRect::pixelRect(POINT tL, POINT bR) {
        load=false;
        init(tL,bR);
    }
    pixelRect::pixelRect() {
        load=false;
    }
    pixelRect::~pixelRect() {
        clean();
    }
    void pixelRect::init(POINT tL, POINT bR) {
        if (load)clean();
        HDC	screen = GetDC(0);
        int horz = abs(tL.x - bR.x);
        int vert = abs(tL.y - bR.y);
        top = new DWORD[horz];
        bot = new DWORD[horz];
        left = new DWORD[vert];
        right = new DWORD[vert];
        minX = min(tL.x,bR.x);
        maxX = max(tL.x,bR.x);
        minY = min(tL.y,bR.y);
        maxY = max(tL.y, bR.y);
        for (int i = 0; i < horz; i++) {
            top[i]=(DWORD)GetPixel(screen,minX+i,minY);
            bot[i]=(DWORD)GetPixel(screen,minX+i,maxY);
        }
        for (int i = 0; i < vert; i++) {
            left[i]=(DWORD)GetPixel(screen,minX,minY+i);
            right[i]=(DWORD)GetPixel(screen,maxX,minY+i);
        }
        load=true;
        ReleaseDC(0,screen);
    }
	void pixelRect::display() {
        HDC screen = GetDC(0);
        int horz = maxX-minX;
        int vert = maxY-minY;
        for (int i = 0; i < horz; i++) {
            //SetPixel(screen,minX+i,minY,top[i]);
            //SetPixel(screen,minX+100+i,maxY,bot[i]);
        }
        for (int i = 0; i < vert; i++) {
            //SetPixel(screen,minX,minY+i,left[i]);
            //SetPixel(screen,maxX,minY+100+i,right[i]);
        }
        ReleaseDC(0,screen);
    }

void Marker(LONG x, LONG y, HWND hwnd) {
    HDC hdc;
    hdc = GetDC(hwnd);
    MoveToEx(hdc, (int) x - 10, (int) y, (LPPOINT) NULL);
    LineTo(hdc, (int) x + 10, (int) y);
    MoveToEx(hdc, (int) x, (int) y - 10, (LPPOINT) NULL);
    LineTo(hdc, (int) x, (int) y + 10);
    ReleaseDC(hwnd, hdc);
}
void crossCursor() {
    HCURSOR hcCross = LoadCursor(0, IDC_CROSS);
    HCURSOR hcCrossCopy = CopyCursor(hcCross);
    BOOL ret = SetSystemCursor(hcCrossCopy, 32512);
    DestroyCursor(hcCross);
}
void revertCursor() {
    HCURSOR hcCross = LoadCursor(0, IDC_ARROW);
    HCURSOR hcCrossCopy = CopyCursor(hcCross);
    BOOL ret = SetSystemCursor(hcCrossCopy, 32512);
    DestroyCursor(hcCross);
}
void Screen2Clipboard() {
    {
        int x, y,w,h;
        // get screen dimensions
        x  = GetSystemMetrics(SM_XVIRTUALSCREEN);
        y  = GetSystemMetrics(SM_YVIRTUALSCREEN);
        w   = GetSystemMetrics(SM_CXVIRTUALSCREEN) - x;
        h   = GetSystemMetrics(SM_CYVIRTUALSCREEN) - y;
        // copy screen to bitmap
        HDC     hScreen = GetDC(NULL);
        HDC     hDC     = CreateCompatibleDC(hScreen);
        HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
        HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
        BOOL    bRet    = BitBlt(hDC, 0, 0, w, h, hScreen, x, y, SRCCOPY);
        // save bitmap to clipboard
        OpenClipboard(NULL);
        EmptyClipboard();
        SetClipboardData(CF_BITMAP, hBitmap);
        CloseClipboard();
        // clean up
        SelectObject(hDC, old_obj);
        DeleteDC(hDC);
        ReleaseDC(NULL, hScreen);
        DeleteObject(hBitmap);
    }
}
bool isMouseDown() {
    return (GetKeyState(VK_LBUTTON) & 0x100) != 0;
}
void drawText(POINT loc, string message) {
    HDC h = GetDC(0);
    RECT r;
    //DrawText(h,(LPCWSTR)message.c_str(),message.length(),&r,DT_CENTER);
}
void drawRect(POINT topLeft, POINT botRight,pixelRect * oldRect) {
    //Marker(100,100,0);
    HDC screenDC = ::GetDC(0);
    POINT * p = new POINT();
    HPEN hPen = CreatePen(PS_DASHDOTDOT, 1, RGB(0,0,0));
    HGDIOBJ hBrush = GetStockObject(NULL_BRUSH);
    SelectObject(screenDC, hPen);
    SelectObject(screenDC, hBrush);
    POINT  *old = new POINT();
    //oldRect->display();
    //oldRect->init(topLeft,botRight);
    Rectangle(screenDC, topLeft.x, topLeft.y, botRight.x,botRight.y);
    //for (int i = topLeft.x; i != botRight.x; i++)
    ::ReleaseDC(0, screenDC);
    delete p;
}
HBITMAP getImageAt(POINT tL, int width, int height) {
    HDC     hScreen = GetDC(NULL);
    HDC     hDC     = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL    bRet    = BitBlt(hDC, 0, 0, width, height, hScreen, tL.x, tL.y, SRCCOPY);
    return hBitmap;
}
void setImageAt(HBITMAP &img, POINT tL, int w, int h) {
    HDC     hScreen = GetDC(NULL);
    HDC     hDC     = CreateCompatibleDC(hScreen);
    BitBlt(hScreen,0,0,w,h,hDC,tL.x,tL.y,SRCCOPY);
    ReleaseDC(0,hScreen);
}
}
