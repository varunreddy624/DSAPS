#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

    void bfs(vector<vector<char>>& grid,vector<vector<int>>& distances){
        struct node{
            int i,j,dist;
        };
        typedef struct node node;
        
        int i,j,dist,n = grid.size(),m = grid[0].size();
        vector<vector<int>> v(n,vector<int>(m,0));
        queue<node> q;
        node l = {1,0,0};
        v[1][0]=1;
        q.push(l);
        while(q.size()!=0){
            node front = q.front();
            q.pop();
            i=front.i;
            j=front.j;
            dist=front.dist;
            distances[i][j]=dist;
            int x[4] = {i-1,i,i+1,i};
            int y[4] = {j,j-1,j,j+1};
            for(int k=0;k<4;k++){
                if(x[k]>=0 && x[k]<n && y[k]>=0 && y[k]<m && v[x[k]][y[k]]==0 && grid[x[k]][y[k]]!='#'){
                    v[x[k]][y[k]]=1;
                    l={x[k],y[k],dist+1};
                    q.push(l);
                }
             }
        }
    }


int main(){
    int i,j,n,m;
    cin >> n >> m;
    vector<vector<char>> grid(n,vector<char>(m));
    vector<vector<int>> distances(n,vector<int>(m,INT_MAX));
    for(i=0;i<n;i++)
        for(j=0;j<m;j++) 
            cin >> grid[i][j];

    bfs(grid,distances);

    int r=INT_MAX;

    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(grid[i][j]=='R')
                r=min(r,distances[i][j]);
            if(grid[i][j]=='A'){
                if(distances[i][j]!=INT_MAX && distances[i][j]<=r)
                    cout << "Yes" << endl << distances[i][j];
                else
                    cout << "No";
            }
        }
    }
}

//Sample test case 2.3
// 7 8
// ########
// .......#
// #####..#
// #.#.#..#
// #R#..#.#
// #.....A#
// ########