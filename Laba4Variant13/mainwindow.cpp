#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <iomanip>
#include <fstream>

using std::vector;
using namespace::std;

void changeThreeColimns(vector <vector<int>> &vv);
void insertRow(vector <vector<int>> &vv);
void deleteColumns(vector <vector<int>> &vv);
void changeLine(vector <vector<int>> &vv);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vector <vector <int>> sourceArray;
    readArray(sourceArray);
    printArray(ui->tableWidget_5,sourceArray);

    vector <vector <int>> task1(sourceArray);
    changeThreeColimns(task1);
    printArray(ui->tableWidget,task1);

    vector <vector <int>> task2(sourceArray);
    insertRow(task2);
    printArray(ui->tableWidget_2,task2);

    vector <vector <int>> task3(sourceArray);
    deleteColumns(task3);
    printArray(ui->tableWidget_3,task3);

    vector <vector <int>> task4(sourceArray);
    changeLine(task4);
    printArray(ui->tableWidget_4,task4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void changeThreeColimns(vector <vector<int>> &vv)
{
    for(int j =0;j<vv[0].size();j++){
        for(int i =0;i<vv.size();i++){
            if(j<3){
                vv[i][j]=pow(vv[i][j],2);
            }
        }
    }
}

void pushRow(vector <vector<int>> &vv,int row);

void insertRow(vector <vector<int>> &vv)
{

    int rows=vv.size();

    vv.resize(vv.size()+vv.size()/2);
    for(int i=1;i<vv.size();i++){
        vv[i].resize(vv[0].size());
    }

    int shift =0;

    for(int i = 0;i<rows;i++){
            if((i+1)%2==0){
                pushRow(vv,i+shift);
                shift++;
                }
    }
}

void pushRow(vector <vector<int>> &vv,int row)
{
    bool check =true;

    for(int i = vv.size()-1;i>=0;i--)
    {
        for(int j =0;j<vv[0].size();j++)
        {
            if(i==row)
            {
                check = false;
            }

            if(check)
            {
               int temp =  vv[i][j];
               vv[i][j] = vv[i-1][j];
               vv[i-1][j] = temp;
            }else
            {
                if(row==0)
                {
                    vv[row][j]=vv[1][j];
                }else
                vv[row][j]=vv[0][j];
            }
        }

        if(check==false)
        {
            break;
        }
    }
}

void deleteColumns(vector <vector<int>> &vv)
{


    for(int i =0;i<vv[0].size();i++)
    {
        int index =-1;

            if(vv[0][i]>vv[vv.size()-1][i])
            {
                index = i;
            }


        if(index!=-1 )
        {
           bool point = true;

           for(int j = 0;j<vv[1].size();j++)
           {
               for(int k = 0;k<vv.size();k++)
               {
                   if(index==j)
                   {
                         point =false;
                         vv[k][j]=vv[k][j+1];
                   }
                   else if(!point)
                   {
                        vv[k][j]=vv[k][j+1];
                   }

               }
           }

           for (int z = 0;z<vv.size();z++)
               vv[z].resize(vv[z].size()-1);
        }
    }

}

void MainWindow::readArray(vector <vector<int>> &vv)
{
    ifstream file("D:\\Massiv.txt");

    if(file)
    {
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

void changeLine(vector <vector<int>> &vv)
{
    int average = vv.size()/2;

    for(int i=0;i<vv[0].size();i++)
    {
        int temp = vv[0][i];
        vv[0][i] = vv[average-1][i];
        vv[average-1][i]=temp;

        int temp1 = vv[vv.size()-1][i];
        vv[vv.size()-1][i] = vv[average][i];
        vv[average][i]=temp1;
    }
}

void MainWindow::printArray(QTableWidget *tablecopy,vector <vector <int>> sourceArray)
{
    tablecopy->setRowCount(sourceArray.size());
    tablecopy->setColumnCount(sourceArray[0].size());

    for(int i =0;i<sourceArray.size();i++){
        for(int j =0;j<sourceArray[i].size();j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(sourceArray[i][j]));
            tablecopy->setItem(i,j,item);
        }
    }
}


