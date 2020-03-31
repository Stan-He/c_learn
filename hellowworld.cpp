#include <iostream>
#include "Obj.h"
using namespace std;




void foo(int n){

    Obj obj;
    if(n==42)
        throw "life, the universe and everything";
}


int main(){

    double array[10]={1,1,1,1,1,1,1,1,1};
    for(int i=0;i<100;i++){
        array[i%10]+=i;
    }

    try{
        foo(41);
        foo(42);
    }
    catch(const char*s){
        puts(s);
    }
    return 0;
}