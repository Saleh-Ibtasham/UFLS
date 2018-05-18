#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>


using namespace std;

int numberOfFacility,numberOfDemandPointsIterative;
double **costMat,*allocationCostMat;

vector < pair < int , double > > facilityRank;

vector <int> *allocatedSites;

double *totalCostOfFacility;
int *demandPoint_is_allocated_iterative;

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

void readfileForSetCover()
{
    ifstream iFile;
    iFile.open("p2.txt");
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
    cout << "Demand Point " << x+1 << " wil be served by facility " << located_facilities[place]+1 << endl;
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
    cout << endl;
    cout << "The located facilities are:" << endl;
    for(int i=0; i<numberOfFacility; i++)
        if(is_finally_located[i] == 1)
            cout << i+1 << endl;
    cout << endl;
    for(int i=0; i<finally_located_facilities.size(); i++)
        computeSum += allocationCostMat[finally_located_facilities[i]];
    cout << "The Optimal Value: " << computeSum << endl;
}

int main()
{
    readfileForSetCover();
    computeMedianDistance();
    allocateInitiallyFilteredSites();
    computeCostOfFacility();
    computeObjectiveFunction();
    computeCost();
    return 0;
}
