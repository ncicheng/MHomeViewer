/**************************************************************************

Author: andycheng

Email:  ustbyangcheng@gmail.com

Date:   2017-05-20

**************************************************************************/

#include "MHomeViewer.h"
#include "ui_MHomeViewer.h"

#include "WinUtils.h"
#include "MTaskPanel.h"
#include <QStyle>
#include <QDebug>

MHomeViewer::MHomeViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MHomeViewer)
{
    ui->setupUi(this);

    this->showMaximized();

    m_taskPanel = new MTaskPanel;
    ui->horizontalLayout->addWidget(m_taskPanel);

//    QStyle *style = QApplication::style();
//    m_taskPanel->AddTask(NULL, "测试一下", QIcon(style->standardIcon(QStyle::SP_ComputerIcon)));
}

MHomeViewer::~MHomeViewer()
{
    delete ui;
}

void MHomeViewer::on_pushButton_clicked()
{
    HWND myHwnd = (HWND)this->winId();
    //WinUtils::ShowMaximized(myHwnd);

    QString noteFile = QString("C:\\Windows\\notepad.exe");
    HWND hwnd = WinUtils::OpenExec(noteFile);
    //WinUtils::ShowMaximized(hwnd);
    if (hwnd)
    {
        QPoint GlobalPoint(ui->frame->mapToGlobal(QPoint(0, 0)));//获取控件在窗体中的坐标
        qDebug() << GlobalPoint;
        qDebug() << ui->frame->geometry();
        WinUtils::SetMyParent(hwnd, myHwnd);
        WinUtils::AdjustWindow(hwnd, this->geometry().width(), ui->frame->geometry().height());
        m_taskPanel->AddTask(hwnd, WinUtils::GetWinTitleFromHwnd(hwnd), WinUtils::GetWinIconFromHwnd(hwnd));
        //WinUtils::CloseWindow(hwnd);
    }
}

void MHomeViewer::on_pushButton_2_clicked()
{
    HWND myHwnd = (HWND)this->winId();
    //WinUtils::ShowMaximized(myHwnd);

    QString noteFile = QString("C:\\Windows\\System32\\calc.exe");
    HWND hwnd = WinUtils::OpenExec(noteFile);
    if (hwnd)
    {
        //WinUtils::ShowMaximized(hwnd);
        QPoint GlobalPoint(ui->frame->mapToGlobal(QPoint(0, 0)));//获取控件在窗体中的坐标
        qDebug() << GlobalPoint;
        qDebug() << ui->frame->geometry();
        WinUtils::SetMyParent(hwnd, myHwnd);
        WinUtils::AdjustWindow(hwnd, this->geometry().width(), ui->frame->geometry().height());
        m_taskPanel->AddTask(hwnd, WinUtils::GetWinTitleFromHwnd(hwnd), WinUtils::GetWinIconFromHwnd(hwnd));
        //WinUtils::CloseWindow(hwnd);
    }
}
