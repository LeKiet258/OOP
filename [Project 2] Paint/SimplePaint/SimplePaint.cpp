// SimplePaint.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SimplePaint.h"
#include <WindowsX.h>
//#include "stdafx.h"
#include "SimplePaint.h"
#include <windowsx.h>
#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")
#include <commdlg.h>
#include<memory>
#include<iostream>
#include<fstream>

#include"DrawObject.h"
#include"ShapeFactory.h"
#include"Line.h"
#include"Ellipse.h"
#include"Rectangle.h"

#define MAX_LOADSTRING 100

#define IMAGE_WIDTH     18
#define IMAGE_HEIGHT    18
#define BUTTON_WIDTH    0
#define BUTTON_HEIGHT   0

enum options { LINE, RECTANGLE, ELLIPSE, TEXT, SAVE_FILE, DELETE_ALL, COPY};

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
CHOOSECOLOR  cc; // Thông tin màu chọn
COLORREF  acrCustClr[16]; // Mảng custom color
DWORD  rgbCurrent = RGB(255, 0, 0); // Red
HBRUSH  hbrush; // Tạo ra brush từ màu đã chọn
DrawObject drawObj;
int fromX;
int fromY;
int toX;
int toY;
bool isPreview;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnDestroy(HWND hwnd);
void OnPaint(HWND hwnd);
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
void saveFile(HWND hwnd);
void openFile(HWND hwnd);
void removeAll(HWND hwnd);
void repeatDrawing(HWND hwnd);
void drawAShape(HDC hdc, IShape_ptr shape);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SIMPLEPAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLEPAINT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SIMPLEPAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE +1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SIMPLEPAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
        HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
        HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);
        HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
        HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
        HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);

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

HFONT hFont;
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    // Lấy font hệ thống
    LOGFONT lf;
    GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
    hFont = CreateFont(lf.lfHeight, lf.lfWidth,
        lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
        lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
        lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
        lf.lfPitchAndFamily, lf.lfFaceName);

    InitCommonControls();
    TBBUTTON tbButtons[] =
    {
        { STD_FILENEW,	ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_FILEOPEN,	ID_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_FILESAVE,	ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
    };

    HWND hToolBarWnd = CreateToolbarEx(hwnd,
        WS_CHILD | WS_VISIBLE | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS,
        ID_TOOLBAR,
        sizeof(tbButtons) / sizeof(TBBUTTON),
        HINST_COMMCTRL,
        0,
        tbButtons,
        sizeof(tbButtons) / sizeof(TBBUTTON),
        BUTTON_WIDTH, BUTTON_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT,
        sizeof(TBBUTTON));
    TBBUTTON buttonsToAdd[] =
    {
        { 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 }, // Nút phân cách
        { STD_CUT,	ID_EDIT_CUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_COPY,	ID_EDIT_COPY, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_PASTE, ID_EDIT_PASTE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_DELETE, ID_EDIT_DELETE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_UNDO, ID_EDIT_UNDO, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
        { STD_REDOW, ID_EDIT_REDO, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0}
    };
    SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM)sizeof(buttonsToAdd) / sizeof(TBBUTTON),
        (LPARAM)(LPTBBUTTON)&buttonsToAdd);
    TBBUTTON mainUserButtons[] =
    {
        { 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
        { 0, ID_DRAW_ELLIPSE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { 1, ID_DRAW_RECTANGLE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { 2, ID_DRAW_LINE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { 3, ID_DRAW_TEXT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
    };
    TBADDBITMAP	tbBitmap = { hInst, IDB_BITMAP1 };
    // Thêm danh sách ảnh vào toolbar
    int idx = SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)sizeof(tbBitmap) / sizeof(TBADDBITMAP),
        (LPARAM)(LPTBADDBITMAP)&tbBitmap);

    // Xác định chỉ mục hình ảnh của mỗi button từ ảnh bự liên hoàn nhiều tấm
    mainUserButtons[1].iBitmap += idx;
    mainUserButtons[2].iBitmap += idx;
    mainUserButtons[3].iBitmap += idx;
    mainUserButtons[4].iBitmap += idx;
    // Thêm nút bấm vào toolbar
    SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM)sizeof(mainUserButtons) / sizeof(TBBUTTON),
        (LPARAM)(LPTBBUTTON)&mainUserButtons);

    //TEST

    return TRUE;
}

bool newFileMode = 0;
ofstream newFile;
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    if (ID_DRAW_LINE == id) {
        drawObj.setObject(LINE);
    }
    if (ID_DRAW_RECTANGLE == id) {
        drawObj.setObject(RECTANGLE);
    }
    if (ID_DRAW_ELLIPSE == id) {
        drawObj.setObject(ELLIPSE);
    }
    if (ID_CHOOSE_COLOR == id) {
        ZeroMemory(&cc, sizeof(CHOOSECOLOR));
        cc.lStructSize = sizeof(CHOOSECOLOR);
        cc.hwndOwner = hwnd;
        cc.lpCustColors = (LPDWORD)acrCustClr;
        cc.rgbResult = rgbCurrent;
        cc.Flags = CC_FULLOPEN | CC_RGBINIT;
        if (ChooseColor(&cc))
        {
            hbrush = CreateSolidBrush(cc.rgbResult); //màu nền
            rgbCurrent = cc.rgbResult; //màu viền
        }
    }

    if (ID_FILE_SAVE == id) {
        drawObj.setObject(SAVE_FILE);
        saveFile(hwnd);
    }
    if (ID_FILE_OPEN == id) {
        openFile(hwnd);
        InvalidateRect(hwnd, NULL, TRUE);
    }
    if (ID_EDIT_DELETE == id) {
        removeAll(hwnd);

    }
    if (ID_FILE_NEW == id) {
        //need to delete file before continuing
        drawObj.setObject(DELETE_ALL);
        drawObj.clear();
        InvalidateRect(hwnd, NULL, TRUE);

        OPENFILENAME ofn;
        wchar_t szFileName[MAX_PATH] = { (wchar_t)"" };
        vector<shared_ptr<IShape>> shapes = drawObj.shapes();
        int n = shapes.size();

        ZeroMemory(&ofn, sizeof(ofn));

        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = hwnd;
        ofn.lpstrFilter = (LPCWSTR)L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0";
        ofn.lpstrFile = (LPTSTR)szFileName; // This will hold the file name
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_NOVALIDATE | OFN_ENABLETEMPLATEHANDLE | OFN_CREATEPROMPT;
        ofn.lpstrDefExt = (LPCWSTR)L"txt";

        GetSaveFileName(&ofn); //initialize the dialog box
        newFile.open(ofn.lpstrFile);
        newFileMode = 1;
    }
    if (ID_EDIT_UNDO == id) {
        vector<IShape_ptr> origin = drawObj.shapes();

        if (!origin.empty()) {
            drawObj.addUndoShape(origin.back());
            vector<IShape_ptr> tmp(origin.begin(), origin.end() - 1);
            drawObj.setShapes(tmp);
            InvalidateRect(hwnd, NULL, TRUE);
            repeatDrawing(hwnd);
        }
    }
    if (ID_EDIT_REDO == id) {
        vector<IShape_ptr> originUndoShapes = drawObj.undoShapes();

        if (!originUndoShapes.empty()) {
            IShape_ptr undoObj = drawObj.undoShapes().back();

            originUndoShapes.pop_back();
            drawObj.setUndoShapes(originUndoShapes);
            drawObj.addShape(undoObj);
            InvalidateRect(hwnd, NULL, TRUE);
            repeatDrawing(hwnd);
        }
    }
}

void OnDestroy(HWND hwnd)
{
    if (newFileMode == 1) {
        vector<IShape_ptr> shapes = drawObj.shapes();
        int n = shapes.size();
        //newFile.seekp(0);
        newFile << n << endl;

        for (int i = 0; i < n; ++i) {
            newFile << shapes[i]->type() << ": " << shapes[i]->toString() << " " << shapes[i]->color() << endl;
        }

        newFile.close();
    }
    PostQuitMessage(0);
}

void OnPaint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // Tạo pen với nét gạch chấm, độ dày là 3, màu đỏ
    HPEN hPen = CreatePen(PS_DASHDOT, 3, rgbCurrent);
    int n = drawObj.shapes().size();

    //vẽ lại hình cũ
    for (int i = 0; i < n; ++i) {
        shared_ptr<IShape> shape = drawObj.shapes()[i];
        DWORD oldColor = shape->color();
        HPEN oldHPen = CreatePen(PS_DASHDOT, 3, oldColor);
        SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
        SelectObject(hdc, oldHPen); //có màu

        drawAShape(hdc, shape);
        DeleteObject(oldHPen);
    }

    SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
    SelectObject(hdc, hPen); //có màu

    //vẽ hình mới
    if (drawObj.object() == LINE) {
        MoveToEx(hdc, fromX, fromY, NULL);
        LineTo(hdc, toX, toY);
    }
    else if (drawObj.object() == RECTANGLE) {
        Rectangle(hdc, fromX, fromY, toX, toY);
    }
    else if (drawObj.object() == ELLIPSE) {
        Ellipse(hdc, fromX, fromY, toX, toY);
    }

    EndPaint(hwnd, &ps);
    DeleteObject(hPen);
}

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    isPreview = true;
    fromX = x;
    fromY = y;

    //reset
    toX = x;
    toY = y;
}

void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    isPreview = false;

    if (!(fromX == x && fromY == y)) {

        // Báo hiệu cần xóa đi toàn bộ màn hình & vẽ lại
        InvalidateRect(hwnd, NULL, TRUE);

        //thêm các hình vừa vẽ ngay khi nhấc chuột kết thúc
        if (drawObj.object() == LINE) {
            Line line(Point(fromX, fromY), Point(toX, toY));
            line.setRGB(rgbCurrent);
            drawObj.addShape(std::make_shared<Line>(line));
        }
        else if (drawObj.object() == RECTANGLE) {
            class Rectangle rect(Point(fromX, fromY), Point(toX, toY));
            rect.setRGB(rgbCurrent);
            drawObj.addShape(std::make_shared<class Rectangle>(rect));
        }
        else if (drawObj.object() == ELLIPSE) {
            class Ellipse ell(Point(fromX, fromY), Point(toX, toY));
            ell.setRGB(rgbCurrent);
            drawObj.addShape(std::make_shared<class Ellipse>(ell));
        }

    }
}

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
    if (isPreview) {
        toX = x;
        toY = y;

        // Báo hiệu cần xóa đi toàn bộ màn hình
        InvalidateRect(hwnd, NULL, TRUE);
    }
}

void saveFile(HWND hwnd) {
    OPENFILENAME ofn;
    wchar_t szFileName[MAX_PATH] = { (wchar_t)"" };
    vector<shared_ptr<IShape>> shapes = drawObj.shapes();
    int n = shapes.size();

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = (LPCWSTR)L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0";
    ofn.lpstrFile = (LPTSTR)szFileName; // This will hold the file name
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_NOVALIDATE | OFN_ENABLETEMPLATEHANDLE | OFN_CREATEPROMPT;
    ofn.lpstrDefExt = (LPCWSTR)L"txt";

    bool success = GetSaveFileName(&ofn); //initialize the dialog box

    if (success == true) {
        ofstream fout(ofn.lpstrFile);
        fout << n << endl;

        for (int i = 0; i < n; ++i) {
            fout << shapes[i]->type() << ": " << shapes[i]->toString() << " " << shapes[i]->color() << endl;
        }

        fout.close();
    }
}

void openFile(HWND hwnd) {
    OPENFILENAME ofn;
    wchar_t szFileName[MAX_PATH] = { (wchar_t)"" };
    vector<shared_ptr<IShape>> shapes = drawObj.shapes();
    int n = shapes.size();

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = (LPCWSTR)L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0";
    ofn.lpstrFile = (LPTSTR)szFileName; // This will hold the file name
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_READONLY | OFN_FILEMUSTEXIST ;
    //OFN_FILEMUSTEXIST, OFN_CREATEPROMPT, OFN_PATHMUSTEXIST
    ofn.lpstrDefExt = (LPCWSTR)L"txt";

    bool success = GetOpenFileName(&ofn); //initialize the dialog box

    if (success == true) {
        ifstream fin(ofn.lpstrFile);
        drawObj.setShapes(ShapeFactory::instance()->readFile(fin));
        OnPaint(hwnd);
        fin.close();
    }
}

void removeAll(HWND hwnd) {
    drawObj.setObject(DELETE_ALL);
    drawObj.clear();
    InvalidateRect(hwnd, NULL, TRUE);
}

void repeatDrawing(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    HPEN hPen = CreatePen(PS_DASHDOT, 3, rgbCurrent);
    int n = drawObj.shapes().size();

    for (int i = 0; i < n; ++i) {
        IShape_ptr shape = drawObj.shapes()[i];
        DWORD oldColor = shape->color();
        HPEN oldHPen = CreatePen(PS_DASHDOT, 3, oldColor);

        SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
        SelectObject(hdc, oldHPen); //có màu
        drawAShape(hdc, shape);

        DeleteObject(oldHPen);
    }
    EndPaint(hwnd, &ps);
    DeleteObject(hPen);

}

void drawAShape(HDC hdc, IShape_ptr shape) {
    if (shape->type() == "Line") {
        MoveToEx(hdc, shape->srcPoint().x(), shape->srcPoint().y(), NULL);
        LineTo(hdc, shape->dstPoint().x(), shape->dstPoint().y());
    }
    if (shape->type() == "Rectangle") {
        Rectangle(hdc, shape->srcPoint().x(), shape->srcPoint().y(),
            shape->dstPoint().x(), shape->dstPoint().y());
    }
    if (shape->type() == "Ellipse") {
        Ellipse(hdc, shape->srcPoint().x(), shape->srcPoint().y(),
            shape->dstPoint().x(), shape->dstPoint().y());
    }
}