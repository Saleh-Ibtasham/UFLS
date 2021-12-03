#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clusteringapproach.h"
#include "setcover.h"
#include "iterative.h"
#include <iostream>
#include <QDebug>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    close();
    clusteringApproach c; //= new clusteringApproach(this);
    c.setModal(true);
    c.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
    SetCover s;
    s.setModal(true);
    s.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    close();
    Iterative i;
    i.setModal(true);
    i.exec();
}
