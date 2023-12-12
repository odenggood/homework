#include <windows.h>

// 전역 변수
HINSTANCE hInst;
HWND hMainWnd;
const int windowWidth = 800;
const int windowHeight = 480;
const int margin = 8;
const int padding = 8;
const int numButtons = 5;
const int buttonSize = (windowWidth - 2 * margin - (numButtons + 1) * padding) / numButtons;

POINT startPoint = { 0 }; //시작점
POINT endPoint = { 0 }; //끝점
POINT moveStartPoint = { 0 }; //이동시작점
POINT moveEndPoint = { 0 }; //이동끝점
int isMouseLButtonPressed = 0;




// 박스를 나타내는 변수
bool isBoxVisible = false;

void DrawBox(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    if (isBoxVisible) {
        // 박스 그리기
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 박스
        SelectObject(hdc, hBrush);
        Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        DeleteObject(hBrush);
    }
}

// 원을 나타내는 변수
bool isCircleVisible = false;

// 원 그리기 함수
void DrawCircle(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    if (isCircleVisible) {
        // 원 그리기
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 원
        SelectObject(hdc, hBrush);
        Ellipse(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        DeleteObject(hBrush);
    }
}

//보노보노 나타내는 변수
bool isBonobonoVisible = false;

// 보노보노 그리기 함수
void DrawBonobono(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    if (isBonobonoVisible) {
        // 보노보노 그리기
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255)); // 피부
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 253, 184, 607, 535);

        hBrush = CreateSolidBrush(RGB(255, 150, 255)); // 입
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 404, 355, 453, 454);

        hBrush = CreateSolidBrush(RGB(255, 255, 255)); // 주둥이
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 370, 353, 431, 409); //왼
        Ellipse(hdc, 431, 353, 492, 408); //오

        hBrush = CreateSolidBrush(RGB(0, 0, 0)); //코
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 410, 342, 451, 379);

        hBrush = CreateSolidBrush(RGB(0, 0, 0)); //왼쪽 눈(검)
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 290, 335, 304, 356);
        hBrush = CreateSolidBrush(RGB(255, 255, 255)); //왼쪽 눈(흰)
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 293, 336, 299, 348);

        hBrush = CreateSolidBrush(RGB(0, 0, 0)); //오른쪽 눈(검)
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 563, 334, 576, 355);
        hBrush = CreateSolidBrush(RGB(255, 255, 255)); //오른쪽 눈(흰)
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 565, 339, 571, 347);

        HPEN hPen = (HPEN)GetStockObject(BLACK_PEN);
        SelectObject(hdc, hPen);
        MoveToEx(hdc, 358, 370, NULL); // 왼쪽 수염(위)
        LineTo(hdc, 392, 378);

        MoveToEx(hdc, 398, 385, NULL); // 왼쪽 수염(아래)
        LineTo(hdc, 359, 406);

        MoveToEx(hdc, 512, 359, NULL); // 오른쪽 수염(위)
        LineTo(hdc, 472, 377);

        MoveToEx(hdc, 472, 389, NULL); // 오른쪽 수염(아래)
        LineTo(hdc, 511, 400);

        DeleteObject(hPen);
        DeleteObject(hBrush);

        EndPaint(hWnd, &ps);
    }
    
}

// 라이언 나타내는 변수
bool isRyanVisible = false;

// 라이언 그리기 함수
void DrawRyan(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    if (isRyanVisible) {
        // 라이언 그리기
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 원
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 300, 150, 500, 300);
        DeleteObject(hBrush);
    }
}



// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static POINT MousePos;
    switch (message) {
    case WM_CREATE:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 투명한 사각형 그리기
        HBRUSH transparentBrush = CreateSolidBrush(RGB(255, 240, 200));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);
        Rectangle(hdc, 8, 8, 800 - 8, 480 - 8);

        HBRUSH drawingBrush = CreateSolidBrush(RGB(255, 255, 255));
        oldBrush = (HBRUSH)SelectObject(hdc, drawingBrush);
        Rectangle(hdc, 16, 88, 800 - 16, 480 - 16);

        SelectObject(hdc, oldBrush);
        DeleteObject(transparentBrush);

        DrawBox(hWnd, hdc);
        EndPaint(hWnd, &ps);

        break;
    }

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            // 첫 번째 버튼 클릭
            isBoxVisible = true;
            isCircleVisible = false;
            isBonobonoVisible = false;
            isRyanVisible = false;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 2) {
            // 두 번째 버튼 클릭
            isBoxVisible = false;
            isCircleVisible = true;
            isBonobonoVisible = false;
            isRyanVisible = false;
            InvalidateRect(hWnd, NULL, TRUE);
            
        }
        else if (LOWORD(wParam) == 3) {
            // 세 번째 버튼 클릭
            isBoxVisible = false;
            isCircleVisible = false;
            isBonobonoVisible = true;
            isRyanVisible = false;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 4) {
            // 네 번째 버튼 클릭
            isBoxVisible = false;
            isCircleVisible = false;
            isBonobonoVisible = false;
            isRyanVisible = true;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
 
    case WM_LBUTTONDOWN:
    {
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        isMouseLButtonPressed = 1;
    }
    break;
    
    case WM_MOUSEMOVE:
    {
        
      
        // 마우스 이동 중
        if (isMouseLButtonPressed)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);

            // WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    break;

    case WM_LBUTTONUP:
    {
        endPoint.x = LOWORD(lParam);
        endPoint.y = HIWORD(lParam);
        isMouseLButtonPressed = 0;
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 투명한 사각형 그리기
        HBRUSH transparentBrush = CreateSolidBrush(RGB(255, 240, 200));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);
        Rectangle(hdc, 8, 8, 800 - 8, 480 - 8);

        HBRUSH drawingBrush = CreateSolidBrush(RGB(255, 255, 255));
        oldBrush = (HBRUSH)SelectObject(hdc, drawingBrush);
        Rectangle(hdc, 16, 88, 800 - 16, 480 - 16);

        SelectObject(hdc, oldBrush);
        DeleteObject(transparentBrush);

        DrawBox(hWnd, hdc);
        EndPaint(hWnd, &ps);


        
    }
    break;

    case WM_KEYDOWN:
        if (wParam == 32)
        {
            PAINTSTRUCT ps;
            HDC hdc = GetDC(hWnd);


            HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255)); // 피부
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 253, 184, 607, 535);

            hBrush = CreateSolidBrush(RGB(255, 150, 255)); // 입
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 404, 355, 453, 454);

            hBrush = CreateSolidBrush(RGB(255, 255, 255)); // 주둥이
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 370, 353, 431, 409); //왼
            Ellipse(hdc, 431, 353, 492, 408); //오

            hBrush = CreateSolidBrush(RGB(0, 0, 0)); //코
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 410, 342, 451, 379);

            InvalidateRect(hWnd, NULL, TRUE);
            return 0;

        }
        break;

  

    case WM_DESTROY:
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



// 프로그램 진입점
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    hInst = hInstance;
    HWND hButton1, hButton2, hButton3, hButton4, hButton5;

    WNDCLASSEX wcex;
    memset(&wcex, 0, sizeof(wcex));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hbrBackground = CreateSolidBrush(RGB(255, 240, 200));
    wcex.lpszClassName = L"TransparentWindowWithButtons";
    RegisterClassEx(&wcex);

    // Window viewport 영역 조정
    RECT rect = { 150, 100, 800, 480 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;


    hMainWnd = CreateWindow(L"TransparentWindowWithButtons", L"MidtermExam", WS_OVERLAPPEDWINDOW,
        100, 100, windowWidth+20, windowHeight+35, NULL, NULL, hInstance, NULL);

    if (!hMainWnd)
        return FALSE;

    
    //버튼
    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        16, 16, 140, 64, hMainWnd, (HMENU)1, hInst, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        172, 16, 140, 64, hMainWnd, (HMENU)2, hInst, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        328, 16, 140, 64, hMainWnd, (HMENU)3, hInst, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        484, 16, 140, 64, hMainWnd, (HMENU)4, hInst, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        640, 16, 140, 64, hMainWnd, (HMENU)5, hInst, NULL);


    ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}