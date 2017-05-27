#ifndef LOOKSAMENAME_H
#define LOOKSAMENAME_H
#include "user.h"
#include <QDialog>

namespace Ui {
class looksamename;
}

class looksamename : public QDialog
{
    Q_OBJECT

public:
    explicit looksamename(QWidget *parent = 0);
    ~looksamename();
private slots:
    void rece_uhead(user*uh);
private:
    Ui::looksamename *ui;
};

#endif // LOOKSAMENAME_H
