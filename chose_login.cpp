#include "chose_login.h"
#include "ui_chose_login.h"

chose_login::chose_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chose_login)
{
    ui->setupUi(this);
    //设置登录对话框的标题
    this->setWindowTitle("登录");
    //设置登录对话框大小固定为399*252
    this->setMaximumSize(399,252);
    this->setMinimumSize(399,252);
    //设置调色板,用于设置titlelabel的颜色
    QPalette p;
    p.setColor(QPalette::WindowText,Qt::blue);
    ui->titlelabel->setPalette(p);

  }

chose_login::~chose_login()
{
    delete ui;
}

void chose_login::on_admin_button_clicked()
{
     admin_login.show();
     this->close();
     if(admin_login.exec() == QDialog::Accepted) this->show();
}


void chose_login::on_user_button_clicked()
{
   user_login.show();
    this->close();
   if(user_login.exec() == QDialog::Accepted) this->show();

}


