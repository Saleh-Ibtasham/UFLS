#include "iterative.h"
#include "ui_iterative.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <QDebug>
#include <QFileDialog>
#include <string>
#include <QString>
#include <outputdialogue.h>

using namespace std;

int numberOfFacilityIterative,numberOfDemandPoints;
double **costMatIterative,*allocationCostMatIterative;

vector < pair < int , double > > facilityRankIterative;

vector <int> *allocatedSitesIterative;

double *totalCostOfFacilityIterative;
int *demandPoint_is_allocated;
vector <int> chosen_facility;
int *checked_facility;
int optimum_is_changed = 0;
double optimum_value = pow(2,63) - 10;

Iterative::Iterative(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Iterative)
{
    ui->setupUi(this);
}

Iterative::~Iterative()
{
    delete ui;
}

void makematForIterative()
{
    allocatedSitesIterative = new vector<int>[numberOfFacilityIterative];
    costMatIterative = new double*[numberOfDemandPoints];
    for(int i=0; i<numberOfDemandPoints; i++)
        costMatIterative[i] = new double[numberOfFacilityIterative];
    allocationCostMatIterative = new double[numberOfFacilityIterative];
    totalCostOfFacilityIterative = new double[numberOfFacilityIterative];
    demandPoint_is_allocated = new int[numberOfDemandPoints];
}

void readfileForIterative(string filename)
{
    ifstream iFile;
    const char *filename1 = filename.c_str();
    iFile.open(filename1);
    iFile >> numberOfFacilityIterative >> numberOfDemandPoints;
    makematForIterative();
    for(int i=0; i<numberOfDemandPoints; i++)
        for(int j=0; j<numberOfFacilityIterative; j++)
            iFile >> costMatIterative[i][j];

    for(int i=0; i<numberOfDemandPoints; i++)
        iFile >> allocationCostMatIterative[i];
}

vector < pair < int , int > > ranked_list;

int computeTotalDistance(int x)
{
    int sum=0;
    for(int i=0; i<numberOfDemandPoints; i++)
        sum += costMatIterative[i][x];
    return sum;
}

void rankFacilities()
{
    for(int i=0; i<numberOfFacilityIterative; i++)
    {
        int x = computeTotalDistance(i);
        ranked_list.push_back(make_pair(x,i));
    }
    sort(ranked_list.begin(), ranked_list.end());
}

QString outputIt = "";

void printFacilities()
{
    //cout << "The facilities chosen: " <<endl;
    outputIt.append(QString("The facilities chosen: \n"));
    for(int i=0; i<chosen_facility.size(); i++)
        outputIt.append(QString("%1\n").arg(chosen_facility[i]+1));
        //cout << chosen_facility[i]+1 << endl;
    //cout << endl;
    outputIt.append(QString("\n"));
}

double checkVal(int temporary[], int clusterOfFacility)
{
    double sum = 0;
    checked_facility = new int[clusterOfFacility];
    for(int i=0; i<clusterOfFacility; i++)
        checked_facility[i] = 0;
    for(int i=0; i<numberOfDemandPoints; i++)
    {
        int minimum = 100000000;
        int x = -1;
        for(int j=0; j<clusterOfFacility; j++)
            if(costMatIterative[i][temporary[j]] < minimum)
            {
                minimum = costMatIterative[i][temporary[j]];
                x=j;
            }
        if(x>-1)
            checked_facility[x] = 1;
        sum += minimum;
    }

    for(int i=0; i<clusterOfFacility; i++)
        if(checked_facility[i] == 1)
            sum+= allocationCostMatIterative[temporary[i]];

    return sum;
}

void combinationCompute(int temporary[], int firstEntry, int lastEntry, int index, int clusterOfFacility, int &combination_tolerance)
{
    if(index == clusterOfFacility)
    {
        double value = checkVal(temporary,clusterOfFacility);
        if(optimum_value > value)
        {
            chosen_facility.clear();
            optimum_value = value;
            for(int i=0; i<clusterOfFacility; i++)
                if(checked_facility[i] == 1)
                    chosen_facility.push_back(temporary[i]);
            if(combination_tolerance)
                combination_tolerance--;
            optimum_is_changed = 1;
        }
        else
            combination_tolerance++;
        delete [] checked_facility;
        return;
    }
    for(int i=firstEntry; (i<=lastEntry) && ((lastEntry-i+1) >= (clusterOfFacility-index)); i++)
    {
        temporary[index] = ranked_list[i].second;
        combinationCompute(temporary, i+1, lastEntry, index+1, clusterOfFacility, combination_tolerance);
        if(combination_tolerance > 10)
        {
            combination_tolerance = 0;
            break;
        }
    }
    return;
}

void computeOptimumValue()
{
    int n = numberOfFacilityIterative/2;
    int group_tolerance = 0, combination_tolerance = 0;
    for(int i=1; i<=n; i++)
    {
        combination_tolerance = 0;
        int temporary[i];
        combinationCompute(temporary,0,numberOfFacilityIterative-1,0,i,combination_tolerance);

        if(optimum_is_changed)
        {
            if(group_tolerance)
                group_tolerance--;
            optimum_is_changed = 0;
        }
        else
            group_tolerance++;
        if(i == 10)
            break;
        if(group_tolerance == 5)
            break;
    }
}

void printOptimum()
{
    //cout << "The Optimum Value: " << optimum_value << endl;
    outputIt.append(QString("The Optimum Value: %1\n\n").arg(optimum_value));
    //cout << endl;
}

void printDemandPointAssignments()
{
    for(int i=0; i<numberOfDemandPoints; i++)
    {
        int minimum = 100000000;
        int x=-1;
        for(int j=0; j<chosen_facility.size(); j++)
            if(costMatIterative[i][chosen_facility[j]] < minimum)
            {
                minimum = costMatIterative[i][chosen_facility[j]];
                x = j;
            }
        outputIt.append(QString("Demand Point %1 will be served by facility %2\n").arg(i+1).arg(chosen_facility[x]+1));
        //cout << "Demand Point " << i+1 << " will be served by facility " << chosen_facility[x]+1 <<endl;
    }
    outputIt.append(QString("\n"));
    //cout << endl;
}

void print_outputIterative()
{
    Outputdialogue mydialogue(outputIt);
    mydialogue.setModal(true);
    mydialogue.exec();
}

void Iterative::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Pick a File"),"G:/git/Spl1/SPL 1/Uncapacitated facility location problem solver/qt files/uncapacitated instances/","Text File(*.txt)");
    string ss = filename.toStdString();
    readfileForIterative(ss);
    rankFacilities();
    /*for(int i=0; i<numberOfFacility; i++)
        cout << ranked_list[i].first << " " << ranked_list[i].second << endl;*/
    computeOptimumValue();
    printDemandPointAssignments();
    printFacilities();
    printOptimum();
    print_outputIterative();
    close();
}
