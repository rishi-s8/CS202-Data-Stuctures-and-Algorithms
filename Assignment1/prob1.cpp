/*
 * CS202 LAB ASSIGNMENT 1
 * Author: Rishi Sharma (B17138)
 * Problem 1
 */

#include "seqLinearList.hpp"
#include "sorting.hpp"
int main()
{
        int MOD = 1000000007;
        int n;
        cin >> n;
        LinearList<long long> l(n);
        for(int i=0; i<n; ++i)
                cin >> l[i];
        Sort<long long> s;
        s.mergeSort(l,0,n-1);
        long long ans = 0;
        if(n&1)
                ans = (l[n/2] + MOD)%MOD;
        else
        {
                long long a = l[n/2-1], b = l[n/2];
                if((a&1 && b&1) || (!(a&1) && (!(b&1))))
                        ans = ((((a+b)/2)+MOD)%MOD * ((b-a+1+MOD)%MOD))%MOD;
                else
                        ans = (((((b-a+1)/2+MOD)%MOD) * (b+a)%MOD)%MOD);
        }
        cout << (ans+MOD)%MOD << endl;
}
