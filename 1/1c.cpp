#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <climits>
#include <math.h>
#include <algorithm>

using namespace std;

class SegmentTree{
    public:
        int n;
        vector<int> segmentTree;
        int RMQ(int segmentStart, int segmentEnd, int queryStart, int queryEnd, int index)
        {
            if (queryStart <= segmentStart && queryEnd >= segmentEnd)
                return segmentTree[index];

            if (segmentEnd < queryStart || segmentStart > queryEnd)
                return INT_MAX;

            int mid = segmentStart + (segmentEnd-segmentStart)/2 ;
            return min(RMQ(segmentStart, mid, queryStart, queryEnd, 2*index+1),RMQ(mid+1, segmentEnd, queryStart, queryEnd, 2*index+2));
        }

        int getMinRange(int i,int j){
            return RMQ(0,n-1,i,j,0);
        }

        int constructSTUtil(vector<int>& arr, int segmentStart, int segmentEnd, int segmentIndex)
        {
            if (segmentStart == segmentEnd){
                segmentTree[segmentIndex] = arr[segmentStart];
                return arr[segmentStart];
            }

            int mid = segmentStart + (segmentEnd-segmentStart)/2 ;
            segmentTree[segmentIndex] = min(constructSTUtil(arr, segmentStart, mid, segmentIndex*2+1),constructSTUtil(arr, mid+1, segmentEnd, segmentIndex*2+2));
            return segmentTree[segmentIndex];
        }

        void constructST(vector<int>& arr)
        {
            n=arr.size();
            int x = (int)(ceil(log2(n)));

            int max_size = 2*(int)pow(2, x) - 1;

            segmentTree.resize(max_size);

            constructSTUtil(arr, 0, n-1, 0);

            return ;
        }
};

bool cmp(vector<int> a,vector<int> b){
    if(a[0]==b[0]){
        if(a[1]<b[1])
            return 1;
        else
            return 0;
    }
    else{
        if(a[0]<b[0])
            return 1;
        else
            return 0;
    }
}

vector<int> getSuffixArray(string s){
    s=s+"$";
    int i,k,n = s.length(),r;
    
    vector<vector<int>> RA(n,vector<int>(3,0)); 
    
    for(i=0;i<n;i++){
        RA[i][0]=s[i];
        RA[i][2]=i;
    }

    /*
        RA[i][0] = s[i]
        RA[i][1] = s[i+k]
        RA[i][2] = SA[i]
    */
    
    for(k=1;k<n;k*=2){

        vector<int> ind(n,0); // S[i] to original index mapping
        for(i=0;i<n;i++)
            ind[RA[i][2]]=i;

        for(i=0;i<n;i++)
             RA[i][1] = (RA[i][2]+k<n) ? RA[ind[RA[i][2]+k]][0] : 0;

        stable_sort(RA.begin(),RA.end(),cmp);   // sort RA
        

        vector<int> tempRA(n,0);
        r=0;
        tempRA[0]=r; // will be zero since 1st suffix in sorted suffixes will have rank zero
        for(i=1;i<n;i++){
            if(RA[i][0] == RA[i-1][0] && RA[i][1] == RA[i-1][1])
                tempRA[i]=r;
            else
                tempRA[i]=++r;
        }

        for(i=0;i<n;i++)
            RA[i][0]=tempRA[i];

    }
    vector<int> SA(n-1,0);
    for(i=1;i<n;i++)
        SA[i-1]=RA[i][2];
    
    return SA;
}

vector<int> getRankArr(vector<int>& SA){
    int n=SA.size();
    vector<int> RANK(n,0);
    for(int i=0;i<n;i++)
        RANK[SA[i]]=i;
    return RANK;
}

vector<int> getLCPFromSA(string s,vector<int>& SA,vector<int>& RANK){
    int h=0,k,n=s.length();
    vector<int> LCP(n,0);
    for(int i=0;i<n;i++){
        if(RANK[i]>0){
            k=SA[RANK[i]-1];
            while(s[i+h]==s[k+h])
                h++;
            LCP[RANK[i]]=h;
            if(h>0)
                h--;
        }
    }
    return LCP;
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        freopen("err.txt","w",stderr);
    #endif
    string s;
    cin >> s;
    int n=s.length(),k,i;
    string srev="";
    for(int i=n-1;i>=0;i--)
        srev+=s[i];
    s=s+"~"+srev;
    vector<int> SA = getSuffixArray(s);
    vector<int> RANK = getRankArr(SA);
    vector<int> LCP = getLCPFromSA(s,SA,RANK);

    int ind=SA[0],length=1;

    SegmentTree st;
    st.constructST(LCP);
    
    int leftInd,rightInd,leftEvenInd,rightEvenInd,leftOddInd,rightOddInd,oddLen,evenLen;

    for(i=0;i<2*n;i++){

            if(SA[i]>n){
                rightInd=SA[i];
                leftOddInd=RANK[(2*n)-rightInd];
                leftEvenInd=(((2*n)-rightInd+1)<2*n) ? RANK[(2*n)-rightInd+1] : 2*n;
                int oddLCP = st.getMinRange(min(leftOddInd,i)+1,max(leftOddInd,i));
                int evenLCP = st.getMinRange(min(leftEvenInd,i)+1,max(leftEvenInd,i));
                oddLen = (oddLCP==INT_MAX) ? 0 :(2*oddLCP)-1;
                evenLen = (evenLCP==INT_MAX)? 0 : (2*evenLCP);
                if(oddLen > evenLen){
                    if(oddLen > length){
                        length=oddLen;
                        ind = (2*n)-rightInd-oddLCP+1;
                    }
                }
                else{
                    if(evenLen > length){
                        length=evenLen;
                        ind = (2*n)-rightInd+1-evenLCP;
                    } 
                }
            }

            else{
                leftInd=SA[i];
                rightEvenInd= (((2*n)-leftInd+1)<2*n) ? RANK[(2*n)-leftInd+1] : 2*n ;
                rightOddInd=RANK[(2*n)-leftInd];
                int oddLCP = st.getMinRange(min(rightOddInd,i)+1,max(rightOddInd,i));
                int evenLCP = st.getMinRange(min(rightEvenInd,i)+1,max(rightEvenInd,i));
                oddLen = (oddLCP==INT_MAX) ? 0 :(2*oddLCP)-1;
                evenLen = (evenLCP==INT_MAX)? 0 : (2*evenLCP);
                if(oddLen > evenLen){
                    if(oddLen > length){
                        length=oddLen;
                        ind = leftInd-oddLCP+1;
                    }
                }
                else{
                    if(evenLen > length){
                        length=evenLen;
                        ind = leftInd-evenLCP;
                    } 
                }
            }
    }
    cout << s.substr(ind,length);
}