#include "mainwindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QTableWidget>
#include <iostream>
#include <string.h>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <iomanip>
#include <fstream>

using std::vector;
using namespace::std;

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
    setWhatsThis("Лабораторная работа 4");

    draw_window1();
    draw_window2();
}

void MainWindow::draw_window1()
{

    QWidget *tab = new QWidget(central);
    QGridLayout *layout = new QGridLayout(tab);
    tab->setLayout(layout);
    central->addTab(tab,"Файлы 1 задача");

    QLabel *task = new QLabel(tab);
    task->setText("Дан текст на русском языке. Подсчитать количество слов, начинающихся и заканчивающихся на одну и ту же букву.");
    layout->addWidget(task,0,0,1,2);

    QPushButton *button = new QPushButton(tab);
    button->setText("Решить");
    layout->addWidget(button,2,0);
    button->connect(button,SIGNAL(clicked()),this,SLOT(calculateFirst()));

    answer = new QLineEdit(tab);
    answer->setText("Answer");
    layout->addWidget(answer,2,1,1,1);

    line =new QLineEdit(tab);
    line->setText("Введите строку");
    layout->addWidget(line,3,0);


}

void MainWindow::calculateFirst(){
    QString text = line->text();

    QStringList array = text.split(" ",QString::SkipEmptyParts);
    int result =0;

    for(int i =0;i<array.length();i++){
        if(array[i][0]==array[i][array[i].length()-1]){
            result++;
        }
    }
    answer->setText(QString::number(result));

}

void MainWindow::draw_window2()
{
    QWidget *tab = new QWidget(central);
    QGridLayout *layout = new QGridLayout(tab);
    tab->setLayout(layout);
    central->addTab(tab,"Файлы 2 задача");

    QLabel *task = new QLabel(tab);
    task->setText("Дан двумерный массив размером n*m. \n "
                  "1.Заменить максимальный элемент каждой строки на противоположный по знаку \n "
                  "2.Вставить после всех столбцов, содержащих максимальный элемент столбец из нулей. "
                  "\n 3.Удалить все столбцы, в которых есть отрицательный элемент \n  4.Поменять местами первый и последний столбцы");
    layout->addWidget(task,0,0,1,4);

    QPushButton *button = new QPushButton(tab);
    button->setText("Решить");
    layout->addWidget(button,1,0);
    button->connect(button,SIGNAL(clicked()),this,SLOT(calculateFirst()));

    QLabel *task1 = new QLabel(tab);
    task1->setText("Задача 1");
    layout->addWidget(task1,2,0);

    table1 = new QTableWidget(tab);
    layout->addWidget(table1,3,0,1,2);

    QLabel *task2 = new QLabel(tab);
    task2->setText("Задача 2");
    layout->addWidget(task2,2,2);

    table2 = new QTableWidget(tab);
    layout->addWidget(table2,3,2,1,2);


    table3 = new QTableWidget(tab);
    layout->addWidget(table3,5,0,1,2);

    table4 = new QTableWidget(tab);
    layout->addWidget(table4,5,2,1,2);

    QLabel *task3 = new QLabel(tab);
    task3->setText("Задача 3");
    layout->addWidget(task3,4,0);

    QLabel *task4 = new QLabel(tab);
    task4->setText("Задача 4");
    layout->addWidget(task4,4,2);

    QLabel *taskOsnova = new QLabel(tab);
    taskOsnova->setText("Матрица с файла");
    layout->addWidget(taskOsnova,6,1);

    table = new QTableWidget(tab);
    layout->addWidget(table,7,1,1,2);

    vector <vector <int>> originalTable;
    readArray(originalTable);
    printArray(table,originalTable);
    replaceMax(originalTable);
    insertNull(originalTable);
    deleteMinusElements(originalTable);
    changeFirstAndLastColumn(originalTable);

}

void MainWindow::printArray(QTableWidget *tablecopy,vector <vector <int>> originalTable)
{
    tablecopy->setRowCount(originalTable.size());
    tablecopy->setColumnCount(originalTable[0].size());

    for(int i =0;i<originalTable.size();i++){
        for(int j =0;j<originalTable[i].size();j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(originalTable[i][j]));
            tablecopy->setItem(i,j,item);
        }
    }
}


void MainWindow::readArray(vector <vector<int>> &vv){

    ifstream file("C:\\Users\\garae\\Documents\\LabaNumber4\\Massiv.txt");

    if(file){
            vector <int> temp;
            int i ;
               while (file >> i)
               {
                   temp.push_back(i);
                   if (file.peek() == '\n' || file.peek() == EOF)
                   {
                       vv.push_back(temp);
                       temp.clear();
                   }
               }
               file.close();
    }

}

void MainWindow::replaceMax(vector <vector<int>> vv)
{
    for(int i =0;i<vv.size();i++)
    {
        int max = vv[i][0];
        int index =0;

        for(int j =0;j<vv[i].size();j++)
        {
            if(vv[i][j]>max){
                max =vv[i][j];
                index = j;
            }
        }
        vv[i][index]=-vv[i][index];
    }

    printArray(table1,vv);
}

void MainWindow::insertNull(vector <vector<int>> vv)
{
    vector <vector <int>> copy(vv);
    for(int i =0;i<vv.size();i++)
    {
        int index =0;
        int max=copy[i][0];

        for(int j =0;j<copy[0].size();j++)
        {
            if(copy[i][j]>max){
                max =copy[i][j];
                index = j;
            }
        }

        if(copy[0][index+1]!=0 )
        {

            for (int z = 0;z<copy.size();z++)
                copy[z].resize(copy[z].size()+1);

            bool point = true;
           for(int j = copy[1].size()-1;j>=0;j--)
           {
               for(int k = copy.size()-1;k>=0;k--)
               {
                   if(index+1==j)
                   {
                         copy[k][j]=0;
                         point =false;
                   }
                   else
                   copy[k][j]=copy[k][j-1];
               }
               if(!point) break;
           }
        }else if(index+1==copy[0].size())
        {
            for (int z = 0;z<copy.size();z++)
                copy[z].resize(copy[z].size()+1);
        }


    }
        printArray(table2,copy);
}

void MainWindow::deleteMinusElements(vector <vector<int>> vv)
{
    vector <vector <int>> copy(vv);

    for(int i =0;i<copy[0].size();i++)
    {
        int index =-1;

        for(int j =0;j<copy.size();j++)
        {
            if(copy[j][i]<0){
                index = i;
            }
        }

        if(index!=-1 )
        {

           bool point = true;
           for(int j = 0;j<copy[1].size();j++)
           {
               for(int k = 0;k<copy.size();k++)
               {
                   if(index==j)
                   {
                         point =false;
                         copy[k][j]=copy[k][j+1];
                   }
                   else if(!point)
                   {
                        copy[k][j]=copy[k][j+1];
                   }

               }
           }
           for (int z = 0;z<copy.size();z++)
               copy[z].resize(copy[z].size()-1);
        }
    }
    printArray(table3,copy);
}

void MainWindow::changeFirstAndLastColumn(vector <vector<int>> vv)
{
    for(int i = 0;i<vv.size();i++)
    {
       int temp = vv[i][0];
       vv[i][0]=vv[i][vv[0].size()-1];
       vv[i][vv[0].size()-1]=temp;
    }
    printArray(table4,vv);
}


