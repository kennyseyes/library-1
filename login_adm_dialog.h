#ifndef LOGIN_ADM_DIALOG_H
#define LOGIN_ADM_DIALOG_H

#include "a_mainwindow.h"

#include <QDialog>
#include <QMessageBox>
namespace Ui {
class login_adm_dialog;
}

class login_adm_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit login_adm_dialog(QWidget *parent = 0);
    ~login_adm_dialog();

private slots:
    void on_ok_Button_clicked();
    void clearAll();
    void on_returnButton_clicked();

private:
    Ui::login_adm_dialog *ui;
    A_MainWindow admin_mainwindow;

};

#endif // LOGIN_ADM_DIALOG_H
