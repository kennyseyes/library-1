#include "u_mainwindow.h"
#include "ui_u_mainwindow.h"
#include "login_user_dialog.h"
#include "book.h"
#include "user.h"
#include "showbookfound.h"
#include <QMessageBox>
#include <sstream>
book* book_head1;
user* user_head1;
user* client;
book* returnlist;
book* selected;//pointer used to check book info and borrow

u_MainWindow::u_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::u_MainWindow)
{
    ui->setupUi(this);
    ui->searchbook->hide();
    ui->returnbook->hide();
    ui->clientinfo->hide();
    ui->payback->hide();
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

    connect(this,SIGNAL(send_bookhead(book *)),form,SLOT(rece_bookhead(book *)));
    // dlg->setModal(true); ������ģ̬���߷�ģ̬������������ֵ
    emit(send_bookhead(book_head1));
    connect(this,SIGNAL(send_userhead(user *)),form,SLOT(rece_userhead(user *)));
    emit(send_userhead(user_head1));
    connect(this,SIGNAL(send_curuser(user *)),form,SLOT(rece_curuser(user *)));
    emit(send_curuser(client));


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

    connect(this,SIGNAL(send_curuser(user *)),changepw,SLOT(rece_curuser(user *)));
    emit(send_curuser(client));
}







void u_MainWindow::on_return_2_clicked()
{
    ui->showbook->clear();
    ui->returnbook->show();
    ui->searchbook->hide();
    ui->clientinfo->hide();
    ui->payback->hide();

    //returnlist=client->book_login();
    returnlist=client->getbookborrowed();
    book* temp=returnlist->next;
    while (temp!=NULL)
    {
        string str=temp->getname();
        QString qstr = QString::fromStdString(str);
        ui->showbook->addItem(qstr);
        temp=temp->next;
    }

}

void u_MainWindow::on_search_clicked()
{
    ui->searchbook->show();
    ui->returnbook->hide();
    ui->clientinfo->hide();
    ui->payback->hide();


}

void u_MainWindow::on_debt_clicked()
{
    ui->payback->show();
    ui->returnbook->hide();
    ui->searchbook->hide();
    ui->clientinfo->hide();

    QString str1="�黹Ƿ��";
    string str2;
    stringstream ss;
    ss<<client->get_debt();
    ss>>str2;
    QString qstr = QString::fromStdString(str2);
    QString str3="��������Ҫ�黹��Ƿ�����";

    ui->label_10->setText(str1+qstr+str3);
}

void u_MainWindow::on_permission_clicked()
{
    ui->infowig->clear();
    ui->clientinfo->show();
    ui->returnbook->hide();
    ui->searchbook->hide();
    ui->payback->hide();

    stringstream ss;
    string type,permission,book_num,book_hand,expire_num,debt,credit;
    ss<<client->get_type();ss>>type;ss.clear();
    ss<<client->get_permission() ;ss>>permission;ss.clear();
    ss<<client->getnumber() ;ss>>book_num;ss.clear();
    ss<<client->get_bookhand();ss>>book_hand;ss.clear();
    ss<<client->get_expirenum();ss>>expire_num;ss.clear();
    ss<<client->get_debt();ss>>debt;ss.clear();
    ss<<client->getcredit();ss>>credit;ss.clear();

    QString _name=QString::fromStdString(client->getname());//����
    QString _id=QString::fromStdString(client->get_id());//ѧ��/����֤
    QString _usertype=QString::fromStdString(type);//��ʦ0ѧ��1
    QString _academy=QString::fromStdString(client->get_academy());//ѧԺ
    QString _book_number=QString::fromStdString(book_num);//����������
    QString _permission=QString::fromStdString(permission);//����Ȩ�ޣ�С��
    QString _debt=QString::fromStdString(debt);//Ƿ��
    QString _books_hand=QString::fromStdString(book_hand);//�����е�������
    QString _expire_num=QString::fromStdString(expire_num);//������Ŀ����
    QString _credit=QString::fromStdString(credit);//�û����ö�

    ui->infowig->addItem("��ӭ��������Ůͼ��� ");
    ui->infowig->addItem("����:"+_name);
    ui->infowig->addItem("�û����:"+_usertype);
    ui->infowig->addItem("ѧԺ:"+_academy);
    ui->infowig->addItem("����������:"+_book_number);
    ui->infowig->addItem("����Ȩ��:"+_permission);
    ui->infowig->addItem("Ƿ��:"+_debt);
    ui->infowig->addItem("�����е�������:"+_books_hand);
    ui->infowig->addItem("������Ŀ����:"+_expire_num);
    ui->infowig->addItem("�û����ö�:"+_credit);

}



void u_MainWindow::on_search_2_clicked()
{

    ui->showresult->clear();


    QString _id=ui->id->text();
    QString _name=ui->name->text();
    QString _isbn=ui->isbn->text();
    QString _type=ui->type->text();
    QString _author=ui->author->text();
    QString _publish=ui->publish->text();
    string id = _id.toStdString();
    string name = _name.toStdString();
    string isbn =_isbn.toStdString();
    string type = _type.toStdString();
    string author = _author.toStdString();
    string publish = _publish.toStdString();

    returnlist=new book;//��ͷ���
    book* connect=returnlist;
    book* temp=book_head1;
    bool found=0;


    string getname,getauthor,getpub;
    while (found==0)
    {
        temp=book_head1->next;
        while(temp!=NULL)
        {
            getname=temp->getname();
            getauthor=temp->getauthor();
            getpub=temp->getpublish();
            if( temp->getid()==id || temp->getISBN()==isbn || (!(ui->name->text().isEmpty()) && (getname.find(name)!=-1)) ||
                    (!(ui->author->text().isEmpty()) && (getauthor.find(author)!=-1)) || temp->gettype()==type ||
                    ( !(ui->publish->text().isEmpty()) && (getpub.find(publish)!=-1) ))

            //��������һ��ͼ�������
            {
                book* copybook=new book;
                copybook->copybook(temp);
                connect->next=copybook;
                connect=connect->next;
            }
            temp=temp->next;
        }
        if(returnlist->next!=NULL)
        {
            temp=returnlist->next;
            while(temp!=NULL)
            {
                string str=temp->getname();
                QString qstr = QString::fromStdString(str);
                ui->showresult->addItem(qstr);
                temp=temp->next;
            }
            found=1;
        }

        else
        {
            QMessageBox::about(this,"nothing was found", "δ�ҵ��������");
            break;
        }


    }
   /* book* pre=returnlist;
    book* tpr=returnlist->next;
    while(tpr!=NULL)
    {
        delete pre;
        pre=tpr;
        tpr=tpr->next;
    }*/
}

void u_MainWindow::on_pushButton_clicked()
{

}

void u_MainWindow::on_showresult_itemDoubleClicked(QListWidgetItem *item)
{
    ui->info->clear();
    int i=ui->showresult->currentRow();
    book* ptr=returnlist;
    for(int j=0;j<i;j++)//use pointer to search for book selected in current returnlist
        ptr=ptr->next;
    selected=ptr->next;

    stringstream ss;
    string _all_number,_avil_number,_price,_authority;
    ss<<selected->getall_number();ss>>_all_number;ss.clear();
    ss<<selected->getavil_number();ss>>_avil_number;ss.clear();
    ss<<selected->getprice();ss>>_price;ss.clear();
    ss<<selected->getauth();ss>>_authority;ss.clear();

    QString name=QString::fromStdString(selected->getname());
    QString id=QString::fromStdString(selected->getid());
    QString author=QString::fromStdString(selected->getauthor());
    QString publish=QString::fromStdString(selected->getpublish());
    QString intro=QString::fromStdString(selected->getintro());
    QString in_time=QString::fromStdString(selected->getin_time());
    QString all_number=QString::fromStdString(_all_number);
    QString avil_number=QString::fromStdString(_avil_number);
    QString price=QString::fromStdString(_price);
    QString type=QString::fromStdString(selected->gettype());
    QString authority=QString::fromStdString(_authority);
    QString isbn=QString::fromStdString(selected->getISBN());

    ui->info->insertPlainText("title:"+name+"\n");
    ui->info->insertPlainText("author:"+author+"\n");
    ui->info->insertPlainText("id:"+id+"\n");
    ui->info->insertPlainText("isbn:"+isbn+"\n");
    ui->info->insertPlainText("type:"+type+"\n");
    ui->info->insertPlainText("all_numbe:"+all_number+"\n");
    ui->info->insertPlainText("avil_numbe:"+avil_number+"\n");
    ui->info->insertPlainText("publish:"+publish+"\n");
    ui->info->insertPlainText("in_time:"+in_time+"\n");
    ui->info->insertPlainText("price:"+price+"\n");
    ui->info->insertPlainText("authority:"+authority+"\n");
    ui->info->insertPlainText("intro:"+intro+"\n");
}

void u_MainWindow::on_borrow_clicked()
{
    int i;
    QString name=QString::fromStdString(selected->getname());
    if(QMessageBox::Yes==QMessageBox::question(this,"BORROW BOOK","Do you want to borrow"+name+"?",QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
    {
        i=client->book_borrow(selected);
        if(i==1){//�ɹ�����
            QMessageBox::about(this,"congrats!","book borrowed!");
            selected->set_avil_num(selected->getavil_number()-1);
            client->save_book_borrowed(selected);//����д���ļ�
            selected->state_and_avil_change(selected->getavil_number(),selected->getid());
        }
        else if(i==2)
            QMessageBox::about(this,"oops!", "��Ǹ���������Ͻ�������������������������ˮƽ��");
        else if(i==3)
        {
            QMessageBox::StandardButton reply = QMessageBox::question(this,"oops!","��Ǹ�����޿�档�Ƿ�ԤԼ��", QMessageBox::Yes | QMessageBox::No);
            if(reply==QMessageBox::Yes)
            {
                client->order_book(selected);
            }
            else{}
        }
    }
}

void u_MainWindow::on_return_3_clicked()
{
    int i=ui->showbook->currentRow();
    book* temp=returnlist;
    for(int j=0;j<=i;j++)
        temp=temp->next;
    QString str1="return";
    QString str2=QString::fromStdString( temp->getname());
    QString str3=" ?";
    QMessageBox::StandardButton reply =QMessageBox::information(this,"confirm",str1+str2+str3, QMessageBox::Yes |QMessageBox::No);
    if(reply==QMessageBox::Yes)
    {
         client->book_return(i);
         QMessageBox::about(this,"","book returned");

         client->save_book_return(temp->getid());
         ui->showbook->clear();
         returnlist=client->getbookborrowed();
         book* temp=returnlist->next;
         while (temp!=NULL)
         {
             string str=temp->getname();
             QString qstr = QString::fromStdString(str);
             ui->showbook->addItem(qstr);
             temp=temp->next;
         }
    }
    else
    {
        ui->showbook->clear();
        returnlist=client->getbookborrowed();
        book* temp=returnlist->next;
        while (temp!=NULL)
        {
            string str=temp->getname();
            QString qstr = QString::fromStdString(str);
            ui->showbook->addItem(qstr);
            temp=temp->next;
        }
    }


}

void u_MainWindow::on_pay_clicked()
{
    stringstream ss;
    string s=ui->debt_2->text().toStdString();
    double money_to_pay;
    ss<<s;ss>>money_to_pay;
    if(money_to_pay<=client->get_debt())
    {
        client->setdebt(client->get_debt()-money_to_pay);
        QString str1="";//"���ѳɹ�����";
        QString str2="Ԫ��";
        QString str3=QString::fromStdString(s);
        QMessageBox::about(this,"",str1+str3+str2);

        QString str11="�黹Ƿ��";
        string str21;
        stringstream ss;
        ss<<client->get_debt();
        ss>>str21;
        QString qstr = QString::fromStdString(str21);
        QString str31="��������Ҫ�黹��Ƿ�����";

        ui->label_10->setText(str11+qstr+str31);
    }
    else{
        QMessageBox::about(this,"","лл���Ŀ������ң��������ǲ���Ҫ����������������Ƿ���");
    }
}
