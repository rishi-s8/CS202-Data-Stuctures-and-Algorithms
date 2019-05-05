/*
  * CS202 Data Structures and Algorithms
  * Assignment 3
  * Dynamic Programming
  * Part 3: Divide and Conquer BONUS: Space Complexity O(m+n)
  * Author: Rishi Sharma
  */

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctype.h>
using namespace std;
vector< pair<int, int> > nodes;
vector< vector<long long> > misMatchPenalty;
long long gapPenalty;
string s1, s2;
vector< vector<long long> > A, B;

int getIndex(char ch)
{
    switch(ch)
    {
        case 'A':
            return 0;
        case 'T':
            return 1;
        case 'G':
            return 2;
        case 'C':
            return 3;
    }
    return 4;
}

long long getCost(char x, char y)
{
    x=toupper(x), y=toupper(y);
    if(x==y) return 0;
    return misMatchPenalty[getIndex(x)][getIndex(y)];
}

void forwardSpaceEfficientAlignment(int iStart, int iEnd, int jStart, int jEnd)
{
    A.clear();
    A.assign(2, vector<long long>(iEnd+1));
    A[0][iStart-1] = 0;
    for(int i = iStart; i<=iEnd; ++i) A[0][i] = gapPenalty + A[0][i-1];
    for(int j = jStart; j<=jEnd; ++j)
    {
        A[1][iStart-1] = A[0][iStart-1] + gapPenalty;
        for(int i = iStart; i<= iEnd; ++i)
        {
            long long misMatchCost = getCost(s1[i], s2[j]);
            A[1][i] = min(A[0][i-1]+misMatchCost, min(A[1][i-1]+gapPenalty, A[0][i] + gapPenalty));
        }
        for(int i = iStart-1; i<=iEnd; ++i)
            A[0][i] = A[1][i];
    }
}


void backwardSpaceEfficientAlignment(int iStart, int iEnd, int jStart, int jEnd)
{
    B.clear();
    B.assign(2, vector<long long>(iEnd+2));
    B[1][iEnd+1] = 0;
    for(int i = iEnd; i>=iStart; i--) B[1][i] = gapPenalty + B[1][i+1];
    for(int j = jEnd; j>=jStart; --j)
    {
        B[0][iEnd+1] = B[1][iEnd+1] + gapPenalty;
        for(int i = iEnd; i>= iStart; --i)
        {
            long long misMatchCost = getCost(s1[i], s2[j]);
            B[0][i] = min(B[1][i+1]+misMatchCost, min(B[0][i+1]+gapPenalty, B[1][i] + gapPenalty));
        }
        for(int i = iEnd+1; i>=iStart; --i)
            B[1][i] = B[0][i];
    }
}

long long alignment(int iStart, int iEnd, int jStart, int jEnd)
{
    vector< vector<long long> > dp(jEnd-jStart+2, vector<long long>(iEnd-iStart+2));
    dp[0][0]=0;
    for(int i=1; i<=iEnd-iStart+1; ++i)
        dp[0][i] = gapPenalty*i;
    for(int j = 1; j<=jEnd-jStart+1; ++j)
        dp[j][0] = gapPenalty*j;

    for(int i=1; i<=iEnd-iStart+1; ++i)
    {
        for(int j=1; j<=jEnd-jStart+1; j++)
        {
            long long misMatchCost = getCost(s1[i+iStart-1], s2[j+jStart-1]);
            dp[j][i] = min( dp[j-1][i-1] + misMatchCost , min(dp[j-1][i] + gapPenalty, dp[j][i-1] + gapPenalty));
        }
    }

    int i =iEnd-iStart+1, j=jEnd-jStart+1;
    long long cost = dp[j][i];
    while(i!=0 && j!=0)
    {
        long long misMatchCost = getCost(s1[i+iStart-1], s2[j+jStart-1]);
        nodes.push_back(make_pair(j+jStart-1,i+iStart-1));
        if(dp[j][i] == dp[j-1][i-1] + misMatchCost)
            --i, --j;
        else if(dp[j][i] == dp[j-1][i] + gapPenalty)
            --j;
        else
            --i;
    }

    while(i!=0)
        nodes.push_back(make_pair(j+jStart-1,(i--)+iStart-1));
    while(j!=0)
        nodes.push_back(make_pair((j--)+jStart-1,i+iStart-1));
    return cost;
}

long long divideAndConquerAlignment(int iStart, int iEnd, int jStart, int jEnd)
{
    int m = iEnd - iStart + 1, n = jEnd - jStart + 1;
    if(m<=2 || n<=2)
    {
        return alignment(iStart, iEnd, jStart, jEnd);
    }
    else
    {
        int mid = (jStart+jEnd)/2;
        forwardSpaceEfficientAlignment(iStart, iEnd, jStart, mid);

        backwardSpaceEfficientAlignment(iStart, iEnd, mid+1, jEnd);

        int q = iStart-1;
        long long leastCost = A[1][iStart-1] + B[1][iStart];
        for(int i = iStart; i<=iEnd; ++i)
        {
            long long curCost = A[1][i] + B[1][i+1];
            if(curCost < leastCost)
                leastCost = curCost, q = i;
        }
        nodes.push_back(make_pair(mid, q));
        divideAndConquerAlignment(iStart, q, jStart, mid);
        divideAndConquerAlignment(q+1, iEnd, mid+1, jEnd);
        return leastCost;
    }
}

long long reConstruct(string &s3, string &s4)
{
    long long cost = 0;
    int i = 0, j = 0;
    for(vector< pair<int,int> >::iterator iter = nodes.begin(); iter!=nodes.end(); ++iter)
    {
        int x = iter->second, y = iter->first;
        long long misMatchCost = getCost(s1[x], s2[y]);
        if(x==i+1 && y==j+1)
        {
            s3+=s1[x], s4+=s2[y];
            cost+=misMatchCost;
        }
        else if(x==i && y==j+1)
        {
            s3+="-", s4+=s2[y];
            cost+=gapPenalty;
        }
        else
        {
            s3+=s1[x], s4+="-";
            cost+=gapPenalty;
        }
        i=x, j=y;
    }
    return cost;

}

void instantiateCosts(int argc, char *argv[])
{
    if(argc!=6)
    {
        cerr << "USAGE: ./part3 gap_penalty mismatch_penalty_forA_T mismatch_penalty_forG_C mismatch_penalty_forA_C mismatch_penalty_for_other_combinations\n";
        exit(-1);
    }
    gapPenalty = atoll(argv[1]);
    long long temp = atoll(argv[5]);
    misMatchPenalty.assign(5, vector<long long>(5, temp));
    for(int i=0; i<4; ++i) misMatchPenalty[i][i]=0;
    misMatchPenalty[0][1] = misMatchPenalty[1][0] = atoi(argv[2]);
    misMatchPenalty[2][3] = misMatchPenalty[3][2] = atoi(argv[3]);
    misMatchPenalty[0][3] = misMatchPenalty[3][0] = atoi(argv[4]);
}

int main(int argc, char *argv[])
{
    instantiateCosts(argc, argv);
    cin >> s1 >> s2;
    int m = s1.size(), n = s2.size();
    s1 = " " + s1;
    s2 = " " + s2;
    long long cost1 = divideAndConquerAlignment(1, m, 1, n);
    sort(nodes.begin(), nodes.end());
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
    string s3="", s4="";
    long long cost = reConstruct(s3, s4);
    cout << s3 << endl << s4 << endl;
    if(cost1!=cost)
        cerr << "Costs didn't Match.. \n" << endl;
    cout << "Cost = " << cost << endl;
}
