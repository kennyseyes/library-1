#include "borrow_book_form.h"
#include "ui_borrow_book_form.h"

borrow_book_form::borrow_book_form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrow_book_form)
{
    ui->setupUi(this);
}

borrow_book_form::~borrow_book_form()
{
    delete ui;
}

void borrow_book_form::on_pushButton_2_clicked()
{
    this->close();
}
