#include <windows.h>

// ���� ����
HINSTANCE hInst;
HWND hMainWnd;
const int windowWidth = 800;
const int windowHeight = 480;
const int margin = 8;
const int padding = 8;
const int numButtons = 5;
const int buttonSize = (windowWidth - 2 * margin - (numButtons + 1) * padding) / numButtons;

POINT startPoint = { 0 }; //������
POINT endPoint = { 0 }; //����
POINT moveStartPoint = { 0 }; //�̵�������
POINT moveEndPoint = { 0 }; //�̵�����
int isMouseLButtonPressed = 0;




// �ڽ��� ��Ÿ���� ����
bool isBoxVisible = false;

void DrawBox(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    if (isBoxVisible) {
        // �ڽ� �׸���
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // ������ �ڽ�
        SelectObject(hdc, hBrush);
        Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        DeleteObject(hBrush);
    }
}

// ���� ��Ÿ���� ����
bool isCircleVisible = false;

// �� �׸��� �Լ�
void DrawCircle(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    if (isCircleVisible) {
        // �� �׸���
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // ������ ��
        SelectObject(hdc, hBrush);
        Ellipse(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        DeleteObject(hBrush);
    }
}

//���뺸�� ��Ÿ���� ����
bool isBonobonoVisible = false;

// ���뺸�� �׸��� �Լ�
void DrawBonobono(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    if (isBonobonoVisible) {
        // ���뺸�� �׸���
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255)); // �Ǻ�
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 253, 184, 607, 535);

        hBrush = CreateSolidBrush(RGB(255, 150, 255)); // ��
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 404, 355, 453, 454);

        hBrush = CreateSolidBrush(RGB(255, 255, 255)); // �ֵ���
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 370, 353, 431, 409); //��
        Ellipse(hdc, 431, 353, 492, 408); //��

        hBrush = CreateSolidBrush(RGB(0, 0, 0)); //��
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 410, 342, 451, 379);

        hBrush = CreateSolidBrush(RGB(0, 0, 0)); //���� ��(��)
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 290, 335, 304, 356);
        hBrush = CreateSolidBrush(RGB(255, 255, 255)); //���� ��(��)
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 293, 336, 299, 348);

        hBrush = CreateSolidBrush(RGB(0, 0, 0)); //������ ��(��)
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 563, 334, 576, 355);
        hBrush = CreateSolidBrush(RGB(255, 255, 255)); //������ ��(��)
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 565, 339, 571, 347);

        HPEN hPen = (HPEN)GetStockObject(BLACK_PEN);
        SelectObject(hdc, hPen);
        MoveToEx(hdc, 358, 370, NULL); // ���� ����(��)
        LineTo(hdc, 392, 378);

        MoveToEx(hdc, 398, 385, NULL); // ���� ����(�Ʒ�)
        LineTo(hdc, 359, 406);

        MoveToEx(hdc, 512, 359, NULL); // ������ ����(��)
        LineTo(hdc, 472, 377);

        MoveToEx(hdc, 472, 389, NULL); // ������ ����(�Ʒ�)
        LineTo(hdc, 511, 400);

        DeleteObject(hPen);
        DeleteObject(hBrush);

        EndPaint(hWnd, &ps);
    }
    
}

// ���̾� ��Ÿ���� ����
bool isRyanVisible = false;

// ���̾� �׸��� �Լ�
void DrawRyan(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    if (isRyanVisible) {
        // ���̾� �׸���
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // ������ ��
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 300, 150, 500, 300);
        DeleteObject(hBrush);
    }
}



// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static POINT MousePos;
    switch (message) {
    case WM_CREATE:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // ������ �簢�� �׸���
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
            // ù ��° ��ư Ŭ��
            isBoxVisible = true;
            isCircleVisible = false;
            isBonobonoVisible = false;
            isRyanVisible = false;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 2) {
            // �� ��° ��ư Ŭ��
            isBoxVisible = false;
            isCircleVisible = true;
            isBonobonoVisible = false;
            isRyanVisible = false;
            InvalidateRect(hWnd, NULL, TRUE);
            
        }
        else if (LOWORD(wParam) == 3) {
            // �� ��° ��ư Ŭ��
            isBoxVisible = false;
            isCircleVisible = false;
            isBonobonoVisible = true;
            isRyanVisible = false;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 4) {
            // �� ��° ��ư Ŭ��
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
        
      
        // ���콺 �̵� ��
        if (isMouseLButtonPressed)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);

            // WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
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

        // ������ �簢�� �׸���
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


            HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255)); // �Ǻ�
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 253, 184, 607, 535);

            hBrush = CreateSolidBrush(RGB(255, 150, 255)); // ��
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 404, 355, 453, 454);

            hBrush = CreateSolidBrush(RGB(255, 255, 255)); // �ֵ���
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 370, 353, 431, 409); //��
            Ellipse(hdc, 431, 353, 492, 408); //��

            hBrush = CreateSolidBrush(RGB(0, 0, 0)); //��
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



// ���α׷� ������
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

    // Window viewport ���� ����
    RECT rect = { 150, 100, 800, 480 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;


    hMainWnd = CreateWindow(L"TransparentWindowWithButtons", L"MidtermExam", WS_OVERLAPPEDWINDOW,
        100, 100, windowWidth+20, windowHeight+35, NULL, NULL, hInstance, NULL);

    if (!hMainWnd)
        return FALSE;

    
    //��ư
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