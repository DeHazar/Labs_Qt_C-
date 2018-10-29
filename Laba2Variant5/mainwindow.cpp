#include "mainwindow.h"

#include <QGridLayout>
#include <QInputDialog>
#include <QLabel>
#include <QTableWidget>
#include <vector>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    draw_window();
}

MainWindow::~MainWindow()
{


}

void MainWindow::draw_window()
{
    central = new QTabWidget(this);
    setCentralWidget(central);
    setWindowTitle(tr("Лабораторная работа №2"));
    draw_window1();
    draw_window2();
    draw_window3();
}

void MainWindow::draw_window1()
{
    QWidget *tab = new QWidget(central);        //Создаем окно ,где можно переключаться

    QGridLayout *layout = new QGridLayout(tab); // создаем сетку
    tab->setLayout(layout);
    central->addTab(tab,"Задача 1");

    QLabel *label = new QLabel(central);
    QPixmap pixmax("C:\\task.PNG","PNG");       //Здесь нужно указать путь к картинке,закниь картинку из папки в диск С
    label->setPixmap(pixmax);                   //устанавливаем изображение в лэйбл
    layout->addWidget(label,0,0,1,3);           //Добавляем и растягиваем изображение

    QLabel *a = new QLabel(central);
    a->setText("a=");
    layout->addWidget(a,1,0);

    aTab = new QLineEdit(central);
    aTab->setText("2.3");
    layout->addWidget(aTab,1,1);

    QTableWidget *table = new QTableWidget(tab);        //Создаем табличку где будем ввыводить значения
    table ->setColumnCount(2);                          //Указываем кол-во столбцов
    QTableWidgetItem *header1 = new QTableWidgetItem("t");//Устанавливаем  текст Заголовков для столбцов
    table->setHorizontalHeaderItem(0,header1);             //Устанавливаем  Заголовок для столбца
    QTableWidgetItem * header2 = new QTableWidgetItem("y");
    table->setHorizontalHeaderItem(1,header2);
    table->setRowCount(40);                                  //Устанавливаем количество строк
    layout->addWidget(table,3,0,1,2);

    double A = aTab->text().toDouble();                       //считываем


    double result =0;
    double x=0.2;
    for(int i =0;i<40;i++)
    {
        QTableWidgetItem *Result;                    //Создаем переменную Item ,чтобы дальше присвоить ей значение
        if(x==1)                                    //ПРоверка условий
        {
            result = 1.5*pow(acos(x),2);            //pow(x,2) возведение числа х в степень 2  acos(x) - косинус радиан
            Result = new QTableWidgetItem(QString::number(result));     //Присваеваем айтему результат вычисления . Number() преобразует число в строку
        }
        else if(x>2){                                //Делаем тоже самое
            result = pow((x-2),2)+6;
           Result = new QTableWidgetItem(QString::number(result));
        }else if(x>1 && x<2){                            //Делаем тоже самое
             result = 1.8*A*x;
           Result = new QTableWidgetItem(QString::number(result));
        }else {
            Result = new QTableWidgetItem(tr("Не входит в диапозон значений"));
        }

        QTableWidgetItem *X = new QTableWidgetItem(QString::number(x));    //Присваеваем наш шаг x . Number() преобразует число в строку


        table->setItem(i,0,X);               //выводим в первый столбец х
        table->setItem(i,1,Result);              //во второй  результат
        x+=0.20;                              //увееличиваем х на шаг 0.2

    }
    }

void MainWindow::draw_window2()
{
    QWidget *tab = new QWidget(central);
    QGridLayout *layout = new QGridLayout(tab);
    tab->setLayout(layout);
    central->addTab(tab,tr("Задание 2"));

    QLabel *quest = new QLabel(central);
    QPixmap pixmax("C:\\2.PNG","PNG");               //Здесь нужно указать путь к картинке,закниь картинку из папки в диск С
    quest->setPixmap(pixmax);                       //устанавливаем изображение в лэйбл
    layout->addWidget(quest,0,0,1,3);

    QLabel *nLabel = new QLabel(central);
    nLabel->setText("n=");
    layout->addWidget(nLabel,1,0);

    n = new QLineEdit(central);
    n->setText("3");
    layout->addWidget(n,1,1);


    QLabel *epsLabel = new QLabel(central);
    epsLabel->setText("eps=");
    layout->addWidget(epsLabel,1,2);

    eps = new QLineEdit(central);
    eps->setText("0.0001");
    layout->addWidget(eps,1,3);

    button =new QPushButton(central);
    button->setText(tr("Вычислить"));
    layout->addWidget(button,2,0,1,2);
    connect(button,SIGNAL(clicked()),this,SLOT(calculate_for_N()));//соединяем кнопки  с методами ,чтобы при нажатии вызывал метод
    connect(button,SIGNAL(clicked()),this,SLOT(calcute_for_EPS()));

    QLabel *n_eps = new QLabel(central);
    n_eps->setText("n eps=");
    layout->addWidget(n_eps,2,2);

    nEps = new QLineEdit(central);
    layout->addWidget(nEps,2,3);

    QLabel *sum_eps = new QLabel(central);
    sum_eps->setText("sum eps=");
    layout->addWidget(sum_eps,3,0);

    resultN = new QLineEdit(central);
    layout->addWidget(resultN,3,1);

    QLabel *sum_n = new QLabel(central);
    sum_n->setText("sum n=");
    layout->addWidget(sum_n,3,2);

    resultEPS = new QLineEdit(central);
    layout->addWidget(resultEPS,3,3);


}

void MainWindow::draw_window3(){

    QWidget *tab = new QWidget(central);
    QGridLayout *layout = new QGridLayout(tab);
    tab->setLayout(layout);
    central->addTab(tab,"Задание 3");

    QLabel *nLabel = new QLabel(central);
    nLabel->setText("В простую переменную последовательно вводятся N чисел. Все ли числа меньше заданного числа К?");
    layout->addWidget(nLabel,1,0,1,2);

    QLabel *n_val = new QLabel(central);
    n_val->setText("Введите кол-во цифр,которые хотите ввести");
    layout->addWidget(n_val,2,0);

    n_value = new QLineEdit(central);
    n_value->setText("3");
    layout->addWidget(n_value,2,1);

    QLabel *k= new QLabel(central);
    k->setText("Число К");
    layout->addWidget(k,2,2);

    K = new QLineEdit(central);
    K->setText("6");
    layout->addWidget(K,2,3);

    button2 = new QPushButton(central);
    button2->setText("Вычислить");
    layout->addWidget(button2,3,0);
    connect(button2,SIGNAL(clicked()),this,SLOT(findNumbers()));

    QLabel *answe= new QLabel(central);
    answe->setText("Ответ");
    layout->addWidget(answe,3,1);

    result = new QLineEdit(central);
    layout->addWidget(result,3,2,1,2);

}

void MainWindow::findNumbers()
{
    int n = n_value->text().toInt();
    int k = K->text().toInt();

    vector <int> array;                                                          //Создаем массив(считай что это обычный массив,пытался его использовать ,но кт ругался)
    for(int i=0;i<n;i++){
    int value= QInputDialog::getInt(central,"Введите","Введите целое число "); //Вызываем диалоговые окна ,где надо вводить числа
    array.push_back(value);                                                      //Добавляем в конец массива числа
    }

    bool point =false;                      // метка
    for(int i=0;i<n;i++){
        if(array[i]>k){                    //если в введенных числах , есть значения больше к
            point=true;
        }
    }
    if(point){
        result->setText("Не все числа меньше заданного");
    } else
        result->setText("Все числа меньше заданного");

}


double factorial(int i);

void MainWindow::calcute_for_EPS()              //Расчет ряда
{
    double EPS = eps->text().toDouble();
    double sum =0;
    double last=0;
    double current=0;
    int k=0;

    current = 1/(factorial(k+2)*factorial(k+3));
    sum+=current;
    k++;

    do
    {
       last = current;
       current =  1/(factorial(k+2)*factorial(k+3));
       sum= sum + current;
       k++;
    }
    while(std::abs(current - last)>EPS);


    nEps->setText(QString::number(k-1));
    resultEPS->setText(QString::number(sum));
}

void MainWindow::calculate_for_N()
{
    double sum=0;
    int k = n->text().toInt();

    for(int i =0;i<=k;i++)
    {
        sum= sum +1/(factorial(i+2)*factorial(i+3));
    }

    resultN->setText(QString::number(sum));
}

double factorial(int n){
   double sum =1;

   for(int i = 1; i <=n; ++i)
       {
           sum *= i;
       }
   return sum;

}
