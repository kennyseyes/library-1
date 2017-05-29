#include "borrow_book_form.h"
#include "ui_borrow_book_form.h"
#include "u_mainwindow.h"
#include <QMessageBox>
book* book_head2;
user* user_head2;
user* client1;

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

void borrow_book_form::on_pushButton_clicked()
{
    if(ui->name->text().isEmpty() && ui->id->text().isEmpty())
        QMessageBox::about(this,"输入为空","输入不能为空");
    else
    {
        string name=ui->name->text().toStdString();
        string id=ui->id->text().toStdString();

        book* returnlist=new book;//带头结点
        book* temp=book_head2;
        bool found=0;

        while (found==0)
        {
            temp=book_head2->next;
            while(temp!=NULL)
            {
                if( temp->getid()==id )
                {
                    found=1;
                    QString str1="即将为您借阅";
                    QString str2=QString::fromStdString(temp->getname());
                    QString str3=",是否继续？";
                    QMessageBox::StandardButton reply = QMessageBox::information(this,"请确认您想要借阅的书籍",str1+str2+str3, QMessageBox::Yes |QMessageBox::No);
                    if(reply==QMessageBox::Yes)
                    {
                        client1->book_borrow(temp);
                        QMessageBox::about(this,"成功","借书成功！");
                        temp->set_avil_num(temp->getavil_number()-1);
                        temp->state_and_avil_change(temp->getavil_number(),temp->getid());
                        client1->save_book_borrowed(temp);

                        break;
                    }
                    else{}
                }
                temp=temp->next;
            }
            if(temp==NULL)
            {
                found=1;
                QMessageBox::about(this,"nothing was found", "未找到相符内容,请确认您的流水号输入是否正确或联系管理员。");
            }
        }
    }
}

void borrow_book_form::rece_bookhead(book*bh){
    book_head2=bh;
}

void borrow_book_form:: rece_userhead(user* uh){
    user_head2=uh;
}

void borrow_book_form::rece_curuser(user* cu){
    client1=cu;
    QString cur_name=QString::fromStdString(client1->getname());

}
