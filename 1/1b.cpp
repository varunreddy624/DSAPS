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

vector<int> getLCPFromSA(string s,vector<int>& SA){
    int n=SA.size(),k,h=0;
    vector<int> RANK(n,0),LCP(n,0);
    for(int i=0;i<n;i++)
        RANK[SA[i]]=i;
    for(int i=0;i<n;i++){
        if(RANK[i]>0){
            k=SA[RANK[i]-1];
            while(s[i+h]==s[k+h])
                h++;
            LCP[RANK[i]]=h;
            if(h>0)
                h--;
        }
    }
    return LCP;
}

int getMin(vector<int>& LCP,int i,int j){
    int ans = LCP[i];
    for(int k=i+1;k<=j;k++)
        ans=min(ans,LCP[k]);
    return ans;
}

int getLongestSubStrAtleastKTimes(string s,vector<int>& SA,vector<int>& LCP,int k){
    int i,n=SA.size();
    int ans=-1;
    for(i=0;i<n-k+1;i++)
        ans=max(ans,getMin(LCP,i+1,i+k-1));
    
    if(ans==0)
        return -1;
    else
        return ans; 
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        freopen("err.txt","w",stderr);
    #endif
    string s;
    cin >> s;
    int n=s.length(),k,i;
    vector<int> SA = getSuffixArray(s);
    // vector<int> LCP = getLCPFromSA(s,SA);
    for(i=0;i<n;i++)
        cout << SA[i] << " ";
    // cout << endl;
    // for(i=0;i<n;i++)
    //     cout << LCP[i] << " ";

    // cin >> k;
    // cout << getLongestSubStrAtleastKTimes(s,SA,LCP,k) << endl;
}