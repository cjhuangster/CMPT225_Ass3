/* 
 * QueueTestDriver.cpp
 *
 * Description: Queue data collection ADT class.
 *              Implementation of an int sequence with enqueue/dequeue ...
 * Class Invariant: ... in FIFO order
 *
 * Author: Michael Huang
 * Date: 2019/10/18
 */

#include "Queue.h"
#include <string>
#include <typeinfo>
#include <iostream>
 
// Test Code 
int main(){
    Queue<int>*myList=new Queue<int>;  
    // try {
    //     myList->dequeue();

    // } 

    // catch (EmptyDataCollectionException&anException) {
    //     cout<<"dequeue() unsuccessful because "<<anException.what();
    // }
  
    // try {
    //     int test=myList->peek();
    // }
    
    // catch (EmptyDataCollectionException&anException) {
    //     cout<<"peek() unsuccessful because "<<anException.what();
    // }

    for (int i=10;i<20;i++){
        myList->enqueue(i);
    }
    cout<<"  enqueue:"<<myList->peek()<<endl<<endl;

    while (myList->isEmpty()==false){
        cout<<"  peek:"<<myList->peek();
        myList->dequeue();
    }

    Queue<char>*newList=new Queue<char>;
    newList->dequeue();newList->peek();
    char a = 'd';
    for (int i=10;i<20;i++){
        newList->enqueue(a);
    }
    cout<<"  enqueue:"<<newList->peek()<<endl<<endl;

    while (newList->isEmpty()==false){
        cout<<"  peek:"<<newList->peek();
        newList->dequeue();
    }

    Queue<string>*newList2=new Queue<string>;
    newList2->dequeue();newList2->peek();
    string b = "testing";
    for (int i=10;i<20;i++){
        newList2->enqueue(b);
    }
    cout<<"  enqueue:"<<newList2->peek()<<endl<<endl;

    while (newList2->isEmpty()==false){
        cout<<"  peek:"<<newList2->peek();
        newList2->dequeue();
    }
	return 0;
}