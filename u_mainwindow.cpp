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
    ui->reservebook->hide();
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
    ui->reservebook->hide();

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
    ui->reservebook->hide();
    ui->returnbook->hide();
    ui->clientinfo->hide();
    ui->payback->hide();

    ui->id->clear();ui->name->clear();ui->author->clear();
    ui->isbn->clear();ui->publish->clear();ui->type->clear();
    ui->showresult->clear();
    ui->info->clear();


}

void u_MainWindow::on_debt_clicked()
{
    ui->payback->show();
    ui->reservebook->hide();
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
    ui->reservebook->hide();

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
    ui->info->clear();
    book_head1=book_head1->load_books();//�����鼮��Ϣ


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
    if(ui->showresult->currentRow()>=0)
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
                selected->state_and_avil_change(selected->getavil_number(),selected->getid());//�����鵥״̬

                //����info�����е���Ϣ
                ui->info->clear();
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
            else if(i==2)
                QMessageBox::about(this,"oops!", "��Ǹ���������Ͻ�������������������������ˮƽ��");
            else if(i==3)
            {
                QMessageBox::StandardButton reply = QMessageBox::question(this,"oops!","��Ǹ�����޿�档�Ƿ�ԤԼ��", QMessageBox::Yes | QMessageBox::No);
                if(reply==QMessageBox::Yes)
                {
                    client->order_book(selected);
                    QMessageBox::about(this,"","ԤԼ�ɹ�����ǰ�������Ŷӡ�");
                }
                else{}
            }
        }
    }

}

void u_MainWindow::on_return_3_clicked()
{
    int i=ui->showbook->currentRow();//��ǰ��
    book* temp=returnlist;
    for(int j=0;j<=i;j++)
        temp=temp->next;
    QString str1="return";
    QString str2=QString::fromStdString( temp->getname());
    QString str3=" ?";
    QMessageBox::StandardButton reply =QMessageBox::information(this,"confirm",str1+str2+str3, QMessageBox::Yes |QMessageBox::No);
    if(reply==QMessageBox::Yes)
    {
        //���Ҫ�������Ƿ��¼�
        book* head=book_head1;
        while (head!=NULL)
        {
            if(head->getid()!=temp->getid())
                head=head->next;
        }
        if(head==NULL)
            QMessageBox::about(this,"","�����ѱ��¼ܣ�����ϵ����Ա��");
        else
        {
            client->book_return(i);
             QMessageBox::about(this,"","book returned");

             client->save_book_return(temp->getid());
             temp->set_avil_num(temp->getavil_number()+1);
             temp->state_and_avil_change(temp->getavil_number(),temp->getid());//�����鵥״̬
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

void u_MainWindow::on_exit_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"","ȷ��Ҫ�ǳ���",QMessageBox::Yes|QMessageBox::No);
    if(reply==QMessageBox::Yes)
    {
        client=NULL;
        //u_login=new login_user_dialog;
        //u_login->show();
        this->close();
    }

}

void u_MainWindow::on_reserve_clicked()
{
    ui->reservebook->show();
    ui->payback->hide();
    ui->returnbook->hide();
    ui->searchbook->hide();
    ui->clientinfo->hide();

    ui->showbookreserverd->clear();
    //���Ҹ��û�ԤԼ�����鼮
    fstream file;
    file.open("order_books.txt",ios::out|ios::in);
    string tmp,id_str,book_str,state_str;
    book* add=new book;//����ԤԼ����
    int length=0;

    while(!file.eof())
    {
        getline(file,tmp);//tmp����ǰ��������
        length+=tmp.length();
        int pos=0,second,first,third;

        first=tmp.find_first_of(' ',pos);//first=��һ���ո��λ��
        second=tmp.find_first_of(' ',first+1);//second=�ڶ����ո�λ��
        third=tmp.find_first_of(' ',second+1);//second=�ڶ����ո�λ��
        id_str=tmp.substr(first+1,8);
        book_str=tmp.substr(second+1,13);
        state_str=tmp.substr(third+1,1);

        if(id_str==client->get_id())//���idһ��
        {
            if(state_str=="1")//���Լ���Ȿ��
            {                 
                book* temp=new book;
                    temp->next=NULL;
                    book* head=book_head1;
                    book* searchptr=head;//searchptr������booklist�ж�Ӧ���飬Ҳ����Ҫ���Ƹ�temp����
                    while(searchptr!=NULL)
                    {
                        if(searchptr->getid()==book_str)//���idһ��
                        {
                            //�鿴�Ȿ���Ƿ�ɽ� avil>1??
                            if(searchptr->getavil_number()>0)
                            {
                                //ѯ�ʽ費�裬�裺��������������avil-1����Ԥ�������м�ȥ���޸��ļ���
                                //�����ˣ���ԤԼ�鼮��ԤԼ�����м�ȥ���޸��ļ���
                                QString str=QString::fromStdString(searchptr->getname());
                                QMessageBox::StandardButton reply=QMessageBox::question(this,"","��ԤԼ���鼮��"+str+"���Խ����ˣ��Ƿ���ģ�", QMessageBox::Yes|QMessageBox::No);
                                if(reply==QMessageBox::Yes)
                                {
                                    client->book_borrow(searchptr);
                                    searchptr->set_avil_num(searchptr->getavil_number()-1);
                                    file.seekg(length-1,ios::beg);///��״̬��Ϊ0
                                    file<<"0"<<endl;
                                    client->save_book_borrowed(searchptr);//����д���ļ�
                                    searchptr->state_and_avil_change(searchptr->getavil_number(),searchptr->getid());//�����鵥״̬
                                    break;
                                }
                                else
                                {
                                    file.seekg(length-1,ios::beg);///��״̬��Ϊ0
                                    file<<"0"<<endl;
                                    break;
                                }
                            }
                            else//Ԥ����黹û��
                            {
                                temp->copybook(searchptr);//��ʾԤԼ�鼮������
                                string str=temp->getname();
                                QString qstr = QString::fromStdString(str);
                                ui->showbookreserverd->addItem(qstr);
                                add->next=temp;
                                add=add->next;
                                break;
                            }

                        }
                        else
                            searchptr=searchptr->next;

                    }
             }
        }
        length+=2;
    }
    file.close();
}

void u_MainWindow::on_search_3_clicked()
{
    ui->showresult_2->clear();


    QString _id=ui->id_2->text();
    QString _name=ui->name_2->text();
    QString _isbn=ui->isbn_2->text();
    QString _type=ui->type_2->text();
    QString _author=ui->author_2->text();
    QString _publish=ui->publish_2->text();
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
            if( temp->getid()==id || temp->getISBN()==isbn || (!(ui->name_2->text().isEmpty()) && (getname.find(name)!=-1)) ||
                    (!(ui->author_2->text().isEmpty()) && (getauthor.find(author)!=-1)) || temp->gettype()==type ||
                    ( !(ui->publish_2->text().isEmpty()) && (getpub.find(publish)!=-1) ))

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
                ui->showresult_2->addItem(qstr);
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
}

void u_MainWindow::on_showresult_2_itemClicked(QListWidgetItem *item)
{
    ui->info_2->clear();
    int i=ui->showresult_2->currentRow();
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

    ui->info_2->insertPlainText("title:"+name+"\n");
    ui->info_2->insertPlainText("author:"+author+"\n");
    ui->info_2->insertPlainText("id:"+id+"\n");
    ui->info_2->insertPlainText("isbn:"+isbn+"\n");
    ui->info_2->insertPlainText("type:"+type+"\n");
    ui->info_2->insertPlainText("all_numbe:"+all_number+"\n");
    ui->info_2->insertPlainText("avil_numbe:"+avil_number+"\n");
    ui->info_2->insertPlainText("publish:"+publish+"\n");
    ui->info_2->insertPlainText("in_time:"+in_time+"\n");
    ui->info_2->insertPlainText("price:"+price+"\n");
    ui->info_2->insertPlainText("authority:"+authority+"\n");
    ui->info_2->insertPlainText("intro:"+intro+"\n");
}

void u_MainWindow::on_reserve_2_clicked()
{
    if(ui->showresult_2->currentRow()>=0)
    {
        QString name=QString::fromStdString(selected->getname());

        //���ǰ���м�����ԤԼ
        string tmp,id_str,book_str,state_str,num;
        int n=0;//ԤԼ����
        ifstream f;
        f.open("order_books.txt");
        while(!f.eof())
        {
            getline(f,tmp);
            int pos=0,second,first,third;

            first=tmp.find_first_of(' ',pos);//first=��һ���ո��λ��
            second=tmp.find_first_of(' ',first+1);//second=�ڶ����ո�λ��
            third=tmp.find_first_of(' ',second+1);//second=�ڶ����ո�λ��
            id_str=tmp.substr(first+1,8);
            book_str=tmp.substr(second+1,13);
            state_str=tmp.substr(third+1,1);

            if(book_str==selected->getid())//�����ˮ��һ��
            {
                if(state_str=="1")//���ԤԼ���Ȿ��
                    n++;
            }
        }
        f.close();
        stringstream ss;
        ss<<n;ss>>num;
        QString _num=QString::fromStdString(num);

        QMessageBox::StandardButton reply=QMessageBox::question(this,"","ҪԤԼ"+name+_num+"���Ŷӡ�",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes)
        {
            client->order_book(selected);

            //����ԤԼͼ��
            ui->showbookreserverd->clear();
            ifstream file;
            file.open("order_books.txt");
            string tmp,id_str,book_str,state_str;
            book* add=new book;//����ԤԼ����

            while(!file.eof())
            {
                getline(file,tmp);
                int pos=0,second,first,third;

                first=tmp.find_first_of(' ',pos);//first=��һ���ո��λ��
                second=tmp.find_first_of(' ',first+1);//second=�ڶ����ո�λ��
                third=tmp.find_first_of(' ',second+1);//second=�ڶ����ո�λ��
                id_str=tmp.substr(first+1,8);
                book_str=tmp.substr(second+1,13);
                state_str=tmp.substr(third+1,1);

                if(id_str==client->get_id())//���idһ��
                {
                    if(state_str=="1")//���Լ���Ȿ��
                    {
                            book* temp=new book;
                            temp->next=NULL;
                            book* head=book_head1;
                            book* searchptr=head;//searchptr������booklist�ж�Ӧ���飬Ҳ����Ҫ���Ƹ�temp����
                            while(searchptr!=NULL)
                            {
                                if(searchptr->getid()==book_str)//���idһ��
                                {
                                    temp->copybook(searchptr);
                                    string str=temp->getname();
                                    QString qstr = QString::fromStdString(str);
                                    ui->showbookreserverd->addItem(qstr);
                                    add->next=temp;
                                    add=add->next;
                                    break;
                                }
                                searchptr=searchptr->next;

                            }
                     }
                }
            }
            file.close();

            QMessageBox::about(this,"","ԤԼ�ɹ���");
        }
    }
    else{}


}

void u_MainWindow::on_cancel_clicked()//ȡ��ԤԼ
{    
    if(ui->showbookreserverd->currentRow()>=0)
    {
        int i=ui->showbookreserverd->currentRow();
        QString s=ui->showbookreserverd->item(i)->text();
        string str=s.toStdString();
        QMessageBox::StandardButton reply=( QMessageBox::question(this,"","ȷ��Ҫȡ��ԤԼ"+s+"��?", QMessageBox::Yes | QMessageBox::No));

        if(reply==QMessageBox::Yes)
        {
                
            //�ҵ�ѡ�е������ˮ��,tempָ���ҵ�����

            book* temp=book_head1;
            while(temp!=NULL)
            {
                if(temp->getname()==str)
                    break;
                temp=temp->next;
            }

            //��дorder_books.txt�ļ������Ա�Ϊ0
            fstream ifs;
                ifs.open("order_books.txt",ios_base::out|ios_base::in );
                string tmp,id_str,book_str,state_str;//tmp�����洢ÿһ�У�id_str���洢ÿһ�е��û���������ƥ��
                int success=0;
                int length=0;//ʹ��length�����Ӷ��ҵ�������ݵ�ָ��λ��

                while(!ifs.eof() && success==0)
                {
                    getline(ifs,tmp);
                    length+=tmp.length();


                    int pos=0,mark,n,third;
                    n=tmp.find_first_of(' ',pos);//n=��һ���ո��λ��
                    mark=tmp.find_first_of(' ',n+1);//mark=�ڶ����ո�λ��
                    third=tmp.find_first_of(' ',mark+1);//mark=�ڶ����ո�λ��

                    id_str=tmp.substr(n+1,8);
                    book_str=tmp.substr(mark+1,13);
                    state_str=tmp.substr(third+1,1);

                    if(id_str.compare(client->get_id())==0)//����û�id�ͼ�¼idһ��
                    {
                        if(book_str.compare(temp->getid())==0 && state_str.compare("1")==0)
                        {

                            ifs.seekg(length-1,ios::beg);///��״̬��Ϊ0
                            ifs<<"0"<<endl;
                            success=1;
                        }
                    }
                    length+=2;
                }
                ifs.close();

            //��������orderbooks.txt����showbookreserved����ʾ
                ui->showbookreserverd->clear();
                ifstream file;
                file.open("order_books.txt");

                book* add=new book;//����ԤԼ����

                while(!file.eof())
                {
                    getline(file,tmp);
                    int pos=0,second,first,third;

                    first=tmp.find_first_of(' ',pos);//first=��һ���ո��λ��
                    second=tmp.find_first_of(' ',first+1);//second=�ڶ����ո�λ��
                    third=tmp.find_first_of(' ',second+1);//second=�ڶ����ո�λ��
                    id_str=tmp.substr(first+1,8);
                    book_str=tmp.substr(second+1,13);
                    state_str=tmp.substr(third+1,1);

                    if(id_str==client->get_id())//���idһ��
                    {
                        if(state_str=="1")//���Լ���Ȿ��
                        {
                                book* temp=new book;
                                temp->next=NULL;
                                book* head=book_head1;
                                book* searchptr=head;//searchptr������booklist�ж�Ӧ���飬Ҳ����Ҫ���Ƹ�temp����
                                while(searchptr!=NULL)
                                {
                                    if(searchptr->getid()==book_str)//���idһ��
                                    {
                                        temp->copybook(searchptr);
                                        string str=temp->getname();
                                        QString qstr = QString::fromStdString(str);
                                        ui->showbookreserverd->addItem(qstr);
                                        add->next=temp;
                                        add=add->next;
                                        break;
                                    }
                                    searchptr=searchptr->next;

                                }
                         }
                    }
                }
                file.close();
            }
    }
    else{}
}


