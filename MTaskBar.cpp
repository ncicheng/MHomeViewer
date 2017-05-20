/**************************************************************************

Author: andycheng

Email:  ustbyangcheng@gmail.com

Date:   2017-05-20

**************************************************************************/

#include "MTaskBar.h"

#include <QAction>
#include <QDebug>
#include "WinUtils.h"

MTaskBar::MTaskBar(HWND hwnd, QWidget *parent):QPushButton(parent)
{
    m_hwnd = hwnd;

    this->setObjectName("MTaskBar");

    this->setCheckable(true);

    QString styleSheet = QString("\
    QPushButton#MTaskBar{  \
        color: rgb(255, 255, 255);              \
        background-color: rgb(167, 205, 255);   \
        border:none;                            \
        padding: 1px;                           \
        font-family: \"Microsfot YaHei\";       \
        font-size: 15px;                        \
        text-align: left; }                   \
    QPushButton#MTaskBar:hover, QPushButton#MTaskBar:pressed , QPushButton#MTaskBar:checked { \
        background-color: rgb(85, 170, 255);        \
        border: 1px;                                \
        font-weight: bold; }                        \
    ");

    this->setStyleSheet(styleSheet);

    setContextMenuPolicy(Qt::ActionsContextMenu);
    action_max = new QAction(this);
    action_min = new QAction(this);
    action_restore = new QAction(this);
    action_close = new QAction(this);

    action_max->setText("最大化");
    action_min->setText("最小化");
    action_restore->setText("还原");
    action_close->setText("关闭");

    action_max->setCheckable(false);
    action_min->setCheckable(false);
    action_restore->setCheckable(false);
    action_close->setCheckable(false);

    addAction(action_max);
    addAction(action_min);
    addAction(action_restore);
    addAction(action_close);

    connect(action_max, SIGNAL(triggered()), this, SLOT(onActionMax()));
    connect(action_min, SIGNAL(triggered()), this, SLOT(onActionMin()));
    connect(action_restore, SIGNAL(triggered()), this, SLOT(onActionRestore()));
    connect(action_close, SIGNAL(triggered()), this, SLOT(onActionClose()));

    isClose = false;
}

bool MTaskBar::isClosed()
{
    return isClose;
}

void MTaskBar::onActionMax()
{
    qDebug() << "My HWND: " << m_hwnd;
    WinUtils::ShowRestore(m_hwnd);
}

void MTaskBar::onActionMin()
{
    WinUtils::ShowMinimized(m_hwnd);
    WinUtils::HideWindow(m_hwnd);
}

void MTaskBar::onActionRestore()
{
    WinUtils::ShowRestore(m_hwnd);
}

void MTaskBar::onActionClose()
{
    WinUtils::CloseWindow(m_hwnd);
    isClose = true;
}
