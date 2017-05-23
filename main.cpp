#include "chose_login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("logo.png"));
    chose_login choose;
    choose.show();

    return a.exec();
}
