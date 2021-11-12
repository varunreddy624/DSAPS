#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<cstring>

using namespace std;

template <typename T>
struct singlyLinkedListNode{
	int column;
	T value;
	singlyLinkedListNode<T> *next;
};

template <typename T>
class Solution{

	public:
		singlyLinkedListNode<T>* createSinglyLinkedListNode(int column, T value){
			singlyLinkedListNode<T>* temp=(singlyLinkedListNode<T>*)(malloc(sizeof(singlyLinkedListNode<T>)));
			temp->column=column;
			temp->value=value;
			temp->next=nullptr;
			return temp;
		}

		T mulTwoLinkedLists(singlyLinkedListNode<T>* a,singlyLinkedListNode<T>* b){
			singlyLinkedListNode<T> *tempa=a,*tempb=b;
			T res=0;
			while(tempa!=nullptr && tempb!=nullptr){
				if(tempb->column<tempa->column)
					tempb=tempb->next;
				else if(tempa->column<tempb->column)
					tempa=tempa->next;
				else{
					res+=(tempa->value * tempb->value);
					tempa=tempa->next;
					tempb=tempb->next;
				}
			}
			return res;
		}


		singlyLinkedListNode<T>* addTwoLinkedLists(singlyLinkedListNode<T>* a,singlyLinkedListNode<T>* b){
			singlyLinkedListNode<T> *temp,*tempa=a,*tempb=b,*head=nullptr,*tail=nullptr;
			while(tempa!=nullptr || tempb!=nullptr){
				if(tempa==nullptr || tempb->column<tempa->column){
					temp = createSinglyLinkedListNode(tempb->column,tempb->value);
					tempb=tempb->next;
				}
				else if(tempb==nullptr || tempa->column<tempb->column){
					temp = createSinglyLinkedListNode(tempa->column,tempa->value);
					tempa=tempa->next;
				}
				else{
					if(tempa->value+tempb->value!=0)
						temp=createSinglyLinkedListNode(tempa->column,tempa->value+tempb->value);
					else
						temp=nullptr;
					tempa=tempa->next;
					tempb=tempb->next;
				}
				if(temp!=nullptr){
					if(head==nullptr)
						head=temp;
					else
						tail->next=temp;
					tail=temp;
				}
			}
			return head;
		}


		singlyLinkedListNode<T>** addMatricesUsingLikedLists(singlyLinkedListNode<T>** a,singlyLinkedListNode<T>** b,int rows){
			int i;
			singlyLinkedListNode<T>** result=(singlyLinkedListNode<T>**)(malloc(rows*sizeof(singlyLinkedListNode<T>*)));
			for(i=0;i<rows;i++)
				result[i]=addTwoLinkedLists(a[i],b[i]);
			return result;
		}


		singlyLinkedListNode<T>** transposeAdjList(singlyLinkedListNode<T>** a,int rows,int columns){
			singlyLinkedListNode<T>** result = (singlyLinkedListNode<T>**)(malloc(columns*sizeof(singlyLinkedListNode<T>*)));
			singlyLinkedListNode<T>** lastPointers=(singlyLinkedListNode<T>**)(malloc(columns*sizeof(singlyLinkedListNode<T>*)));
			singlyLinkedListNode<T>* temp;
			int i;
			for(i=0;i<columns;i++)
				result[i]=nullptr;
			for(i=0;i<rows;i++){
				temp=a[i];
				while(temp!=nullptr){
					singlyLinkedListNode<T>* temp2=createSinglyLinkedListNode(i,temp->value);
					if(result[temp->column]==nullptr)
						result[temp->column]=temp2;
					else
						lastPointers[temp->column]->next=temp2;
					lastPointers[temp->column]=temp2;
					temp=temp->next;
				}
			}
			free(lastPointers);
			return result;
		}


		singlyLinkedListNode<T>** mulMatricesUsingLikedLists(singlyLinkedListNode<T>** a,singlyLinkedListNode<T>** b,int rows1,int columns1,int columns2){
			singlyLinkedListNode<T>** btranspose = transposeAdjList(b,columns1,columns2);
			singlyLinkedListNode<T>** result=(singlyLinkedListNode<T>**)(malloc(rows1*sizeof(singlyLinkedListNode<T>*)));
			int i,j;
			T res;
			singlyLinkedListNode<T> *temp,*tail;
			for(i=0;i<rows1;i++){
				result[i]=nullptr;
				for(j=0;j<columns2;j++){
					res=mulTwoLinkedLists(a[i],btranspose[j]);
					if(res!=0){
						temp = createSinglyLinkedListNode(j,res);
						if(result[i]==nullptr)
							result[i]=temp;
						else
							tail->next=temp;
						tail=temp;
					}
				}
			}
			return result;
		}


		singlyLinkedListNode<T>** readValuesUsingAdjLists(){
			singlyLinkedListNode<T> *tail,*temp;
			int i,j,r,c;
			cin >> r >> c;
			T arr[r][c];
			singlyLinkedListNode<T>** a = (singlyLinkedListNode<T>**)(malloc(r*sizeof(singlyLinkedListNode<T>*)));
			for(i=0;i<r;i++)
				a[i]=nullptr;
			for(i=0;i<r;i++){
				for(j=0;j<c;j++){
					cin >> arr[i][j];
					if(arr[i][j]!=0){
						temp=createSinglyLinkedListNode(j,arr[i][j]);
						if(a[i]==nullptr)
							a[i]=temp;
						else
							tail->next=temp;
						tail=temp;
					}
				}
			}
			return a;
		}


		void printAdjList(singlyLinkedListNode<T>** a,int rows){
			singlyLinkedListNode<T>* temp;
			int i;
			for(i=0;i<rows;i++){
				printf("row =%d ->",i);
				temp=a[i];
				while(temp!=nullptr){
					cout << "[" << temp->column << "  " << temp->value << "]==>"; 
					temp=temp->next;
				}
				cout << endl;
			}
			cout << endl;
		}

};

int main(){
	int r1,c1,r2,c2,k1,k2;

	Solution<double> sol;

	singlyLinkedListNode<double>** arr1=sol.readValuesUsingAdjLists();
	singlyLinkedListNode<double>** arr2=sol.readValuesUsingAdjLists();


	sol.printAdjList(arr1,2);
	sol.printAdjList(arr2,2);


	singlyLinkedListNode<double>** transposeArr1=sol.transposeAdjList(arr1,2,2);
	singlyLinkedListNode<double>** transposeArr2=sol.transposeAdjList(arr2,2,2);

	sol.printAdjList(transposeArr1,2);
	sol.printAdjList(transposeArr2,2);

	singlyLinkedListNode<double>** resultOfAdn=sol.addMatricesUsingLikedLists(arr1,arr2,2);

	sol.printAdjList(resultOfAdn,2);

	singlyLinkedListNode<double>** resultOfMuln=sol.mulMatricesUsingLikedLists(arr1,arr2,2,2,2);

	sol.printAdjList(resultOfMuln,2);

}
