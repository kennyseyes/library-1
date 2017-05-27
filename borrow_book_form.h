#ifndef BORROW_BOOK_FORM_H
#define BORROW_BOOK_FORM_H
#include "book.h"
#include "user.h"
#include <QDialog>

namespace Ui {
class borrow_book_form;
}

class borrow_book_form : public QDialog
{
    Q_OBJECT

public:
    explicit borrow_book_form(QWidget *parent = 0);
    ~borrow_book_form();

private slots:
    void on_pushButton_2_clicked();
    void rece_bookhead(book * bh);
    void rece_userhead(user* uh);
    void rece_curuser(user* cu);
    void on_pushButton_clicked();

private:
    Ui::borrow_book_form *ui;
};

#endif // BORROW_BOOK_FORM_H
