#include "a_mainwindow.h"
#include "ui_a_mainwindow.h"
#define NAME 0
#define ID 1
book* book_head2;
user* user_head2;
user* search_user_result=user_head2;
user* search_user_result1=user_head2;
 bool is_all=0;
A_MainWindow::A_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::A_MainWindow)
{
    ui->setupUi(this);
    book_head2=book_head2->load_books();
    user_head2=user_head2->load_user();

    ui->adm->setCurrentIndex(0);
    QString valuestr=QString::fromStdString(user_head2->next->get_id());
    ui->tst1->setText(valuestr);
    QString valuestr1=QString::fromStdString(book_head2->next->getname());
    ui->tst2->setText(valuestr1);

}

A_MainWindow::~A_MainWindow()
{
    delete ui;
    //固定窗口大小
    this->setMaximumSize(822,583);
    this->setMinimumSize(822,583);

    //设置窗口标题
    this->setWindowTitle("给辛苦的管理员揉揉肩");
}

void A_MainWindow::on_b_add_clicked()
{
    ui->adm->setCurrentIndex(1);
    //this->btnsetfalse();
}

void A_MainWindow::on_b_delete_clicked()
{
    ui->adm->setCurrentIndex(2);
    //this->btnsetfalse();
}

void A_MainWindow::on_u_add_clicked()
{
    ui->adm->setCurrentIndex(3);
   // this->btnsetfalse();
}

void A_MainWindow::on_u_delete_clicked()
{
    ui->adm->setCurrentIndex(4);
   // this->btnsetfalse();
}

void A_MainWindow::on_u_find_clicked()
{
   ui->adm->setCurrentIndex(5);
   ui->u_findlineEdit->clear();
   hide_findu();
}
void A_MainWindow::on_find_butn_clicked()
{
    if(!this->judgeEmpty())
    {
        return;
    }

    QString getname=ui->u_findlineEdit->text();
    string username=getname.toStdString();


    search_user_result=search_user_result->search_user(user_head2, username,NAME);

    //无重名

        if(search_user_result==NULL)
        {
           QMessageBox::warning(this,"出错啦","蠢蠢的管理员，这个人还没有注册呢");
           ui->u_findlineEdit->clear();
           ui->booklist->clear();
           return;
        }
       else if(search_user_result==search_user_result->next->next){
            book* borro_bookptr=search_user_result->book_login();//载入借阅的书籍信息;
            ui->samename->setEnabled(false);
            if(search_user_result->get_type()!=-1)
            {
                QString checkname=QString::fromStdString(search_user_result->getname());
                ui->dana_label->setText(checkname);
                if(search_user_result->get_type())   ui->daty_label->setText("学生");
                else   ui->daty_label->setText("教师");
                QString checkid=QString::fromStdString(search_user_result->get_id());
                ui->daid_label->setText(checkid);
                QString checkcre=QString::number ( search_user_result->get_credit() , 10 );
                ui->dacre_label->setText(checkcre);
                QString checkac=QString::fromStdString(search_user_result->get_academy());
                ui->daac_label->setText(checkac);
                QString checkpass=QString::fromStdString(search_user_result->get_password());
                ui->dapas_label->setText(checkpass);
                QString checkau=QString::number( search_user_result->get_permission() , 10 );
                ui->daau_label->setText(checkau);
                QString checkpay=QString::number(search_user_result->get_debt() , 10, 2 );
                ui->dapay_label->setText(checkpay);
                //tst
               // QString info =QString::fromStdString(borro_bookptr->getname());
               // ui->borrowlabel->setText( info);
                QString info,info0,info1,info2,info3;
                book* temp=borro_bookptr;
                for(;temp!=NULL ;){
                    info0 = QString::fromStdString(temp->getid());
                    info1 = QString::fromStdString(temp->getname());
                    info2 = QString::fromStdString(temp->getauthor());
                    info3 = QString::fromStdString(temp->getISBN());
                    info =info0+" "+info1+" "+ info2+" "+ info3+" ";
                    ui->booklist->addItem ( info );
                    temp=temp->next;
                }
                show_findu();

            }

 /*           user * nex=search_user_result;
            while(nex!=NULL){
                search_user_result=nex;
                nex=search_user_result->next;
                delete search_user_result;
                search_user_result=NULL;
            }
            book*  b_nex = borro_bookptr;
             while(b_nex!=NULL){
                 borro_bookptr=b_nex;
                 b_nex=borro_bookptr->next;
                 delete borro_bookptr;
                 borro_bookptr=NULL;
             }*/
            return;

        }
    else{
         ui->samename->setEnabled(true);
         QString checkname=QString::fromStdString(search_user_result->getname());
         ui->dana_label->setText(checkname);
         if(search_user_result->get_type())   ui->daty_label->setText("学生");
         else   ui->daty_label->setText("教师");
         QString checkid=QString::fromStdString(search_user_result->get_id());
         ui->daid_label->setText(checkid);
         QString checkcre=QString::number ( search_user_result->get_credit() , 10 );
         ui->dacre_label->setText(checkcre);
         QString checkac=QString::fromStdString(search_user_result->get_academy());
         ui->daac_label->setText(checkac);
         QString checkpass=QString::fromStdString(search_user_result->get_password());
         ui->dapas_label->setText(checkpass);
         QString checkau=QString::number( search_user_result->get_permission() , 10 );
         ui->daau_label->setText(checkau);
         QString checkpay=QString::number(search_user_result->get_debt() , 10, 2);
         ui->dapay_label->setText(checkpay);
        book* borro_bookptr=search_user_result->book_login();//载入借阅的书籍信息;
        QString info,info0,info1,info2,info3;
        book* temp=borro_bookptr;
        for(;temp!=NULL ;){
            info0 = QString::fromStdString(temp->getid());
            info1 = QString::fromStdString(temp->getname());
            info2 = QString::fromStdString(temp->getauthor());
            info3 = QString::fromStdString(temp->getISBN());
            info =info0+" "+info1+" "+ info2+" "+ info3+" ";
            ui->booklist->addItem ( info );
            temp=temp->next;
        }
         show_findu();

    }

}

bool A_MainWindow::judgeEmpty()
{
    if(ui->u_findlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"好笨啊","瓜怂，你不填我咋知道你要找谁");
        return false;
    }
    else
        return true;
}

void A_MainWindow::clearAll()
{
    ui->u_findlineEdit->clear();
}

void A_MainWindow::hide_findu(){
    ui->daac_label->hide();
    ui->stac_label->hide();
    ui->stn_label->hide();
    ui->stau_label->hide();
    ui->stcre_label->hide();
    ui->stpay_label->hide();
    ui->stpas_label->hide();
    ui->stid_label->hide();
    ui->sty_label->hide();
    ui->dana_label->hide();
    ui->daau_label->hide();
    ui->dacre_label->hide();
    ui->dapay_label->hide();
    ui->dapas_label->hide();
    ui->daid_label->hide();
    ui->daty_label->hide();
    ui->borrowlabel->hide();
    //ui->borrbooks->hide();
     ui->samename->hide();
     ui->booklist->hide();
}
void A_MainWindow::show_findu(){
    ui->daac_label->show();
    ui->stac_label->show();
    ui->stn_label->show();
    ui->stau_label->show();
    ui->stcre_label->show();
    ui->stpay_label->show();
    ui->stpas_label->show();
    ui->stid_label->show();
    ui->sty_label->show();
    ui->dana_label->show();
    ui->daau_label->show();
    ui->dacre_label->show();
    ui->dapay_label->show();
    ui->dapas_label->show();
    ui->daid_label->show();
    ui->daty_label->show();
    ui->borrowlabel->show();
    //ui->borrbooks->show();
     ui->samename->show();
     ui->booklist->show();
}

void A_MainWindow::on_samename_clicked()
{
    looksamename* looksame=new looksamename;
    looksame->show();
    connect(this, SIGNAL(send_users(user*)), looksame, SLOT(rece_uhead(user*)));
   emit(send_users(search_user_result));

}


void A_MainWindow::on_handon_clicked()
{

    if(!this->judgeEmpty_newu())
    {
        return;
    }

    QString getid=ui->inputIDlineEdit->text();
    QString getname=ui->inputnamelineEdit->text();
    QString getac=ui->inputacdlineEdit->text();
    string u_id,u_name,u_ac;
    int type;
    if(ui->teach_choose->isChecked()) type=0;
    if(ui->stu_choose->isChecked())type=1;
    u_id=getid.toStdString();
    u_name=getname.toStdString();
    u_ac=getac.toStdString();

    user u;
    int i=u.new_user(user_head2, u_id, u_name,u_ac,type);
    if (i==1){
         QMessageBox::warning(this,"笨蛋","这个用户已经注册了");
         clear_newu();
    }

    else{
        QMessageBox::warning(this,"yeah!","添加成功！要管理员抱抱，人家累死啦～");
        clear_newu();
    }


}
void A_MainWindow::clear_newu(){
       ui->inputIDlineEdit->clear();
       ui->inputnamelineEdit->clear();
       ui->inputacdlineEdit->clear();
}

bool A_MainWindow::judgeEmpty_newu()
{
    if(ui->inputIDlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"笨蛋","ID没填");
        return false;
    }
    if(ui->inputnamelineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"笨蛋","姓名没填");
        return false;
    }
    if(ui->inputacdlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"笨蛋","学院没填");
        return false;
    }
    if(!ui->teach_choose->isChecked() && !ui->stu_choose->isChecked())
    {
        QMessageBox::warning(this,"笨蛋","是老师还是学生没填");
        return false;
    }
    else
        return true;
}

void A_MainWindow::on_del_butn_clicked()
{
    ui->delete_list->clear();
    QString s = ui->delete_find->text();
    string str=s.toStdString();
   switch (ui->del_con->currentIndex()){
   case 0:
       search_user_result1=search_user_result1->search_user(user_head2, str, NAME);
       break;
   case 1:
       search_user_result1=search_user_result1->search_user(user_head2, str, ID);
       break;
   }

   if(search_user_result1!=NULL){
       QString info,info0,info1,info2,info3,info4,info5,info6,info7,info2_0;
       user* temp=search_user_result1;
       for(;search_user_result1!=temp->next ;)
       {
           info0 = QString::fromStdString(temp->get_id());
           info1 = QString::fromStdString(temp->getname());
           if(temp->get_type()==1)
           {
               info2="学生";
               info2_0="学   号： ";
           }
           else
           {
               info2="教师";
               info2_0="工作号： ";
           }
           info3 = QString::fromStdString(temp->get_academy());
           info4 = QString::number(temp->get_credit(),10);
           info5 = QString::number(temp->get_permission(),10);
           info6 = QString::number(temp->get_debt(),10,2);
           info7 = QString::fromStdString(temp->get_password());
           info =info2_0+info0+"  姓名： "+info1+"  类型：  "+ info2+"  学院： "+ info3+"  信用： "+info4+"  权限： "+info5+"  欠款： "+info6+"  密码： "+info7;
           ui->delete_list->addItem ( info );
           temp=temp->next;
       }
   }
   else
   {
       QMessageBox::warning(this,"笨蛋","没有蠢蠢滴管理员要删的用户");
   }


}

void A_MainWindow::on_delete_list_clicked(const QModelIndex &index)
{
   int i= ui->delete_list->currentRow ();

   QMessageBox megBox;
   megBox.addButton("少罗嗦，就要删",QMessageBox::AcceptRole);
   megBox.addButton("呃……不删了不删了",QMessageBox::RejectRole);
   megBox.setText("嘤嘤嘤，管理员咱们的用户本来就少还要删掉这个可怜的孩纸吗～");
   if(search_user_result1->next->next==search_user_result1) ui->delall_butn->setEnabled(false);
   else
   {
       ui->delall_butn->setEnabled(true);
   }

   if(megBox.exec() ==QMessageBox:: AcceptRole)
   {
       int j=0;
       user* temp=search_user_result1;
       while(j!=i && temp->next!=search_user_result1)
       {
           j++;
           temp=temp->next;
       }
       user u;
       u.delete_user(user_head2, temp,0);
       ui->delete_list->takeItem(ui->delete_list->currentRow());
   }


}



void A_MainWindow::on_delall_butn_clicked()
{
    QMessageBox megBox;
    megBox.addButton("凶你咋滴，删！",QMessageBox::AcceptRole);
    megBox.addButton("不怕不怕啊…不删了",QMessageBox::RejectRole);
    megBox.setText("嘤嘤嘤，居然要全删掉，哇哇哇你太凶了，本系统怕怕的");
    if(megBox.exec() ==QMessageBox:: AcceptRole) is_all=1;
    else is_all=0;
    user* temp=search_user_result1;
    int j=1;
    while( temp->next!=search_user_result1)
    {
        j++;
        temp=temp->next;
    }
    user u;
    u.delete_user(user_head2, search_user_result1, is_all);
    for(int i=0; i<=j; i++)
    {
        ui->delete_list->takeItem(i);
    }

}

void A_MainWindow::on_pushButton_clicked()
{
    QString info,info0,info1,info2,info3,info4,info5,info6,info7,info8;
    info0 = ui->bnamelineEdit->text();
    string name=info0.toStdString();
    info1 = ui->bauthlineEdit->text();
    string auth =info1.toStdString();
    info2 = ui->btypelineEdit->text();
    string type=info2.toStdString();
    info3 = ui->bcrelineEdit->text();
    int cre=info3.toInt();
    info4 = ui->bpricelineEdit->text();
    float price=info4.toFloat();
    info5 = ui->bnumberlineEdit->text();
    int number=info5.toInt();
    info6 = ui->bpubliclineEdit->text();
    string publican=info6.toStdString();
    info7 = ui->bisbnlineEdit->text();
    string isbn=info7.toStdString();
    info8 = ui->intro_Edit->toPlainText();
    string intro=info8.toStdString();

    book *cur_book = book_head2;
     cur_book=cur_book->add_books( book_head2, name, auth, publican , price, type, isbn , cre ,intro,number);

     if(cur_book!=NULL){
         QString id=QString::fromStdString(cur_book->getid());
      QMessageBox::warning(this,"笨蛋",id);
         //megBox.addButton("摸摸头，辛苦了",QMessageBox::AcceptRole);
         //megBox.addButton("呃……不删了不删了",QMessageBox::RejectRole);

     }

}
