#ifndef U_MAINWINDOW_H
#define U_MAINWINDOW_H

#include <QMainWindow>
#include <change_password.h>
#include <borrow_book_form.h>
#include "user.h"

namespace Ui {
class u_MainWindow;
}

class u_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit u_MainWindow(QWidget *parent = 0);
    ~u_MainWindow();

private slots:
    //void on_exit_clicked();

    void on_changepw_clicked();
    void rece_bookhead(book * bh);
    void rece_userhead(user* uh);
    void rece_curuser(user* cu);
    void on_form_in_clicked();

private:
    Ui::u_MainWindow *ui;
    change_password *changepw;
    borrow_book_form *form;

};

#endif // U_MAINWINDOW_H
