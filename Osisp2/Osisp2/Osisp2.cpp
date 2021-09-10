#include <Windows.h>
#include <vector>

#include "FileTable.h"

using namespace std;

void DrawTable(HWND hwnd, FileTable textSheet);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

    const wchar_t CLASS_NAME[] = L"Window Class";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClass(&wc);


    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Lab2",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (hwnd == nullptr) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static FileTable textSheet("..\\src.txt");
    switch (uMsg)
    {
        case WM_CREATE:
        {
            break;
        }
        case WM_PAINT:
        {
            DrawTable(hwnd, textSheet);
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        case WM_SIZE:
        {
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        default:
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    return 0;
}

void DrawTable(HWND hwnd, FileTable textSheet)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

    TEXTMETRIC tm;
    GetTextMetrics(hdc, &tm);
    int cellHeight = tm.tmHeight;

    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    int cellWidth = (clientRect.right - clientRect.left) / textSheet.column_count;
    int tableHeight = 0;

    MoveToEx(hdc, 0, tableHeight, nullptr);
    LineTo(hdc, clientRect.right, tableHeight);

    for (int i = 0; i < textSheet.row_count; i++)
    {
        int curCellHeight = cellHeight;
        for (int j = 0; j < textSheet.tableData[i].size(); j++)
        {
            RECT cell;
            cell.left = j * cellWidth;
            cell.right = cell.left + cellWidth;
            cell.top = tableHeight + cellHeight / 2;
            cell.bottom = clientRect.bottom;
            wstring line = wstring(textSheet.tableData[i][j].begin(), textSheet.tableData[i][j].end());
            curCellHeight = DrawText(hdc, line.c_str(),
                -1, &cell, DT_WORDBREAK | DT_CENTER | DT_END_ELLIPSIS);
            curCellHeight = curCellHeight > cellHeight ? curCellHeight : cellHeight;
        }

        tableHeight += curCellHeight + cellHeight;
        MoveToEx(hdc, 0, tableHeight, nullptr);
        LineTo(hdc, clientRect.right, tableHeight);
    }

    for (int i = 0; i <= textSheet.column_count; i++) {
        MoveToEx(hdc, cellWidth * i, 0, nullptr);
        LineTo(hdc, cellWidth * i, tableHeight);
    }

    EndPaint(hwnd, &ps);
}