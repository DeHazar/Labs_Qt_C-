#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTabWidget *central;
    QLineEdit *aTab;
    QLineEdit *bTab;

    QPushButton *button;
    QLineEdit *resultN;
    QLineEdit *resultEPS;
    QLineEdit *n;
    QLineEdit *n_value;
    QLineEdit *eps;
    QLineEdit *nEps;
     QLineEdit *K;

    QPushButton *button2;
    QLineEdit *result;

    void draw_window();
    void draw_window1();
    void draw_window2();
    void draw_window3();

public slots:
    void calculate_for_N();
    void calcute_for_EPS();
    void findNumbers();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
