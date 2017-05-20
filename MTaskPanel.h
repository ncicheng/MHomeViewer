/**************************************************************************

Author: andycheng

Email:  ustbyangcheng@gmail.com

Date:   2017-05-20

**************************************************************************/

#ifndef MTASKPANEL_H
#define MTASKPANEL_H

#include <QWidget>
#include <QList>

class MTaskBar;
class QHBoxLayout;
class QTimer;

class MTaskPanel : public QWidget
{
    Q_OBJECT
public:
    explicit MTaskPanel(QWidget *parent = 0);
    void AddTask(HWND hwnd, QString taskName, QIcon taskIcon);

signals:

public slots:
    void onTimeOut();

private:
    QList<MTaskBar *> m_taskList;
    QHBoxLayout *hboxLayout;
    QTimer *timer;  // 定时更新窗口列表
};

#endif // MTASKPANEL_H
