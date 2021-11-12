#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<iostream>
#include<climits>

using namespace std;

class Heap{
    public:
        vector<pair<int,int>> heap;
        int size(){
            return heap.size();
        } 
        pair<int,int> top(){
            return heap[0];
        }
        void swap(int i,int j){
            int t;
            t=heap[i].first;
            heap[i].first=heap[j].first;
            heap[j].first=t;
            t=heap[i].second;
            heap[i].second=heap[j].second;
            heap[j].second=t;
        }
        void push(pair<int,int> data){
            heap.push_back(data);
            int i=heap.size()-1,parent;
            while(i>0){
                parent = (i-1)/2;
                if(heap[i].first<heap[parent].first){
                    swap(i,parent);
                    i=parent;
                }
                else
                    break;
            }
        }
        void pop(){
            pair<int,int> lastElem = heap.back();
            heap.pop_back();
            if(heap.size()>0){
                int next=-1,minimum;
                heap[0].first=lastElem.first;
                heap[0].second=lastElem.second;
                int i=0,child1,child2;
                while(i<heap.size()){   
                    child1=(2*i)+1;
                    child2=(2*i)+2;
                    minimum = heap[i].first;
                    if(child1<heap.size()){
                        if(heap[child1].first < minimum){
                            minimum=heap[child1].first;
                            next=child1;
                        }
                    }
                    if(child2<heap.size())
                        if(heap[child2].first < minimum)
                            next=child2;
                    if(next==-1)
                        break;
                    swap(i,next);
                    i=next;
                    next=-1;
                }
            }
        }

        void printQ(){
            for(int i=0;i<heap.size();i++)
                cout << i << " " << heap[i].first << " " << heap[i].second << endl;
            cout << endl;
        }
};

    void dijkstra(int V, vector<vector<pair<int,int>>> adj, int S){
        Heap q;
        int i,j,x,dist;
        vector<int> ans(V,INT_MAX),v(V,0),parent(V,-1);
        q.push(make_pair(0,S));
        while(q.size()!=0){
            while(q.size()!=0 && v[q.top().second]==1)
                q.pop();
            if(q.size()!=0){
                x=q.top().second;
                dist=q.top().first;
                v[x]=1;
                ans[x]=dist;
                for(auto y : adj[x]){
                    if(v[y.first]==0 && ans[x]+y.second<ans[y.first]){
                        ans[y.first]=y.second+ans[x];
                        q.push(make_pair(ans[y.first],y.first));
                        parent[y.first]=x;
                    }
                    else if(ans[x]+y.second==ans[y.first] && to_string(x)<to_string(parent[y.first]))
                        parent[y.first]=x;
                }
            }
        }
        vector<int> path;
        for(i=0;i<V;i++){
            if(i!=S){
                j=i;
                path.push_back(j);
                while(parent[j]!=-1){
                    path.push_back(parent[j]);
                    j=parent[j];
                }
                for(j=0;j<path.size();j++)
                    cout << path[j] << " ";
                cout << endl;
                path.clear();
            }
        }
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
    int D,k,V,i,j;

    vector<vector<pair<int,int>>> adjMat = readAdjList();
    V = adjMat.size();
    cin >> D;
    dijkstra(adjMat.size(),adjMat,D);
}

// sample test case 2.1
// 10 10
// 0 1 5
// 1 2 5
// 2 8 5
// 8 9 5
// 0 4 15
// 4 9 5
// 0 3 5
// 0 5 5
// 0 6 5
// 0 7 5
// 9
// OP:
// 0 1 2 8 9
// 1 2 8 9
// 2 8 9
// 3 0 1 2 8 9
// 4 9
// 5 0 1 2 8 9
// 6 0 1 2 8 9
// 7 0 1 2 8 9
// 8 9

// 10 10
// 0 1 5
// 1 2 5
// 2 8 5
// 8 9 5
// 0 4 15
// 4 9 5
// 0 3 5
// 0 5 5
// 0 6 5
// 0 7 5
// 0

// OP:
// 1 0
// 2 1 0
// 3 0
// 4 0
// 5 0
// 6 0
// 7 0
// 8 2 1 0
// 9 4 0
