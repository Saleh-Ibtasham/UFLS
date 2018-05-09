#Include <iostream>

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

void rankFacilities()
{

}

int main()
{
    readfile();
    rankFacilities();

    return 0;
}
