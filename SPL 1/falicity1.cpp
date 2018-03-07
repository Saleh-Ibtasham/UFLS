#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

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
    iFile.open("input.txt");
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
        init[i][0] = facility[i][0];        init[i][1] = facility[i][1];
    }

    for(int l=0; l<(demand_points) ; l++)
    {
        for(int i=0; i<k; i++)
            myv[i].clear();
        for(int i=0; i<demand_points; i++)
        {
            int x;
            double mini = 10000;
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
            init[i][0] = sumx/myv[i].size();
            init[i][1] = sumx/myv[i].size();
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
        double mini = 10000;
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

void print_facility()
{
    for(int i=0; i<k; i++)
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
}

int main()
{
    readfile();
    clustering();
    reverse_greedy();
    print_facility();
    memoryclear();

    return 0;
}
