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

vector<int> getRankArr(vector<int>& SA){
    int n=SA.size();
    vector<int> RANK(n,0);
    for(int i=0;i<n;i++)
        RANK[SA[i]]=i;
    return RANK;
}

vector<int> getLCPFromSA(string s,vector<int>& SA,vector<int>& RANK){
    int h=0,k,n=s.length();
    vector<int> LCP(n,0);
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

int getMinRange(int i,int j,vector<int>& LCP){
    int ans=LCP[i];
    for(int k=i+1;k<=j;k++)
        ans=min(ans,LCP[k]);
    
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
    string srev="";
    for(int i=n-1;i>=0;i--)
        srev+=s[i];
    s=s+"~"+srev;
    vector<int> SA = getSuffixArray(s);
    vector<int> RANK = getRankArr(SA);
    vector<int> LCP = getLCPFromSA(s,SA,RANK);

    // cout << "i" << "\t\t" << "SA"  << "\t\t" <<  "LCP" << "\t\t" << "RANK" <<  "\t\t" << "suffix"<< "\t\t" << endl;

    // cout << endl;

    // for(i=0;i<=2*n;i++)
    //     cout << i << "\t\t" << SA[i]  << "\t\t" <<  LCP[i] << "\t\t" << RANK[i] <<  "\t\t" << s.substr(SA[i]) << "\t\t" << endl;
    // cout << endl;

    int ind=SA[0],length=1;

    // even

    for(i=1;i<n;i++){
        int leftInd=i,rightInd=(2*n)-i;
        int leftIndLCPInd = RANK[leftInd];
        int rightIndLCPInd = RANK[rightInd];
        int start = min(leftIndLCPInd,rightIndLCPInd);
        int end = max(leftIndLCPInd,rightIndLCPInd);
        int temp = getMinRange(start+1,end,LCP);
        // cout << leftInd << " " << rightInd << " " << rightIndLCPInd << " " << leftIndLCPInd << " " << temp << endl;
        int len = (2*temp)-1;
        if(len > length){
            length = len;
            ind = i-temp+1;
        }
    }

    // odd

    for(i=1;i<n;i++){
        int leftInd=i,rightInd=(2*n)+1-i;
        int leftIndLCPInd = RANK[leftInd];
        int rightIndLCPInd = RANK[rightInd];
        int start = min(leftIndLCPInd,rightIndLCPInd);
        int end = max(leftIndLCPInd,rightIndLCPInd);
        int temp = getMinRange(start+1,end,LCP);
        // cout << leftInd << " " << rightInd << " " << rightIndLCPInd << " " << leftIndLCPInd << " " << temp << endl;
        int len = (2*temp);
        if(len > length){
            length = len;
            ind = i-temp;
        }
    }

    // cout << ind << " " << length << endl;

    cout << s.substr(ind,length);
}