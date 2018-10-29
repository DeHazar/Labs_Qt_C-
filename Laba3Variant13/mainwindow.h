#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QTableWidget>

using std::vector;
using namespace::std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    void show_array(QLineEdit *line,int array[],int size);
    void printArray(QTableWidget *tablecopy,vector <vector <int>> originalTable);

public slots:
    void task1();
    void task2();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
