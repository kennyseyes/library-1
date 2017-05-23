#include "change_password.h"
#include "ui_change_password.h"

change_password::change_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_password)
{
    ui->setupUi(this);
}

change_password::~change_password()
{
    delete ui;
}

void change_password::on_pushButton_2_clicked()
{
    this->close();
}
