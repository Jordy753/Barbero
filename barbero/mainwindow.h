#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>

#include"librerias.h"
#include"barbero.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int *a1;
    int *a2;
    int *a3;
    vector<Cliente*> silla;
    vector<Cliente*> sofa;
    vector<Cliente*> espera;

    //Barbero *bar1=new Barbero();
    //Barbero *bar2=new Barbero();
    Cliente *c1=new Cliente(1,&silla,&sofa,&espera,a1,a2,a3,this);
    vector<Cliente> cs;

};
#endif // MAINWINDOW_H
