/**************************************************************************

Author: andycheng

Email:  ustbyangcheng@gmail.com

Date:   2017-05-20

**************************************************************************/

#include "MTaskPanel.h"
#include "MTaskBar.h"

#include <QHBoxLayout>
#include <QTimer>

MTaskPanel::MTaskPanel(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(40);

    hboxLayout = new QHBoxLayout;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer->start(100);

}

void MTaskPanel::AddTask(HWND hwnd, QString taskName, QIcon taskIcon)
{
    MTaskBar *taskBar = new MTaskBar(hwnd);
    taskBar->setFixedSize(150, 30);
    taskBar->setText(taskName);
    taskBar->setIcon(taskIcon);
    m_taskList.append(taskBar);

    hboxLayout->addWidget(taskBar);
    this->setLayout(hboxLayout);
}

void MTaskPanel::onTimeOut()
{
    for (int i = 0; i < m_taskList.count(); ++i)
    {
        if (m_taskList.at(i)->isClosed())
        {
            m_taskList.at(i)->close();
            m_taskList.removeAt(i);
        }
    }
}
