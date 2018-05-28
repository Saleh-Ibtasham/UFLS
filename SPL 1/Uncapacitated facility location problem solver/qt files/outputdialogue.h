#ifndef OUTPUTDIALOGUE_H
#define OUTPUTDIALOGUE_H

#include <QDialog>

namespace Ui {
class Outputdialogue;
}

class Outputdialogue : public QDialog
{
    Q_OBJECT

public:
    explicit Outputdialogue(const QString &str,QWidget *parent = 0);
    ~Outputdialogue();

private:
    Ui::Outputdialogue *ui;
};

#endif // OUTPUTDIALOGUE_H
