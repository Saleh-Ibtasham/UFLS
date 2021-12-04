#ifndef SETCOVER_H
#define SETCOVER_H

#include <QDialog>

namespace Ui {
class SetCover;
}

class SetCover : public QDialog
{
    Q_OBJECT

public:
    explicit SetCover(QWidget *parent = 0);
    ~SetCover();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SetCover *ui;
};

#endif // SETCOVER_H
