/**************************************************************************

Author: andycheng

Email:  ustbyangcheng@gmail.com

Date:   2017-05-20

**************************************************************************/

#ifndef WINUTILS_H
#define WINUTILS_H

#include <QString>
#include <QIcon>
#include <windows.h>

// 窗口状态
enum WINSTATE
{
    HIDE = 0,   //  隐藏
    SHOW,       //  正常显示
    MAXIMIZED,  //  最大化
    MINIMIZED   //  最小化
};

class WinUtils
{
public:
    /**
        * @brief 打开程序
        * @param exeFile    可执行程序的路径
        * @param WINSTATE   程序打开时的窗口状态
        *
        * @return HWND 打开程序的窗口句柄
        *        -<em>NULL</em> fail
        *        -<em>not NULL</em> succeed
    **/
    static HWND OpenExec(QString exeFile, WINSTATE openState = SHOW);

    /**
        * @brief 最大化窗口
        * @param HWND    窗口句柄
        *
        * @return 是否成功
        *        -<em>false</em> fail
        *        -<em>true</em> succeed
    **/
    static bool ShowMaximized(HWND hwnd);

    /**
        * @brief 最小化窗口
        * @param HWND    窗口句柄
        *
        * @return 是否成功
        *        -<em>false</em> fail
        *        -<em>true</em> succeed
    **/
    static bool ShowMinimized(HWND hwnd);

    /**
        * @brief 恢复窗口
        * @param HWND    窗口句柄
        *
        * @return 是否成功
        *        -<em>false</em> fail
        *        -<em>true</em> succeed
    **/
    static bool ShowRestore(HWND hwnd);

    /**
        * @brief 隐藏窗口,但不退出
        * @param HWND    窗口句柄
        *
        * @return 是否成功
        *        -<em>false</em> fail
        *        -<em>true</em> succeed
    **/
    static bool HideWindow(HWND hwnd);

    /**
        * @brief 关闭窗口
        * @param HWND    窗口句柄
        *
        * @return 是否成功
        *        -<em>false</em> fail
        *        -<em>true</em> succeed
    **/
    static bool CloseWindow(HWND hwnd);

    /**
        * @brief 根据HWND句柄获取窗口标题
        * @param HWND    窗口句柄
        *
        * @return 窗口标题文字
        *        -<em>empty</em> fail
        *        -<em>not empty</em> succeed
    **/
    static QString GetWinTitleFromHwnd(HWND hwnd);

    /**
        * @brief 根据HWND句柄获取窗体的ICON图标
        * @param HWND    窗口句柄
        *
        * @return ICON图标
        *        -<em>NULL</em> fail
        *        -<em>not NULL</em> succeed
    **/
    static QIcon GetWinIconFromHwnd(HWND hwnd);

    /**
        * @brief 设置父进程
        * @param childHWND    子窗口句柄
        * @param parentHWND   父窗口句柄
        *
        * @return 是否成功
        *        -<em>false</em> fail
        *        -<em>true</em> succeed
    **/
    static bool SetMyParent(HWND childHWND, HWND parentHWND);

    /**
        * @brief 设置窗口的位置和大小
        * @param hwnd    窗口句柄
        * @param nWidth   窗口宽度
        * @param nHeigth  窗口高度
        * @param x        X坐标
        * @param y        Y坐标
        *
        * @return 是否成功
        *        -<em>false</em> fail
        *        -<em>true</em> succeed
    **/
    static bool AdjustWindow(HWND hwnd, int nWidth, int nHeight, int x = 0, int y = 0);

    /**
        * @brief 获取窗口的当前状态
        * @param hwnd    窗口句柄
        *
        * @return 窗口状态
        *        -<em>WINSTATE</em>
    **/
    static WINSTATE GetWindowState(HWND hwnd);
};

#endif // WINUTILS_H
