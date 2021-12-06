#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#define NUMBER_OF_INTS_PER_FILE 1000000 //

using namespace std;

typedef struct fileData{
    int data;
    int valuesOver;
    int totalValuesPossible;
    FILE* fileptr;
}fileData;

class Heap{
    public:
        vector<fileData> heap;
        int size(){
            return heap.size();
        } 
        fileData top(){
            return heap[0];
        }
        void swap(int i,int j){
            int t;

            t=heap[i].data;
            heap[i].data=heap[j].data;
            heap[j].data=t;

            t=heap[i].valuesOver;
            heap[i].valuesOver=heap[j].valuesOver;
            heap[j].valuesOver=t;

            t=heap[i].totalValuesPossible;
            heap[i].totalValuesPossible=heap[j].totalValuesPossible;
            heap[j].totalValuesPossible=t;

            FILE* tempPtr = heap[i].fileptr;
            heap[i].fileptr=heap[j].fileptr;
            heap[j].fileptr=tempPtr;
        }

        void push(fileData data){
            heap.push_back(data);
            int i=heap.size()-1,parent;
            while(i>0){
                parent = (i-1)/2;
                if(heap[i].data<heap[parent].data){
                    swap(i,parent);
                    i=parent;
                }
                else
                    break;
            }
        }
        void pop(){
            fileData lastElem = heap.back();
            heap.pop_back();
            if(heap.size()>0){
                int next=-1,minimum;

                heap[0].data=lastElem.data;
                heap[0].valuesOver=lastElem.valuesOver;
                heap[0].totalValuesPossible=lastElem.totalValuesPossible;
                heap[0].fileptr=lastElem.fileptr;

                int i=0,child1,child2;
                while(i<heap.size()){   
                    child1=(2*i)+1;
                    child2=(2*i)+2;
                    minimum = heap[i].data;
                    if(child1<heap.size()){
                        if(heap[child1].data < minimum){
                            minimum=heap[child1].data;
                            next=child1;
                        }
                    }
                    if(child2<heap.size())
                        if(heap[child2].data < minimum)
                            next=child2;
                    if(next==-1)
                        break;
                    swap(i,next);
                    i=next;
                    next=-1;
                }
            }
        }
};


int main(int argc,char** argv){
    FILE *filePointer;
    filePointer = fopen(argv[1], "r");

    if (filePointer == NULL)
    {
        printf("error reading file\n");
        return 0;
    }

    int t,c=0;
    while(fscanf(filePointer,"%d,",&t) !=EOF)
        c++;
    
    fclose(filePointer);

    // ------------------------------------------------

    filePointer = fopen(argv[1], "r");

    if (filePointer == NULL)
    {
        printf("error reading file\n");
        return 0;
    }

    int numberOfFiles = c / NUMBER_OF_INTS_PER_FILE;

    vector<int> fileArray;
    vector<fileData> fileMetaData;

    for(int i=0;i<numberOfFiles;i++){

        t= NUMBER_OF_INTS_PER_FILE;
        int temp;
        fileArray.clear();

        while(t--){
            fscanf(filePointer,"%d,",&temp);   
            fileArray.push_back(temp);
        }
        sort(fileArray.begin(),fileArray.end());

        FILE *filePointerTemp=fopen(("temp_files/"+to_string(i)+".txt").c_str(), "w");

        fileData d = {fileArray[0],0,NUMBER_OF_INTS_PER_FILE,filePointerTemp};
        fileMetaData.push_back(d);

        t= 0;
        while(t<NUMBER_OF_INTS_PER_FILE)
            fprintf(filePointerTemp,"%d,",fileArray[t++]);   

        fclose(filePointerTemp);
    }

    if(c%NUMBER_OF_INTS_PER_FILE != 0){
        numberOfFiles++;
        int noOfIntsInLastFile = c%NUMBER_OF_INTS_PER_FILE;
        t= noOfIntsInLastFile;
        int temp;
        fileArray.clear();

        while(t--){
            fscanf(filePointer,"%d,",&temp);   
            fileArray.push_back(temp);
        }
        sort(fileArray.begin(),fileArray.end());

        FILE *filePointerTemp=fopen(("temp_files/"+to_string(numberOfFiles-1)+".txt").c_str(), "w");

        fileData d = {fileArray[0],0,noOfIntsInLastFile,filePointerTemp};
        fileMetaData.push_back(d);

        t= 0;
        while(t<noOfIntsInLastFile)
            fprintf(filePointerTemp,"%d,",fileArray[t++]);  

        fclose(filePointerTemp); 
    }
    fclose(filePointer);

    Heap heap;

    for(int i=0;i<numberOfFiles;i++){
        FILE *filePointerTemp=fopen(("temp_files/"+to_string(i)+".txt").c_str(), "r");
        int t;
        fscanf(filePointerTemp,"%d,",&t);
        fileMetaData[i].fileptr=filePointerTemp;
        heap.push(fileMetaData[i]);
    }

    FILE *writeFP=fopen(argv[2], "w");

    while(heap.size()!=1){
        fileData temp = heap.top();
        heap.pop();
        fprintf(writeFP,"%d,",temp.data);
        if(temp.valuesOver<temp.totalValuesPossible){
            temp.valuesOver++;
            int t;
            fscanf(temp.fileptr,"%d,",&t);
            temp.data=t;
            heap.push(temp);
        }
        else{
            fclose(temp.fileptr);
        }
    }

    fprintf(writeFP,"%d",heap.heap[0].data);

    fclose(writeFP);
    // --------------------------------------------
    
}
