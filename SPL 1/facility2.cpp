#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

int numberOfFacility,numberOfDemandPoints;
double **costMat,*allocationCostMat;

vector < pair < int , double > > facilityRank;

vector <int> *allocatedSites;

double *totalCostOfFacility;
int *demandPoint_is_allocated;

void makemat()
{
    allocatedSites = new vector<int>[numberOfFacility];
    costMat = new double*[numberOfDemandPoints];
    for(int i=0; i<numberOfDemandPoints; i++)
        costMat[i] = new double[numberOfFacility];
    allocationCostMat = new double[numberOfFacility];
    totalCostOfFacility = new double[numberOfFacility];
    demandPoint_is_allocated = new int[numberOfDemandPoints];
}

void readfile()
{
    ifstream iFile;
    iFile.open("p2.txt");
    iFile >> numberOfFacility >> numberOfDemandPoints;
    makemat();
    for(int i=0; i<numberOfDemandPoints; i++)
        for(int j=0; j<numberOfFacility; j++)
            iFile >> costMat[i][j];

    for(int i=0; i<numberOfDemandPoints; i++)
        iFile >> allocationCostMat[i];
}

void computeMedianDistance()
{
    for(int i=0; i<numberOfFacility; i++)
    {
        int arr[numberOfDemandPoints];
        int sum = 0;
        for(int j=0; j<numberOfDemandPoints; j++)
        {
            arr[j] = costMat[j][i];
            sum += costMat[j][i];
        }
        sort(arr,arr+numberOfDemandPoints);

        double average = (sum*1.0/numberOfDemandPoints*1.0);

        double rankingDistance;

        if(numberOfDemandPoints%2)
            rankingDistance = arr[numberOfDemandPoints/2];
        else
            rankingDistance = (arr[numberOfDemandPoints/2] + arr[numberOfDemandPoints/2 - 1])/2.0;

        if(rankingDistance > average)
            rankingDistance = average;

        facilityRank.push_back(make_pair(i,rankingDistance));
    }
    for(int i=0; i<facilityRank.size(); i++)
        cout << facilityRank[i].first << " " << facilityRank[i].second << endl;

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
    for(int i=0; i<numberOfDemandPoints; i++)
        demandPoint_is_allocated[i] = 0;

    for(int i=0; i<numberOfFacility; i++)
    {
        for(int j=0; j<numberOfDemandPoints; j++)
        {
            if((double)costMat[j][i] < facilityRank[i].second)
            {
                allocatedSites[i].push_back(j);
                demandPoint_is_allocated[j] = 1;
            }
        }
    }

    computeCostOfFacility();

    for(int i=0; i<numberOfDemandPoints; i++)
        if(demandPoint_is_allocated[i] == 0)
        {
            int k = shortestDistancedFacility(i);
            allocatedSites[k].push_back(i);
            demandPoint_is_allocated[i] = 1;
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
            if(demandPoint_is_allocated[allocatedSites[i][j]] == 1)
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
        demandPoint_is_allocated[allocatedSites[x][i]] = 1;
}

void updateFacilities()
{
    for(int i=0; i < numberOfDemandPoints; i++)
    {
        if(demandPoint_is_allocated[i] == 1)
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

vector < int > located_facilities;

void computeObjectiveFunction()
{
    for(int i=0; i<numberOfDemandPoints; i++)
        demandPoint_is_allocated[i] = 0;
    int allocationNumber = 0;
    while(allocationNumber < numberOfDemandPoints)
    {
        int x = findLeastCost(allocationNumber);
        located_facilities.push_back(x);
        allocationNumber += allocatedSites[x].size();
        updateDemandPoints(x);
        updateFacilities();
    }
}

int findMinimum(int x)
{
    int minimum = costMat[x][located_facilities[0]];
    int place;
    for(int i=0; i<located_facilities.size(); i++)
    {
        if(minimum < costMat[x][located_facilities[i]])
        {
            minimum = costMat[x][located_facilities[i]];
            place = i;
        }
    }
    cout << "Demand Point " << x << " wil be served by facility " << located_facilities[place] << endl;
    return minimum;
}

void computeCost()
{
    int computeSum=0;
    for(int i=0; i<located_facilities.size(); i++)
        cout << located_facilities[i] << " ";
    cout << endl;
    for(int i=0; i<located_facilities.size(); i++)
        computeSum += allocationCostMat[located_facilities[i]];
    for(int i=0; i<numberOfDemandPoints; i++)
    {
        int x = findMinimum(i);
        computeSum += x;
    }
    cout << "The Optimal Value is: " << computeSum << endl;
}

int main()
{
    readfile();
    computeMedianDistance();
    allocateInitiallyFilteredSites();
    computeCostOfFacility();
    computeObjectiveFunction();
    computeCost();

    return 0;
}
