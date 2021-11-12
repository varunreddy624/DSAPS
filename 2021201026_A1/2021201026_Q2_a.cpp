#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>


using namespace std;


typedef struct doublyLinkedListNode{
    int key;
    doublyLinkedListNode *left;
    doublyLinkedListNode *right;
}doublyLinkedListNode;

typedef struct mapValue{
    int value;
    doublyLinkedListNode* ptr;
}mapValue;

class LRUCache {
    
public:
    doublyLinkedListNode *last,*first;
    int cacheSize,capacity;
    map<int,mapValue> hashMap;
    
    void deleteLastNode(){
        hashMap.erase(last->key);
        doublyLinkedListNode* temp=last->right;
        if(temp!=nullptr)
            temp->left=nullptr;
        free(last);
        last=temp;
        cacheSize--;
    }

    void deleteSpecificNodeAndInsertAtBeginining(doublyLinkedListNode* a){
        if(a->right!=nullptr){
            if(a->left!=nullptr)
                a->left->right=a->right;
            else
                last=a->right;
            a->right->left=a->left;
            first->right=a;
            a->left=first;
            a->right=nullptr;
            first=a;
        }
    }
    

    void printDLL(doublyLinkedListNode* a){
        doublyLinkedListNode* t=a;
        while(t!=nullptr){
            cout << t->key << " ";
            t=t->right;
        }
    }

    void printMap(){
        for(auto i=hashMap.begin();i!=hashMap.end();i++){
            cout << i->first << " " << (i->second).value << " ";
            printDLL((i->second).ptr);
        }
    }


    LRUCache(int cap) {
        capacity=cap;
        first=nullptr;
        last=nullptr;
        cacheSize=0;
    }
    
    int get(int key) {
        auto it=(hashMap.find(key));
        if(it==hashMap.end())
            return -1;
        mapValue mv=it->second;
        deleteSpecificNodeAndInsertAtBeginining(mv.ptr);
        return mv.value;
    }
    
    void set(int key, int value) {
        if(capacity>0){
            if(get(key)==-1){
                if(cacheSize==capacity)
                    deleteLastNode();
                doublyLinkedListNode* temp = (doublyLinkedListNode*)(malloc(sizeof(doublyLinkedListNode)));
                temp->key=key;
                temp->left=nullptr;
                temp->right=nullptr;
                if(last==nullptr){
                    first=temp;
                    last=temp;
                }
                else{
                    first->right=temp;
                    temp->left=first;
                    first=temp;
                }
                mapValue mv;
                mv.value=value;
                mv.ptr=temp;
                hashMap.insert({key,mv});
                cacheSize++;
            }
            else{
                auto it =hashMap.find(key);
                (it->second).value=value;
            }
        }
    }
};
