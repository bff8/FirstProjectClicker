#include"lib.h"

LRESULT CALLBACK WindowEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static int ptX = 0, ptY = 0;
    static int countLKM = 0;
    switch (message) {
    case WM_GETMINMAXINFO: {
        MINMAXINFO* ptr = (MINMAXINFO*)lParam;
        ptr->ptMinTrackSize.x = WindowSizeX;
        ptr->ptMinTrackSize.y = WindowSizeY;
        ptr->ptMaxTrackSize.x = WindowSizeX;
        ptr->ptMaxTrackSize.y = WindowSizeY;
        break;
    }
    case WM_TIMER: {
        if (wParam == 2)
            MainGameSum += Button_1_Speed;
        else
            InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case Button_Speed_ID: {
            if (MainGameSum >= ButtonBuy_1_Sell_Speed) {
                MainGameSum -= ButtonBuy_1_Sell_Speed;
                ButtonBuy_1_Sell_Speed *= 1.5;
                Button_1_Speed += 1;
                SetTimer(hWnd, 2, 1000, NULL);
                wstring st = { L"Увеличение скорости \n (Дает +1 каждую секунду) \n [ " + to_wstring(ButtonBuy_1_Sell_Speed) + L" LP ]\0" };
                SetWindowTextW(ButtonBuy[0],st.c_str());
            }
            break;
        }
        case Button_Efficiency_ID: {
            if (MainGameSum >= ButtonBuy_2_Sell_Efficiency) {
                MainGameSum -= ButtonBuy_2_Sell_Efficiency;
                ButtonBuy_2_Sell_Efficiency *= 5;
                Button_2_Efficiency += ButtonBuy_2_Sell_Efficiency / 100;
                wstring st = { L"Эффективность \n (Дает +"+to_wstring(Button_2_Efficiency)+L" к каждому клику)\n[ " + to_wstring(ButtonBuy_2_Sell_Efficiency) + L" LP ]\0" };
                SetWindowTextW(ButtonBuy[1],st.c_str());    
            }
            break;
        }
        case Button_Sound_ID: {
            if (Button_3_Sound == TRUE) {
                PlaySound(0, 0, 0);
                Button_3_Sound = FALSE;
            }
            else {
                PlaySoundW(L"backsound", 0, SND_RESOURCE | SND_ASYNC);
                Button_3_Sound = TRUE;
            } 
            break;
        }
        case Button_ChangePlanet_ID: {
            if (MainGameSum >= 10000) {
                index++;
                if (index > 4)index = 0;
                switch (index) {
                case Earth: {
                    picture = LoadBitmap(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDB_BITMAP1));break;
                }
                case Moon: {
                    picture = LoadBitmap(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDB_BITMAP2));break;
                }
                case Pluto: {
                    picture = LoadBitmap(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDB_BITMAP3));break;
                }
                case Mars: {
                    picture = LoadBitmap(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDB_BITMAP4));break;
                }
                case Wiener: {
                    picture = LoadBitmap(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDB_BITMAP5));break;
                } 
                }
                MainGameSum -= 1000;
            }
            break;
        }
        }
    }
    case WM_MOUSEMOVE: {
        POINT pt = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
        double circle_check = (sqrt(pow(pt.x - WindowCenterX, 2) + pow(pt.y - WindowCenterY, 2)));
        if (circle_check < RadiusWordl)SetCursor(cursorHand);
        else SetCursor(cursorArrow);
        break;
    }
    case WM_LBUTTONDOWN: {
        POINT pt = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
        ptX = pt.x;
        ptY = pt.y;
        countLKM = 0;
        if (kryg < RadiusWordl) {
            if (Button_1_Speed == 0)MainGameSum += Button_2_Efficiency;
            else MainGameSum += Button_2_Efficiency + Button_1_Speed;
        }
        break;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)GetStockObject(BLACK_BRUSH));
        BITMAP pictureObj;
        GetObject(picture, sizeof(BITMAP), &pictureObj);
        HDC buffer = CreateCompatibleDC(hdc);
        SelectObject(buffer, picture);
        BitBlt(hdc, WindowCenterX - 150, WindowCenterY - 150, ImageSize, ImageSize, buffer, 0, 0, SRCCOPY);
        HFONT BigTextForClick = CreateFontW(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH, L"GOST type A");
        HFONT SmallTextForClick = CreateFontW(36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH, L"GOST type A");
        SelectObject(hdc, BigTextForClick);
        SetTextColor(hdc, RGB(0, 0, 0));
        wstring str = to_wstring(MainGameSum) + L" LP";
        SetTextColor(hdc, RGB(255, 255, 0));
        SetBkColor(hdc, RGB(0, 0, 0));  
        SetTextAlign(hdc, TA_RIGHT);
        TextOutW(hdc, ps.rcPaint.right - 50, ps.rcPaint.top + 50, str.c_str(), static_cast<int>(str.length()));
        if (kryg < RadiusWordl) {
            if (countLKM < 1) {
                SelectObject(hdc, BigTextForClick);
                SetBkMode(hdc, TRANSPARENT);
                SetTextColor(hdc, RGB(0, 0, 0));
                wstring text = L"+" + to_wstring(Button_2_Efficiency);
                SetTextAlign(hdc, TA_LEFT);
                TextOutW(hdc, ptX + 20, ptY - 30, text.c_str(), static_cast<int>(text.length()));
                SelectObject(hdc, SmallTextForClick);
                SetTextColor(hdc, RGB(255, 255, 0));
                TextOutW(hdc, ptX + 20, ptY - 30, text.c_str(), static_cast<int>(text.length()));
                countLKM++;
            }
        }
        DeleteObject(buffer);
        DeleteObject(BigTextForClick);
        DeleteObject(SmallTextForClick);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

ATOM StartClassWindows() {
    WNDCLASSEXW startbox;
    memset(&startbox, 0, sizeof(startbox));
    startbox.cbSize = sizeof(WNDCLASSEX);
    startbox.style = CS_HREDRAW | CS_VREDRAW;
    startbox.lpfnWndProc = WindowEvent;
    startbox.hCursor = cursorArrow;
    startbox.lpszClassName = L"MainClass";
    startbox.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    return RegisterClassExW(&startbox);
}

BOOL Window() {
    cursorArrow = LoadCursor(nullptr, IDC_ARROW);
    cursorHand = LoadCursor(nullptr, IDC_HAND);
    picture = LoadBitmap(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
    PlaySoundW(L"backsound", 0, SND_RESOURCE | SND_ASYNC);

    HWND MainWindow = CreateWindowExW(NULL, L"MainClass", L"MyWindow", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX | WS_CLIPCHILDREN,
        245, 175, WindowSizeX, WindowSizeY, nullptr, nullptr, 0, nullptr);
    ShowWindow(MainWindow, SW_SHOWNORMAL);
    SetTimer(MainWindow,1,166,NULL);
    
    wchar_t text[4][MAX_PATH] = {
        L"Увеличение скорости \n (Дает +1 каждую секунду) \n [ %i LP ]\0",
        L"Эффективность \n (Дает +1 к каждому клику) [ %i LP ]\0",
        L"Включить | Выключить музыку\0",
        L"Изменить планету \n [ 10.000 LP ]\0"
    };
    wchar_t buf[MAX_PATH] = { 0 };
    HFONT TextInButton = CreateFontW(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH, L"GOST type A");
    for (int i = 0; i < 4; i++) {
        _swprintf(buf, text[i], !i ? ButtonBuy_1_Sell_Speed : ButtonBuy_2_Sell_Efficiency);
        ButtonBuy[i] = CreateWindowExW(NULL, L"BUTTON", buf, WS_CHILD | BS_MULTILINE,
            spawnButtonX, spawnButtonY, 200, 100, MainWindow, (HMENU)i, 0, nullptr);
        spawnButtonY += 140;
        SetWindowFont(ButtonBuy[i], TextInButton, FALSE);
        ShowWindow(ButtonBuy[i], SW_SHOWNORMAL);
    }
    return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    if (!StartClassWindows()) MessageBox(NULL, L"Ошибка создания изначального окна", L"ERROR", MB_OK);
    Window();
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}