#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myexception.h"
#include <QMessageBox>
#include <math.h>
#include <QDebug>
#include "date.h"


int days = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

    ui->setupUi(this);
    ui->day->setValue(dt.d); // сразу установим текущую дату
    ui->month->setValue(dt.m);
    ui->year->setValue(dt.y);
    ui->day1->setValue(dt.d); // сразу установим текущую дату
    ui->month1->setValue(dt.m);
    ui->year1->setValue(dt.y);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* ){
    days = abs(dt - dt1);

    ui->livedays->setText("Количество прожитых дней: " + QString::number(days));
    QPainter painter;
    painter.begin(this);

    painter.setRenderHint(QPainter::Antialiasing, true);



    QPoint pos = QCursor::pos(); //позиция курсора
    QPoint pos2 = this->pos();  //позиция окна
    int diffx = pos.x()-pos2.x();
    painter.drawLine(diffx, 0,diffx ,height()); // отнимая от положения курсора положение окна будем рисовать вертикальную линию


    diffx -= width()/2;
    ui->result_label->setText("Физиологический:\t" + QString::number(sin(-diffx*M_PI/23/15)*100) +
                              "\nПсихологический:\t" + QString::number(sin(-diffx*M_PI/28/15)*100) +
                              "\nУмственный:\t\t" + QString::number(sin(-diffx*M_PI/33/15)*100));




    painter.translate(width()/2,height()/2 + 50); // перенесем начало координат
    painter.drawLine(-width(),0,width(),0); // ось

    QPoint point;
    painter.save();
    for(double j = -width()/60, i = -width() / 60; i < width() / 60; i += 0.01){ // будем растягивать ось Х в 30 раз поэтому делим на 30 значения
        j += 0.01;
        point.setX(j*30);


        QPen linepen(Qt::red);
        linepen.setWidth(3);
        painter.setPen(linepen);
        point.setY(sin(-(i+days)*2*M_PI/23)*100);
        painter.drawPoint(point);

        linepen.setColor(Qt::blue);
        painter.setPen(linepen);
        point.setY(sin(-(i+days)*2*M_PI/28)*100);
        painter.drawPoint(point);

        linepen.setColor(QColor(64,38,52));
        painter.setPen(linepen);
        point.setY(sin(-(i+days)*2*M_PI/33)*100);
        painter.drawPoint(point);


    }

    painter.restore();

    for (int j=-width()/60; j <= width()/60; j++){
        if(j == 0){
            painter.save();
            QPen linepen(Qt::black);
            linepen.setWidth(3);
            painter.setPen(linepen);
            QFont font = painter.font();
            font.setPointSize(10);
            painter.setFont(font);
            painter.drawLine(j*30,-20, j*30,20);
            painter.rotate(90);
            Date dd(dt1);
            dd = dd - j * (int)(days / 2);
            QString date = QString::number(dd.d) + "." + QString::number(dd.m) + "." + QString::number(dd.y);
            //QString date= ui->current_date->date().addDays(-j).toString();
            painter.drawText(10, j*30, date);
            painter.restore();
        }
        else{

            painter.drawLine(j*30,-10, j*30,10);


            painter.save();
            painter.rotate(90);
            //QString date= ui->current_dat e->date().addDays(-j).toString();
            Date dd(dt);
            dd = dd - j * (int)(days / 2);
            QString date = QString::number(dd.d) + "." + QString::number(dd.m) + "." + QString::number(dd.y);
            painter.drawText(10, j*30, date);
            painter.restore();
        }
    }


    painter.end();
    //update();
}

void MainWindow::on_action_triggered()
{
    QApplication::quit();
}

void MainWindow::on_action_2_triggered()
{
    QMessageBox::about(this, "О программе", "Эта программа считает биоритмы. Жизнь человека, как и все в природе, подвержено влиянию циклических изменений. Успешность того или иного вида деятельности в каждый момент времени определяется балансом притока и оттока его внутренней энергии. Такой баланс изменяется в соответствии  с циклами биоритмов человека");
}

void MainWindow::on_day_valueChanged(int arg1)
{
    if (dt.m == 2)
    {
        if(dt.IsLeapYear(dt.y))
            ui->day->setMaximum(29);
        else
            ui->day->setMaximum(28);
    }
    dt.d = arg1;
    if (dt > dt1)
    {
        while (dt > dt1)
            dt = dt - 1;
        ui->day->setValue(dt.d);
    }
}


void MainWindow::on_month_valueChanged(int arg1)
{
    dt.m = arg1;
    if (arg1 != 2)
        ui->day->setMaximum(dt.day_count[arg1-1]);
    else
        if(dt.IsLeapYear(dt.y))
            ui->day->setMaximum(29);
        else
            ui->day->setMaximum(28);
}


void MainWindow::on_year_valueChanged(int arg1)
{
    if (arg1 == 0)
        ui->year->setValue(1);
    else
        dt.y = arg1;
    if (dt.m == 2)
    {
        if(dt.IsLeapYear(dt.y))
            ui->day->setMaximum(29);
        else
            ui->day->setMaximum(28);
    }
}


void MainWindow::on_day1_valueChanged(int arg1)
{
    if (dt1.m == 2)
    {
        if(dt1.IsLeapYear(dt1.y))
            ui->day1->setMaximum(29);
        else
            ui->day1->setMaximum(28);
    }
    dt1.d = arg1;
}


void MainWindow::on_month1_valueChanged(int arg1)
{
    dt1.m = arg1;
    if (arg1 != 2)
        ui->day1->setMaximum(dt1.day_count[arg1-1]);
    else
        if(dt1.IsLeapYear(dt1.y))
            ui->day1->setMaximum(29);
        else
            ui->day1->setMaximum(28);
}


void MainWindow::on_year1_valueChanged(int arg1)
{
    if (arg1 == 0)
        ui->year1->setValue(1);
    else
        dt1.y = arg1;
    if (dt1.m == 2)
    {
        if(dt1.IsLeapYear(dt1.y))
            ui->day1->setMaximum(29);
        else
            ui->day1->setMaximum(28);
    }
}

