#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <math.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *button = ui->pushButton;//Связываем баттон с кнопкой которую мы расположили в mainwindow.ui(где перетаскивали на форму баттон)
    connect(button,SIGNAL(clicked()),this,SLOT(task()));//Соединяем кнопку button к сигнал clicked и методу task.То есть при нажатии на кнопку (это clicked) вызывался метод task 22 строка здесь.А слот мы описали в mainwindow.h

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::task()//Метод который вызывается при нажатии на кнопку
{
    double x1 = ui->lineEdit->text().toDouble();//Создаем переменную x1 и с формы получаем данные .Получаем с формы строку и преобразуем его в тип double.
    double x2 =ui->lineEdit_2->text().toDouble();
    double x3 = ui->lineEdit_3->text().toDouble();
    double y1 = ui->lineEdit_4->text().toDouble();
    double y2 = ui->lineEdit_5->text().toDouble();
    double y3 = ui->lineEdit_6->text().toDouble();

    double a=sqrt(pow((x2-x1),2)+pow((y2-y1),2));//считаем стороны треугольника pow-возведение в степень, sqrt -корень
    double b=sqrt(pow((x3-x2),2)+pow((y3-y2),2));
    double c=sqrt(pow((x1-x3),2)+pow((y1-y3),2));

    if(ui->radioButton->isChecked())//Проверяем состояния  радиоБаттонов
    {
        double answer = (a+b+c)/2;
        ui->lineEdit_7->setText(QString::number(answer));//Здесь выводим ответ.Так как setText требует только строку, то используем статический метод QString::number ,который преобразует число в строку
    }
    else if(ui->radioButton_2->isChecked())
    {
        double p = (a+b+c)/2;
        double answer =sqrt(p*(p - a)*(p - b)*(p - c));
        ui->lineEdit_7->setText(QString::number(answer));
    }
}

