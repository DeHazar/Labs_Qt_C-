#include "mainwindow.h"
#include "ui_mainwindow.h"
using std::vector;
using namespace::std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *button = ui->pushButton;
    connect(button,SIGNAL(clicked()),this,SLOT(task1()));

     QPushButton *button2 = ui->pushButton_2;
     connect(button2,SIGNAL(clicked()),this,SLOT(task2()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void generateArray(int array[],int size);
void changeFirstMinus(int array[],int size,int change[]);
void change3mod(int array[],int size,int change[]);
void changeArray(int array[],int size,int change[]);

void  MainWindow::task1()
{
    int size = ui->lineEdit->text().toInt();
    int array[size];                      //Создаем одномерный массив
    generateArray(array,size);            //вызов метода для заполнения массива рандомными числами
    show_array(ui->lineEdit_2,array,size);//вывод

    int change1[size];                      //Новый массив ,потому что в следующем методе мы будем менять массив,,а исходный массив менять не надо,так как и дальше он нужен
    changeFirstMinus(array,size,change1);   //Вызываем метод ,чтобы изменить копию массива
    show_array(ui->lineEdit_3,change1,size);//ВЫводим копию массива

    int change2[size];
    change3mod(array,size,change2);
    show_array(ui->lineEdit_4,change2,size);

    int change3[size];
    changeArray(array,size,change3);
    show_array(ui->lineEdit_5,change3,size);
}

void generateArray(int array[],int size)
{
    for (int i =0;i<size;i++)
    {
        array[i]=rand()%40 - 20 ;   //rand()%ДОсколькиНАДОбратьЧИСЛО - число на которое сдвигаем в отрицательную (Вобще хз как объяснить эту хуйню ,лучше загугли) ОН спросит
    }
}

void changeFirstMinus(int array[],int size,int change[])
{
    int index =-1;   //Создаем переменную с минус 1

    for(int i =0;i<size;i++){
        if(array[i]<0)
        {                   //если меньше нуля присваеваем индексу текущий
            index =i;
        }
        change[i]=array[i];
    }
    if(index !=-1)
    {          //если индекс изменился с -1 то делаем
        change[index]=change[size-2];
    }
}

void change3mod(int array[],int size,int change[])
{
    for(int i =0;i<size;i++)
    {
        if(array[i]%3==0)
        {//кратность трем проверяем
            change[i]=i*array[i];
        }else
        change[i]=array[i];
    }
}

void changeArray(int array[],int size,int change[])
{
    for(int i =0;i<size;i++)
    {
        if((i+1)%3==0)
        {//кратность индекса массива на 3
            change[i]=i*array[i];
        }else
        change[i]=-array[i]*(i+1);
    }
}


void MainWindow::show_array(QLineEdit *line,int array[],int size)
{
    QString arrayStr="";//строка пустая

    for(int i =0;i<size;i++){
        arrayStr=arrayStr+ QString::number(array[i])+" ";//присваеваем строке элементы массива
    }
    line->setText(arrayStr);
}

void generateArrayVector(vector<vector<int>> &array,int n,int m);
void replaceOddElement(vector<vector<int>> &array);
void insertRow(vector<vector<int>> &array);
void replaceColumn(vector<vector<int>> &array);
void deleteColumn(vector<vector<int>> &array);

void MainWindow::task2()
{
    int size_n= ui->lineEdit_6->text().toInt();
    int size_m= ui->lineEdit_7->text().toInt();

    vector<vector <int>> array;
    generateArrayVector(array,size_n,size_m);
    printArray(ui->tableWidget,array);

    vector <vector<int>> changed(array);//тоже делаем коппии чтобы не трогать старые
    replaceOddElement(changed); //заменяем нечетные элементы
    printArray(ui->tableWidget_2,changed);
                                            //ну и так далее
    vector <vector<int>> changed2(array);
    insertRow(changed2);
    printArray(ui->tableWidget_3,changed2);

    vector <vector<int>> changed3(array);
    deleteColumn(changed3);
    printArray(ui->tableWidget_4,changed3);

    replaceColumn(array);
    printArray(ui->tableWidget_5,array);
}

void generateArrayVector(vector<vector<int>> &array,int n,int m)
{
     vector <int> temp;  //создаем массив для заполнения строк

     for(int i=0;i<n;i++)
     {
         for(int j =0;j<m;j++)
         {
             temp.push_back(rand()%40 - 20); //пуш бэк это типо класть последним элемент(представь очередь и когда ты приходишь ты встаешь в конец очереди)
         }

         array.push_back(temp); //СКАЖИ что нашла это в инете или подсказали ,если спросит
         temp.clear();//чистим временную переменную
     }
}

void MainWindow::printArray(QTableWidget *tablecopy,vector <vector <int>> originalTable)
{
    tablecopy->setRowCount(originalTable.size());//size() -получает размер текущего измерения массива .
    tablecopy->setColumnCount(originalTable[0].size());//просто устанавливаем количество строк и столбцов в табликчке

    for(int i =0;i<originalTable.size();i++){
        for(int j =0;j<originalTable[i].size();j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(originalTable[i][j]));
            tablecopy->setItem(i,j,item);
        }
    }
}

void replaceOddElement(vector<vector<int>> &array)
{
    for(int i =0;i<array.size();i++)
    {
        for(int j =0;j<array[i].size();j++)
        {
            if(array[i][j]%2!=0){//проверка на нечетность
                array[i][j]=0;            }
        }
    }
}

void insertRow(vector<vector<int>> &array)
{
    vector<vector<int>>copy(array);
    array.resize(array.size()*2);//увеличиваем количество строк в массиве. Потом объясню эти методы сам.

    for(int i =copy.size();i<array.size();i++)
    {
        array[i].resize(copy[0].size());//увеличиваем количество столбцов в строках ,которые добавили выше в массиве.
    }


    for(int i =0;i<array.size();i++)
    {
        for(int j = 0;j<array[i].size();j++)
        {
            if((i+1)%2==0)
            {
                array[i][j]=j+1;
            }else
            {
                array[i][j]=copy[i/2][j];
            }
        }
    }

}

void replaceColumn(vector<vector<int>> &array)//просто меняем столбцы местами
{
        for(int j = 0;j<array.size();j++)
        {
           int temp = array[j][0];
           array[j][0]=array[j][array[0].size()-1];
           array[j][array[0].size()-1]= temp;
        }

}

void deleteColumn(vector<vector<int>> &array)
{

    for(int i =0;i<array[0].size();i++)//проходимся по столбцам циклом
    {
        int index =-1;
        if(array[0][i]%2==0)
        {//если первый элемент столбца четный то индекс приравниваем столбцу текущему
                index = i;
        }

        if(index!=-1 )
        {
           bool point = true; //метка

           for(int j = 0;j<array[1].size();j++)//столбцы
           {
               for(int k = 0;k<array.size();k++)//строки
               {
                   if(index==j)
                   {
                         point =false;
                         array[k][j]=array[k][j+1];
                   }
                   else if(!point)
                   {
                        array[k][j]=array[k][j+1];
                   }

               }
           }
           for (int z = 0;z<array.size();z++)
               array[z].resize(array[z].size()-1);
        }
    }

}
