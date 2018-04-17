#include <iostream>

using namespace std;

int numberOfFacility,numberOfDemandPoints;

int **costMat,*allocationCostMat;

void makemat()
{
    costMat = new int*[numberOfDemandPoints];
    for(int i=0; i<numberOfFacility; i++)
        costMat[i] = new int[numberOfFacility];
    allocationCostMat = new int[numberOfFacility];
}

void readfile()
{
    ifstream iFile;
    iFile.open("inp.txt");
    iFile >> numberOfFacility >> numberOfDemandPoints;
    makemat();
    for(int i=0; i<numberOfDemandPoints; i++)
        for(int j=0; j<numberOfFacility; j++)
            iFile >> costMat[i][j];
    for(int i=0; i<numberOFDemandPoints; i++)
        iFile >> allocationCostMat[i];
}

void computeMedianDistance()
{

}

int main()
{
    readfile();
    computeMedianDistance();

    return 0;
}
