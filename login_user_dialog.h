#ifndef LOGIN_USER_DIALOG_H
#define LOGIN_USER_DIALOG_H

#include "u_mainwindow.h"
#include "user.h"
#include <QTextCodec>
#include <QDialog>
#include <QMessageBox>


namespace Ui {
class login_user_dialog;
}

class login_user_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit login_user_dialog(QWidget *parent = 0);
    ~login_user_dialog();
    bool judgeEmpty();


signals:
    void send_bookhead(book* book_head);
    void send_userhead(user* user_head);
    void send_curuser(user* cur_user);

private slots:
    void on_login_Button_clicked();
    void on_return_Button_clicked();
    void clearAll();
    void login_ButtonSetSlot(QString);

private:
    Ui::login_user_dialog *ui;
    u_MainWindow u;
    login_user_dialog *loginu;
};

#endif // LOGIN_USER_DIALOG_H
