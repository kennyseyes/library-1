#include "login_user_dialog.h"
#include "ui_login_user_dialog.h"
book * book_head=NULL;
user* user_head=NULL;


login_user_dialog::login_user_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login_user_dialog)
{
    book_head=book_head->load_books();
    user_head=user_head->load_user();//载入用户
    ui->setupUi(this);
    ui->login_Button->setEnabled(false);

    //测试
    QString valuestr=QString::fromStdString(user_head->next->get_id());
    ui->id_label->setText(valuestr);

    //设置lineedit提示语句
    ui->uname_lineEdit->setPlaceholderText("请输入用户名");
    ui->pasw_lineEdit->setPlaceholderText("请输入密码");

    //登陆按钮可用
    connect(ui->uname_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(login_ButtonSetSlot(QString)));
    connect(ui->pasw_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(login_ButtonSetSlot(QString)));

}

login_user_dialog::~login_user_dialog()
{
    delete ui;
}

void login_user_dialog::on_login_Button_clicked()
{
    if(!this->judgeEmpty())
    {
        ui->pasw_lineEdit->clear();
        return;
    }

    QString input_password=ui->pasw_lineEdit->text();
    QString input_username=ui->uname_lineEdit->text();


    string id;
    string password=input_password.toStdString();
    string username=input_username.toStdString();

    user* temp=user_head->next;

    id=temp->get_id();
    int success_id=0;
    while( temp!=NULL )
    {
        if(username!=id)
        {
            if(temp->next!=NULL)
            {
                temp=temp->next;
                id=temp->get_id();
            }
            else
            {
                temp=temp->next;
            }
        }
       else
        {
            success_id=1;
            break;
        }
    }
    if(temp==NULL)//没有这个人
    {
        success_id=0;
        QMessageBox::warning(this,"提示","用户不存在,请注册",QMessageBox::Yes);
        this->clearAll();
        return;
    }
    if(success_id==1 && password.compare(temp->get_password())!=0)
    {
        QMessageBox::information(this,"提示","密码输入有误",QMessageBox::Yes);
        this->clearAll();
        return;
    }

    else if(success_id==1 && password.compare(temp->get_password())==0){

        user* client=temp;
        client->book_login();
        QString str1="登录成功";
        QString str2= QString::fromStdString(temp->getname());
        QString str3="欢迎使用美少女的图书管理系统";
        QMessageBox::information(this,"提示",str3+str2+"\n"+str1,QMessageBox::Yes);
        this->clearAll();
        u_MainWindow  *user_mainwindow=new u_MainWindow;
        user_mainwindow->show();


        connect(this,SIGNAL(send_bookhead(book *)),user_mainwindow,SLOT(rece_bookhead(book *)));
        // dlg->setModal(true); 不论是模态或者非模态都可以正常传值
        emit(send_bookhead(book_head));
        connect(this,SIGNAL(send_userhead(user *)),user_mainwindow,SLOT(rece_userhead(user *)));
        emit(send_userhead(user_head));
        connect(this,SIGNAL(send_curuser(user *)),user_mainwindow,SLOT(rece_curuser(user *)));
        emit(send_curuser(client));
        this->hide();



        return;
    }
}

void login_user_dialog::on_return_Button_clicked()
{
     accept();
}

void login_user_dialog::clearAll()
{
    ui->uname_lineEdit->clear();
    ui->pasw_lineEdit->clear();
}

void login_user_dialog::login_ButtonSetSlot(QString)
{ 
    ui->login_Button->setEnabled(true);
}

bool login_user_dialog::judgeEmpty()
{
    if(ui->pasw_lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","密码不能为空");
        return false;
    }
    if(ui->uname_lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户名不能为空");
        return false;
    }
    else
        return true;
}

