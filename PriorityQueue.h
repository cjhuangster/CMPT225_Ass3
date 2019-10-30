/* 
 * PriorityQueue.h
 *
 * Description: Priority Queue ADT class.
 *              Implementation as an array-based ...
 * Class Invariant: ... MIN Priority Queue 
 *
 * Author: Cheng Jie Huang
 * Date: October 24, 2019
 */
#include <math.h>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#include "Event.h"
#include "Event.cpp"
#include "EmptyDataCollectionException.h"
#include "EmptyDataCollectionException.cpp"

using namespace std;

template <class ElementType>
class PriorityQueue {
    private:
        //Description: Private Variables
        unsigned const int indexOfRoot=0;
        unsigned int indexOfBottom;
        unsigned int indexOfParent;
        unsigned int elementCount;
        unsigned int capacity = 5;
        ElementType*BHeap = new ElementType [capacity];

        //Description: prints the heap structure
        void printHeap () {
            cout<<"Printing Queue:"<<endl;
            // unsigned int levels = log2(elementCount);
            unsigned int elementsPerLevel = 1;
            unsigned int counter = 0;
            for (int i=0;i<elementCount;i++) {
                cout<<BHeap[i]<<" ";
                counter++;
                if (counter==elementsPerLevel) {
                    cout<<endl;
                    elementsPerLevel=elementsPerLevel*2;
                    counter=0;
                }
            }
            cout<<endl<<endl;
        }

        //Description: prints the array structure along with the corresponding array index
        void printArray () {
            cout<<"printing arrayIndex: "<<endl;
            for (int i=0;i<elementCount;i++) {
                cout<<i<<" \t";
            }
            cout<<endl<<"printing arrayElements: "<<endl;
            for (int i=0;i<elementCount;i++) {
                // cout<<BHeap[i]<<" \t";
            }
            cout<<endl<<endl;
        }

        //Description: swaps heap elements of provided indices.
        void swapElements (unsigned const int &index1, unsigned const int &index2) {
            ElementType temp = BHeap[index1];
            BHeap[index1]=BHeap[index2];
            BHeap[index2]=temp;
        }

        void swapElements (unsigned const int &index1, unsigned const int &index2, Event &anEvent) {
            Event temp = BHeap[index1];
            BHeap[index1] = BHeap[index2];
            BHeap[index2] = temp;
        }

        //Description: resizes anArray based on the original size and the multipler factor. 
        void resizeArray(ElementType *&anArray, int size, float multiplier){
            int newSize=(int)size*multiplier;
            ElementType *resized = new ElementType [newSize];
            for (int i=0;i<=elementCount;i++){
                ElementType temp = anArray[i];
                resized[i]= temp;
            }
            delete[]anArray;
            anArray=resized;
        }

        // friend class Event; 

    public:

        //Description: Basic constructor.
        PriorityQueue ();

        //Description: Basic destructor.
        ~PriorityQueue () {
            delete[]BHeap;    
        }

    /******* Priority Queue Public Interface - START - *******/

   // Description: Returns "true" is this Priority Queue is empty, otherwise "false".
   // Postcondition:  The Priority Queue is unchanged by this operation.
   // Time Efficiency: O(1)
    bool isEmpty() const;


   // Description: enqueues newElement in the Priority Queue.
   //              It returns "true" if successful, otherwise "false".
   // Time Efficiency: O(log2 n)
    bool enqueue(ElementType& newElement);


   // Description: Removes (but does not return) the element with the "highest" priority.
   // Precondition: This Priority Queue is not empty.
   // Exception: Throws EmptyDataCollectionException if this Priority Queue is empty.
   // Time Efficiency: O(log2 n)
    void dequeue() throw(EmptyDataCollectionException);
    
   // Description: Returns (but does not remove) the element with the "highest" priority.
   // Precondition: This Priority Queue is not empty.
   // Exception: Throws EmptyDataCollectionException if this Priority Queue is empty.
   // Time Efficiency: O(1)
    ElementType& peek() throw(EmptyDataCollectionException);

    /******* Priority Queue Public Interface - END - *******/

};

template <class ElementType>
PriorityQueue<ElementType>::PriorityQueue () {
    indexOfBottom = 0;
    indexOfParent = 0;
    elementCount = 0;
}

template <class ElementType>
bool PriorityQueue<ElementType>::isEmpty() const {
        if (elementCount==0) {
            return true;
        }
        else return false;
}

template <class ElementType>
bool PriorityQueue<ElementType>::enqueue(ElementType& newElement) {
    if (elementCount>=(capacity-1)){
        int multiplier = 2;
        resizeArray(BHeap,capacity,multiplier);
        capacity=capacity*multiplier;
    }

    indexOfBottom=elementCount;
    BHeap[indexOfBottom] = newElement;
    elementCount++;
    int indexOfChild=indexOfBottom;

    //Description: Reheap MIN heap post enqueueion   
    //Precondition: index given must not be the root.
    //Postcondition: Priority Queue ordered.
    while(indexOfChild>indexOfRoot) {
        indexOfParent = floor((indexOfChild-1)/2);
        //compare to see if heapification required
        if (BHeap[indexOfParent] > BHeap[indexOfChild]) {
            swapElements(indexOfParent,indexOfChild);
            //recursively reheapup
            indexOfChild=indexOfParent;
        }
        else {
            break;
        }
    }

    printArray();
}

template <class ElementType>
void PriorityQueue<ElementType>::dequeue() throw(EmptyDataCollectionException) {
    indexOfBottom = elementCount-1;
    if (elementCount<=(capacity/4)){
        float multiplier = 0.5;
        resizeArray(BHeap,capacity,multiplier);
        capacity=(int)capacity*multiplier;
    }
    //enforce check on precondition
    if (!isEmpty()){
        swapElements(indexOfBottom,indexOfRoot);
        elementCount--;
        int indexOfParent = indexOfRoot;
        //Description: Reheap MIN heap post removal   
        //Precondition: index given must not be a leaf.
        //Postcondition: Priority Queue ordered.
        indexOfBottom=elementCount-1;
        unsigned int level = floor(log2(elementCount));
        unsigned int lastNotLeaf;
        if (level==0) {
            lastNotLeaf=0;
        }
        else {
            lastNotLeaf = pow(2,level)-2;
        }
        //reinforcing precondition.
        while (indexOfParent<=lastNotLeaf) {
            unsigned int indexOfLChild = 2*indexOfParent+1;
            unsigned int indexOfRChild = indexOfLChild+1;
            unsigned int indexOfMinChild=indexOfParent;
            //checks for minimum child.
            if ((BHeap[indexOfRChild]<BHeap[indexOfLChild])&&(indexOfRChild<=indexOfBottom)) {
                indexOfMinChild=indexOfRChild;
            }
            
            else if (indexOfLChild<=indexOfBottom){
                indexOfMinChild=indexOfLChild;
            }

            //checks if min child value is less than parent value, and confirm if recursion is required
            if (BHeap[indexOfMinChild]<BHeap[indexOfParent]&&indexOfMinChild<=indexOfBottom) {
                swapElements (indexOfParent,indexOfMinChild);        
                //recursively reheap until leaf.
                indexOfParent=indexOfMinChild;
            }

            else {
                break;
            }
        }
        //exclude dequeued element from heap by decrementing elementCount.
        printHeap();
    }
    else {
        cout<<"error: attempting to dequeue from an empty Priority Queue."<<endl;     
        throw(EmptyDataCollectionException("error: dequeue() called for an empty priority queue."));   
    }
}

template <class ElementType>
ElementType&  PriorityQueue<ElementType>::peek() throw(EmptyDataCollectionException) { 
    //enforce check on precondition
    if (!isEmpty()){
        return BHeap[indexOfRoot];
    }
    else cout<<"error: attempting to peek from an empty Priority Queue."<<endl;
    throw(EmptyDataCollectionException("error: peek() called for an empty priority queue."));
}

template <>
bool PriorityQueue<Event>::enqueue(Event& newElement) {
    if (elementCount>=(capacity-1)){
        int multiplier = 2;
        resizeArray(BHeap,capacity,multiplier);
        capacity=capacity*multiplier;
    }

    indexOfBottom=elementCount;
    BHeap[indexOfBottom]=newElement;
    elementCount++;
    int indexOfChild=indexOfBottom;
    Event parent = BHeap[indexOfParent];
    Event child = BHeap[indexOfChild];
    //Description: Reheap MIN heap post enqueue   
    //Precondition: index given must not be the root.
    //Postcondition: Priority Queue ordered.
    while(indexOfChild>indexOfRoot) {
        indexOfParent = floor((indexOfChild-1)/2);
        // compare to see if heapification required
        bool swapRequired = child<=parent;
        if (swapRequired) {
            swapElements(indexOfParent,indexOfChild);
            //recursively reheapup
            indexOfChild=indexOfParent;
        }
        else {
            break;
        }
    }
    // printArray();
}

template <>
void PriorityQueue<Event>::dequeue() throw(EmptyDataCollectionException) {
    indexOfBottom = elementCount-1;
    if (elementCount<=(capacity/4)){
        float multiplier = 0.5;
        resizeArray(BHeap,capacity,multiplier);
        capacity=(int)capacity*multiplier;
    }
    //enforce check on precondition
    if (!isEmpty()){
        swapElements(indexOfBottom,indexOfRoot);
        elementCount--;
        int indexOfParent = indexOfRoot;
        //Description: Reheap MIN heap post removal   
        //Precondition: index given must not be a leaf.
        //Postcondition: Priority Queue ordered.
        indexOfBottom=elementCount-1;
        unsigned int level = floor(log2(elementCount));
        unsigned int lastNotLeaf;
        if (level==0) {
            lastNotLeaf=0;
        }
        else {
            lastNotLeaf = pow(2,level)-2;
        }
        //reinforcing precondition.
        while (indexOfParent<=lastNotLeaf) {
            unsigned int indexOfLChild = 2*indexOfParent+1;
            unsigned int indexOfRChild = indexOfLChild+1;
            unsigned int indexOfMinChild=indexOfParent;
            Event lChild = BHeap[indexOfLChild];
            Event rChild = BHeap[indexOfRChild];
            bool rChildSmaller = rChild<=lChild;
            //checks for minimum child.
            if (rChildSmaller&&(indexOfRChild<=indexOfBottom)) {
                indexOfMinChild=indexOfRChild;
            }
            
            else if (indexOfLChild<=indexOfBottom){
                indexOfMinChild=indexOfLChild;
            }

            Event minChild=BHeap[indexOfMinChild];
            Event parent =BHeap[indexOfParent];
            bool swapRequired = (minChild<=parent)&&(indexOfMinChild<=indexOfBottom);
            //checks if min child value is less than parent value, and confirm if recursion is required
            if (swapRequired) {
                swapElements (indexOfParent,indexOfMinChild);        
                //recursively reheap until leaf.
                indexOfParent=indexOfMinChild;
            }

            else {
                break;
            }
        }
        //exclude dequeued element from heap by decrementing elementCount.
        // printHeap();
    }
    else {
        cout<<"error: attempting to dequeue from an empty Priority Queue."<<endl;   
        throw(EmptyDataCollectionException("error: dequeue() called for an empty priority queue."));     
    }
}
//end of PriorityQueue.h template


//end of PriorityQueue.h