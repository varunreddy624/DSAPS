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