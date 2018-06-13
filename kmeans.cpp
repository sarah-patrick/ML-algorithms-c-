/*
    Homework 1 A
    Machine Learning
    Sarah Patrick
*/

#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<cstring>
#include <time.h>

using namespace std;

int getData(double* sx, double* sy, int data_size);
int getNumClusters(int k, int data_size);
bool getClusters(int k, int data_size, double* sx, double* sy, double* cx, double* cy);
void showDatum(double* x, double* y, int data_size);
int argMin(int i, int k, double* sx_full, double* sy_full, double* cx, double* cy);
void printFinalClusters(int* A, int k, int data_size);
bool isNew(int t[], int i);             //isNew compares indices
bool isNew(int tx[], int ty[], int i);  //overload inNew for coordinates


int main()
{
    //initialize some things
    int k;                                      //number of clusters
    int data_size;                              //number of data points
    double* sx = new double[data_size];         //copy of x coordinates, changes
    double* sy = new double[data_size];         //copy of y coordinates, changes
    double* sx_full = new double[data_size];    //full x coordinates
    double* sy_full = new double[data_size];    //full y coordinates
    double* cx = new double[k];                 //holds cluster vectors (x coordinate)
    double* cy = new double[k];                 //holds cluster vectors (y coordinate)
    int* A = new int[data_size];                //holds the cluster number of a given data point
    data_size = 0;                              //must be assigned value after dynamic arrays declared
    k = 0;
    double meanx, meany;

    //==========TITLE SCREEN===========
    cout << "|=====================================|\n";
    cout << "|          K-Means Algorithm          |\n";
    cout << "|=====================================|\n";

    //get data size, get data
    while(data_size <= 0){data_size = getData(sx, sy, data_size);}

    memcpy(sx_full, sx, data_size * sizeof(double));
    memcpy(sy_full, sy, data_size * sizeof(double));

    //get num clusters
    while(k <= 0 || k > data_size){k = getNumClusters(k, data_size);}

    //allocate clusters
    while(!getClusters(k, data_size, sx, sy, cx, cy));

    //assigning initial clusters, where A[i] is the cluster number of data point i
    for(int i = 0; i < data_size; i++)
    {
        A[i] = argMin(i, k, sx_full, sy_full, cx, cy);
    }

    // running
    bool change = 1;
    int A_alt;
    //flag the first loop so change = TRUE is certain.
    //for(int i = 0; i < data_size; i++){A[i] = -1;}

    while(change)
    {
        change = 0;
        for(int i = 0; i < data_size; i++)
        {
            A_alt = argMin(i, k, sx_full, sy_full, cx, cy); //should pass the least costly group
            if(A_alt != A[i])
            {
                A[i] = A_alt;
                change = 1;
            }
        }

        //recalculation
        if(change)
        {
            for(int i = 0; i < k; i++)
            {
                meanx = 0;
                meany = 0;
                int c = 0;

                for(int j = 0; j < data_size; j++)
                {
                    if(A[j] == i) //if The associated cluster matches the current cluster
                    {
                        meanx += sx_full[j];
                        meany += sy_full[j];
                        c += 1;
                    }
                }
                cx[i] = meanx/c;
                cy[i] = meany/c;
            }
        }
    }

    printFinalClusters(A, k, data_size);


    //cleanup
    delete[] sx;
    delete[] sy;
    delete[] sx_full;
    delete[] sy_full;
    delete[] cx;
    delete[] cy;
    delete[] A;

    return 0;
}

int getData(double* sx, double* sy, int data_size)
{
    cout<< "Enter data manually or use stock data?\n";
    cout<< "1. Manually\n";
    cout<< "2. Use stock\n";
    int choice = 2;
    cin>> choice;

    switch(choice)
    {
    case 1:
        {
            cout<< "Please enter the number of of data points.\n";
            cin>> data_size;
            while(data_size <= 0)
            {
                cout<< "\nThat is not a valid size. Please re-enter the number of data points.\n";
                cin>> data_size;
            }

            for(int i = 0; i < data_size; i++)
            {
                cout<< "\nPlease enter the x coordinate for data point " << i+1 << ":    ";
                cin>> sx[i];
                cout<< "Please enter the y coordinate for data point " << i+1 << ":    ";
                cin>> sy[i];
            }
            break;
        }

        case 2:
        {
            cout<< "Implementing stock data.\n";
            data_size = 8;
            double x[] = {2, 2, 8, 5, 7, 6, 1, 4};
            double y[] = {10, 5, 4, 8, 5,4, 2, 9};
            memcpy(sx, x, data_size * sizeof(double));
            memcpy(sy, y, data_size * sizeof(double));

            break;
        }
        default:
        {
            cout<< "You have entered an invalid choice.";
            break;
        }

    }
    return data_size;
}

int getNumClusters(int k, int data_size)
{
    cout<< "\nPlease enter the number of clusters:    ";
    cin>> k;
    if(k > data_size)
        cout<< "\nk cannot be greater than than the number of datum.\n";

    return k;
}

bool getClusters(int k, int data_size, double* sx, double* sy, double* cx, double* cy)
{
    bool flag = 0;
    int choice;
    cout<< "Enter Clusters manually or assign randomly?\n";
    cout<< "1. Manually\n";
    cout<< "2. Randomly between data\n";
    cout<< "3. Randomly in space\n";
    cin>> choice;

    switch(choice)
    {
    case 1:
        {
            int tVal; //temp value for holding data;
            for(int i = 0; i < k; i++)
            {
                cout<< "\nPlease select the data point for cluster " << i+1 << ". ";
                showDatum(sx, sy, data_size);
                cout<<endl<<endl;
                cin>> tVal;
                if(0 <= tVal && tVal < data_size)
                {
                    //assign cluster
                    cx[i] = sx[tVal];
                    cy[i] = sy[tVal];
                    //mark data from sx and sy as being chosen as a cluster already
                    sx[tVal] = -1;
                    sy[tVal] = -1;
                }
            }
            flag = 1; //done
            break;
        }
        case 2:
        {
            int t[data_size];
            int tVal;
            srand(time(NULL));
            for(int i = 0; i < k; i++)
            {
                t[i] = rand() % data_size;  //0 to data_size-1
                if(i == 0)
                {
                    //assign cluster
                    tVal = t[i];
                    cx[i] = sx[tVal];
                    cy[i] = sy[tVal];
                }
                else if(isNew(t, i))
                {
                    //assign cluster
                    tVal = t[i];
                    cx[i] = sx[tVal];
                    cy[i] = sy[tVal];
                }
                else{i = i-1;}    //Picked same data point, re-roll

            }
            flag = 1;
            break;
        }
        case 3:
        {
            int tx[data_size], ty[data_size];
            int tValx, tValy;
            srand(time(NULL));
            cout << "\n Randomly from \n\t1. 0,0 to 10,10\n\tor\n\t2. 0,0 to 15,15?\n";
            int rand_type;
            cin >> rand_type;
            for(int i = 0; i < k; i++)
            {
                if(rand_type == 1)
                   {
                        tx[i] = rand() % 10 + 1;  //0 to 10
                        ty[i] = rand() % 10 + 1;  //0 to 10
                   }
                else if(rand_type == 2)
                {
                    tx[i] = rand() % 15 + 1;  //0 to 15
                    ty[i] = rand() % 15 + 1;  //0 to 15
                }
                else
                    {return 0;}

                if(i == 0)
                {
                    //assign cluster
                    tValx = tx[i];
                    tValy = ty[i];
                    cx[i] = tValx;
                    cy[i] = tValy;
                }
                else if(isNew(tx, ty, i))
                {
                    //assign cluster
                    tValx = tx[i];
                    tValy = ty[i];
                    cx[i] = tValx;
                    cy[i] = tValy;
                }
                else{i = i-1;}    //Picked same data point, re-roll

                //cout<<"for iteration "<<i<<" the centerpoint is: "<<cx[i]<<" "<<cy[i]<<endl;
            }
            flag = 1;
            break;
        }
        default:
        {
            cout<< "You have entered an invalid choice.";
            break;
        }
    }

    return flag;
}

// Shows the datum for 2D coordinates based on two pointer-arrays passed.
// It's used by getClusters. A value of -1 indicates an unlisted point.
void showDatum(double* x, double* y, int data_size)
{
    cout<< "The datum are:\n";
    for(int i = 0; i < data_size; i++)
    {
        if(x[i] == -1 || y[i] == -1)
        {
            cout<< "       n/a\n";
        }
        else
        {
            cout<< i << ":    <" << x[i] << ", " << y[i] << ">\n";
        }

    }
    return;
}

int argMin(int i, int k, double* sx_full, double* sy_full, double* cx, double* cy)
{
    double temp;
    int miniCluster;
    double p = -1;     // -1 to flag first loop
    for(int j = 0; j < k; j++)
    {
        temp = (fabs(sx_full[i] - cx[j])) + (fabs(sy_full[i] - cy[j]));
        if(j == 0)
        {
            p = temp;
            miniCluster = j;
        }
        if(temp < p)
        {
            p = temp;
            miniCluster = j;
        }
    }
    return miniCluster;
}

void printFinalClusters(int* A, int k, int data_size)
{
    for(int i = 0; i < k; i++)
    {
        cout<< "Cluster " << i+1 <<":  {";
        for(int j = 0; j < data_size; j++)
        {
            if(A[j] == i)
            cout<< " A" << j+1 <<" ";
        }
        cout<< "}\n\n";
    }
    return;
}

bool isNew(int t[], int i)
{
    bool is_new = 1;   //true, is new
    for(int j = i-1; j >= 0; j--)
    {
        if(t[j] == t[i])
        {
            is_new = 0; //if not new, return false
        }
    }
    return is_new;
}

bool isNew(int tx[], int ty[], int i)
{
    bool is_new = 1;   //true, is new
    for(int j = i-1; j >= 0; j--)
    {
        if(tx[j] == tx[i] && ty[j] == ty[i])
        {
            is_new = 0; //if both coordinates are not new, return false
        }
    }
    return is_new;
}
