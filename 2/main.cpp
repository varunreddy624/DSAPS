#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#define NUMBER_OF_INTS_PER_FILE 4 // 10 MB

using namespace std;

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

    for(int i=0;i<numberOfFiles;i++){

        t= NUMBER_OF_INTS_PER_FILE;
        int temp;
        fileArray.clear();

        while(t--){
            fscanf(filePointer,"%d,",&temp);   
            fileArray.push_back(temp);
        }
        sort(fileArray.begin(),fileArray.end());

        FILE *filePointertemp=fopen(("temp_files/temp"+to_string(i)+".txt").c_str(), "w");
        t= 0;
        while(t<NUMBER_OF_INTS_PER_FILE)
            fprintf(filePointertemp,"%d\n",fileArray[t++]);   

        fclose(filePointertemp);
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

        FILE *filePointertemp=fopen(("temp_files/temp"+to_string(numberOfFiles-1)+".txt").c_str(), "w");
        t= 0;
        while(t<noOfIntsInLastFile)
            fprintf(filePointertemp,"%d\n",fileArray[t++]);   

        fclose(filePointertemp);
    }
    fclose(filePointer);

    // --------------------------------------------
}
