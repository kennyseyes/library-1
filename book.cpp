 #include "book.h"

book::book()
{

}
book:: book(string _id,string _name,string _author,string _publish,\
            float _price,string _type,string _ISBN,int _all,int _now,bool _state,\
            int _authority,string _date,string _intro)//构造函数 ：初始化图书信息（购入图书时，不必设置状态）
       {
           ID=_id;
           name=_name;
           author=_author;
           publish=_publish;
           price=_price;
           type=_type;
           ISBN=_ISBN;
           all_number=_all;
           avil_number=_now;
           state=_state;
           authority=_authority;
           in_time=_date;
           intro=_intro;
           next=NULL;
       }
string book::getname()
{
    return name;
}

string book:: getid()
{
    return ID;
}

string book:: getauthor()
{
    return author;
}

string book::  getpublish()
{
    return publish;
}

string book:: gettype()
{
    return type;
}

string book:: getintro()
{
    return intro;
}

string book:: getin_time()
{
    return in_time;   //购入时间
}

int book::getall_number()
{
    return all_number;   //所有数量
}

int book:: getavil_number()
{
    return avil_number;   //剩余数量
}

bool book:: getstate()
{
    return state;
}

double book:: getprice()
{
    return price;   //定价
}

int book:: getauth()
{
    return authority;
}

/*
void book:: add_log(int type,int act_num,string u_id,book* b_book)
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
                fptr<<u_id<<"\n";
            // else
            //fptr<<u_id<<" "<<cre<<":"<<cre_la<<"\n";
        }
    }
    fptr.close();
}

*/

void book:: copybook(book* target)//将target拷贝给当前类
   {
       ID=target->getid();//图书编号，需生成， XX（类型）XX（出版社）XXXXX（流水号）
       name=target->getname();//书名
       author=target->getauthor();//作者
       publish=target->getpublish();//出版社
       intro=target->getintro();//简介
       in_time=target->getin_time();//购入时间
       all_number=target->getall_number();//所有数量
       avil_number=target->getavil_number();	//剩余数量
       price=target->getprice();//定价
       type=target->gettype();//类别
       state=target->getstate();//状态（借出1，未借出0）
       authority=target->getauth();//权限
       ISBN=target->getISBN();//ISBN
       next=NULL;
   }

void book::set_avil_num(int n)
{
    avil_number=n;
}

bool book:: state_and_avil_change(int avil_number,string ID)   //修改txt中图书的剩余数量和状态，返回状态state
{
    fstream booklist;
    booklist.open("user_borrow.txt",ios::binary|ios::out|ios::in);
    string s;
    int length=0;//使用length计数从而找到添加数据的指针位置

    string _id;
    string s_state;

    int _state;

    int h;
    int k = 2;

    getline(booklist,s);
    length+=s.length()+1;  //先读取第一行的长度
    while(!booklist.eof())//读取每本书的信息
    {
        int pos=0,mark;
        stringstream ss;
        getline(booklist,s);

        mark=s.find_first_of(' ',pos);
        _id=s.substr(pos,mark-pos);
        pos=mark+1;

        if(_id == ID)  //匹配到书名然后修改
        {
            for(int a=0; a<7; a++)
            {
                mark=s.find_first_of(' ',pos);
                pos=mark+1;
            }
            mark=s.find_first_of(' ',pos);
            h = pos +length;
            // cout << pos <<" "<< mark <<" "<< h << endl;
            booklist.seekp(h,ios::beg);
            booklist << avil_number;  //改变剩余书籍数量
            pos=mark+1;

            mark=s.find_first_of(' ',pos);
            s_state=s.substr(pos,mark-pos);
            ss<<s_state;
            ss>>_state;
            ss.clear();
            h = pos +length;
            booklist.seekp(h,ios::beg);
            if(avil_number == 0)      //馆内没有该书了，则将状态改为1
            {
                booklist << "1";
                _state=1;

            }
            else                   //馆内有该书，则将状态改为0
            {
                booklist << "0";
                _state=0;
            }
            pos=mark+1;
            cout << "图书状态修改成功！";
            booklist.close();
            return _state;

            //          booklist.seekp(0,ios::beg);   //将光标移动到起始位置

            //          for(int j = 1;j<=k;j++){
            //              getline(booklist,s);
            //          }
        }
        length+=s.length()+1;
        k++;
    }
    cout << "修改失败！";
    booklist.close();
    return _state;
}

void book:: add()//购入图书
{
    all_number++;
    avil_number++;
}

void book:: output()
{
    cout<<"ID:"<<ID<<endl;
    cout<<"名称:"<<name;
    cout<<" 作者:"<<author<<" 出版社："<<publish<<endl;
    cout<<"购入时间:"<<in_time<<" 所有数量:"<<all_number<<endl;
    cout<<" 定价:"<<price<<" 类别:"<<type<<" 借阅权限："<<authority<<endl;
    cout<<intro<<endl;
    cout<<endl;
}

void book:: borrow_out()
{
    avil_number--;
    state=state_and_avil_change(avil_number,ID); //修改txt中图书的剩余数量和状态
}

book::~book(){}

book* book:: load_books()//载入书籍
{
    ifstream booklist;
    booklist.open("book_storage.txt");
    string s;
    getline(booklist,s);
    book* firstbook=new book;//头节点
    firstbook->next=NULL;
    book *temp=firstbook;

    string _id,_name, _author,_publish,_type,_ISBN,_date,_intro;
    string s_all,s_now,s_state,s_authority,s_price;

    int _all, _now, _state,_authority;

    double price;

    while(getline(booklist,s))//读取每本书的信息
    {
        int pos=0,mark;
        stringstream ss;

        mark=s.find_first_of(' ',pos);
        _id=s.substr(pos,mark-pos);
        //    cout<<_id<<". "<<endl;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        _name=s.substr(pos,mark-pos);
        //    cout<<"name："<<_name<<". "<<endl;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        _author=s.substr(pos,mark-pos);
        //    cout<<"author："<<_author<<". "<<endl;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        _publish=s.substr(pos,mark-pos);
        //    cout<<"publish："<<_publish<<". "<<endl;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        s_price=s.substr(pos,mark-pos);
        ss<<s_price;
        ss>>price;
        ss.clear();
        //   cout<<"定价："<<price<<". "<<endl;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        _type=s.substr(pos,mark-pos);
        //     cout<<"类："<<_type<<". "<<endl;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        _ISBN=s.substr(pos,mark-pos);
        //   cout<<"isbn："<<_ISBN<<". "<<endl;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        s_all=s.substr(pos,mark-pos);
        ss<<s_all;
        ss>>_all;
        ss.clear();
        //   cout<<"在馆数量："<<_all<<"."<<endl;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        s_now=s.substr(pos,mark-pos);
        ss<<s_now;
        ss>>_now;
        ss.clear();
        //cout<<"nowavailable："<<_now<<". "<<endl;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        s_state=s.substr(pos,mark-pos);
        ss<<s_state;
        ss>>_state;
        ss.clear();
        //    cout<<"state："<<_state<<". "<<endl;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        s_authority=s.substr(pos,mark-pos);
        ss<<s_authority;
        ss>>_authority;
        ss.clear();
        //     cout<<"权限："<<_authority<<". "<<endl;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        _date=s.substr(pos,mark-pos);
        //     cout<<"date："<<_date<<".\n "<<endl;
        pos=mark+1;

        mark=s.find_first_of(' ',pos);
        _intro=s.substr(pos,mark-pos);

        book* newbook=new book(_id,_name,_author,_publish,price,_type,_ISBN,_all,_now,_state,_authority,_date,_intro);
        newbook->next=NULL;
        temp->next=newbook;
        temp=newbook;
    }

    booklist.close();
    return firstbook;
}

