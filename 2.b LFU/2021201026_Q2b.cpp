#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>

using namespace std;

typedef struct keyNode keyNode;

typedef struct freqNode{
	int freq;
	freqNode *left,*right;
	keyNode *first,*last;
}freqNode;

struct keyNode{
	int key;
	keyNode *left,*right;
	freqNode *parentFreqNode;
};

typedef struct mapValue{
	int value;
	keyNode* ptr;
}mapValue;


class LFUCache {

    
public:
    int capacity,presentCacheSize;
    map<int, mapValue> hashMap;
    freqNode* head;
    
    freqNode* createFreqNode(int freq){
        freqNode* a=(freqNode*)(malloc(sizeof(freqNode)));
        a->freq=freq;
        a->left=nullptr;
        a->right=nullptr;
        a->first=nullptr;
        a->last=nullptr;
        return a;
    }


    keyNode* createKeyNode(int key){
        keyNode* a=(keyNode*)(malloc(sizeof(keyNode)));
        a->key=key;
        a->left=nullptr;
        a->right=nullptr;
        a->parentFreqNode=nullptr;
        return a;
    }


    mapValue createMapValue(int value,keyNode* b){
        mapValue a;
        a.value=value;
        a.ptr=b;
        return a;
    }
    
    
    void insertAfterSpecifiedFrequencyNode(freqNode* prevFreqNode,keyNode* presentNode){
        freqNode* currFreqNode;
        if(prevFreqNode==nullptr){
            freqNode* temp=createFreqNode(1);
            if(head==nullptr)
                head=temp;
            else if(head->freq!=1){
                temp->right=head;
                head->left=temp;
                head=temp;
            }
            currFreqNode=head;
        }
        else{ 
            if(prevFreqNode->right==nullptr || (prevFreqNode->freq)+1!=prevFreqNode->right->freq){
                freqNode* temp=createFreqNode((prevFreqNode->freq)+1);
                freqNode* nextOfPrev=prevFreqNode->right;
                prevFreqNode->right=temp;
                temp->left=prevFreqNode;
                if(nextOfPrev!=nullptr){
                    nextOfPrev->left=temp;
                    temp->right=nextOfPrev;
                }
            }
            currFreqNode=prevFreqNode->right;
        }
        if(currFreqNode->last==nullptr)
            currFreqNode->first=presentNode;
        else{
            currFreqNode->last->right=presentNode;
            presentNode->left=currFreqNode->last;
            presentNode->right=nullptr;
        }
        presentNode->parentFreqNode=currFreqNode;
        currFreqNode->last=presentNode;
    }


    void deleteFreqNode(freqNode* node){
        if(node->left==nullptr){
            head=node->right;
            if(node->right!=nullptr)
                node->right->left=nullptr;
        }
        else{
            node->left->right=node->right;
            if(node->right!=nullptr)
                node->right->left=node->left;
        }
        free(node);
    }


    void removeFromFreqLL(keyNode* node,int flag){
        if(node->left==nullptr){
            node->parentFreqNode->first=node->right;
            if(node->right!=nullptr)
                node->right->left=nullptr;
            else
                node->parentFreqNode->last=nullptr;
        }
        else{
            node->left->right=node->right;
            if(node->right==nullptr)
                node->parentFreqNode->last=node->left;
            else
                node->right->left=node->left;
        }
        if(flag==1)
            free(node);
        else{
            node->right=nullptr;
            node->left=nullptr;
        }
    }

    void printKeyNodeLL(keyNode* a){
        keyNode* temp=a;
        while(temp!=nullptr){
            cout << temp->key << " ";
            temp=temp->right;
        }
        cout << endl;
    }


    void printCache(){
        freqNode* temp=head;
        while(temp!=nullptr){
            cout << "freq=" <<temp->freq << "->";
            printKeyNodeLL(temp->first);
            temp=temp->right;
        }
    }

    LFUCache(int cap) {
        capacity=cap;
        presentCacheSize=0;
        head=nullptr;
    }
    
    int get(int key) {
        auto it=(hashMap.find(key));
        if(it==hashMap.end())
            return -1;
        else{
            mapValue mv=it->second;
            removeFromFreqLL(mv.ptr,0);
            freqNode* parent = (mv.ptr)->parentFreqNode;
            insertAfterSpecifiedFrequencyNode(parent,mv.ptr);
            if(parent->first==nullptr)
                deleteFreqNode(parent);

            return mv.value;
        }
    }
    
    void put(int key, int value) {
        if(capacity>0){
            if(get(key)==-1){
                if(presentCacheSize==capacity){
                    hashMap.erase(head->first->key);
                    removeFromFreqLL(head->first,1);
                    if(head->last==nullptr)
                        deleteFreqNode(head);
                    presentCacheSize--;
                }
                keyNode* temp = createKeyNode(key);
                insertAfterSpecifiedFrequencyNode(nullptr,temp);		
                mapValue mv = createMapValue(value,temp);
                hashMap.insert({key,mv});
                presentCacheSize++;
            }
            else{
                auto it =hashMap.find(key);
                (it->second).value=value;
            }
        }
    }
};


int main(){
	
}