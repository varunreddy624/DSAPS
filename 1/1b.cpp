#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

vector<int> getSuffixArray(string s){
    map<string, int> suffixMap;
    int n = s.length();
    vector<int> suffixArr(n);
    string sub = "";
    for (int i = n - 1; i >= 0; i--) {
        sub = s[i] + sub;
        suffixMap[sub] = i;
    }
 
    int j = 0;
    for (auto x : suffixMap) {
        suffixArr[j] = x.second;
        j++;
    }

    return suffixArr;
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
    for(int k=i+1;i<=j;i++)
        ans=min(ans,LCP[k]);
    return ans;
}

int getLongestSubStrAtleastKTimes(string s,vector<int>& SA,vector<int>& LCP,int k){
    int i,n=SA.size();
    int ans=-1;
    for(i=0;i<n-k-1;i++)
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
    vector<int> LCP = getLCPFromSA(s,SA);
    for(i=0;i<n;i++)
        cout << SA[i] << " ";
    cout << endl;
    for(i=0;i<n;i++)
        cout << LCP[i] << " ";

    cin >> k;
    cout << getLongestSubStrAtleastKTimes(s,SA,LCP,k) << endl;
}