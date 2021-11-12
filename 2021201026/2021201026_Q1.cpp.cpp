#include<stdio.h>
#include<stdlib.h>
#include <string>
#include<iostream>
#include<vector>

using namespace std;

class Trie {
public:
    struct trieNode{
        int flag;
        struct trieNode *next[26];
    };
    typedef struct trieNode trieNode;
    trieNode *root;

    vector<int> ans;
    vector<vector<int>> dp;

    int n;

    string autoCorrectString;

    
    Trie() {
        root = createTrieNode();
        dp.clear();
        ans.clear();
    }
    
    trieNode* createTrieNode(){
        trieNode* temp = (trieNode*)malloc(sizeof(trieNode));
        temp->flag=-1;
        for(int i=0;i<26;i++)
            temp->next[i]= nullptr;
        return temp;
    }
    
    void insert(string word,int ind) {
        trieNode* r = root;
        int index,i;
        for(i=0;i<(int)word.length();i++){
            index = (int)word[i]-97;
            if(r->next[index]==nullptr)
                r->next[index]=createTrieNode();
            r=r->next[index];
        }
        r->flag=ind;
    }
    
    bool search(string word) {
        trieNode* r = root;
        int index,i;
        for(i=0;i<(int)word.length();i++){
            index = (int)word[i]-97;
            if(r->next[index]==nullptr)
                return false;
            r=r->next[index];
        }
        return r->flag!=-1;
    }
    
    void autoCompleteRecursive(trieNode* r){
        int i;
        if(r->flag!=-1)
            ans.push_back(r->flag);
        for(i=0;i<26;i++)
            if(r->next[i]!=nullptr)
                autoCompleteRecursive(r->next[i]);
        return ;
    }

    void autoComplete(string prefix){
        trieNode* r = root;
        int index,i;
        for(i=0;i<(int)prefix.length();i++){
            index = (int)prefix[i]-97;
            if(r->next[index]==nullptr)
                return ;
            r=r->next[index];
        }
        autoCompleteRecursive(r);
    }

    void printDPUtil(){
        for(int i=0;i<dp.size();i++){
            for(int j=0;j<dp[i].size();j++)
                cout << dp[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }

    void autoCorrectRecursive(vector<vector<int>>& dp,trieNode* r){
        
        int i,j,a;

        a=dp.size()-1;

        if(r->flag!=-1)
            if(dp[a][n]<=3)
                ans.push_back(r->flag);
        
        for(i=0;i<26;i++){
            if(r->next[i]!=nullptr){
                vector<int> temp;
                temp.push_back(dp[a][0]+1);
                for(j=1;j<=n;j++){
                    if((int)autoCorrectString[j-1]-97==i)
                        temp.push_back(dp[a][j-1]);
                    else
                        temp.push_back(1+min(temp[j-1],min(dp[a][j],dp[a][j-1])));
                }
                dp.push_back(temp);
                autoCorrectRecursive(dp,r->next[i]);
                dp.pop_back();
            }
        }
    }

    void autoCorrect(string prefix){
        autoCorrectString=prefix;
        n=autoCorrectString.length(); 
        vector<int> temp;
        for(int i=0;i<=n;i++)
            temp.push_back(i);
        dp.push_back(temp);
        autoCorrectRecursive(dp,root);
    }

};

int main(){
    int i,n;
    cin >> n;
    string temp;
    Trie t;
    vector<string> words;
    for(i=0;i<n;i++){
        cin >> temp;
        words.push_back(temp);
        t.insert(temp,i);
    }
    cin >> n >> temp;

    if(n==1)
        cout << t.search(temp) << endl;

    else{
        if(n==2)
            t.autoComplete(temp); 
        else
            t.autoCorrect(temp);

        cout << t.ans.size() << endl;
        for(auto& i:t.ans)
            cout << words[i] << endl;
    }
}

// 4
// ed
// eddie
// edward
// e
// 2 e