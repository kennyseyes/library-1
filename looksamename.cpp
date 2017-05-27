#include "looksamename.h"
#include "ui_looksamename.h"
user* users_h;
looksamename::looksamename(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::looksamename)
{
    ui->setupUi(this);
}

looksamename::~looksamename()
{
    delete ui;

}

void looksamename::rece_uhead(user*uh){
   users_h=uh;
   QString info,info0,info1,info2,info3;
   user*u_temp=users_h;
   while(u_temp->next!=users_h){
       info0 = QString::fromStdString(u_temp->get_id());
       info1 = QString::fromStdString(u_temp->getname());
       if(u_temp->get_type()) info2 ="学生";
       else info2 ="教师";
       info3 = QString::number(u_temp->get_credit(), 10);
       info ="工作号／学号："+info0+"   姓名："+info1+"    类型："+ info2+" 信用度："+ info3;
       ui->userlist->addItem ( info );
       u_temp=u_temp->next;
   }
   /*
   book* temp=borro_bookptr;
   for(;temp!=NULL ;temp=temp->next;){
       info0 = QString::fromStdString(temp->getid());
       info1 = QString::fromStdString(temp->getname());
       info2 = QString::fromStdString(temp->getauthor());
       info3 = QString::fromStdString(temp->getISBN());
       info =info0+" "+info1+" "+ info2+" "+ info3+" ";
       ui->booklist->addItem ( info );

   }
*/
}
