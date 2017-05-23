#include "a_mainwindow.h"
#include "ui_a_mainwindow.h"

A_MainWindow::A_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::A_MainWindow)
{
    ui->setupUi(this);
}

A_MainWindow::~A_MainWindow()
{
    delete ui;
}

void A_MainWindow::on_b_add_clicked()
{

}

void A_MainWindow::on_b_delete_clicked()
{

}

void A_MainWindow::on_u_add_clicked()
{

}

void A_MainWindow::on_u_delete_clicked()
{

}

void A_MainWindow::on_u_find_clicked()
{

}


