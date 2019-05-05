/*
  * CS202 Data Structures and Algorithms
  * Assignment 3
  * Dynamic Programming
  * Part 1: Simple Space Complexity O(m*n)
  * Author: Rishi Sharma 
  */

#include <bits/stdc++.h>
using namespace std;

vector< vector<long long> > dp;
long long misMatchPenalty;
long long gapPenalty;
string s1, s2;

void alignmentHelper(int m, int n)
{
    for(int i=1; i<=m; ++i)
    {
        for(int j=1; j<=n; ++j)
        {
            long long misMatchCost = (s1[i]==s2[j]) ? 0 : misMatchPenalty;
            dp[i][j] = min(dp[i-1][j-1]+misMatchCost, min(dp[i][j-1]+gapPenalty, dp[i-1][j]+gapPenalty));
        }
    }
}

void alignment(int m, int n)
{
    dp.assign(m+1, vector<long long>(n+1, 0));
    dp[0][0] = 0;
    for(int i=1; i<=m; ++i)
        dp[i][0] = gapPenalty*i;
    for(int j=1; j<=n; ++j)
        dp[0][j] = gapPenalty*j;
    alignmentHelper(m, n);
    stack<char> s3, s4;
    int i=m, j=n;
    while(i!=0 && j!=0)
    {
        long long misMatchCost = (s1[i]==s2[j]) ? 0 : misMatchPenalty;
        if(dp[i][j] == dp[i-1][j-1] + misMatchCost)
            s3.push(s1[i--]), s4.push(s2[j--]);
        else if(dp[i][j] == dp[i][j-1] + gapPenalty)
            s3.push('-'), s4.push(s2[j--]);
        else
            s3.push(s1[i--]), s4.push('-');
    }
    while(i!=0)
    {
        s3.push(s1[i]);
        s4.push('-');
        i--;
    }
    while(j!=0)
    {
        s4.push(s2[j]);
        s3.push('-');
        j--;
    }
    while(!s3.empty())
    {
        cout << s3.top();
        s3.pop();
    }
    cout << endl;
    while(!s4.empty())
    {
        cout << s4.top();
        s4.pop();
    }
    cout << endl;
    cout << "Cost = " << dp[m][n] << endl;

}



int main(int argc, char *argv[])
{
    int argument = atoi(argv[1]);
    gapPenalty = (argument == 1) ? 6 : 4;
    misMatchPenalty = (argument == 1) ? 4 : 6;
    cin >> s1 >> s2;
    int m = s1.size(), n = s2.size();
    s1 = " " + s1;
    s2 = " " + s2;
    alignment(m, n);
}
