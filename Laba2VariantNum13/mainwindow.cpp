#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QPushButton>
#include <math.h>
#include<QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *buttonTask1 = ui->pushButton;                  //Связываем баттон с кнопкой которую мы расположили в mainwindow.ui(где перетаскивали на форму баттон)
    connect(buttonTask1,SIGNAL(clicked()),this,SLOT(task1()));  //Соединяем кнопку button к сигнал clicked и методу task.
                                                                //То есть при нажатии на кнопку (это clicked) вызывался метод task 22 строка здесь.А слот мы описали в mainwindow.h

    QPushButton *buttonTask2 = ui->pushButton_2;
    connect(buttonTask2,SIGNAL(clicked()),this,SLOT(calcuteEPS())); //здесь соединяем сразу два метода на кнопку
    connect(buttonTask2,SIGNAL(clicked()),this,SLOT(calculateN()));

    ui->lineEdit_9->setText(findNumbers());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::task1()
{

    double a = ui->lineEdit->text().toDouble();     //Считываем данные формы ui - это интерфейс пользователя, text()- получаем текст с формы
    double b =ui->lineEdit_2->text().toDouble();    //toDouble- преобразуем строковое значение в число с плавающей точкой
    double c =ui->lineEdit_3->text().toDouble();

    QTableWidget *table = ui->tableWidget;      //просто присваем переменной(ссылку,значение ) с формы,чтобы можно было обращаться по этому имени, а не постоянно  ui->tableWidget
    table->setColumnCount(2);       //Устанавлиеваем таблице данных 2 столбца
    table->setRowCount(13);         //Устанавлиеваем 13 строк
    QTableWidgetItem *header1 = new QTableWidgetItem("i");      //создаем элемент таблицы ,в данном случае это заголовок
    QTableWidgetItem *header2 = new QTableWidgetItem("y");
    table->setHorizontalHeaderItem(0,header1);      // устанавливаем Горизонтальные заголовки в таблицах ,Где в скобках(номер столдбца, элемент столбца созданный ранее)
    table->setHorizontalHeaderItem(1,header2);

    double y=0;     //переменная для хранения результата

    for(int i =0;i<13;i++)
    {
        if(i<4)
        {
            y = a/i+b*pow(i,2) +c;
        }else if(i>=4 &&i<=6)
        {
            y =i;
        }else
        {
            y =a*i+b*pow(i,3);
        }

         QTableWidgetItem *i_table = new QTableWidgetItem(QString::number(i));      //QString::number(i) преобразует числовое значение в строку,так как элеменет таблицы принимает только строку
         QTableWidgetItem *y_table = new QTableWidgetItem(QString::number(y));
         table->setItem(i,0,i_table);                                               //устанавливаем элемент в i-ую строку 0 столбца
         table->setItem(i,1,y_table);
    }
}

double factorial(int i);

void MainWindow::calcuteEPS()                                //Расчет ряда с точностью
{
    double eps = ui->lineEdit_5->text().toDouble();         //считываем данные с формы

    double sum =0;
    double last=0;
    double current=0;
    int k=0;

    current = pow(-1,k)/(factorial(k)*factorial(k+1));
    sum+=current;
    k++;

    do      //цикл  сначала делает потом проверяет
    {
       last = current;
       current =  pow(-1,k)/(factorial(k)*factorial(k+1));
       sum= sum + current;
       k++;
    }
    while(abs(current - last)>eps); // по модулю проверяет

    ui->lineEdit_6->setText(QString::number(k-1));
    ui->lineEdit_8->setText(QString::number(sum));
}

void MainWindow::calculateN()       //расчет по кол-ву
{
    double sum=0;
    int k = ui->lineEdit_4->text().toInt();

    for(int i =0;i<=k;i++)
    {
        sum= sum +pow(-1,i)/(factorial(i)*factorial(i+1));
    }

    ui->lineEdit_7->setText(QString::number(sum));
}

double factorial(int n)
{        //Расчет факториала ЦИКЛОМ, не рекурсивно
   double sum =1;

   for(int i = 1; i <=n; ++i)
       {
           sum *= i;
       }
   return sum;

}


QString  MainWindow::findNumbers()                  //метод возращает стринг ,а не void
{
    QString find = "нет таких чисел";                //создаем переменную для ответа

    for(int i =10;i<100;i++){
        if((i*2)%10==8 && (i*3)%10==4){              // Проверка условия (i*2)%10==8  так процент это остаток от деления , == - это проверка на равенство . ПРимер (46*2)%10 =92%10 = 2 что  !=8
            find.append(QString::number(i)+" ");        //присоеденяем к строке число найденное и пробел
        }
    }
    return find; // возврат найденных значений
}

