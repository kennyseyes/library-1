#include "showbookfound.h"
#include "ui_showbookfound.h"

showbookfound::showbookfound(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showbookfound)
{
    ui->setupUi(this);
}

showbookfound::~showbookfound()
{
    delete ui;
}
