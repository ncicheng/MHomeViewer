/**************************************************************************

Author: andycheng

Email:  ustbyangcheng@gmail.com

Date:   2017-05-20

**************************************************************************/


#ifndef MTASHBAR_H
#define MTASHBAR_H

#include <QPushButton>

class QAction;
class MTaskBar : public QPushButton
{
    Q_OBJECT
public:
    explicit MTaskBar(HWND hwnd, QWidget *parent = 0);
    bool isClosed();  // 对应的窗口句柄是否已关闭

protected slots:
    void onActionMax();
    void onActionMin();
    void onActionRestore();
    void onActionClose();

private:
    HWND m_hwnd;  // 对应的窗口句柄
    bool isClose; // 对应的句柄是否关闭
    QAction *action_max; // 最大化
    QAction *action_min; // 最小化
    QAction *action_restore; // 还原
    QAction *action_close;  // 关闭
};

#endif // MTASHBAR_H
