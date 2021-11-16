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

int main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        freopen("err.txt","w",stderr);
    #endif
    string s;
    cin >> s;
    int n=s.length(),k,i;
    string srev="";
    for(int i=n-1;i>=0;i--)
        srev+=s[i];
    s=s+"$"+srev;
    vector<int> SA = getSuffixArray(s);
    vector<int> LCP = getLCPFromSA(s,SA);
    for(i=0;i<=2*n;i++)
        cout << SA[i] << " " << s.substr(SA[i]) << endl;
    cout << endl;
    for(i=0;i<=2*n;i++)
        cout << LCP[i] << " ";
    
    cout << endl;

    int ind=SA[0],length=1;
    for(i=1;i<=2*n;i++){
        if((SA[i]>=n && SA[i-1]<n) || (SA[i]<n && SA[i-1]>=n)){
            if(LCP[i]>length){
                length=LCP[i];
                ind=min(SA[i],SA[i-1]);
            }
        }
    }
    cout << s.substr(ind,length);
}