#Include <iostream>
#include <fstream>

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

vector < pair < int , int > > ranked_list;

int computeTotalDistance(int x)
{
    int sum=0;
    for(int i=0; i<numberOfDemandPoints; i++)
        sum += costMat[i][x];
    return sum;
}

void rankFacilities()
{
    for(int i=0; i<numberOfFacility; i++)
    {
        int x = computeTotalDistance(i);
        ranked_list.push_back(make_pair(x,i));
    }
    sort(ranked_list.begin(), ranked_list.end());
}

void computeOptimumValue()
{
    int n = numberOfFaclity/2;
    int stage_tolerance = 0;
    double optimum_value = pow(2,63) - 10;
    int numberOfValidFacility = 0;
    for(int i=1; i<=n; i++)
    {
        double data[i];
        double present_value = combinationUtility(data,0,numberOfFacility-1,0,i);
        if(present_value < optimum_value)
        {
            optimum_value = present_value;
            numberOfValidFacility = i;
        }
    }
}

int main()
{
    readfile();
    rankFacilities();
    computeOptimumValue();

    return 0;
}
