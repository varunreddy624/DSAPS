#include <vector>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

vector<string> split_string(string);


struct node{
    node* next[2];
};

typedef struct node nodeData;

nodeData* createNode(){
    nodeData* t = (nodeData*)malloc(sizeof(nodeData));
    t->next[0]=nullptr;
    t->next[1]=nullptr;
    return t;
}

string retBin(long long int a){
    string bin="";
    int c=43;
    while(c--){
        bin=to_string(a%2)+bin;
        a=a/2;
    }
    return bin;
}

nodeData* root = nullptr;

void insert(long long int a){
    string bin = retBin(a);
    if(root==nullptr)
        root=createNode();
    nodeData* r=root;
    for(int i=0;i<43;i++){
        int bit = bin[i]-48;
        if(r->next[bit]==nullptr)
            r->next[bit]=createNode();
        r=r->next[bit];
    }
}

long long int helper(long long int a){
    string bin = retBin(a);
    long long int ans=0;
    nodeData* r=root;
    for(int i=0;i<43;i++){
        int bit = bin[i]-48;
        if(bit==0){
            if(r->next[1]!=nullptr){
                ans=(ans*2)+1;
                r=r->next[1];
            }
            else{
                ans=ans*2;
                r=r->next[0];
            }
        }
        else{
            if(r->next[0]!=nullptr){
                ans=(ans*2)+1;
                r=r->next[0];
            }
            else{
                ans=ans*2;
                r=r->next[1];
            }
        }
    }
    return ans;
}

vector<long long int> maxXor(vector<long long int>& arr, vector<long long int>& queries) {
    for(long long int i:arr)
        insert(i);
    vector<long long int> ans;
    for(long long int i:queries)
        ans.push_back(helper(i));
    return ans;
}

int main()
{

    int n;
    cin >> n;

    vector<long long int> arr(n);

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int m;
    cin >> m;

    vector<long long int> queries(m);

    for (int i = 0; i < m; i++) 
        cin >> queries[i];

    vector<long long int> result = maxXor(arr, queries);

    for (int i = 0; i < (int)result.size(); i++)
        cout << result[i] << endl;

    return 0;
}
