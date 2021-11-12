#include<stdio.h>
#include<stdlib.h>
#include <string>
#include<iostream>

using namespace std;

    struct trieNode{
        int index;
        struct trieNode *next[26];
    };
    
    typedef struct trieNode trieNode;
    
    trieNode *root;

    int m,n,x;

    char **board;

    int* ans;
     
    int **v;
    
    trieNode* createTrieNode(){
        trieNode* temp = (trieNode*)malloc(sizeof(trieNode));
        temp->index=-1;
        for(int i=0;i<26;i++)
            temp->next[i]= nullptr;
        return temp;
    }
    
    void insert(string word,int ind) {
        trieNode* r = root;
        int index,i;
        for(i=0;i<word.length();i++){
            index = (int)word[i]-97;
            if(r->next[index]==nullptr)
                r->next[index]=createTrieNode();
            r=r->next[index];
        }
        r->index=ind;
    }
    
    void helper(int i,int j,trieNode* r){
        if(r==nullptr)
            return ;
        
        if(r->index!=-1)
            ans[r->index]=1;
        
        if(i<0 || i>=m || j<0 || j>=n || v[i][j]==1)
            return ;
        
        int index = (int)board[i][j]-97;
        r=r->next[index];
        v[i][j]=1;

            helper(i,j-1,r);
    
            helper(i,j+1,r);
        
            helper(i-1,j,r);
      
            helper(i+1,j,r);
        
        v[i][j]=0;
    }

    void printAnsFromTrie(trieNode* r, string words[]){
        if(r->index!=-1){
            if(ans[r->index]==1)
                cout << words[r->index] << " ";
        }
        for(int i=0;i<26;i++)
            if(r->next[i]!=nullptr)
                printAnsFromTrie(r->next[i],words);
    }

int main(){

    int i,j;
    cin >> m >> n;

    board = (char**)malloc(m*sizeof(char*));
    v = (int**)malloc(m*sizeof(int*));


    for(i=0;i<m;i++){
        board[i] = (char*)malloc(n*sizeof(char));
        v[i] = (int*)malloc(n*sizeof(int));
        for(j=0;j<n;j++){
            v[i][j]=0;
            cin >> board[i][j];
        }
    }

    cin >> x;

    ans = (int*)malloc(x*sizeof(int));

    root = createTrieNode();

    // string *words = (string*)malloc(x*sizeof(string));
    string words[x];

    string temp;
    for(i=0;i<x;i++){
        cin >> words[i];
        ans[i]=0;
        insert(words[i],i);
    }

    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            helper(i,j,root);
         
    // for(i=0;i<x;i++)
    //     if(ans[i]==1)
    //         cout << words[i] << endl;

    printAnsFromTrie(root,words);
}

// 4 4
// o a a n
// e t a e
// i h k r
// i f l v
// 5
// oath
// pea
// eat
// train
// nerv
// 4 4
// o a b n
// o t a e
// a h k r
// a f l v
// 2
// oa
// oaa