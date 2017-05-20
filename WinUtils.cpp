/**************************************************************************

Author: andycheng

Email:  ustbyangcheng@gmail.com

Date:   2017-05-20

**************************************************************************/

#include "WinUtils.h"

#include <QDebug>
#include <QtWin>
#include <QStyle>

struct ProcessWindow
{
    DWORD dwProcessId;
    HWND hwndWindow;
};

BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam);

// 查找进程主窗口的回调函数
BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam)
{
    ProcessWindow *pProcessWindow = (ProcessWindow *)lParam;

    DWORD dwProcessId;
    GetWindowThreadProcessId(hWnd, &dwProcessId);

    // 判断是否是指定进程的主窗口
    if (pProcessWindow->dwProcessId == dwProcessId && IsWindowVisible(hWnd) && GetParent(hWnd) == NULL)
    {
        pProcessWindow->hwndWindow = hWnd;
        qDebug() << "HWND" << (int)hWnd;

        return FALSE;
    }

    return TRUE;
}


HWND WinUtils::OpenExec(QString exeFile, WINSTATE openState)
{
    if (exeFile.isEmpty())
    {
        return NULL;
    }

    LPCTSTR szCmdLine = (LPCTSTR)(exeFile.unicode());
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    // 窗口打开状态
    si.dwFlags = STARTF_USESHOWWINDOW;
    switch(openState)
    {
    case WINSTATE::SHOW:
        si.wShowWindow = SW_SHOWNORMAL;
        break;
    case WINSTATE::MAXIMIZED:
        si.wShowWindow = SW_SHOWMAXIMIZED;
        break;
    case WINSTATE::MINIMIZED:
        si.wShowWindow = SW_SHOWMINIMIZED;
        break;
    case WINSTATE::HIDE:
        si.wShowWindow = SW_HIDE;
        break;
    default:
        si.wShowWindow = SW_SHOWNORMAL;
    }

    BOOL ret= ::CreateProcess(
                szCmdLine,
                NULL,
                NULL,
                NULL,
                FALSE,
                0,
                NULL,
                NULL,
                &si,
                &pi);

    // 释放句柄，否则新进程将无法退出
    if(ret)
    {
        qDebug() << "新进程的id：" << pi.dwProcessId;
        qDebug() << "Thread id:" << pi.dwThreadId;

        ProcessWindow procwin;
        procwin.dwProcessId = pi.dwProcessId;
        procwin.hwndWindow = NULL;

        // 查找主窗口
        while(::EnumWindows(EnumWindowCallBack, (LPARAM)&procwin))
        {
            Sleep(100);  // 等待新进程初始化完毕
        }

        ::CloseHandle(pi.hProcess);
        ::CloseHandle(pi.hThread);

        return procwin.hwndWindow;
    }
    else
    {
        int nErrorNo = GetLastError();
        qDebug() << QString("打开[%1]失败。 %2 ").arg(exeFile).arg(nErrorNo);

        return NULL;
    }
}

bool WinUtils::ShowMaximized(HWND hwnd)
{
    ::ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

bool WinUtils::ShowMinimized(HWND hwnd)
{
    ::ShowWindow(hwnd, SW_SHOWMINIMIZED);
}

bool WinUtils::ShowRestore(HWND hwnd)
{
    ::ShowWindow(hwnd, SW_RESTORE);
}

bool WinUtils::HideWindow(HWND hwnd)
{
    ::ShowWindow(hwnd, SW_HIDE);
}

bool WinUtils::CloseWindow(HWND hwnd)
{
    ::SendMessage(hwnd, WM_CLOSE, 0, 0);
    //::DestroyWindow(hwnd);
}

QString WinUtils::GetWinTitleFromHwnd(HWND hwnd)
{
    TCHAR szTitle[255];
    //setlocale(LC_ALL, "");  //注意这里
    ::GetWindowText(hwnd, (LPWSTR)szTitle, sizeof(szTitle));
    QString titleText = QString::fromStdWString(szTitle);
    qDebug() << "窗口标题是" << titleText;
    return titleText;
}

QIcon WinUtils::GetWinIconFromHwnd(HWND hwnd)
{
    QIcon icon;
    HICON hIcon;
    hIcon = (HICON)(UINT_PTR)GetClassLongPtr(hwnd, GCLP_HICONSM);

    if (!hIcon) {
        hIcon = LoadIcon(NULL, IDI_APPLICATION);
    }

    icon.addPixmap(QtWin::fromHICON(hIcon));

    ::DestroyIcon(hIcon);
    return icon;
}

bool WinUtils::SetMyParent(HWND childHWND, HWND parentHWND)
{
    HWND ret = ::SetParent(childHWND, parentHWND);
    return (ret == NULL) ? false : true;
}

bool WinUtils::AdjustWindow(HWND hwnd, int nWidth, int nHeight, int x, int y)
{
    return ::MoveWindow(hwnd, x, y, nWidth, nHeight, TRUE);
}

WINSTATE WinUtils::GetWindowState(HWND hwnd)
{
    WINSTATE state = WINSTATE::HIDE;
    LONG winState = ::GetWindowLong(hwnd, GWL_STYLE);
    if (winState & WS_MINIMIZE)
    {
        state = WINSTATE::MINIMIZED;
    }
    else if (winState & WS_MAXIMIZE)
    {
        state = WINSTATE::MAXIMIZED;
    }
    else if (winState & WS_VISIBLE)
    {
        state = WINSTATE::SHOW;
    }
    else
    {
        state = WINSTATE::HIDE;
    }

    return state;
}


