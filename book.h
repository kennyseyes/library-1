#ifndef BOOK_H
#define BOOK_H

#define CLIENT_LOG 0
#define BOOKS_LOG 1
#define SEVERS_LOG 2
#define ACCESS_TOKEN "10"
#define MAX_USERS 500

#include <iomanip>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <fstream>
//#include <windows.h>
#include <time.h>
#include <sstream>

using namespace std;

class book
{

public:
    book* next;//链表存储
    book();
    book(book& u);
    book(string _id,string _name,string _author,string _publish, float _price,string _type,string _ISBN,int _all,int _now,bool _state,int _authority,string _date,string _intro);//构造函数 ：初始化图书信息（购入图书时，不必设置状态）
    string getname();


    string getid();

    string getauthor();

    string getpublish();
    string getISBN()
    {
        return ISBN;
    }
    string gettype();

    string getintro();

    string getin_time();

    int getall_number();

    int getavil_number();

    bool getstate();

    double getprice();

    int getauth();

    void add_log(int type,int act_num,string u_id,book* b_book);


    void copybook(book* target);//将target拷贝给当前类

    bool state_and_avil_change(int avil_number,string ID);   //修改txt中图书的剩余数量和状态，返回状态state

    void add();//购入图书

    void output();

    void borrow_out();

    void return_back();

   book* load_books();

    ~book(); //虚构函数：便于销毁申请的动态内存
private:
    string ID;//图书编号，需生成， XX（类型）XX（出版社）XXXXX（流水号）
    string name;//书名
    string author;//作者
    string publish;//出版社
    string intro;//简介
    string in_time;//购入时间
    int all_number;//所有数量
    int avil_number;	//剩余数量
    double price;//定价
    string type;//类别
    int authority;//权限
    bool state;//状态（借出1，未借出0）
    string ISBN;//ISBN

};

#endif // BOOK_H
