#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

template <typename T>
class deque{
    public:
    int maxCapacity,currentSize,f,r;
    T *q;
    deque(){
        maxCapacity=0;
        currentSize=0;
        f=-1;
        r=0;
    }
    deque(int n,T x){
        q=(T*)malloc(n*sizeof(T));
        for(int i=0;i<n;i++)
            q[i]=x;
        maxCapacity=n;
        currentSize=0;
        f=-1;
        r=0;
    }

    bool empty(){
        return currentSize==0;
    }

    T front(){
        if(currentSize!=0)
            return q[f];
    }

    T back(){
        if(currentSize!=0)
            return q[r];
    }

    int size(){
        return currentSize;
    }

    void push_back(T x){
        if(currentSize<maxCapacity){
            currentSize++;
            if(f==-1){
                f=0;
                r=0;
            }
            else
                r=(r+1)%maxCapacity;
            q[r]=x;
        }
    }

    void push_front(T x){
        if(currentSize<maxCapacity){
            currentSize++;
            if(f==-1){
                f=0;
                r=0;
            }
            else{
                if(f==0)
                    f=maxCapacity-1;
                else
                    f--;
            }
            q[f]=x;
        }
    }

    T pop_front(){
        if(!empty()){
            T ret = q[f];
            if(currentSize==1){
                f=-1;
                r=0;
            }
            else
                f=(f+1)%maxCapacity;
            currentSize--;
            return ret;
        }
    }

    T pop_back(){
        if(!empty()){
            T ret = q[r];
            if(currentSize==1){
                f=-1;
                r=0;
            }
            else if(r==0)
                r=maxCapacity-1;
            else
                r--;
            currentSize--;
            return ret;
        }
    }

    void printQueue(){
        for(int i=0;i<maxCapacity;i++)
            cout << q[i] << " ";
        cout << "f->" << f << " " << "r->" << r << endl;
    }

    void clear(){
        free(q);
        deque();
    }

    void resize(int x,T d){
        T * temp=(T*)malloc(x*sizeof(T));
        int i,t=currentSize;
        for(i=0;i<x;i++)
            temp[i]=d;
        for(i=0;i<t;i++)
            temp[i]=pop_front();
        currentSize=t;
        maxCapacity=x;
        f=0;
        r=t-1;
        free(q);
        q=temp;
    }

    T operator [] (int n){
        if(n<currentSize)
            return q[(f+n)%maxCapacity];
    }
};

int main(){
     #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        freopen("err.txt","w",stderr);
    #endif
    deque<char> q(7,'9');
    q.push_back('1');
    q.push_back('2');
    q.push_back('3');
    q.push_back('4');
    q.push_back('5');
    q.push_back('6');
    q.push_back('7');
    q.printQueue();
    q.pop_back();
    q.pop_front();
    q.pop_front();
    q.pop_front();
    q.printQueue();
    q.push_front('8');
    q.printQueue();
    q.resize(11,'0');
    q.printQueue();
    // cout << q.back()<< endl;
    // q.push_front(15);
    // cout << q.front()<< endl;
    
    // cout << q.front()<< endl;
}