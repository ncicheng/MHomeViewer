/**************************************************************************

Author: andycheng

Email:  ustbyangcheng@gmail.com

Date:   2017-05-20

**************************************************************************/

#ifndef MHOMEVIEWER_H
#define MHOMEVIEWER_H

#include <QMainWindow>

class MTaskPanel;

namespace Ui {
class MHomeViewer;
}

class MHomeViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MHomeViewer(QWidget *parent = 0);
    ~MHomeViewer();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MHomeViewer *ui;

    MTaskPanel *m_taskPanel;
};

#endif // MHOMEVIEWER_H
