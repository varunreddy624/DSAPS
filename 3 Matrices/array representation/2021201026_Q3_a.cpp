#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<cstring>

using namespace std;

template <typename T>
struct arrayNode{
	int row,column;
	T value;
};


template <typename T>
class Solution{
public:
	arrayNode<T> *resOfAdn,*resOfMuln;
	int addUsingArrays(arrayNode<T>* a,int k1,arrayNode<T>* b,int k2){
		int i=0,j=0,k=0,k3=0;
		while(i<k1 || j<k2){
			if(i==k1)
				j++,k3++;
			else if(j==k2)
				i++,k3++;
			else if(a[i].row<b[j].row || (a[i].row==b[j].row && a[i].column<b[j].column))
				i++,k3++;
			else if(a[i].row>b[j].row || (a[i].row==b[j].row && a[i].column>b[j].column))
				j++,k3++;
			else{
				if(a[i].value+b[j].value!=0)
					k3++;
				i++,j++;
			}
		}

		resOfAdn = (arrayNode<T>*)(malloc(k3*sizeof(arrayNode<T>)));
		i=0,j=0,k=0;
		while(i<k1 || j<k2){
			if(i==k1){
				resOfAdn[k].row=b[j].row;
				resOfAdn[k].column=b[j].column;
				resOfAdn[k].value=b[j].value;
				j++,k++;
			}
			else if(j==k2){
				resOfAdn[k].row=a[i].row;
				resOfAdn[k].column=a[i].column;
				resOfAdn[k].value=a[i].value;
				i++,k++;
			}
			else if(a[i].row<b[j].row || (a[i].row==b[j].row && a[i].column<b[j].column)){
				resOfAdn[k].row=a[i].row;
				resOfAdn[k].column=a[i].column;
				resOfAdn[k].value=a[i].value;
				i++,k++;
			}
			else if(a[i].row>b[j].row || (a[i].row==b[j].row && a[i].column>b[j].column)){
				resOfAdn[k].row=b[j].row;
				resOfAdn[k].column=b[j].column;
				resOfAdn[k].value=b[j].value;
				j++,k++;
			}
			else{
				if(a[i].value+b[j].value!=0){
					resOfAdn[k].row=b[j].row;
					resOfAdn[k].column=b[j].column;
					resOfAdn[k].value=a[i].value+b[j].value;
					k++;
				}
				i++,j++;
			}
		}
		return k3;
	}


	T mulUtil(arrayNode<T>* a,int astart,int aend,arrayNode<T>* b,int bstart,int bend){
		T res=0;
		if(astart==aend || bstart==bend)
			return 0;
		else{
			int i,j;
			i=astart;
			j=bstart;
			while(i<aend && j<bend){
				if(a[i].column<b[j].column)
					i++;
				else if(b[j].column<a[i].column)
					j++;
				else{
					res+=(a[i].value * b[j].value);
					i++;
					j++;
				}
			}
			return res;
		}
	}

	int mulUsingArrays(arrayNode<T>* a,int k1,arrayNode<T>* b,int columns,int k2){
		arrayNode<T>* bTranspose=fastTraspose(b,columns,k2);

		int i=0,j=0,k=0,k3=0,prevrowa=-1,prevcolb=-1,astart=-1,aend=-1,bstart=-1,bend=-1;
		T res;

		while(i<=k1){
			if(i==k1 || a[i].row!=prevrowa){
				if(j<=k2){
					if(j==k2 || bTranspose[j].row!=prevcolb){
						res=mulUtil(a,astart,aend,bTranspose,bstart,bend);
						if(res!=0)
							k3++;
						if(j==k2){
							if(i==k1)
								break;
							j=0;
							prevrowa=a[i].row;
							astart=i;
							aend=i;
						}
						prevcolb=bTranspose[j].row;
						bstart=j;
						bend=j;
					}
					else{
						bend++;
						j++;
					}
				}
				else{
					prevrowa=a[i].row;
					astart=i;
					aend=i;
				}
			}
			else{
				aend++;
				i++;
			}
		}

		resOfMuln = (arrayNode<T>*)(malloc(k3*sizeof(arrayNode<T>))); 

		i=0,j=0,k=0,prevrowa=-1,prevcolb=-1,astart=-1,aend=-1,bstart=-1,bend=-1;

		while(i<=k1){
			if(i==k1 || a[i].row!=prevrowa){
				if(j<=k2){
					if(j==k2 || bTranspose[j].row!=prevcolb){
						res=mulUtil(a,astart,aend,bTranspose,bstart,bend);
						if(res!=0){
							resOfMuln[k].row=prevrowa;
							resOfMuln[k].column=prevcolb;
							resOfMuln[k].value=res;
							k++;
						}
						if(j==k2){
							if(i==k1)
								break;
							j=0;
							prevrowa=a[i].row;
							astart=i;
							aend=i;
						}
						prevcolb=bTranspose[j].row;
						bstart=j;
						bend=j;
					}
					else{
						bend++;
						j++;
					}
				}
				else{
					prevrowa=a[i].row;
					astart=i;
					aend=i;
				}
			}
			else{
				aend++;
				i++;
			}
		}
		return k3;
	}

	arrayNode<T>* fastTraspose(arrayNode<T>* a,int columns,int k){
		arrayNode<T>* res=(arrayNode<T>*)(malloc(k*sizeof(arrayNode<T>)));
		int i,c=0,numberOfValueBeforeColumn[columns+1] = {0};
		for(i=0;i<k;i++)
			numberOfValueBeforeColumn[a[i].column+1]++;
		for(i=2;i<columns+1;i++)
			numberOfValueBeforeColumn[i]+=numberOfValueBeforeColumn[i-1];
		for(i=0;i<k;i++){
			res[numberOfValueBeforeColumn[a[i].column]].row=a[i].column;
			res[numberOfValueBeforeColumn[a[i].column]].column=a[i].row;
			res[numberOfValueBeforeColumn[a[i].column]].value=a[i].value;
			numberOfValueBeforeColumn[a[i].column]++;
		}
		return res;
	}

	arrayNode<T>* readValuesUsingArrays(){
		int r,c,i,j,k=0;
		cin >> r >> c;
		T arr[r][c];
		for(i=0;i<r;i++){
			for(j=0;j<c;j++){
				cin >> arr[i][j];
				if(arr[i][j]!=0)
					k++;
			}
		}
		arrayNode<T>* a = (arrayNode<T>*)(malloc(k*sizeof(arrayNode<T>)));
		k=0;
		for(i=0;i<r;i++){
			for(j=0;j<c;j++){
				if(arr[i][j]!=0){
					a[k].row=i;
					a[k].column=j;
					a[k].value=arr[i][j];
					k++;
				}
			}
		}
		printArray(a,k);
		return a;
	}


	void printArray(arrayNode<T>* a,int k){
		for(int i=0;i<k;i++)
			cout << "[" << a[i].row << "  " << a[i].column << "]==>" << a[i].value << endl;
		cout << endl;
	}
};


int main(){

	int r1,c1,r2,c2,k1,k2;

	Solution<float> solution;

	arrayNode<float>* a = solution.readValuesUsingArrays();
	arrayNode<float>* b = solution.readValuesUsingArrays();

	solution.printArray(solution.resOfAdn,solution.addUsingArrays(a,4,b,3));

	arrayNode<float>* bTranspose = solution.fastTraspose(b,2,3);

	solution.printArray(bTranspose,3);

	solution.printArray(solution.resOfMuln,solution.mulUsingArrays(a,4,b,2,3));

}