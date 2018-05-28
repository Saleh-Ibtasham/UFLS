#include "clusteringapproach.h"
#include "ui_clusteringapproach.h"
#include <QDebug>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <QFileDialog>
#include <string>
#include <outputdialogue.h>

using namespace std;

double **mat;
int *visit;
double **facility;
double **clust;
vector <int> *myv;
int facilities,demand_points,k;

clusteringApproach::clusteringApproach(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clusteringApproach)
{
    ui->setupUi(this);
}

clusteringApproach::~clusteringApproach()
{
    delete ui;
}

void makemat()
{
    mat = new double*[demand_points];
    facility = new double*[facilities];
    clust = new double*[k];
    visit = new int[facilities];
    for(int i=0; i<demand_points; i++)
        mat[i] = new double[2];
    for(int i=0; i<facilities; i++)
    {
        facility[i] = new double[2];
        visit[i] = 0;
    }
    for(int i=0; i<k; i++)
        clust[i] = new double[2];
    myv = new vector < int >[k];
}

void readfile(string filename)
{
    ifstream iFile;
    const char *filename1 = filename.c_str();
    iFile.open(filename1);
    iFile >> facilities >> demand_points >> k;
    makemat();
    for(int i=0; i<demand_points; i++)
        iFile >> mat[i][0] >> mat[i][1];
    for(int i=0; i<facilities; i++)
        iFile >> facility[i][0] >> facility[i][1];
}

void clustering()
{
    double init[k][2];

    for(int i=0; i<k; i++)
    {
        init[i][0] = facility[i][0];
        init[i][1] = facility[i][1];
    }

    for(int l=0; l<(demand_points+1) ; l++)
    {
        for(int i=0; i<k; i++)
            myv[i].clear();
        for(int i=0; i<demand_points; i++)
        {
            int x;
            double mini = pow(2,63) - 10;
            for(int j=0; j<k; j++)
            {
                double dis = sqrt((init[j][0]-mat[i][0])*(init[j][0]-mat[i][0]) + (init[j][1]-mat[i][1])*(init[j][1]-mat[i][1]));
                if(dis < mini)
                {
                    mini = dis;
                    x=j;
                }
            }
            myv[x].push_back(i);
        }
        for(int i=0; i<k; i++)
        {
            double sumx=0;
            double sumy=0;
            vector <int>::iterator it;
            for(it=myv[i].begin();it!=myv[i].end(); it++)
            {
                sumx+=mat[*it][0];
                sumy+=mat[*it][1];
            }
            if((sumx != 0.0) || (sumy != 0.0))
            {
                init[i][0] = sumx/myv[i].size();
                init[i][1] = sumy/myv[i].size();
            }
        }
    }

    for(int i=0; i<k; i++)
    {
        clust[i][0] = init[i][0];
        clust[i][1] = init[i][1];
    }
}

void reverse_greedy()
{
    for(int i=0; i<k; i++)
    {
        int x;
        double mini = pow(2,63) - 10;
        for(int j=0; j<facilities; j++)
        {
            double dis = sqrt((clust[i][0]-facility[j][0])*(clust[i][0]-facility[j][0]) + (clust[i][1]-facility[j][1])*(clust[i][1]-facility[j][1]));
            if((dis < mini)&&(visit[j] == 0))
            {
                mini = dis;
                x=j;
            }
        }
        clust[i][0] = facility[x][0];
        clust[i][1] = facility[x][1];
        visit[x] = 1;
    }
}

int *is_finally_allocated;
QString output = "";

void print_allocation()
{
    is_finally_allocated = new int[k];
    for(int i=0; i<k; i++)
        is_finally_allocated[i] = 0;
    double totalCost = 0;
    for(int i=0; i<demand_points; i++)
    {
        int x;
        double mini = pow(2,63) - 10;
        for(int j=0; j<k; j++)
        {
            double dis = sqrt((clust[j][0]-mat[i][0])*(clust[j][0]-mat[i][0]) + (clust[j][1]-mat[i][1])*(clust[j][1]-mat[i][1]));
            if(dis < mini)
            {
                mini = dis;
                x = j;
            }
        }
        is_finally_allocated[x] = 1;
        output.append(QString("Demand point %1 %2 is served by facility %3 %4\n").arg(mat[i][0]).arg(mat[i][1]).arg(clust[x][0]).arg(clust[x][1]));
        //cout << "Demand point " << mat[i][0] << " " << mat[i][1] << " is serverd by facility " << clust[x][0] << " " << clust[x][1] << endl;
        totalCost += sqrt((clust[x][0]-mat[i][0])*(clust[x][0]-mat[i][0]) + (clust[x][1]-mat[i][1])*(clust[x][1]-mat[i][1]));
    }
    output.append(QString("\n\n"));
    output.append(QString("The Optimum Value: %1\n\n").arg(totalCost));
    //cout << "The Optimum Value: " << totalCost << endl;
}

void print_facility()
{
    //cout << endl;
    //cout << "The allocated facilities:" << endl << endl;
    output.append(QString("The allocated facilities:\n\n"));
    for(int i=0; i<k; i++)
        if(is_finally_allocated[i] == 1)
            output.append(QString("%1 %2\n").arg(clust[i][0]).arg(clust[i][1]));
            //cout << clust[i][0] << " " << clust[i][1] << endl;
}

void memoryclear()
{
    delete [] visit;
    for(int i=0; i<demand_points; i++)
        delete [] mat[i];
    delete [] mat;
    for(int i=0; i<facilities; i++)
        delete [] facility[i];
    delete [] facility;
    for(int i=0; i<k; i++)
        delete [] clust[i];
    delete [] clust;
    delete [] is_finally_allocated;
}

void print_output()
{
    Outputdialogue myDialogue(output);
    myDialogue.setModal(true);
    myDialogue.exec();
}

void clusteringApproach::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Pick a File"),"G:/git/Spl1/SPL 1/Uncapacitated facility location problem solver/qt files/pmedian instances/","Text File(*.txt)");
    string ss = filename.toStdString();
    readfile(ss);
    clustering();
    reverse_greedy();
    print_allocation();
    print_facility();
    print_output();
    memoryclear();
    close();
}
