#ifndef A_MAINWINDOW_H
#define A_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class A_MainWindow;
}

class A_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit A_MainWindow(QWidget *parent = 0);
    ~A_MainWindow();

private slots:
    void on_b_add_clicked();
    
    void on_b_delete_clicked();
    
    //void on_b_add_clicked();

    void on_u_add_clicked();
    
    void on_u_delete_clicked();
    
    void on_u_find_clicked();


    
private:
    Ui::A_MainWindow *ui;
};

#endif // A_MAINWINDOW_H
