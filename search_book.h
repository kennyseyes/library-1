#ifndef SEARCH_BOOK_H
#define SEARCH_BOOK_H
#include "book.h"
class search_book
{
    public:
        search_book();
        book* SearchBook(book* head);//注意这个函数和类的区别！！！
        ~search_book();
};

#endif // SEARCH_BOOK_H
