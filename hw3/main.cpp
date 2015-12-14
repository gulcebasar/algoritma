//
//  main.cpp
//  algoritma3
//
//  Created by Gulce on 12/12/14.
//  Copyright (c) 2014 Gulce. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

struct visit
{
    int path;
    bool visited;
};

class ShortestPath
{
private:
    int verNum;
    int** distances;
    visit* path;
    int* visited;
public:
    ShortestPath();
    void print(int, int);
    int findShortest();
    void findPath(int, int);
};

int main(int argc, const char * argv[])
{
    ShortestPath s;
    int init = atoi(argv[1]);
    int dest = atoi(argv[2]);
    
    s.findPath(init, dest);
    
    return 0;
}

ShortestPath::ShortestPath()
{
    ifstream file;
    string line;
    
    file.open("distances.txt");
    
    if (file.is_open())
    {
        getline (file,line);
        stringstream ss(line);
        ss >> verNum;
        
        distances = new int*[verNum];
        for(int i = 0; i < verNum; i++)
        {
            distances[i] = new int[verNum];
            for(int j=0; j<verNum; j++)
                distances[i][j]=-1;
        }
        
        path = new visit[verNum];
        visited = new int[verNum];
        for(int i = 0; i < verNum; i++)
        {
            path[i].path = -1;
            path[i].visited = false;
            visited[i] = -1;
        }
        
        int ver1, ver2, dist;
        while (getline (file,line) )
        {
            stringstream ss(line);
            ss >> ver1 >> ver2 >> dist;
            
            distances[ver1-1][ver2-1] = dist;
            distances[ver2-1][ver1-1] = dist;
        }
    }
    else
    {
        cout << "ERROR OPENING THE FILE!!" << endl;
    }
    
}

void ShortestPath::print(int init, int dest)
{
    cout << "The shortest Path between node " << init << " and " << dest << " is " << path[dest-1].path << " km." << endl << "Other distances:" << endl;
    
    for (int i=0; i<verNum; i++)
        if( (visited[i] != init) && (visited[i] != dest) )
            cout << init << " to " << visited[i] << " -> " << path[visited[i]-1].path << " km" << endl;
}

int ShortestPath::findShortest()
{
    int shortest = 10000;
    int shortestidx = -1;
    for(int i = 0; i < verNum; i++)
    {
        if( !path[i].visited && path[i].path!=-1 && path[i].path<shortest )
        {
            shortest=path[i].path;
            shortestidx = i;
        }
    }
    return shortestidx+1;
}

void ShortestPath::findPath(int init, int dest)
{
    int counter=0;
    path[init-1].path=0;
    
    for(int i=0; i < verNum; i++)
    {
        visited[counter]=findShortest();
        path[visited[counter]-1].visited=true;
        
        for(int j = 0; j < verNum; j++)
        {
            if(distances[ visited[counter]-1 ][j] != -1)
            {
                if(path[j].path == -1 )
                    path[j].path =  path[visited[counter]-1].path + distances[visited[counter]-1][j];
                else if( (!path[j].visited) && (path[j].path > (path[visited[counter]-1].path+distances[visited[counter]-1][j])) )
                path[j].path =  path[visited[counter]-1].path + distances[visited[counter]-1][j];
            }
        }
        counter++;
    }
    
    print(init, dest);
}

