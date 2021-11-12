#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


class Stack{
    int tos,stackCapacity;
    string stack[9999];
public:
    void initializeStack(int capacity){
        tos=-1;
        stackCapacity=capacity;
    }
    void push(string ch){
        stack[++tos]=ch;
    }
    string pop(){
        return stack[tos--];
    }
    string top(){
        return stack[tos];
    }
    bool empty(){
        return tos==-1;
    }
    bool compareOperators(string a){
        if(top()=="+" || top()=="-"){
            if(a=="+" || a=="-")
                return true;
            else
                return false;
        }
        else
            return true;
    }
};


string trimLeadingZeroes(string& a){
    int i=0,n=a.length();
    while(i<n && a[i]=='0')
        i++;
    if(i==n)
        return "0";
    else
        return a.substr(i,n-i);
}


//-------------------------------- ADD ---------------------------------

    char addStringsUtil(string& X,int start,int end,string& Y){
        int s,i=end,j=Y.length()-1,c=0;
        while(i>=start || j>=0){
            s=(X[i]-'0')+c;
            if(j>=0){
                s+=(Y[j]-'0');
                j--;
            }
            c=(int)s/10;
            X[i]=(char)((s%10)+48);
            i--;
        }
        return (char)(c+48);
    }

    string add(string& x,string& y){
        if(x.length()<y.length()){
            string t=x;
            x=y;
            y=t;
        }
        char c = addStringsUtil(x,0,x.length()-1,y);
        x=c+x;
        return trimLeadingZeroes(x);
    } 

//-------------------------------- ADD ---------------------------------


//-------------------------------- SUB ---------------------------------


    void subStringsUtil(string& a,int start,int end,string& b){
        int blen=b.length(),i;
        b=string(end-start+1-blen,'0')+b;
        blen=b.length();
        string one(1,'1');
        for(i=0;i<blen;i++)
            b[i]=(char)(('9'-b[i])+48);
        addStringsUtil(b,0,blen-1,one);
        addStringsUtil(a,start,end,b);
    }

    string sub(string& a,string &b){
        subStringsUtil(a,0,a.length()-1,b);
        return trimLeadingZeroes(a);
    }

//-------------------------------- ADD ---------------------------------


//-------------------------------- MUL ---------------------------------

     string mulUtil(string& a,int num){
        int s,i,n=a.length(),c=0;
        string res(n+1,'0');
        for(i=n-1;i>=0;i--){
            s=((a[i]-'0')*num)+c;
            res[i+1]=(char)((s%10)+48);
            c=(int)s/10;
        }
        res[0]=(char)(c+48);
        return trimLeadingZeroes(res);  
    }


    string mul(string a, string b) {
        int i,lena=a.length(),lenb=b.length();
        string res(lena+lenb,'0'),utilities[10];
        for(i=1;i<=9;i++)
            utilities[i]=mulUtil(a,i);
        for(i=0;i<lenb;i++){
            if(b[i]!='0')
                addStringsUtil(res,0,lena+i,utilities[b[i]-'0']);
        }
        return trimLeadingZeroes(res);
    }

//-------------------------------- MUL ---------------------------------

//-------------------------------- MOD ---------------------------------

int compareStrings(string& a,string& b,int start,int end){
    int i=0,n=b.length();
    if(end-start+1<n)
        return 1;
    if(end-start+1>n) // this line is redudant? see
        return 0;
    while(start<=end){
        if(a[start]<b[i]) // if 1st string is less than second stirng
            return 1;
        else if(a[start]>b[i]) // if 1st string is greater than second stirng
            return 0;
        else
            i++,start++;
    }
    return -1; // figure out a way to remove this line
}


int divSearchUtil(string&a,string& b,int start,int end){
    int i,multiplier;
    string temp;
    for(i=1;i<=9;i++){
        temp=mulUtil(b,i);
        // cout << temp << endl;
        multiplier=compareStrings(a,temp,start,end);
        if(multiplier==1)
            return i-1;
        else if(multiplier==-1)
            return i;
    }
    return 9;
}


void mod(string& a,string &b){
    int temp,multiplier,lena=a.length(),lenb=b.length(),start=0,end=lenb-1;
    while(start<lena && end<lena){
        if(a[start]=='0'){
            start++;
            if(end<start)
                end++;
            continue;
        }
        temp=divSearchUtil(a,b,start,end);
        // cout << temp << " " << start << " " << end << endl;
        if(temp<1){
            end++;
            continue;
        }
        string multiplierString=mulUtil(b,temp);
        // cout << multiplierString << " " << start << " " << end << endl;
        subStringsUtil(a,start,end,multiplierString);
        end++;
    }
    if(start>=end) // is this redundant?
        a="0";
    else{
        a=a.substr(start,end-start);
        a=trimLeadingZeroes(a);
    }
}

//-------------------------------- MOD ---------------------------------

//-------------------------------- MISC ---------------------------------

void gcd(string&a ,string& b){              

    /* check if a is 0 or b is 0 and print the non-zero value */

    // cout << a << " " << b << endl;
    if(b!="0"){
        // cout << a << " " << b << endl;
        mod(a,b);
        // cout << a << endl;
        gcd(b,a);
    }
    else
        return ;
}


string factorial(int num){
    string temp,res="1";
    for(int i=1;i<=num;i++){
        temp=to_string(i);
        res=mul(res,temp);
    }
    return res;
}

string fastPow(string& a, long long exp){
    string res="1";
    while(exp>0){
        if (exp & 1)
            res = mul(res,a);
        a = mul(a,a);
        exp >>= 1;
    }
    return res;
}


//-------------------------------- MISC ---------------------------------

//-------------------------------- EXPR EVAL ---------------------------------

string convertToPostFixAndEvaluate(string encodedStr[],string encodedBigInt[],int c){
    int i,j=0,n = (2*c)-1;  
    Stack operatorStack,bigIntStack;
    operatorStack.initializeStack(c-1);
    bigIntStack.initializeStack(c);
    string operation,a,b;
    for(i=0;i<n;i++){
        if(encodedStr[i]!="+" && encodedStr[i]!="-" && encodedStr[i]!="x")
            bigIntStack.push(encodedBigInt[stoi(encodedStr[i])]);
        else{
            while(!operatorStack.empty() && operatorStack.compareOperators(encodedStr[i])){
                operation=operatorStack.pop();
                b=bigIntStack.pop();
                a=bigIntStack.pop();
                if(operation=="x")
                    bigIntStack.push(mul(a,b));
                else if(operation=="-")
                    bigIntStack.push(sub(a,b));
                else
                   bigIntStack.push(add(a,b));
            }
            operatorStack.push(encodedStr[i]);
        }            
    }
    while(!operatorStack.empty()){
        operation=operatorStack.pop();
        b=bigIntStack.pop();
        a=bigIntStack.pop();
        if(operation=="x")
            bigIntStack.push(mul(a,b));
        else if(operation=="-")
            bigIntStack.push(sub(a,b));
        else
            bigIntStack.push(add(a,b));
    }
    return bigIntStack.pop();
}

string evalExpr(string& a){
    int i,j,n=a.length(),c=0,prev=0;
    for(i=0;i<n;i++)
        if(a[i]=='+' || a[i]=='-' || a[i]=='x' )
            c++;
    string encodeBigInt[2*c],encodedStr[(2*c)+1],encodedPostFixArr[(2*c)+1];
    c=0,j=0;
    for(i=0;i<n;i++){
        if(a[i]=='+' || a[i]=='-' || a[i]=='x' ){
            encodedStr[j++]=to_string(c);
            encodedStr[j++]=string(1,a[i]);
            encodeBigInt[c++]=a.substr(prev,i-prev);
            prev=i+1;
        }
    }
    encodedStr[j]=to_string(c);
    encodeBigInt[c++]=a.substr(prev,i-prev);
    return convertToPostFixAndEvaluate(encodedStr,encodeBigInt,c);
}

//-------------------------------- EXPR EVAL ---------------------------------


int main(){
    string a,b,c;
    int d;
    long long exp;
    int typeofoperation;

    cin >> typeofoperation;

    if(typeofoperation==1){
        cin >> a >> exp;
        cout << fastPow(a,exp) << endl;
    }
    else if(typeofoperation==2){
        cin >> a >> b;
        d=compareStrings(a,b,0,a.length()-1);
        if(d==0){
            gcd(a,b);
            if(a=="0")
                cout << b << endl;
            else
                cout << a << endl;
        }
        else if(d==1){
            c=a;
            a=b;
            b=c;
            gcd(a,b);
            if(a=="0")
                cout << b << endl;
            else
                cout << a << endl;
        }
        else
            cout << a << endl;
    }
    else if(typeofoperation==3){
        cin >> d;
        cout << factorial(d) << endl;
    }
    else{
        cin >> a;
        cout << evalExpr(a);
    }
}

// 56071730
