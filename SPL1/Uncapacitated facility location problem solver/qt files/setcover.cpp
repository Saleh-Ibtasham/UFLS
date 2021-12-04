#include "setcover.h"
#include "ui_setcover.h"
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

int numberOfFacility,numberOfDemandPointsIterative;
double **costMat,*allocationCostMat;

vector < pair < int , double > > facilityRank;

vector <int> *allocatedSites;

double *totalCostOfFacility;
int *demandPoint_is_allocated_iterative;

SetCover::SetCover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetCover)
{
    ui->setupUi(this);
}

SetCover::~SetCover()
{
    delete ui;
}

void makematForSetCover()
{
    allocatedSites = new vector<int>[numberOfFacility];
    costMat = new double*[numberOfDemandPointsIterative];
    for(int i=0; i<numberOfDemandPointsIterative; i++)
        costMat[i] = new double[numberOfFacility];
    allocationCostMat = new double[numberOfFacility];
    totalCostOfFacility = new double[numberOfFacility];
    demandPoint_is_allocated_iterative = new int[numberOfDemandPointsIterative];
}

void readfileForSetCover(string filename)
{
    ifstream iFile;
    const char *filename1 = filename.c_str();
    iFile.open(filename1);
    iFile >> numberOfFacility >> numberOfDemandPointsIterative;
    makematForSetCover();
    for(int i=0; i<numberOfDemandPointsIterative; i++)
        for(int j=0; j<numberOfFacility; j++)
            iFile >> costMat[i][j];

    for(int i=0; i<numberOfDemandPointsIterative; i++)
        iFile >> allocationCostMat[i];
}

void computeMedianDistance()
{
    for(int i=0; i<numberOfFacility; i++)
    {
        int arr[numberOfDemandPointsIterative];
        int sum = 0;
        for(int j=0; j<numberOfDemandPointsIterative; j++)
        {
            arr[j] = costMat[j][i];
            sum += costMat[j][i];
        }
        sort(arr,arr+numberOfDemandPointsIterative);

        double average = (sum*1.0/numberOfDemandPointsIterative*1.0);

        double rankingDistance;

        if(numberOfDemandPointsIterative%2)
            rankingDistance = arr[numberOfDemandPointsIterative/2];
        else
            rankingDistance = (arr[numberOfDemandPointsIterative/2] + arr[numberOfDemandPointsIterative/2 - 1])/2.0;

        if(rankingDistance > average)
            rankingDistance = average;

        facilityRank.push_back(make_pair(i,rankingDistance));
    }
    /*for(int i=0; i<facilityRank.size(); i++)
        cout << facilityRank[i].first << " " << facilityRank[i].second << endl;*/

}

int shortestDistancedFacility(int i)
{
    double minimum = costMat[i][0] + totalCostOfFacility[0];
    int x=0;
    for(int j=0; j<numberOfFacility; j++)
    {
        if((totalCostOfFacility[j]+costMat[i][j]) < minimum)
        {
            minimum = costMat[i][j] + totalCostOfFacility[j];
            x = j;
        }
    }
    return x;
}

void computeCostOfFacility()
{
    for(int i=0; i<numberOfFacility; i++)
    {
        double sum=allocationCostMat[i];
        int l = allocatedSites[i].size();
        for(int j=0; j<l; j++)
            sum += costMat[allocatedSites[i][j]][i];
        totalCostOfFacility[i] = sum;
    }
}

void allocateInitiallyFilteredSites()
{
    for(int i=0; i<numberOfDemandPointsIterative; i++)
        demandPoint_is_allocated_iterative[i] = 0;

    for(int i=0; i<numberOfFacility; i++)
    {
        for(int j=0; j<numberOfDemandPointsIterative; j++)
        {
            if((double)costMat[j][i] < facilityRank[i].second)
            {
                allocatedSites[i].push_back(j);
                demandPoint_is_allocated_iterative[j] = 1;
            }
        }
    }

    computeCostOfFacility();

    for(int i=0; i<numberOfDemandPointsIterative; i++)
        if(demandPoint_is_allocated_iterative[i] == 0)
        {
            int k = shortestDistancedFacility(i);
            allocatedSites[k].push_back(i);
            demandPoint_is_allocated_iterative[i] = 1;
        }
    /*for(int i=0; i<numberOfFacility; i++)
    {
        for(int j=0; j<allocatedSites[i].size(); j++)
            cout << allocatedSites[i][j] << " ";
        cout << endl;
    }*/

}

int findLeastCost(int allocationNumber)
{
    int p;
    int minimum = pow(2, 31) - 10;
    for(int i=0;i < numberOfFacility; i++)
    {
        int y=0;
        int setsize = allocatedSites[i].size();
        int sum=0;
        for(int j=0; j<setsize; j++)
            if(demandPoint_is_allocated_iterative[allocatedSites[i][j]] == 1)
                sum++;
        y = setsize - sum;
        int x;
        if(y)
            x = totalCostOfFacility[i]/y;
        else
            x = pow(2, 31) - 10;
        if(x < minimum)
        {
            minimum = x;
            p = i;
        }
    }
    return p;
}

void updateDemandPoints(int x)
{
    for(int i=0; i<allocatedSites[x].size(); i++)
        demandPoint_is_allocated_iterative[allocatedSites[x][i]] = 1;
}

void updateFacilities()
{
    for(int i=0; i < numberOfDemandPointsIterative; i++)
    {
        if(demandPoint_is_allocated_iterative[i] == 1)
        {
            for(int j=0; j<numberOfFacility; j++)
            {
                int place = -1;
                for(int k=0; k<allocatedSites[j].size(); k++)
                    if(allocatedSites[j][k] == i)
                    {
                        place = k;
                        break;
                    }
                if(place >= 0)
                    allocatedSites[j].erase(allocatedSites[j].begin()+place);
            }
        }
    }
}

vector < int > located_facilities,finally_located_facilities;
int *is_finally_located;

void computeObjectiveFunction()
{
    for(int i=0; i<numberOfDemandPointsIterative; i++)
        demandPoint_is_allocated_iterative[i] = 0;
    int allocationNumber = 0;
    while(allocationNumber < numberOfDemandPointsIterative)
    {
        int x = findLeastCost(allocationNumber);
        located_facilities.push_back(x);
        allocationNumber += allocatedSites[x].size();
        updateDemandPoints(x);
        updateFacilities();
    }
}

QString outputSet="";

int findMinimum(int x)
{
    int minimum = costMat[x][located_facilities[0]];
    int place;
    for(int i=0; i<located_facilities.size(); i++)
    {
        if(costMat[x][located_facilities[i]] < minimum)
        {
            minimum = costMat[x][located_facilities[i]];
            place = i;
        }
    }
    outputSet.append(QString("Demand Point %1 will be served by facility %2\n").arg(x+1).arg(located_facilities[place]+1));
    //cout << "Demand Point " << x+1 << " wil be served by facility " << located_facilities[place]+1 << endl;
    if(is_finally_located[located_facilities[place]] == 0)
    {
        finally_located_facilities.push_back(located_facilities[place]);
        is_finally_located[located_facilities[place]] = 1;
    }

    return minimum;
}

void computeCost()
{
    int computeSum=0;
    is_finally_located = new int[numberOfFacility];
    for(int i=0; i<numberOfFacility; i++)
        is_finally_located[i] = 0;
    for(int i=0; i<numberOfDemandPointsIterative; i++)
    {
        int x = findMinimum(i);
        computeSum += x;
    }
    //cout << endl;
    outputSet.append(QString("\n\n"));
    outputSet.append(QString("The located facilities:\n"));
    //cout << "The located facilities are:" << endl;
    for(int i=0; i<numberOfFacility; i++)
        if(is_finally_located[i] == 1)
            outputSet.append(QString("%1\n").arg(i+1));
            //cout << i+1 << endl;
    //cout << endl;
    outputSet.append(QString("\n"));
    for(int i=0; i<finally_located_facilities.size(); i++)
        computeSum += allocationCostMat[finally_located_facilities[i]];
    //cout << "The Optimal Value: " << computeSum << endl;
    outputSet.append(QString("The Optimal Value: %1").arg(computeSum));
}

void print_outputSetCover()
{
    Outputdialogue myDialogue(outputSet);
    myDialogue.setModal(true);
    myDialogue.exec();
}

void SetCover::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Pick a File"),"G:/git/Spl1/SPL 1/Uncapacitated facility location problem solver/qt files/uncapacitated instances/","Text File(*.txt)");
    string ss = filename.toStdString();
    readfileForSetCover(ss);
    computeMedianDistance();
    allocateInitiallyFilteredSites();
    computeCostOfFacility();
    computeObjectiveFunction();
    computeCost();
    print_outputSetCover();
    close();
}
