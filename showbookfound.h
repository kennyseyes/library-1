#ifndef SHOWBOOKFOUND_H
#define SHOWBOOKFOUND_H

#include <QDialog>


namespace Ui {
class showbookfound;
}

class showbookfound : public QDialog
{
    Q_OBJECT

public:
    explicit showbookfound(QWidget *parent = 0);
    ~showbookfound();

private:
    Ui::showbookfound *ui;
};

#endif // SHOWBOOKFOUND_H
