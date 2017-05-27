#include "change_password.h"
#include "ui_change_password.h"
#include <fstream>
#include <QMessageBox>
user* client3;

change_password::change_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_password)
{
    ui->setupUi(this);
}

change_password::~change_password()
{
    delete ui;
}

void change_password::on_pushButton_2_clicked()
{
    this->close();
}

void change_password::rece_curuser(user* cu){
    client3=cu;
    QString cur_name=QString::fromStdString(client3->getname());

}

void change_password::on_pushButton_clicked()
{
    string old=ui->old->text().toStdString();
    string new_2=ui->new_2->text().toStdString();
    string new2=ui->new2->text().toStdString();

    if(new_2!=new2)
        QMessageBox::about(this,"","两次密码输入不一致，请重新输入。");
    else if(old!=client3->get_password())
        QMessageBox::about(this,"","原密码输入错误，请重新输入。");
    else{
        client3->setpassword(new2);
        QMessageBox::about(this,"","密码修改成功！");
        this->close();

  ///更新用户文件
        fstream ifs;
        ifs.open("user.txt",ios_base::out|ios_base::in );
        string tmp,id_str,pw_str;//tmp用来存储每一行，id_str来存储每一行的用户名，用于匹配
        int success=0;
        int length=0;//使用length计数从而找到添加数据的指针位置
        while(!ifs.eof() && success==0)
        {
            getline(ifs,tmp);


            cout<<length<<endl;
            int pos=0,mark,n,k,p;
            n=tmp.find_first_of(' ',pos);//n=第一个空格的位置
            mark=tmp.find_first_of(' ',n+1);//mark=第二个空格位置
            k=tmp.find_first_of(' ',mark+1);//k=第三个空格的位置
            p=tmp.find_first_of(' ',k+1);//p=第四个空格的位置

            id_str=tmp.substr(mark+1,8);
            pw_str=tmp.substr(k+1,p-k);
            ///  cout<<"client:"<<client->get_id()<<" "<<id_str<<endl;
            if(id_str.compare(client3->get_id())==0)//如果用户id和记录id一致
            {
                ifs.seekg(length+k+1,ios::beg);///改密码
                ifs<<new2;
                int blank=8-new2.length();//blank为需要增加的空格数
                while(blank>0)
                {
                    ifs<<" ";
                    blank--;
                }

                success=1;
            }
            length+=tmp.length();
            length+=2;
        }
        ifs.close();
    }

}
