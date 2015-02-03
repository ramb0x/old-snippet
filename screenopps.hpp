#ifndef SCREENOPPS_HPP
#define SCREENOPPS_HPP
#include <Windows.h>
#include <gdiplus.h>
#include <iostream>
#include <string>
#include <atlimage.h>
#include <time.h>
using namespace std;

namespace screenops {
class pixelRect {
    DWORD * top;
    DWORD * bot;
    DWORD * left;
    DWORD * right;
    int minX,minY,maxX,maxY;
    bool load;
    void clean(); 
  public:
    pixelRect(POINT tL, POINT bR);
    pixelRect();
    ~pixelRect();
    void init(POINT tL, POINT bR); 
	    void display(); 
};

 
void Marker(LONG x, LONG y, HWND hwnd); 
void crossCursor(); 
void revertCursor(); 
void Screen2Clipboard(); 
bool isMouseDown(); 
void drawText(POINT loc, string message); 
void drawRect(POINT topLeft, POINT botRight,pixelRect * oldRect); 
HBITMAP getImageAt(POINT tL, int width, int height); 
void setImageAt(HBITMAP &img, POINT tL, int w, int h);
}
#endif