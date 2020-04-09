#include <iostream>
#include "Obj.h"
#include "Shape.h"
using namespace std;




void foo(int n){

    Obj obj;
    if(n==42)
        throw "life, the universe and everything";
}


void c_plus_lesson2(){

    smart_ptr<circle> ptr1(new circle());
    printf("use count of ptr1 is %ld\n",ptr1.use_count());
    smart_ptr<shape> ptr2;
    printf("use count of ptr2 is %ld\n",ptr2.use_count());
    ptr2=ptr1;
    printf("use count of ptr2 is %ld\n",ptr2.use_count());
    if (ptr1){
        puts("ptr1 is not empty");
    }
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

    c_plus_lesson2();


    return 0;
}