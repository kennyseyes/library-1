#ifndef U_MAINWINDOW_H
#define U_MAINWINDOW_H

#include <QMainWindow>
#include <change_password.h>
#include <borrow_book_form.h>
#include "user.h"
#include <showbookfound.h>
#include <QListWidgetItem>

namespace Ui {
class u_MainWindow;
}

class u_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit u_MainWindow(QWidget *parent = 0);
    ~u_MainWindow();

signals:
    void send_bookhead(book* book_head);
    void send_userhead(user* user_head);
    void send_curuser(user* cur_user);

private slots:
    //void on_exit_clicked();

    void on_changepw_clicked();
    void rece_bookhead(book * bh);
    void rece_userhead(user* uh);
    void rece_curuser(user* cu);
    void on_form_in_clicked();

    void on_search_clicked();

    void on_return_2_clicked();

    void on_search_2_clicked();

    void on_debt_clicked();

    void on_permission_clicked();

    void on_pushButton_clicked();

    void on_showresult_itemDoubleClicked(QListWidgetItem *item);

    void on_borrow_clicked();

    void on_return_3_clicked();

    void on_pay_clicked();

    void on_exit_clicked();

    void on_reserve_clicked();

    void on_search_3_clicked();

    void on_showresult_2_itemClicked(QListWidgetItem *item);

    void on_reserve_2_clicked();

    void on_cancel_clicked();

    void on_showbook_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::u_MainWindow *ui;
    change_password *changepw;
    borrow_book_form *form;
    showbookfound *showbook;


};

#endif // U_MAINWINDOW_H
