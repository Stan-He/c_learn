#include <iostream>
#include "Obj.h"
#include "Shape.h"
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

    smart_ptr<shape> ptr1(new circle());
    printf("use count of ptr1 is %ld\n",ptr1.use_count());


    return 0;
}