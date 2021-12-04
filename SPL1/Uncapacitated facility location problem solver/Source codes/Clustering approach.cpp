#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

double **mat;
int *visit;
double **facility;
double **clust;
vector <int> *myv;
int facilities,demand_points,k;

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

void readfile()
{
    ifstream iFile;
    iFile.open("pmed1.txt");
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
        cout << "Demand point " << mat[i][0] << " " << mat[i][1] << " is serverd by facility " << clust[x][0] << " " << clust[x][1] << endl;
        totalCost += sqrt((clust[x][0]-mat[i][0])*(clust[x][0]-mat[i][0]) + (clust[x][1]-mat[i][1])*(clust[x][1]-mat[i][1]));
    }
    cout << endl;
    cout << "The Optimum Value: " << totalCost << endl;
}

void print_facility()
{
    cout << endl;
    cout << "The allocated facilities:" << endl << endl;
    for(int i=0; i<k; i++)
        if(is_finally_allocated[i] == 1)
            cout << clust[i][0] << " " << clust[i][1] << endl;
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

int main()
{
    readfile();
    clustering();
    reverse_greedy();
    print_allocation();
    print_facility();
    memoryclear();
    return 0;
}
