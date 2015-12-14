//
//  main.cpp
//  algoritma
//
//  Created by Gulce Basar on 10/27/14.
//  Copyright (c) 2014 Gulce Basar. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

class stableMatching
{
private:
    int numW;
    int numM;
    int* arrM;
    int* arrW;
    int* count;
    ofstream outfile;
public:
    int** wPref;
    int** mPref;
    
    stableMatching(int, int);
    void propose(int, int);
    bool comesBeforeW(int, int, int);
    bool comesBeforeM(int, int, int);
    void writeResult();
    bool isStable(string);
    int getNumW() { return numW; };
    int getNumM() { return numM; };
};

int main(int argc, const char * argv[])
{
    ifstream fileWpre, fileMpre;
    string line, str;
    char ch;
    int numM, numW, lineCount=0;
    
    fileWpre.open("/Users/Gulce/Desktop/preference_w.txt");
    fileMpre.open("/Users/Gulce/Desktop/preference_m.txt");
    
    getline(fileWpre, line);
    numW = atoi(line.c_str());
    
    getline(fileMpre, line);
    numM = atoi(line.c_str());
    
    stableMatching stMatch(numM, numW);
    
    while(getline(fileWpre, line))
    {
        stringstream iss(line);
        for(int i=0; i<stMatch.getNumW(); i++)
        {
            iss >> str;
            ch=str[1];
            stMatch.wPref[lineCount][i] = ch-'0';
        }
        lineCount++;
    }
    
    lineCount=0;
    while(getline(fileMpre, line))
    {
        stringstream iss(line);
        for(int i=0; i<stMatch.getNumM(); i++)
        {
            iss >> str;
            ch=str[1];
            stMatch.mPref[lineCount][i] = ch-'0';
        }
        lineCount++;
    }
    
    for(int i=0; i<stMatch.getNumM(); i++)
    {
        stMatch.propose(0, i);
    }
    
    stMatch.writeResult();
    
    cout << "Part B:" << endl << "-Given match is "
         << ( stMatch.isStable("/Users/Gulce/Desktop/match2.txt") ? "stable" : "not stable" ) << endl;
    
    return 0;
}

stableMatching::stableMatching(int numMan, int numWoman)
{
    numM = numMan;
    numW = numWoman;
    
    arrM = new int[numM];
    arrW = new int[numW];
    count = new int[numM];
    
    mPref = new int*[numM];
    for (int i=0; i<numM; i++)
    {
        mPref[i] = new int[numW];
        arrM[i]=-1;
        count[i]=0;
    }
    
    wPref = new int*[numW];
    for (int i=0; i<numW; i++)
    {
        wPref[i] = new int[numM];
        arrW[i]=-1;
    }
    
    outfile.open("/Users/Gulce/Desktop/stable_match.txt");
}

void stableMatching::propose (int num, int man)
{
    int woman=mPref[man][num];
    outfile << "M" << man << " proposes to W" << woman << endl;
    count[man]++;
    if( arrW[woman] == -1 )
    {
        outfile << "W" << woman << " is previously unmatched, M" << man << " matches with W" << woman << endl;
        arrM[man]=woman;
        arrW[woman]=man;
    }
    else if( comesBeforeW(man, arrW[woman], woman) )
    {
        outfile << "W" << woman << " leaves M" << arrW[woman] << " for M" << man << ", M" << arrW[woman] << " is now free" << endl;
        int prevMan=arrW[woman];
        arrM[prevMan] = -1;
        arrM[man] = woman;
        arrW[woman] = man;
        
        propose(count[prevMan], prevMan);
    }
    else
    {
        outfile << "W" << woman << " is matched with M" << arrW[woman] << ", she rejects M" << man << endl;
        propose(num+1, man);
    }
}

bool stableMatching::comesBeforeW(int newMan, int prevMan, int woman)
{
    int newManIdx=-1, prevManIdx=-1;
    
    for(int i=0; i<numW; i++)
    {
        if( wPref[woman][i] == newMan )
            newManIdx = i;
        if( wPref[woman][i] == prevMan )
            prevManIdx = i;
    }
    
    if(newManIdx <= prevManIdx)
        return true;
    
    return false;
}

bool stableMatching::comesBeforeM(int newWoman, int prevWoman, int man)
{
    int newWomanIdx=-1, prevWomanIdx=-1;
    
    for(int i=0; i<numM; i++)
    {
        if( mPref[man][i] == newWoman )
            newWomanIdx = i;
        if( mPref[man][i] == prevWoman )
            prevWomanIdx = i;
    }
    
    if(newWomanIdx <= prevWomanIdx)
        return true;
    
    return false;
}

void stableMatching::writeResult()
{
    outfile << endl << "Match:" << endl;
    for(int i=0; i<numM; i++)
    {
        outfile << "(M" << i << " - W" << arrM[i] << ")" << endl;
    }
}

bool stableMatching::isStable(string fileName)
{
    ifstream inFile;
    string line, str1, str2;
    char ch1, ch2;
    
    inFile.open(fileName.c_str());
    getline(inFile, line);
    int num = atoi(line.c_str());
    
    int* sWomanArr = new int[num];
    int* sManArr = new int[num];
    
    while( getline(inFile, line) )
    {
        stringstream iss(line);
        iss >> str1 >> str2;
        ch1 = str1[2];
        ch2 = str2[1];
        sManArr[ ch1-'0' ] = ch2-'0';
        sWomanArr[ ch2-'0' ] = ch1-'0';
    }

    for (int woman=0; woman<num; woman++)
    {
        for(int man=0; man<num; man++)
        {
            if( comesBeforeW(man, sWomanArr[woman], woman) && comesBeforeM(woman, sManArr[man], man) )
            {
                if(sWomanArr[woman] != man && sManArr[man] != woman)
                    return false;
            }
        }
    }
    return true;
}

