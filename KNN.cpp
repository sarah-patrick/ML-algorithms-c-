// Homework 2, part 1
// Sarah Patrick


#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cmath>
#include<cstring>
#include<string>
#include <time.h>

using namespace std;

struct iris
{
    double sepal_len;
    double sepal_width;
    double petal_len;
    double petal_width;
    int type;
};

void getData(iris* training);
void getTestData(iris* unknown);
void getMinMax(const int TRAINING_SIZE, const int UNKNOWN_SIZE, iris* training, iris* unknown, double &mi1, double &ma1, double &mi2, double &ma2, double &mi3, double &ma3, double &mi4, double &ma4);
void normalizeData(const int TRAINING_SIZE, const int UNKNOWN_SIZE, iris* training, iris* unknown);
double findDistance(int i, int j, iris* unknown, iris* training);


int main()
{
    //arrays to hold training and test data.
    const int TRAINING_SIZE = 147;
    const int UNKNOWN_SIZE = 3;
    iris* training = new iris[TRAINING_SIZE]();
    iris* unknown = new iris[UNKNOWN_SIZE]();

    //==========TITLE SCREEN===========
    cout << "|=====================================|\n";
    cout << "|                 KNN                 |\n";
    cout << "|=====================================|\n";

    //get data
    getData(training);
    getTestData(unknown);

    //normalize things
    normalizeData(TRAINING_SIZE, UNKNOWN_SIZE, training, unknown);

    //predictions
    cout << "\n\n KNN Results: \n\t1 neighbor: ";
    double d, first;
    double maximum = 0;
    for( int i = 0; i < UNKNOWN_SIZE; i++ )
    {
        //find the nearest data point considering 4 factors
        for( int j = 0; j < TRAINING_SIZE; j++ )
        {
            d = findDistance( i, j, unknown, training );
            //cout << "\n D for iteration " << j << "is " << d;
            if( j == 0 )
                {
                    first = d;
                    //cout << "\nUnknown point " << i <<"'s old type: " << unknown[i].type;
                    unknown[i].type = training[j].type;
                    //cout << "\nUnknown point " << i <<"'s new type: " << unknown[i].type;
                }
            else
            {
                //find distance between unknown and training
                if( d < first )
                {
                    first = d;
                    //cout << "\nUnknown point " << i <<"'s old type: " << unknown[i].type;
                    unknown[i].type = training[j].type;
                    //cout << "\nUnknown point " << i <<"'s new type: " << unknown[i].type;
                }
                if( d > maximum )
                {
                    maximum = d;
                }
            }
        }
        //cout<<"\nThe closest type is: " <<unknown[i].type;
        cout << "\n\t\tPoint " << i+1 << "'s classification is ";
        if( unknown[i].type == 1 ){ cout << "Iris-setosa."; }
        if( unknown[i].type == 2 ){ cout << "Iris-versicolor."; }
        if( unknown[i].type == 3 ){ cout << "Iris-virginica."; }
    }


    cout << "\n\t3 neighbors: ";
    double second, third;
    int type1, type2, type3;
    for( int i = 0; i < UNKNOWN_SIZE; i++ )
    {
        first = maximum;
        second = maximum;
        third = maximum;
        //find the nearest data point considering 4 factors
        for( int j = 0; j < TRAINING_SIZE; j++ )
        {
            //cout<<"\tj is : " << j;
            //find distance between unknown and training
            d = findDistance(i, j, unknown, training);
            //compare to see if it is less
            if( d < first )
            {
                third = second;
                second = first;
                first = d;
                type3 = type2;
                type2 = type1;
                type1 = training[j].type;
                //cout<<"\nType 1 for "<<i<<" is: " <<type1;
                //cout<<"\nFirst updated on training point " << j;
            }
            else if( d < second && d != first )
            {
                third = second;
                second = d;
                type3 = type2;
                type2 = training[j].type;
                //cout<<"\nType 2 for "<<i<<" is: " <<type2;
                //cout<<"\nSecond updated on training point " << j;
            }
            else if( d < third && d != first && d != second )
            {
                third = d;
                type3 = training[j].type;
                //cout<<"\nType 3 for "<<i<<" is: " <<type3;
                //cout<<"\nThird updated on training point " << j;
            }
        }

        cout<<"\nType 1 is: " <<type1;
        cout<<"\nType 2 is: " <<type2;
        cout<<"\nType 3 is: " <<type3;
        if( type1 == type2 )                      { unknown[i].type = type1; }
        if( type2 == type3 || type1 == type3 )    { unknown[i].type = type3; }
        if( type1 != type2 != type3 )             { unknown[i].type = type1; }

        cout << "\n\t\tPoint " << i+1 << "'s classification is ";
        if( unknown[i].type == 1 ){ cout << "Iris-setosa."; }
        if( unknown[i].type == 2 ){ cout << "Iris-versicolor."; }
        if( unknown[i].type == 3 ){ cout << "Iris-virginica."; }
    }

    cout << "\n\t5 neighbors: ";
    //5 neighbors:
    double fourth, fifth;
    int type4, type5;
    for( int i = 0; i < UNKNOWN_SIZE; i++ )
    {
        first = maximum;
        second = maximum;
        third = maximum;
        fourth = maximum;
        fifth = maximum;
        //find the nearest data point considering 4 factors
        for( int j = 0; j < TRAINING_SIZE; j++ )
        {
            //find distance between unknown and training
            d = findDistance( i, j, unknown, training );
            //compare to see if it is less
            if( d < first )
            {
                fifth = fourth;
                fourth = third;
                third = second;
                second = first;
                first = d;
                type5 = type4;
                type4 = type3;
                type3 = type2;
                type2 = type1;
                type1 = training[j].type;
            }
            else if( d < second && d != first )
            {
                fifth = fourth;
                fourth = third;
                third = second;
                second = d;
                type5 = type4;
                type4 = type3;
                type3 = type2;
                type2 = training[j].type;
            }
            else if( d < third && d != first && d != second )
            {
                fifth = fourth;
                fourth = third;
                third = d;
                type5 = type4;
                type4 = type3;
                type3 = training[j].type;
            }
            else if( d < third && d != first && d != second && d != third )
            {
                fifth = fourth;
                fourth = d;
                type5 = type4;
                type4 = training[j].type;
            }
            else if( d < third && d != first && d != second && d != third && d != fourth )
            {
                fifth = d;
                type5 = training[j].type;
            }
        }

        //tally seems faster than comparison here? Maybe not, after typing it all out.
        int sum[3];
        for(int m = 0; m < 3; m ++)
        {
            if( type1 == m+1 ) { sum[m]++; }
            if( type2 == m+1 ) { sum[m]++; }
            if( type3 == m+1 ) { sum[m]++; }
            if( type4 == m+1 ) { sum[m]++; }
            if( type5 == m+1 ) { sum[m]++; }
        }
        for(int m = 0; m < UNKNOWN_SIZE; m ++)
        {
            if( sum[m] >= 3 )
            {
                unknown[m].type = m+1;
                break;
            }
            unknown[m].type = -1;
        }

        int temp1 = -1;
        int temp2 = -1;
        if( unknown[i].type < 0 )
        {
            for( int m = 0; m < UNKNOWN_SIZE; m ++ )
            {
                if(sum[m] == 2)
                {
                    temp2 = temp1;
                    temp1 = sum[m];
                }
            }
            if( temp2 == -1 ) { unknown[i].type = temp1; }
            else
            {
                //this means a tie needs to be broken
                srand( time(NULL) );
                int decider = rand() % 2;
                if( decider == 0 ) { unknown[i].type = temp1; }
                else{ unknown[i].type = temp2; }
            }

        }
        cout<<"\nType 1 is: " <<type1;
        cout<<"\nType 2 is: " <<type2;
        cout<<"\nType 3 is: " <<type3;
        cout<<"\nType 4 is: " <<type4;
        cout<<"\nType 5 is: " <<type5;
        cout<<"\nType of unknown is: " <<unknown[i].type;

        cout << "\n\t\tPoint " << i+1 << "'s classification is ";
        if(unknown[i].type == 1){ cout << "Iris-setosa."; }
        if(unknown[i].type == 2){ cout << "Iris-versicolor."; }
        if(unknown[i].type == 3){ cout << "Iris-virginica."; }
    }

    //deallocation
    training = NULL;
    unknown = NULL;
    delete[] training;
    delete[] unknown;
    return 0;
}

//read from file, assign to storage system
void getData(iris* training)
{
    ifstream f;
    f.open("iris.txt");

    if (!f.is_open())  // check file is open, quit if not
    {
        cout << "failed to open file\n";
        return;
    }

    int i = 0;
    double d;
    char* s = new char;
    string temp;
    //while(!f.eof())
    for(int i = 0; i < 147; i++)
    {
        //assign contents
        f.get(s, 8, ',');
        //cout << "\n" << i << ": " << s;
        d = atof(s);
        //cout << "\n" << i << ": " << d;
        training[i].sepal_len = d;
        //cout << "\n" << i << ": " << training[i].sepal_len;
        f.ignore();

        f.get(s, 8, ',');
        //cout << "\n" << i << ": " << s;
        d = atof(s);
        //cout << "\n" << i << ": " << s;
        training[i].sepal_width = d;
        f.ignore();

        f.get(s, 8, ',');
        d = atof(s);
        //cout << "\n" << i << ": " << s;
        training[i].petal_len = d;
        f.ignore();

        f.get(s, 8, ',');
        d = atof(s);
        //cout << "\n" << i << ": " << s;
        training[i].petal_width = d;
        f.ignore();

        //f.get(s, 32, '\n');
        getline (f, temp);
        //cout << "\n" << i << ": " << temp;
        if(temp.compare("Iris-setosa") == 0){ training[i].type = 1; }
        if(temp.compare("Iris-versicolor") == 0){ training[i].type = 2; }
        if(temp.compare("Iris-virginica") == 0){ training[i].type = 3; }
        //cout << "\n" << i << ": " << training[i].type;
        //f.ignore();
        //i++;
    }
    s = NULL;
    delete s;
    f.close();
    return;
}

void getTestData(iris* unknown)
{
    //use default test data, assign to storage system
    unknown[0].sepal_len = 4.9;
    unknown[0].sepal_width = 3.0;
    unknown[0].petal_len = 1.4;
    unknown[0].petal_width = 0.2;
    unknown[0].type = -1;

    unknown[1].sepal_len = 4.9;
    unknown[1].sepal_width = 2.4;
    unknown[1].petal_len = 3.3;
    unknown[1].petal_width = 1.0;
    unknown[1].type = -1;

    unknown[2].sepal_len = 4.9;
    unknown[2].sepal_width = 2.5;
    unknown[2].petal_len = 4.5;
    unknown[2].petal_width = 1.7;
    unknown[2].type = -1;
    /*unknown[2].sepal_len = 6.0;
    unknown[2].sepal_width = 3.0;
    unknown[2].petal_len = 5.0;
    unknown[2].petal_width = 1.7;
    unknown[2].type = -1;*/



    return;
}


void getMinMax(const int TRAINING_SIZE, const int UNKNOWN_SIZE, iris* training, iris* unknown, double &mi1, double &ma1, double &mi2, double &ma2, double &mi3, double &ma3, double &mi4, double &ma4)
{
    //get min and max on the training data
    mi1 = training[0].sepal_len;
    ma1 = training[0].sepal_len;
    mi2 = training[0].sepal_width;
    ma2 = training[0].sepal_width;
    mi3 = training[0].petal_len;
    ma3 = training[0].petal_len;
    mi4 = training[0].petal_width;
    ma4 = training[0].petal_width;

    for(int i = 1; i < TRAINING_SIZE; i++)
    {
        if(training[i].sepal_len < mi1){mi1 = training[i].sepal_len;}
        if(training[i].sepal_len > ma1){ma1 = training[i].sepal_len;}

        if(training[i].sepal_width < mi2){mi2 = training[i].sepal_width;}
        if(training[i].sepal_width > ma2){ma2 = training[i].sepal_width;}

        if(training[i].petal_len < mi3){mi3 = training[i].petal_len;}
        if(training[i].petal_len > ma3){ma3 = training[i].petal_len;}

        if(training[i].petal_width < mi4){mi4 = training[i].petal_width;}
        if(training[i].petal_width > ma4){ma4 = training[i].petal_width;}

    }
    //make sure nothing in the unclassified data was larger or smaller
    for(int i = 0; i < UNKNOWN_SIZE; i++)
    {
        if(unknown[i].sepal_len < mi1){mi1 = unknown[i].sepal_len;}
        if(unknown[i].sepal_len > ma1){ma1 = unknown[i].sepal_len;}

        if(unknown[i].sepal_width < mi2){mi2 = unknown[i].sepal_width;}
        if(unknown[i].sepal_width > ma2){ma2 = unknown[i].sepal_width;}

        if(unknown[i].petal_len < mi3){mi3 = unknown[i].petal_len;}
        if(unknown[i].petal_len > ma3){ma3 = unknown[i].petal_len;}

        if(unknown[i].petal_width < mi4){mi4 = unknown[i].petal_width;}
        if(unknown[i].petal_width > ma4){ma4 = unknown[i].petal_width;}
    }
    return;
}

//scale so that the range of each data point is between 0 and 1
void normalizeData(const int TRAINING_SIZE, const int UNKNOWN_SIZE, iris* training, iris* unknown)
{
    double mi1, ma1, mi2, ma2, mi3, ma3, mi4, ma4;
    getMinMax(TRAINING_SIZE, UNKNOWN_SIZE, training, unknown, mi1, ma1, mi2, ma2, mi3, ma3, mi4, ma4);
    //training
    for(int i = 0; i < TRAINING_SIZE; i++)
    {
        training[i].sepal_len = (training[i].sepal_len - mi1)/(ma1 - mi1);
        training[i].sepal_width = (training[i].sepal_width - mi2)/(ma2 - mi2);
        training[i].petal_len = (training[i].petal_len - mi3)/(ma3 - mi3);
        training[i].petal_width = (training[i].petal_width - mi4)/(ma4 - mi4);
    }
    //unknown. size of unknown is 3.
    for(int i = 0; i < UNKNOWN_SIZE; i++)
    {
        unknown[i].sepal_len = (unknown[i].sepal_len - mi1)/(ma1 - mi1);
        unknown[i].sepal_width = (unknown[i].sepal_width - mi2)/(ma2 - mi2);
        unknown[i].petal_len = (unknown[i].petal_len - mi3)/(ma3 - mi3);
        unknown[i].petal_width = (unknown[i].petal_width - mi4)/(ma4 - mi4);
    }
    return;
}


double findDistance(int i, int j, iris* unknown, iris* training)
{
    return(sqrt(pow(unknown[i].sepal_len - training[j].sepal_len, 2) +
                pow(unknown[i].sepal_width - training[j].sepal_width, 2) +
                pow(unknown[i].petal_len - training[j].petal_len, 2) +
                pow(unknown[i].petal_width - training[j].petal_width, 2)));
}
