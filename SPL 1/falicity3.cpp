#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int numberOfFacility,numberOfDemandPoints;
double **costMat,*allocationCostMat;

vector < pair < int , double > > facilityRank;

vector <int> *allocatedSites;

double *totalCostOfFacility;
int *demandPoint_is_allocated;
vector <int> chosen_facility;
int *checked_facility;
int optimum_is_changed = 0;
double optimum_value = pow(2,63) - 10;

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

void printFacilities()
{
    cout << "The facilities chosen: " <<endl;
    for(int i=0; i<chosen_facility.size(); i++)
        cout << chosen_facility[i]+1 << endl;
    cout << endl;
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
            if(costMat[i][temporary[j]] < minimum)
            {
                minimum = costMat[i][temporary[j]];
                x=j;
            }
        if(x>-1)
            checked_facility[x] = 1;
        sum += minimum;
    }

    for(int i=0; i<clusterOfFacility; i++)
        if(checked_facility[i] == 1)
            sum+= allocationCostMat[temporary[i]];

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
    int n = numberOfFacility/2;
    int group_tolerance = 0, combination_tolerance = 0;
    for(int i=1; i<=n; i++)
    {
        combination_tolerance = 0;
        int temporary[i];
        combinationCompute(temporary,0,numberOfFacility-1,0,i,combination_tolerance);

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
    cout << "The Optimum Value is " << optimum_value << endl;
    cout << endl;
}

void printDemandPointAssignments()
{
    for(int i=0; i<numberOfDemandPoints; i++)
    {
        int minimum = 100000000;
        int x=-1;
        for(int j=0; j<chosen_facility.size(); j++)
            if(costMat[i][chosen_facility[j]] < minimum)
            {
                minimum = costMat[i][chosen_facility[j]];
                x = j;
            }
        cout << "Demand Point " << i+1 << " will be served by facility " << chosen_facility[x]+1 <<endl;
    }
}
int main()
{
    readfile();
    rankFacilities();
    /*for(int i=0; i<numberOfFacility; i++)
        cout << ranked_list[i].first << " " << ranked_list[i].second << endl;*/
    computeOptimumValue();
    printFacilities();
    printOptimum();
    printDemandPointAssignments();
    return 0;
}
