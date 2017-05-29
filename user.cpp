#include "user.h"
#include<QMessageBox>
user::user()
{

}

user::~user()
{

}

void user:: copyuser(user* target)//将target拷贝给当前类
{
    user_type=target->user_type;//老师0学生1
    id=target->id;//学号/工作证
    password=target->password;//密码初始00000000
    name=target->name;//姓名
    academy=target->academy;//学院
    permission=target->permission;//借阅权限，小数
    book_number=target->book_number;//借书总数量
    books_hand=target->books_hand;//在手中的书数量
    expire_num=target->expire_num;//过期书目数量
    credit=target->credit;//用户信用度
    borrowed=target->borrowed;//所借书目
    expire=target->expire;//过期书目
    debt=target->debt;//欠款
}
void user:: init()//添加新用户
{
    ///输入用户类型 (老师0学生1)，姓名，证件号，学院
    int user_type1;
    string name1;
    string id1;
    string academy1;
    cin >> user_type1;
    cin>>name;
    cin >> id1;
    cin >> academy1;
    user_type = user_type1;
    id = id1;
    academy = academy1;
    name=name1;
    borrowed=new book;
    expire= new book;
    next=NULL;
}
user::user(int user_type1,string name1, string id1, string passwd,string academy1,int permission1,int credit1,double debt1)
    {
        user_type = user_type1;
        id = id1;
        academy = academy1;
        name=name1;
        password="00000000";
        permission = permission1;
        book_number = 0;
        books_hand = 0;
        expire_num = 0;
        borrowed = new book;
        expire = new book;
        debt = debt1;
        credit = credit1;
        next=NULL;
        password=passwd;
    }

float user:: payment()
{

    fstream fptr;
    string s;

    fptr.open("user.txt",ios::out|ios::in|ios::binary);

    if (!fptr.is_open())
    {
        cout<<"error"<<endl;
        exit(0);
    }
    string pay;
    float pri=0;

    getline(fptr, s);

    ///测试
    //int id=1;

    while (!fptr.eof())
    {
        getline(fptr, s);

        int i=(int)s.find_first_of(' ', 0);//第一个空格
        i=(int)s.find_first_of(' ', i+1);//第二个空格 标志id
        int p=i;
        for (int k=0; k<4; k++) p=(int)s.find_first_of(' ',p+1);//第四个空格 标志欠款




        if( atoi(get_id().c_str())==atoi(s.substr(i+1,8).c_str()) )
        {
            int k=(int)s.find_first_of(' ',p+1);
            k=k-p;

            cout<<"欠款："<<setiosflags(ios::fixed)<<setprecision(2)<<atof(s.substr(p+1,k).c_str())<<endl;
            cout<<"请输入还款金额"<<endl;
            cin>>pay;

            pri=atof(s.substr(p+1,k).c_str())-atof(pay.c_str());


            ///修改欠款

            if(pri<10)
            {
                k=(k+1)*sizeof(char);
                fptr.seekp(-k,ios::cur);
                fptr<<setiosflags(ios::fixed)<<setprecision(2)<<pri<<" ";
            }
            else
            {
                k=(k+2)*sizeof(char);
                fptr.seekp(-k,ios::cur);
                fptr<<setiosflags(ios::fixed)<<setprecision(2)<<pri<<" ";
            }

            break;
        }
    }
    return pri;
    fptr.close();
}
/*
void user:: add_log(int type,int act_num,string u_id,book* b_book)
     {
         fstream fptr;
         if(type==0)
         {
             fptr.open("client_log.txt",ios::app|ios::in|ios::out);
             if(fptr.is_open())
             {
                 ///日期部分写入文件
                 //cout<<"open";
                 fptr<<"["<<1900+calendar.tm_year<<"-";
                 if(calendar.tm_mon<9) fptr<<"0"<<calendar.tm_mon+1<<"-";
                 else fptr<<calendar.tm_mon+1<<"-";
                 if(calendar.tm_mday<9) fptr<<"0"<<calendar.tm_mday<<"]: ";
                 else fptr<<calendar.tm_mday<<"]: ";
                 ///用户信息
                 fptr<<u_id<<" ";
                 ///用户行为
                 fptr<<client_act[act_num];
                 ///所借书本信息
                 fptr<<b_book->getid()<<":1"<<"\n";
             }
         }
         ///BOOKS_LOG
         else if(type==1)
         {
             fptr.open("books_log.txt",ios::app|ios::in|ios::out);
             if(fptr.is_open())
             {
                 ///日期部分写入文件
                 //cout<<"open";
                 fptr<<"["<<1900+calendar.tm_year<<"-";
                 if(calendar.tm_mon<9) fptr<<"0"<<calendar.tm_mon+1<<"-";
                 else fptr<<calendar.tm_mon+1<<"-";
                 if(calendar.tm_mday<9) fptr<<"0"<<calendar.tm_mday<<"]: ";
                 else fptr<<calendar.tm_mday<<"]: ";
                 ///被操作书本信息
                 fptr<<b_book->getid()<<" ";
                 ///操作
                 fptr<<books_act[act_num]<<" "<<"1"<<"\n";
             }
         }
         else
         {
             fptr.open("severs_log.txt",ios::app|ios::in|ios::out);
             if(fptr.is_open())
             {
                 ///日期部分写入文件
                 //cout<<"open";
                 fptr<<"["<<1900+calendar.tm_year<<"-";
                 if(calendar.tm_mon<9) fptr<<"0"<<calendar.tm_mon+1<<"-";
                 else fptr<<calendar.tm_mon+1<<"-";
                 if(calendar.tm_mday<9) fptr<<"0"<<calendar.tm_mday<<"]: ";
                 else fptr<<calendar.tm_mday<<"]: ";
                 ///动作记录
                 fptr<<books_act[act_num]<<" ";
                 if(act_num<2)
                 {
                     fptr<<b_book->getid()<<'\n';
                 }
                 ///被操作书本信息
                 else if(act_num<4)
                     fptr<<get_id()<<"\n";
                 // else
                 //fptr<<u_id<<" "<<cre<<":"<<cre_la<<"\n";
             }
         }
         fptr.close();
}
*/

void user::order_book(book* target)
{
    fstream f;
    f.open("order_books.txt",ios::app|ios::in|ios::out);
    if(f.is_open())
    {
      /*  f<<"["<<1900+calendar.tm_year<<"-";
        if(calendar.tm_mon<9) f<<"0"<<calendar.tm_mon+1<<"-";
        else f<<calendar.tm_mon+1<<"-";
        if(calendar.tm_mday<9) f<<"0"<<calendar.tm_mday<<"]: ";
        else f<<calendar.tm_mday<<"]: ";*/
        f<<" "<<get_id()<<" "<<target->getid()<<' '<<'1'<<'\n';
    }
    else
        cout<<"预约失败"<<endl;
}

bool user::check_permission(user* client,int authority)
///检查借书权限，传入用户书籍权限，返回1：可借，0：不可借
{
    if(client->get_type()==0)
        return 1;
    else
    {
        int permission=client->getpermission();
        switch(permission)
        {
            case 0:///先写成了什么书都不能借
                return 0;

            case 1:
                if(authority==0) return 1;
                else return 0;

            case 2:
                if(authority<=1) return 1;
                else return 0;

            case 3:
                if(authority<=2) return 1;
                else return 0;

            case 4:
                if(authority<=3) return 1;
                else return 0;

            case 5:
                if(authority<=1) return 1;
                else return 0;
        }
    }

    return -1;
}

bool user::check_credit(user* client,double price)
///检查借书权限，传入用户信用等级、书籍价格，返回1：可借，0：不可借
{
    if(client->get_type()==0)
        return 1;
    else
    {
        int credit=client->getcredit();
        switch(credit)
        {
            case 1:
                if(price<10.00) return 1;
                else return 0;

            case 2:
                if(price<30.00) return 1;
                else return 0;

            case 3:
                if(price<50.00) return 1;
                else return 0;

            case 4:
                if(price<60.00) return 1;
                else return 0;

            case 5:
                return 1;
          }

    }
    return -1;
}

int user::book_borrow(book* target)//将target放入借书链表,有头节点 targer指向书的指针，返回是否借书成功
{
    if(check_permission(this,target->getauth())&&check_credit(this,target->getprice()) && target->getavil_number()!=0)//如果符合借书条件 且书还有剩余
    {
        book* newbook=new book;
        newbook->copybook(target);//newbook 独立出来了的
       // add_log(CLIENT_LOG,0,get_id(),newbook);//用户日志
        //add_log(BOOKS_LOG,0,get_id(),newbook);//图书日志

        book *temp;
        temp=borrowed;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=newbook;
        return 1;
    }
    else if(target->getavil_number()==0)
    {
        return 3;
        cout<<"抱歉，暂无库存。是否预约？1：是；0：否"<<endl;
        int n;
        cin>>n;
        if(n)
        {
            ///预约板块
            order_book(target);
        }
        else
            return 1;
    }
    else 
        return 2;

}

void user::book_return(int n)//n为要删除第几本书
{
    ///从用户借书链表中删除书籍删掉temp
    book* temp=borrowed->next;
    book* pre=borrowed;
    for(int i=0; i<n; i++)
        pre=pre->next;
    temp=pre->next;

    pre->next=temp->next;
    //  add_log(CLIENT_LOG,1,get_id(),temp);//用户日志
 // add_log(BOOKS_LOG,1,get_id(),temp);//图书日志
    temp->next=NULL;
    delete temp;
    ///修改在链表中的书的状态

}
int user::get_type()
{
    return user_type;
}
string user::getname()
{
    return name;
}
string user::get_id()
{
    return id;
}
string user::get_academy()
{
    return academy;
}
string user:: get_password()
{
    return password;
}
int user::get_permission()
{
    return permission;
}
int user::get_credit()
{
    return credit;
}
int user::get_bookhand()
{
    return books_hand;
}
int user::get_expirenum()
{
    return expire_num;
}
double user::get_debt()
{
    return debt;
}
book* user::getbookborrowed()
{
    return borrowed;   //返回借书列表
}
int user:: getpermission()
{
    return permission;
}
int user::getcredit()
{
    return credit;
}
int user::getnumber()
{
    return book_number;
}
void user::setpassword(string s)
{
    password=s;
}
void user::setdebt(double d)
{
    debt=d;
}

void user::output()
{
    cout << "用户类型：";
    if (user_type)
        cout << "学生" << endl << "学号：" << id << endl;
    else
        cout << "老师"<<endl << "工作证：" << id << endl;
    cout << "学院：" <<this->academy << endl;
    cout<<"name:"<<name<<endl;
    cout << "权限：" <<this->permission << endl;
    cout << "信用等级：" <<this->credit << endl;
    cout << "借书数量：" <<book_number << endl;
    cout << "所借书目：" <<  endl;
    book* temp=borrowed->next;
    while(temp!=NULL)
    {
        cout<<temp->getname()<<endl;
        temp=temp->next;
    }

    cout << "欠款：" << debt << endl;
    cout << "password：" << password << endl;
}

book* user::book_login()//载入借过的书
{
    ifstream file;
    file.open("user_borrow.txt");
    string tmp,id_str,book_str,state_str;
    book* add=new book;///添加借的书的指针
    book* add_head=add;
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

        if(id_str==this->id)//如果id一致
        {
            if(state_str=="1")//如果借了这本书
            {
                book* temp=new book;
                temp->next=NULL;
                book* head=temp;
                head=head->load_books();
                book* searchptr=head;//searchptr用来找booklist中对应的书，也就是要复制给temp的书
                while(searchptr!=NULL)
                {
                    if(searchptr->getid()==book_str)//如果id一致
                    {
                        temp->copybook(searchptr);
                        add->next=temp;
                        add=add->next;
                        break;
                    }
                    searchptr=searchptr->next;
                }
                ///未完成：从书籍列表中搜索id相符的书并拷贝给temp
                /*  book* findend=this->borrowed;//找到borrow的末尾
                  while(findend->next!=NULL)
                      findend=findend->next;
                  findend->next=temp;*/
            }
        }
    }
    add->next=NULL;
    file.close();
    borrowed= add_head;
    return add_head->next;
}

user* user:: load_user()///链表存储用户信息,头节点为空的链表存储
{
    ifstream userlist;
    userlist.open("user.txt");
    string s;
    getline(userlist,s);
    user* firstuser=new user;//头节点
    firstuser->next=NULL;
    char type;
    string name,id,academy,s_permission,s_credit,s_debt,password;
    int type_trans,permission,credit;
    double debt;
    user *temp=firstuser;
    stringstream ss;

    while(getline(userlist,s))//读取行
    {
        int mark,pos=2;//first标记空格

        type=s[0];type_trans=type-'0';//用户类型

        ///int find_first_of(char c, int pos = 0) const;//从pos开始查找字符c第一次出现的位置
        ///substr第一个是开始的坐标（第一个字符是0），第二个是截取的长度
        mark=s.find_first_of(' ',pos);
        name=s.substr(pos,mark-pos);
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        id=s.substr(pos,mark-pos);
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        password=s.substr(pos,mark-pos);
        pos=pos+9;

        mark=s.find_first_of(' ',pos);///潜在bug。。。。。
        academy=s.substr(pos,mark-pos);
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        s_permission=s.substr(pos,mark-pos);
        ss.clear();ss<<s_permission;ss>>permission;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        s_credit=s.substr(pos,mark-pos);
        ss.clear();ss<<s_credit;ss>>credit;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        s_debt=s.substr(pos,mark-pos);
        ss.clear();ss<<s_debt;ss>>debt;
        pos=mark+1;

        user* newuser=new user(type_trans,name,id,password,academy,permission,credit,debt);
        newuser->next=NULL;
        temp->next=newuser;
        temp=newuser;

    }

    userlist.close();
    return firstuser;
}


void user::save_book_return(string book)///将用户归还的书籍写入user_borrow.txt，已归还书籍参数为0
{
    cout<<"book:"<<book<<".."<<endl;
    fstream ifs;
    ifs.open("user_borrow.txt",ios_base::out|ios_base::in );
    string tmp,id_str,book_str;//tmp用来存储每一行，id_str来存储每一行的用户名，用于匹配
    int success=0;
    int length=0;//使用length计数从而找到添加数据的指针位置

    while(!ifs.eof() && success==0)
    {
        getline(ifs,tmp);
        length+=tmp.length();


        int pos=0,mark,n;
        n=tmp.find_first_of(' ',pos);//n=第一个空格的位置
        mark=tmp.find_first_of(' ',n+1);//mark=第二个空格位置

        id_str=tmp.substr(n+1,8);
        book_str=tmp.substr(mark+1,13);

        if(id_str.compare(this->get_id())==0)//如果用户id和记录id一致
        {
            if(book_str.compare(book)==0)
            {

                ifs.seekg(length-1,ios::beg);///将状态改为0
                ifs<<"0"<<endl;
                success=1;
            }
        }
        length+=2;
    }
    ifs.close();
}


void user::save_book_borrowed(book* target)///将用户借阅的书籍写入user.txt，1为被用户借走
{
    fstream ifs;
    ifs.open("user_borrow.txt",ios_base::out|ios_base::in|ios::app);
    int success=0;
    while(!ifs.eof() && success==0)
    {
        ifs<<" "<<this->get_id()<<" "<<target->getid()<<" "<<1<<'\n';
        success=1;
    }

    ifs.close();
}
