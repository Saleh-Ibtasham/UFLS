#ifndef ITERATIVE_H
#define ITERATIVE_H

#include <QDialog>

namespace Ui {
class Iterative;
}

class Iterative : public QDialog
{
    Q_OBJECT

public:
    explicit Iterative(QWidget *parent = 0);
    ~Iterative();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Iterative *ui;
};

#endif // ITERATIVE_H
