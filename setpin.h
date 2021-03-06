#ifndef SETPIN_H
#define SETPIN_H

#include <QDialog>
#include "twitter.h"
namespace Ui {
class setPIN;
}

class setPIN : public QDialog
{
    Q_OBJECT

public:
    explicit setPIN(QWidget *parent = 0);
    ~setPIN();
    void getTwitter();
    int checkPin;

private:
    Ui::setPIN *ui;
    Twitter *twitter;
private slots:
    void buttonOKClicked();
};

#endif // SETPIN_H
