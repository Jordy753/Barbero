#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    *a1=0;
    *a2=0;
    *a3=0;

    connect(c1,&Cliente::insert_text,[&](QString n){ui->listWidget->addItem(n);});
    //connect(c1,&Cliente::tiem_esper,[&](double n){ui->desperdicio_p->setNum(n);});
    connect(c1,&Cliente::barra1, ui->s_barra, &QProgressBar::setValue);
    connect(c1,&Cliente::barra2, ui->so_barra, &QProgressBar::setValue);
    connect(c1,&Cliente::barra3, ui->sal_barra, &QProgressBar::setValue);

    //c1->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

