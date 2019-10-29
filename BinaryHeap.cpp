/* 
 * BinaryHeap.cpp
 *
 * Description: Binary Heap ADT class test driver.
 *              Implementation as an array-based ...
 * Class Invariant: ... MIN Binary Heap 
 *
 * Author: Cheng Jie Huang
 * Date: October 24, 2019
 */

#include "BinaryHeap.h"
#include <iostream>
#include <sstream>

int main () {
    cout<<"testing"<<endl;
    BinaryHeap<int>*myBHeap = new BinaryHeap<int>;
    //test case 1: checking empty for empty
    cout<<"isEmpty: "<<myBHeap->isEmpty()<<endl;
    //test case 2: retrieving from empty
    cout<<"retrieved: "<<myBHeap->retrieve()<<endl<<endl;
    //test case 3: inserting while not full
    cout<<"inserting"<<endl;
    for (int i=0;i<5;i++) {
        myBHeap->insert(i);
    }
    //test case 4: inserting past initial capacity
    for (int i=10;i>0;i--) {
        myBHeap->insert(i);
    }
    //test case 5: retrieving and removing from filled
    while(!myBHeap->isEmpty()) {
        cout<<"retrieved: "<<myBHeap->retrieve()<<endl;
        myBHeap->remove();
    }

    return 0;
}
//End of BinaryHeap.cpp