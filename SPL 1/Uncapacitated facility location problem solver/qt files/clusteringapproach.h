#ifndef CLUSTERINGAPPROACH_H
#define CLUSTERINGAPPROACH_H

#include <QDialog>

namespace Ui {
class clusteringApproach;
}

class clusteringApproach : public QDialog
{
    Q_OBJECT

public:
    explicit clusteringApproach(QWidget *parent = 0);
    ~clusteringApproach();

private slots:
    void on_pushButton_clicked();

private:
    Ui::clusteringApproach *ui;
};

#endif // CLUSTERINGAPPROACH_H
