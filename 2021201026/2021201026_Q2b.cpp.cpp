#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;


    void dfs(int i,int c,vector<int>& v,vector<int>& flag,string path,vector<pair<int,string>>& paths,vector<vector<pair<int,int>>>& adj){
        path+=(to_string(i)+" ");
        if(c!=0 && flag[i]==0)
            paths.push_back(make_pair(c,path));
        v[i]=1;
        int f=0;
        for(auto j:adj[i])
            if(v[j.first]==0)
                dfs(j.first,c+j.second,v,flag,path,paths,adj);
        v[i]=0;
    }

    void kShortestPaths(int V, vector<vector<pair<int,int>>>& adj, int k){
        int i;
        vector<pair<int,string>> paths;
        vector<int> flag(V,0),v(V,0);
        for(i=0;i<V;i++){
            dfs(i,0,v,flag,"",paths,adj);
            flag[i]=1;
        }
        sort(paths.begin(),paths.end());
        for(i=0;i<min(k,(int)paths.size());i++)
            cout << paths[i].second << endl;
    }

    vector<vector<pair<int,int>>> readAdjList(){
        int V,E,a,b,w,i=0;
        cin >> V >> E;
        vector<vector<pair<int,int>>> adjMat(V,vector<pair<int,int>>());
        while(i++<E){
            cin >> a >> b >> w;
            adjMat[a].push_back(make_pair(b,w));
            adjMat[b].push_back(make_pair(a,w));
        }
        return adjMat;
    }

int main(){

    vector<vector<pair<int,int>>> adjMat = readAdjList();
    int k,V = adjMat.size();
    cin >> k;
    kShortestPaths(V,adjMat,k);

}   

//Sample test case 2.2
// 4 5 
// 0 1 1
// 1 3 2
// 0 3 3
// 0 2 2
// 2 3 1
// 3