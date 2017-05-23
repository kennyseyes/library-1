#include "u_mainwindow.h"
#include "ui_u_mainwindow.h"
book* book_head1;
user* user_head1;
user* client;
u_MainWindow::u_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::u_MainWindow)
{
    ui->setupUi(this);

}

u_MainWindow::~u_MainWindow()
{
    delete ui;
}
\
void u_MainWindow::on_form_in_clicked()
{
    form=new borrow_book_form;
    form->show();
}

void u_MainWindow::rece_bookhead(book*bh){
    book_head1=bh;
}

void u_MainWindow:: rece_userhead(user* uh){
    user_head1=uh;
}

void u_MainWindow::rece_curuser(user* cu){
    client=cu;
    QString cur_name=QString::fromStdString(client->getname());
    cur_name="hi,"+cur_name;
    ui->title->setText(cur_name);
}
/*
void u_MainWindow::on_exit_clicked()
{
    accept();
}
*/
void u_MainWindow::on_changepw_clicked()
{
    changepw=new change_password;
    changepw->show();
}

