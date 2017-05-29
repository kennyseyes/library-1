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
    // dlg->setModal(true); 不论是模态或者非模态都可以正常传值
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

    QString str1="归还欠款";
    string str2;
    stringstream ss;
    ss<<client->get_debt();
    ss>>str2;
    QString qstr = QString::fromStdString(str2);
    QString str3="请输入您要归还的欠款数额：";

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

    QString _name=QString::fromStdString(client->getname());//姓名
    QString _id=QString::fromStdString(client->get_id());//学号/工作证
    QString _usertype=QString::fromStdString(type);//老师0学生1
    QString _academy=QString::fromStdString(client->get_academy());//学院
    QString _book_number=QString::fromStdString(book_num);//借书总数量
    QString _permission=QString::fromStdString(permission);//借阅权限，小数
    QString _debt=QString::fromStdString(debt);//欠款
    QString _books_hand=QString::fromStdString(book_hand);//在手中的书数量
    QString _expire_num=QString::fromStdString(expire_num);//过期书目数量
    QString _credit=QString::fromStdString(credit);//用户信用度

    ui->infowig->addItem("欢迎光临美少女图书馆 ");
    ui->infowig->addItem("姓名:"+_name);
    ui->infowig->addItem("用户类别:"+_usertype);
    ui->infowig->addItem("学院:"+_academy);
    ui->infowig->addItem("借书总数量:"+_book_number);
    ui->infowig->addItem("借阅权限:"+_permission);
    ui->infowig->addItem("欠款:"+_debt);
    ui->infowig->addItem("在手中的书数量:"+_books_hand);
    ui->infowig->addItem("过期书目数量:"+_expire_num);
    ui->infowig->addItem("用户信用度:"+_credit);

}



void u_MainWindow::on_search_2_clicked()
{

    ui->showresult->clear();
    ui->info->clear();
    book_head1=book_head1->load_books();//更新书籍信息


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

    returnlist=new book;//带头结点
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

            //符合任意一项就加入链表
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
            QMessageBox::about(this,"nothing was found", "未找到相符内容");
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
            if(i==1){//成功借书
                QMessageBox::about(this,"congrats!","book borrowed!");
                selected->set_avil_num(selected->getavil_number()-1);
                client->save_book_borrowed(selected);//借书写入文件
                selected->state_and_avil_change(selected->getavil_number(),selected->getid());//更改书单状态

                //更新info窗口中的信息
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
                QMessageBox::about(this,"oops!", "抱歉，您不符合借书条件，请继续提高您的姿势水平。");
            else if(i==3)
            {
                QMessageBox::StandardButton reply = QMessageBox::question(this,"oops!","抱歉，暂无库存。是否预约？", QMessageBox::Yes | QMessageBox::No);
                if(reply==QMessageBox::Yes)
                {
                    client->order_book(selected);
                    QMessageBox::about(this,"","预约成功！您前面有人排队。");
                }
                else{}
            }
        }
    }

}

void u_MainWindow::on_return_3_clicked()
{
    int i=ui->showbook->currentRow();//当前行
    book* temp=returnlist;
    for(int j=0;j<=i;j++)
        temp=temp->next;
    QString str1="return";
    QString str2=QString::fromStdString( temp->getname());
    QString str3=" ?";
    QMessageBox::StandardButton reply =QMessageBox::information(this,"confirm",str1+str2+str3, QMessageBox::Yes |QMessageBox::No);
    if(reply==QMessageBox::Yes)
    {
        //检查要换的书是否被下架
        book* head=book_head1;
        while (head!=NULL)
        {
            if(head->getid()!=temp->getid())
                head=head->next;
        }
        if(head==NULL)
            QMessageBox::about(this,"","此书已被下架，请联系管理员！");
        else
        {
            client->book_return(i);
             QMessageBox::about(this,"","book returned");

             client->save_book_return(temp->getid());
             temp->set_avil_num(temp->getavil_number()+1);
             temp->state_and_avil_change(temp->getavil_number(),temp->getid());//更改书单状态
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
        QString str1="";//"您已成功还款";
        QString str2="元。";
        QString str3=QString::fromStdString(s);
        QMessageBox::about(this,"",str1+str3+str2);

        QString str11="归还欠款";
        string str21;
        stringstream ss;
        ss<<client->get_debt();
        ss>>str21;
        QString qstr = QString::fromStdString(str21);
        QString str31="请输入您要归还的欠款数额：";

        ui->label_10->setText(str11+qstr+str31);
    }
    else{
        QMessageBox::about(this,"","谢谢您的慷慨解囊，但是我们不需要您的资助。（超出欠款金额）");
    }
}

void u_MainWindow::on_exit_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"","确定要登出吗？",QMessageBox::Yes|QMessageBox::No);
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
    //查找该用户预约过的书籍
    fstream file;
    file.open("order_books.txt",ios::out|ios::in);
    string tmp,id_str,book_str,state_str;
    book* add=new book;//返回预约链表
    int length=0;

    while(!file.eof())
    {
        getline(file,tmp);//tmp：当前操作的行
        length+=tmp.length();
        int pos=0,second,first,third;

        first=tmp.find_first_of(' ',pos);//first=第一个空格的位置
        second=tmp.find_first_of(' ',first+1);//second=第二个空格位置
        third=tmp.find_first_of(' ',second+1);//second=第二个空格位置
        id_str=tmp.substr(first+1,8);
        book_str=tmp.substr(second+1,13);
        state_str=tmp.substr(third+1,1);

        if(id_str==client->get_id())//如果id一致
        {
            if(state_str=="1")//如果约了这本书
            {                 
                book* temp=new book;
                    temp->next=NULL;
                    book* head=book_head1;
                    book* searchptr=head;//searchptr用来找booklist中对应的书，也就是要复制给temp的书
                    while(searchptr!=NULL)
                    {
                        if(searchptr->getid()==book_str)//如果id一致
                        {
                            //查看这本书是否可借 avil>1??
                            if(searchptr->getavil_number()>0)
                            {
                                //询问借不借，借：将书加入借书链表，avil-1，从预借链表中减去（修改文件）
                                //不借了：将预约书籍从预约链表中减去（修改文件）
                                QString str=QString::fromStdString(searchptr->getname());
                                QMessageBox::StandardButton reply=QMessageBox::question(this,"","您预约的书籍："+str+"可以借阅了，是否借阅？", QMessageBox::Yes|QMessageBox::No);
                                if(reply==QMessageBox::Yes)
                                {
                                    client->book_borrow(searchptr);
                                    searchptr->set_avil_num(searchptr->getavil_number()-1);
                                    file.seekg(length-1,ios::beg);///将状态改为0
                                    file<<"0"<<endl;
                                    client->save_book_borrowed(searchptr);//借书写入文件
                                    searchptr->state_and_avil_change(searchptr->getavil_number(),searchptr->getid());//更改书单状态
                                    break;
                                }
                                else
                                {
                                    file.seekg(length-1,ios::beg);///将状态改为0
                                    file<<"0"<<endl;
                                    break;
                                }
                            }
                            else//预借的书还没货
                            {
                                temp->copybook(searchptr);//显示预约书籍到窗口
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

    returnlist=new book;//带头结点
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

            //符合任意一项就加入链表
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
            QMessageBox::about(this,"nothing was found", "未找到相符内容");
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

        //检查前方有几个人预约
        string tmp,id_str,book_str,state_str,num;
        int n=0;//预约人数
        ifstream f;
        f.open("order_books.txt");
        while(!f.eof())
        {
            getline(f,tmp);
            int pos=0,second,first,third;

            first=tmp.find_first_of(' ',pos);//first=第一个空格的位置
            second=tmp.find_first_of(' ',first+1);//second=第二个空格位置
            third=tmp.find_first_of(' ',second+1);//second=第二个空格位置
            id_str=tmp.substr(first+1,8);
            book_str=tmp.substr(second+1,13);
            state_str=tmp.substr(third+1,1);

            if(book_str==selected->getid())//如果流水号一致
            {
                if(state_str=="1")//如果预约了这本书
                    n++;
            }
        }
        f.close();
        stringstream ss;
        ss<<n;ss>>num;
        QString _num=QString::fromStdString(num);

        QMessageBox::StandardButton reply=QMessageBox::question(this,"","要预约"+name+_num+"人排队。",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes)
        {
            client->order_book(selected);

            //更新预约图书
            ui->showbookreserverd->clear();
            ifstream file;
            file.open("order_books.txt");
            string tmp,id_str,book_str,state_str;
            book* add=new book;//返回预约链表

            while(!file.eof())
            {
                getline(file,tmp);
                int pos=0,second,first,third;

                first=tmp.find_first_of(' ',pos);//first=第一个空格的位置
                second=tmp.find_first_of(' ',first+1);//second=第二个空格位置
                third=tmp.find_first_of(' ',second+1);//second=第二个空格位置
                id_str=tmp.substr(first+1,8);
                book_str=tmp.substr(second+1,13);
                state_str=tmp.substr(third+1,1);

                if(id_str==client->get_id())//如果id一致
                {
                    if(state_str=="1")//如果约了这本书
                    {
                            book* temp=new book;
                            temp->next=NULL;
                            book* head=book_head1;
                            book* searchptr=head;//searchptr用来找booklist中对应的书，也就是要复制给temp的书
                            while(searchptr!=NULL)
                            {
                                if(searchptr->getid()==book_str)//如果id一致
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

            QMessageBox::about(this,"","预约成功！");
        }
    }
    else{}


}

void u_MainWindow::on_cancel_clicked()//取消预约
{    
    if(ui->showbookreserverd->currentRow()>=0)
    {
        int i=ui->showbookreserverd->currentRow();
        QString s=ui->showbookreserverd->item(i)->text();
        string str=s.toStdString();
        QMessageBox::StandardButton reply=( QMessageBox::question(this,"","确定要取消预约"+s+"吗?", QMessageBox::Yes | QMessageBox::No));

        if(reply==QMessageBox::Yes)
        {
                
            //找到选中的书的流水号,temp指向找到的书

            book* temp=book_head1;
            while(temp!=NULL)
            {
                if(temp->getname()==str)
                    break;
                temp=temp->next;
            }

            //改写order_books.txt文件，属性变为0
            fstream ifs;
                ifs.open("order_books.txt",ios_base::out|ios_base::in );
                string tmp,id_str,book_str,state_str;//tmp用来存储每一行，id_str来存储每一行的用户名，用于匹配
                int success=0;
                int length=0;//使用length计数从而找到添加数据的指针位置

                while(!ifs.eof() && success==0)
                {
                    getline(ifs,tmp);
                    length+=tmp.length();


                    int pos=0,mark,n,third;
                    n=tmp.find_first_of(' ',pos);//n=第一个空格的位置
                    mark=tmp.find_first_of(' ',n+1);//mark=第二个空格位置
                    third=tmp.find_first_of(' ',mark+1);//mark=第二个空格位置

                    id_str=tmp.substr(n+1,8);
                    book_str=tmp.substr(mark+1,13);
                    state_str=tmp.substr(third+1,1);

                    if(id_str.compare(client->get_id())==0)//如果用户id和记录id一致
                    {
                        if(book_str.compare(temp->getid())==0 && state_str.compare("1")==0)
                        {

                            ifs.seekg(length-1,ios::beg);///将状态改为0
                            ifs<<"0"<<endl;
                            success=1;
                        }
                    }
                    length+=2;
                }
                ifs.close();

            //重新载入orderbooks.txt并在showbookreserved中显示
                ui->showbookreserverd->clear();
                ifstream file;
                file.open("order_books.txt");

                book* add=new book;//返回预约链表

                while(!file.eof())
                {
                    getline(file,tmp);
                    int pos=0,second,first,third;

                    first=tmp.find_first_of(' ',pos);//first=第一个空格的位置
                    second=tmp.find_first_of(' ',first+1);//second=第二个空格位置
                    third=tmp.find_first_of(' ',second+1);//second=第二个空格位置
                    id_str=tmp.substr(first+1,8);
                    book_str=tmp.substr(second+1,13);
                    state_str=tmp.substr(third+1,1);

                    if(id_str==client->get_id())//如果id一致
                    {
                        if(state_str=="1")//如果约了这本书
                        {
                                book* temp=new book;
                                temp->next=NULL;
                                book* head=book_head1;
                                book* searchptr=head;//searchptr用来找booklist中对应的书，也就是要复制给temp的书
                                while(searchptr!=NULL)
                                {
                                    if(searchptr->getid()==book_str)//如果id一致
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


