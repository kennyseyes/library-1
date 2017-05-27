#ifndef A_MAINWINDOW_H
#define A_MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include "looksamename.h"
#include <QTableWidget>
#include <QTableWidgetItem>

namespace Ui {
class A_MainWindow;
}

class A_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit A_MainWindow(QWidget *parent = 0);
    ~A_MainWindow();
    bool judgeEmpty();
     void clearAll();
     void hide_findu();
     void show_findu();
     bool judgeEmpty_newu();
     void clear_newu();

signals:
   void send_users(user* users_head);


private slots:
    void on_b_add_clicked();
    
    void on_b_delete_clicked();
    
    //void on_b_add_clicked();

    void on_u_add_clicked();
    
    void on_u_delete_clicked();
    
    void on_u_find_clicked();
    
    void on_find_butn_clicked();

    void on_samename_clicked();

    void on_handon_clicked();

    void on_del_butn_clicked();

    void on_delete_list_clicked(const QModelIndex &index);

    void on_delall_butn_clicked();

    void on_pushButton_clicked();

private:
    Ui::A_MainWindow *ui;
};

#endif // A_MAINWINDOW_H
