#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMainWindow>
#include <QTableWidget>
#include <stdio.h>
#include <iomanip>
#include <fstream>

using std::vector;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTabWidget *central;
    QLineEdit *line;
    QLineEdit *answer;
    QTableWidget *table ;
    QTableWidget *table1;
    QTableWidget *table2;
    QTableWidget *table3;
    QTableWidget *table4;

    void draw_window2();
    void draw_window1();
    void draw_window();
    void readArray(vector <vector<int>> &x);
    void printArray(QTableWidget * table,vector <vector <int>> originalTable);
    void replaceMax(vector <vector<int>> vv);
    void insertNull(vector <vector<int>> vv);
    void deleteMinusElements(vector <vector<int>> vv);
    void changeFirstAndLastColumn(vector <vector<int>> vv);
public slots:
    void calculateFirst();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
