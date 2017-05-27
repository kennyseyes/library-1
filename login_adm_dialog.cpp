#include "login_adm_dialog.h"
#include "ui_login_adm_dialog.h"
#include<QMessageBox>

login_adm_dialog::login_adm_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login_adm_dialog)
{
    ui->setupUi(this);

}

login_adm_dialog::~login_adm_dialog()
{
    delete ui;
}
 int i=3;
void login_adm_dialog::on_ok_Button_clicked()
{
    i--;
    QString input_password=ui->lineEdit->text();
    if(input_password==tr("1")) {
        admin_mainwindow.show();
        this->close();
    }
    else if(i>0){
        QString times= QString::number(i, 10);

        times="令牌错误请重试! 还有"+times;
        times=times+"次，抓紧啦！";
        clearAll();
        QMessageBox::warning(this,tr("错误"),
        times,
        QMessageBox::Yes);
    }

    else{
        QMessageBox megBox;
        megBox.addButton("老老实实去用户区",QMessageBox::AcceptRole);
        megBox.addButton("哼不玩了，再见",QMessageBox::RejectRole);
        megBox.setText("你根本不是萌萌的管理员!");

        if(megBox.exec() ==QMessageBox:: AcceptRole)
        {
                 accept();
        }
        else this->close();

    }
}

void login_adm_dialog::on_returnButton_clicked()
{
    accept();
}
void login_adm_dialog::clearAll()
{
    ui->lineEdit->clear();
}
