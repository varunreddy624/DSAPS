#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <typeinfo>
#include <sstream>

using namespace std;

typedef struct LinkedList LinkedList;

template <typename K,typename V>
class HashMap{

    struct LinkedList{
        K key;
        V value;
        LinkedList* next;
    };

    public:

    int tablesize=4099,alpha=33,index,size=0;
    LinkedList *prev,*curr;
    LinkedList** hashTable = (LinkedList**)malloc(tablesize*sizeof(LinkedList*));

        HashMap(){
            for(int i=0;i<tablesize;i++)
                hashTable[i]=nullptr;
        }

        LinkedList* createNode(K k,V v){
            LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
            node->key=k;
            node->value=v;
            node->next=nullptr;
            return node;
        }

        long long binPow(int base,int exp){
            long long res=1,a = base;
            while(exp){
                if(exp%2==1)
                    res=(res*a)%tablesize;
                a=a*a;
                exp=exp/2;
            }
            return res;
        }

        int hashValueOfString(K k){
            string s;
            s=to_string(k);

            int i,n=s.length();
            long long hash=0,alphapower = binPow(alpha,n);
            for(i=0;i<n;i++){
                alphapower=alphapower/alpha;
                hash=(hash+(alphapower*(int)(s[i])))%tablesize;
            }
            return (int)hash;
        } 

        void commonRoutine(K key){
            index=hashValueOfString(key);
            prev=nullptr,curr=hashTable[index];
            while(curr!=nullptr && curr->key!=key){
                prev=curr;
                curr=curr->next;
            }
        }

        void insert(K key,V value){
            commonRoutine(key);
            if(curr==nullptr){
                LinkedList* node = createNode(key,value);
                node->next=hashTable[index];
                hashTable[index]=node;
                size++;
            }
            else
                curr->value=value;
        }

        void erase(K key){
            commonRoutine(key);
            if(curr!=nullptr){
                if(prev!=nullptr)
                    prev->next=curr->next;
                else
                    hashTable[index]=nullptr;
                size--;
                free(curr);
            }
        }

        bool find(K key){
            commonRoutine(key);
            return curr!=nullptr;
        }

        V operator [] (K key){
            V value;
            commonRoutine(key);
            if(curr!=nullptr)
                return curr->value;
            else
                return value;
        }

        string to_string(K k){
            ostringstream buffer;
            buffer << k;
            return buffer.str();
        }

        void printMap(){
            for(int i=0;i<tablesize;i++){
                if(hashTable[i]!=nullptr){
                    cout << i << "->";
                    LinkedList* t= hashTable[i];
                    while(t!=nullptr){
                        cout << t->key << " " << t->value << "->";
                        t=t->next;
                    }
                    cout << endl;
                }
            }
        }

};

int main(){

    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        freopen("err.txt","w",stderr);
    #endif
    // cout << "hi" << endl;
    HashMap<int,int> map;
    map.insert(101,100);
    map.insert(102,2);

    cout << map[101] << endl << map[102];
    // int t,n,k,i;
    // cin >> t;
    // while(t--){
    //     cin >> n >> k;
    //     int arr[n];
    //     HashMap<int,int> hm;
    //     for(i=0;i<n;i++)
    //         cin >> arr[i];
    //     for(i=0;i<k;i++){
    //         if(hm.find(arr[i]))
    //             hm.insert(arr[i],hm[arr[i]]+1);
    //         else
    //             hm.insert(arr[i],1);
    //     }
    //     cout << hm.size << " ";
    //     // hm.printMap();
    //     // cout << endl;
    //     for(i=k;i<n;i++){
    //         if(hm[arr[i-k]]==1)
    //             hm.erase(arr[i-k]);
    //         else
    //             hm.insert(arr[i-k],hm[arr[i-k]]-1);
    //         if(hm.find(arr[i]))
    //             hm.insert(arr[i],hm[arr[i]]+1);
    //         else
    //             hm.insert(arr[i],1);
    //         cout << hm.size << " ";
    //         // hm.printMap();
    //         // cout << endl;
    //     }
    //     cout << endl;
    // }
}