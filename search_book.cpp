#include "search_book.h"
#include "book.h"

search_book::search_book(){}
search_book::~search_book(){}


book* search_book::SearchBook(book *head)
{
    string input,tempname,m;
        book* returnlist=new book;//带头结点
        book* connect=returnlist;
        book* temp=head;
        bool found=0;
        int pos;

        cout<<"按信息查询：（退出请输0）"<<endl;
        cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
        char n;
        cin>>n;
        while( n!='0'&&n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6' )
        {
            cout<<"输入有误请重新输入。"<<endl;
            cin>>n;
        }
        ///str.find(xx)函数：如果在str中没找到xx，返回-1
        while(n!='0'||n=='1'||n=='2'||n=='3'||n=='4'||n=='5'||n=='6')
        {
            switch(n)
            {
                case '0':break;
                case '1':
                    found=0;
                    cout<<"请输入图书编号：（输入0退出）"<<endl;
                    cin>>input;
                    if(input=="0")
                    {
                        cout<<"按信息查询：（退出请输0）"<<endl;
                        cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                        cin>>n;
                        while( n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6' &&n!='0')
                        {
                            cout<<"输入有误请重新输入。"<<endl;
                            cin>>n;
                        }
                        break;
                    }
                    temp=head;
                    while(found==0)
                    {
                        while(input.length()!=13)
                        {
                            cout<<"输入有误,请重新输入。"<<endl;
                            cin>>input;
                            if(input=="0")
                            {
                                cout<<"按信息查询：（退出请输0）"<<endl;
                                cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                                cin>>n;
                                while( n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6'&&n!='0' )
                                {
                                    cout<<"输入有误请重新输入。"<<endl;
                                    cin>>n;
                                }
                                break;
                            }
                        }
                        if(input=="0") break;
                        while(temp!=NULL)
                        {
                            if(temp->getid()==input)
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
                            found=1;
                            n='0';
                        }
                        else
                        {
                            cout<<"未找到符合的记录，请重新输入（返回输入0）"<<endl;
                            cin>>input;
                            temp=head;
                            if(input=="0")
                            {
                                found=1;
                                cout<<"按信息查询：（退出请输0）"<<endl;
                                cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                                cin>>n;
                                while( n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6'&&n!='0' )
                                {
                                    cout<<"输入有误请重新输入。"<<endl;
                                    cin>>n;
                                }
                                break;
                            }
                        }
                    }

                    break;

                case '2':
                    found=0;
                    cout<<"请输入书名或书名中的关键字（输入0返回）：";
                    cin>>input;
                    if(input=="0")
                    {
                        cout<<"按信息查询：（退出请输0）"<<endl;
                        cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                        cin>>n;
                        while( n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6'&&n!='0' )
                        {
                            cout<<"输入有误请重新输入。"<<endl;
                            cin>>n;
                        }
                        break;
                    }

                    while(found==0)
                    {
                         temp=head;
                         while(temp!=NULL)
                        {
                            tempname=temp->getname();
                            pos=tempname.find(input);//找到关键字
                            if(pos!=-1)
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
                            found=1;
                            n='0';
                        }
                        else
                        {
                            cout<<"未找到符合的记录，请重新输入（返回输入0）"<<endl;
                            cin>>input;
                            if(input=="0")
                            {
                                found=1;
                                cout<<"按信息查询：（退出请输0）"<<endl;
                                cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                                cin>>n;
                                while( n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6'&&n!='0' )
                                {
                                    cout<<"输入有误请重新输入。"<<endl;
                                    cin>>n;
                                }
                                break;
                            }
                        }
                    }

                    break;
                case '3':
                    found=0;
                    cout<<"请输入作者（返回输入0）：";
                    cin>>input;
                    if(input=="0")
                    {
                        cout<<"按信息查询：（退出请输0）"<<endl;
                        cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                        cin>>n;
                        while( n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6'&&n!='0' )
                        {
                            cout<<"输入有误请重新输入。"<<endl;
                            cin>>n;
                        }
                        break;
                    }

                    while(found==0)
                    {
                        temp=head;
                        while(temp!=NULL)
                        {
                            pos=temp->getauthor().find(input);
                            if(pos!=-1)
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
                            found=1;
                            n='0';
                        }
                        else
                        {
                            cout<<"未找到符合的记录，请重新输入（返回输入0）"<<endl;
                            cin>>input;
                            if(input=="0")
                            {
                                found=1;
                                cout<<"按信息查询：（退出请输0）"<<endl;
                                cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                                cin>>n;
                                while( n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6'&&n!='0' )
                                {
                                    cout<<"输入有误请重新输入。"<<endl;
                                    cin>>n;
                                }
                                break;
                            }
                        }
                    }
                    break;

                case '4':
                    found=0;
                    cout<<"请输入出版社（输入0退出）：";
                    cin>>input;
                    if(input=="0")
                    {
                        cout<<"按信息查询：（退出请输0）"<<endl;
                        cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                        cin>>n;
                        while( n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6'&&n!='0' )
                        {
                            cout<<"输入有误请重新输入。"<<endl;
                            cin>>n;
                        }
                        break;
                    }
                    while(found==0)
                    {
                        temp=head;
                        while(temp!=NULL)
                        {
                            pos=temp->getpublish().find(input);
                            if(pos!=-1)
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
                            found=1;
                            n='0';
                        }
                        else
                        {
                            cout<<"未找到符合的记录，请重新输入（返回输入0）"<<endl;
                            cin>>input;
                            if(input=="0")
                            {
                                found=1;
                                cout<<"按信息查询：（退出请输0）"<<endl;
                                cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                                cin>>n;
                                while( n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6'&&n!='0' )
                                {
                                    cout<<"输入有误请重新输入。"<<endl;
                                    cin>>n;
                                }
                                break;
                            }
                        }

                    }
                    break;
                case '5':
                    found=0;
                    cout<<"请输入类别（输入0退出）：";
                    cin>>input;
                    if(input=="0")
                    {
                        cout<<"按信息查询：（退出请输0）"<<endl;
                        cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                        cin>>n;
                        while( n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6'&&n!='0' )
                        {
                            cout<<"输入有误请重新输入。"<<endl;
                            cin>>n;
                        }
                        break;
                    }
                    while(found==0)
                    {
                        temp=head;
                        while(temp!=NULL)
                        {
                            if(temp->gettype()==input)
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
                            found=1;
                            n='0';
                        }
                        else
                        {
                            cout<<"未找到符合的记录，请重新输入（返回输入0）"<<endl;
                            cin>>input;
                            if(input=="0")
                            {
                                found=1;
                                cout<<"按信息查询：（退出请输0）"<<endl;
                                cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                                cin>>n;
                                while( n!='0'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6'&&n!='0' )
                                {
                                    cout<<"输入有误请重新输入。"<<endl;
                                    cin>>n;
                                }
                                break;
                            }
                        }
                    }
                    break;
                case '6':
                    found=0;
                    cout<<"请输入ISBN（退出输入0）：";
                    cin>>input;
                    if(input=="0")
                    {
                        cout<<"按信息查询：（退出请输0）"<<endl;
                        cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                        cin>>n;
                        while( n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6'&&n!='0' )
                        {
                            cout<<"输入有误请重新输入。"<<endl;
                            cin>>n;
                        }
                        break;
                    }
                    while(found==0)
                    {
                        temp=head;
                        while(temp!=NULL)
                        {
                            if(temp->getISBN()==input)
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
                            found=1;
                            n='0';
                        }
                        else
                        {
                            cout<<"未找到符合的记录，请重新输入（返回输入0）"<<endl;
                            cin>>input;
                            if(input=="0")
                            {
                                found=1;
                                cout<<"按信息查询：（退出请输0）"<<endl;
                                cout<<"1.图书编号\n2.书名\n3.作者\n4.出版社\n5.类别\n6.ISBN\n";
                                cin>>n;
                                while( n!='1'&&n!='2'&&n!='3'&&n!='4'&&n!='5'&&n!='6'&&n!='0' )
                                {
                                    cout<<"输入有误请重新输入。"<<endl;
                                    cin>>n;
                                }
                                break;
                            }
                        }
                    }
                    break;
                    default:break;
            }

        }


        return returnlist;
}
