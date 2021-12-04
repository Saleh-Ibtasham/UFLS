#include "outputdialogue.h"
#include "ui_outputdialogue.h"
#include <string>
#include <QString>

using namespace std;

string out;

Outputdialogue::Outputdialogue(const QString &str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Outputdialogue)
{
    ui->setupUi(this);
    //out = str.toStdString();
    ui->textEdit->setText(str);

}

Outputdialogue::~Outputdialogue()
{
    delete ui;
}
