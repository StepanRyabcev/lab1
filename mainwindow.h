#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QMouseEvent>
#include "date.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Date dt = Date::LocalTime();
    Date dt1 = Date::LocalTime();
protected:
    void paintEvent(QPaintEvent* ) override;
private slots:
    void on_action_triggered();
    void on_action_2_triggered();
    void on_day_valueChanged(int arg1);
    void on_month_valueChanged(int arg1);
    void on_year_valueChanged(int arg1);
    void on_day1_valueChanged(int arg1);
    void on_month1_valueChanged(int arg1);
    void on_year1_valueChanged(int arg1);
};
#endif // MAINWINDOW_H
