//
//  main.cpp
//  algoritma
//
//  Created by Gulce on 11/20/14.
//  Copyright (c) 2014 Gulce. All rights reserved.
//

#include <iostream>
#include<fstream>
#include <sstream>
using namespace std;

class topologic
{
private:
    int size;
    int* topol;
    int counter;
    bool dag;
public:
    
    int** mtx;
    topologic(int);
    bool noIncomingEdge(int num);
    bool topolHas(int num);
    void order();
    void print();
};

int main(int argc, const char * argv[])
{
    int size;
    string line;
    ifstream infile;
    stringstream ss;
    
    infile.open(argv[1]);
    
    if (infile.is_open())
    {
        getline (infile,line);
        stringstream ss(line);
        ss >> size;
        
        topologic t1(size);
        
        int num1, num2;
        while ( getline (infile,line) )
        {
            stringstream ss2(line);
            ss2 >> num1 >> num2;
            t1.mtx[num1-1][num2-1] =1;
        }
        infile.close();
        
        t1.order();
        t1.print();
     
    }
    else cout << "Unable to open file";
    
    return 0;
}

topologic::topologic(int num)
{
    size=num;
    counter = 0;
    
    mtx = new int*[size];
    for(int i = 0; i < size; i++)
        mtx[i] = new int[size];
    
    for (int i=0; i<size; i++)
        for (int j=0; j<size; j++)
            mtx[i][j]=0;
    
    topol = new int[size];
    for (int i=0; i<7; i++)
        topol[i]=0;
}

bool topologic::noIncomingEdge(int num)
{
    for(int i=0; i<size; i++)
    {
        if(mtx[i][num-1] == 1)
            return false;
    }
    return true;
}

bool topologic::topolHas(int num)
{
    for(int i=0; i<size; i++)
    {
        if(topol[i] == num)
            return true;
    }
    return false;
}

void topologic::order()
{
    dag=false;
    
    for(int num=1; num<size+1; num++)
    {
        if(!topolHas(num))
        {
            if(noIncomingEdge(num))
            {
                dag=true;
                topol[counter]=num;
                counter++;
                for(int i=0; i<size; i++)
                    mtx[num-1][i]=0;
            }
        }
    }

    if( topol[size-1] == 0 && dag )
        order();
}

void topologic::print()
{
    if(dag)
    {
        cout << "The topological order of the graph is:" << endl;
        for(int i=0; i<size; i++)
            cout << topol[i] << " " ;
        cout << endl;
    }
    else
        cout << "The graph is not DAG" << endl;
}
