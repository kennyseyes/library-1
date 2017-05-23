#ifndef CHOSE_LOGIN_H
#define CHOSE_LOGIN_H
#include "login_adm_dialog.h"
#include "login_user_dialog.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QDebug>
#include <QPalette>
#include <QButtonGroup>
#include <QMessageBox>
namespace Ui {
class chose_login;
}

class chose_login : public QDialog
{
    Q_OBJECT

public:
    explicit chose_login(QWidget *parent = 0);
    ~chose_login();


private slots:
    void on_admin_button_clicked();
    void on_user_button_clicked();


private:
    Ui::chose_login *ui;
    login_adm_dialog admin_login;
    login_user_dialog user_login;
};

#endif // CHOSE_LOGIN_H
