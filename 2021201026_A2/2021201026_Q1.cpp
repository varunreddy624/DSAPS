#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class customClass{
    bool operator < (customClass b){

    }

    bool operator > (customClass b){

    }
};

template <typename T>
class AVL{
    public:
    typedef struct TreeNode{
        T data;
        int count,numberOfElementsToLeft,numberOfElementsToRight,height;
        TreeNode *left,*right;
    }TreeNode;
    
    struct Trunk{
        Trunk *prev;
        string str;
        Trunk(Trunk *prev, string str){
            this->prev = prev;
            this->str = str;
        }
    };

    TreeNode *root,*lower,*upper,*closest;



    AVL(){
        root=nullptr;
    }

    TreeNode* createTreeNode(T element){
        TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
        node->data=element;
        node->count=1;
        node->height=0;
        node->numberOfElementsToLeft=0;
        node->numberOfElementsToRight=0;
        node->left=nullptr;
        node->right=nullptr;
        return node;
    }
 
    void showTrunks(Trunk *p){
        if (p == nullptr)
            return;
        showTrunks(p->prev);
        cout << p->str;
    }

    void printTree(TreeNode* r, Trunk *prev, bool isLeft){

        if (r == nullptr) 
        return;
 
        string prev_str = "    ";
        Trunk *trunk = new Trunk(prev, prev_str);
    
        printTree(r->right, trunk, true);
 
        if (!prev) 
            trunk->str = "———";

        else if (isLeft){
            trunk->str = ".———";
            prev_str = "   |";
        }

        else {
            trunk->str = "`———";
            prev->str = prev_str;
        }
    
        showTrunks(trunk);
        cout << r->data << "," << r->count << "," << r->height << "," << r->numberOfElementsToLeft << "," << r->numberOfElementsToRight << "," << endl;
        
    
        if (prev) 
            prev->str = prev_str;
        
        trunk->str = "   |";
        printTree(r->left, trunk, false);
    }

// ------------------------------- MAIN API -------------------------------------

    bool search(T x){
        TreeNode *t=root;
        while(t!=nullptr){
            if(t->data==x)
                return true;

            else if(x>t->data)
                t=t->right;
            
            else
                t=t->left;
        }
        return false;
    }

    T countOccurencesOfElement(T x){
        TreeNode *t=root;
        while(t!=nullptr){
            if(t->data==x)
                return t->count;

            else if(x>t->data)
                t=t->right;
            
            else
                t=t->left;
        }
        return 0;
    }

    void lower_bound(TreeNode* r,T x){
        if(r!=nullptr){
            if(x==r->data)
                lower=r;
            else if(x<r->data)
                lower_bound(r->left,x);
            
            else{
                lower=r;
                lower_bound(r->right,x);
            }
        }
        return ;
    }

    void upper_bound(TreeNode* r,T x){
        if(r!=nullptr){
            if(x==r->data)
                upper=r;
            else if(x<r->data){
                upper=r;
                upper_bound(r->left,x);
            }
            
            else
                upper_bound(r->right,x);
        }
        return ;
    }

    void closestElementToSomeValue(TreeNode *r,T x){
        if(r!=nullptr){
            if(x==r->data)
                closest=r;
            else if(x<r->data){
                upper=r;
                closestElementToSomeValue(r->left,x);
            }
            
            else{
                lower=r;
                closestElementToSomeValue(r->right,x);
            }
        }
        else{
            if(x-lower->data <= upper->data -x)
                closest = lower;
            else
                closest = upper;
        }
    }

    int countElementsinRange(TreeNode* r,T lb,T ub){
        if(r!=nullptr){
            if(r->data >= lb && r->data<=ub)
                return r->count + countElementsinRange(r->right,lb,ub) + countElementsinRange(r->left,lb,ub);
            else if(r->data < lb)
                return countElementsinRange(r->right,lb,ub);
            else if(r->data > ub)
                return countElementsinRange(r->left,lb,ub);
        }
        return 0;
    }

    T getKthLargestElement(int k){
        TreeNode *r=root;
        int temp;
        T ans;
        while(r!=nullptr){
            temp=k-(r->numberOfElementsToRight);
            if(temp<=0)
                r=r->right;
            
            else if(temp<=r->count)
                return r->data;
            else{
                k-=(r->count+r->numberOfElementsToRight);
                r=r->left;
            }
        }
        return ans;
    }

    void deleteNodeRecursive(T x,TreeNode* r,TreeNode *parent){
        if(r!=nullptr){
            if(r->data==x){
                if(r->count>1)
                    (r->count)--;
                else if(r->left==nullptr || r->right==nullptr){
                    if(parent==nullptr)
                        root=getMaxOfNodes(r->left,r->right);
                    else{
                        if(x<parent->data)
                            parent->left=getMaxOfNodes(r->left,r->right);
                        else
                            parent->right=getMaxOfNodes(r->left,r->right);
                    }
                }
                else{
                    TreeNode *temp=r->right;
                    while(temp->left!=nullptr)
                        temp=temp->left;
                    T data = temp->data;
                    deleteNodeRecursive(data,r,nullptr);
                    r->data=data;
                }
            }
            else{
                if(x<r->data){
                    deleteNodeRecursive(x,r->left,r);
                    (r->numberOfElementsToLeft)--;
                }
                    
                else{
                    deleteNodeRecursive(x,r->right,r);
                    (r->numberOfElementsToRight)--;
                }
                fix_Node(r,parent);
            } 
        }
    }

    void insertNodeRecursive(T x,TreeNode *t,TreeNode* parent){
        if(t!=nullptr){
            if(t->data==x){
                (t->count)++;
    
            }
            else{
                if(x<t->data){
                    (t->numberOfElementsToLeft)++;
                    insertNodeRecursive(x,t->left,t); 
                }
                else{
                    (t->numberOfElementsToRight)++;
                    insertNodeRecursive(x,t->right,t);
                }
                fix_Node(t,parent);
            }
        }
        else{
            TreeNode* node = createTreeNode(x);
            if(parent==nullptr)
                root=node;
            else{
                if(x<parent->data)
                    parent->left=node;
                else
                    parent->right=node;
            }
        }
    }   

// ------------------------------- MAIN API -------------------------------------


// -------------------------- ROTATIONS -------------------------------------

    void LR(TreeNode* z,TreeNode* parent){
        TreeNode* y = z->left;
        RR(y,z);
        LL(z,parent);
    }

    void RL(TreeNode* z,TreeNode* parent){
        TreeNode* y=z->right;
        LL(y,z);
        RR(z,parent);
    }

    void LL(TreeNode* z,TreeNode* parent){
        TreeNode* y=z->left;
        TreeNode* x=y->left;
        TreeNode* temp=y->right;
        if(parent!=nullptr){
            if(z->data<parent->data)
                parent->left=y;
            else
                parent->right=y;
        }
        else
            root=y;
        y->right=z;
        z->left=temp;

        z->height=getHeight(z->left,z->right);
        y->height=getHeight(y->left,y->right);

        y->numberOfElementsToRight=y->numberOfElementsToRight+(1+z->numberOfElementsToRight);
        if(temp!=nullptr)
            z->numberOfElementsToLeft=temp->count+temp->numberOfElementsToLeft+temp->numberOfElementsToRight;
        else
            z->numberOfElementsToLeft=0;
    }

    void RR(TreeNode* z,TreeNode* parent){
        TreeNode* y=z->right;
        TreeNode* x=y->right;
        TreeNode* temp=y->left;
        if(parent!=nullptr){
            if(z->data<parent->data)
                parent->left=y;
            else
                parent->right=y;
        }
        else
            root=y;
        y->left=z;
        z->right=temp;

        z->height=getHeight(z->left,z->right);
        y->height=getHeight(y->left,y->right);

        y->numberOfElementsToLeft=y->numberOfElementsToLeft+(1+z->numberOfElementsToLeft);
        if(temp!=nullptr)
            z->numberOfElementsToRight=temp->count+temp->numberOfElementsToLeft+temp->numberOfElementsToRight;
        else
            z->numberOfElementsToRight=0;
    }


// -------------------------- ROTATIONS -------------------------------------

// ---------------------- HELPER FUNCTIONS -------------------------------

    void fix_Node(TreeNode* a,TreeNode* parent){
        TreeNode *t;
        if(getBalancingFactor(a)>1){
            t=a->left;
            if(t->left==nullptr || (t->right!=nullptr && t->left->height < t->right->height))
                LR(a,parent);
            else
                LL(a,parent);
        }
        else if(getBalancingFactor(a)<-1){
            t=a->right;
            if(t->right==nullptr || (t->left!=nullptr && t->right->height < t->left->height))
                RL(a,parent);
            else
                RR(a,parent); 
        }
        else
            a->height=getHeight(a->left,a->right);
    }

    TreeNode* getMaxOfNodes(TreeNode* a,TreeNode* b){
        if(a!=nullptr)
            return a;
        else if(b!=nullptr)
            return b;
        else
            return nullptr;
    }

    int getHeight(TreeNode* a,TreeNode* b){
        if(a!=nullptr && b!=nullptr)
            return 1+max(a->height,b->height);
        else if(a==nullptr && b!=nullptr)
            return 1+b->height;
        else if(a!=nullptr && b==nullptr)
            return 1+a->height;
        else
            return 0;
    }

    int getBalancingFactor(TreeNode* a){
        int left=-1,right=-1;
        if(a->left!=nullptr)
            left=a->left->height;
        if(a->right!=nullptr)
            right=a->right->height;
        return left-right;
    }

// ---------------------- HELPER FUNCTIONS -------------------------------


};


int main(){
     #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        freopen("err.txt","w",stderr);
    #endif
    AVL<int> tree;

    tree.insertNodeRecursive(13,tree.root,nullptr);

    tree.insertNodeRecursive(10,tree.root,nullptr);
    tree.insertNodeRecursive(15,tree.root,nullptr);

    tree.insertNodeRecursive(5,tree.root,nullptr);
    tree.insertNodeRecursive(11,tree.root,nullptr);
    tree.insertNodeRecursive(16,tree.root,nullptr);
    tree.insertNodeRecursive(14,tree.root,nullptr);

    tree.insertNodeRecursive(4,tree.root,nullptr);
    tree.insertNodeRecursive(4,tree.root,nullptr);
    tree.insertNodeRecursive(4,tree.root,nullptr);
    tree.insertNodeRecursive(6,tree.root,nullptr);
        // LL 
        tree.insertNodeRecursive(3,tree.root,nullptr);

        //LR
        // tree.insertNodeRecursive(7,tree.root,nullptr);

    tree.printTree(tree.root,nullptr,false);

    cout << tree.countElementsinRange(tree.root,7,14) << endl;
}