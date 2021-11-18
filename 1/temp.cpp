#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <climits>
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
            int x = (int)(ceil(log2(n)));
            n=arr.size();

            int max_size = 2*(int)pow(2, x) - 1;

            segmentTree.resize(max_size);

            constructSTUtil(arr, 0, n-1, 0);

            return ;
        }
};


int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        freopen("err.txt","w",stderr);
    #endif

	vector<int> arr{1, 3, 2, -100, 9, -1100};

    SegmentTree s;
	s.constructST(arr);

	int qs = 0; // Starting index of query range
	int qe = 4; // Ending index of query range

	// Print minimum value in arr[qs..qe]
	cout<<"Minimum of values in range ["<<qs<<", "<<qe<<"] "<<
	"is = "<<s.getMinRange(qs,qe)<<endl;

	return 0;
}
