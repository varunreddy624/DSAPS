#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

bool cmp(vector<int> a,vector<int> b){
    if(a[0]==b[0]){
        if(a[1]<b[1])
            return 1;
        else
            return 0;
    }
    else{
        if(a[0]<b[0])
            return 1;
        else
            return 0;
    }
}

vector<int> getSuffixArray(string s){
    s=s+"$";
    int i,k,n = s.length(),r;
    
    vector<vector<int>> RA(n,vector<int>(3,0)); 
    
    for(i=0;i<n;i++){
        RA[i][0]=s[i];
        RA[i][2]=i;
    }

    /*
        RA[i][0] = s[i]
        RA[i][1] = s[i+k]
        RA[i][2] = SA[i]
    */
    
    for(k=1;k<n;k*=2){

        vector<int> ind(n,0); // S[i] to original index mapping
        for(i=0;i<n;i++)
            ind[RA[i][2]]=i;

        for(i=0;i<n;i++)
             RA[i][1] = (RA[i][2]+k<n) ? RA[ind[RA[i][2]+k]][0] : 0;

        stable_sort(RA.begin(),RA.end(),cmp);   // sort RA
        

        vector<int> tempRA(n,0);
        r=0;
        tempRA[0]=r; // will be zero since 1st suffix in sorted suffixes will have rank zero
        for(i=1;i<n;i++){
            if(RA[i][0] == RA[i-1][0] && RA[i][1] == RA[i-1][1])
                tempRA[i]=r;
            else
                tempRA[i]=++r;
        }

        for(i=0;i<n;i++)
            RA[i][0]=tempRA[i];

    }
    vector<int> SA(n-1,0);
    for(i=1;i<n;i++)
        SA[i-1]=RA[i][2];
    
    return SA;
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        freopen("err.txt","w",stderr);
    #endif
    string s;
    cin >> s;
    int n=s.length();
    vector<int> suffixArr = getSuffixArray(s+s);
    for (auto i:suffixArr){
        if(i<n){
            cout << s.substr(i)+s.substr(0,i);
            break;
        }
    }
}