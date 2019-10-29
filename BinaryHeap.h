/* 
 * BinaryHeap.h
 *
 * Description: Binary Heap ADT class.
 *              Implementation as an array-based ...
 * Class Invariant: ... MIN Binary Heap 
 *
 * Author: Cheng Jie Huang
 * Date: October 24, 2019
 */
#include <math.h>
#include <iostream>
#include <sstream>

using namespace std;

template <class ElementType>
class BinaryHeap {
    private:
        //Description: Private Variables
        unsigned const int indexOfRoot=0;
        unsigned int indexOfBottom;
        unsigned int indexOfParent;
        unsigned int elementCount;
        unsigned int capacity = 5;
        int*BHeap = new int [capacity];
    
        //Description: Reheap MIN heap post insertion   
        //Precondition: index given must not be the root.
        //Postcondition: Binary Heap ordered.
        void reMinHeapUp (unsigned const int indexOfChild) {
             //Reinforcing precondition.
             if (indexOfChild > indexOfRoot) {
                 indexOfParent = floor((indexOfChild-1)/2);
                //compare to see if heapification required
                if (BHeap[indexOfParent] > BHeap[indexOfChild]) {
                    swapElements(indexOfParent,indexOfChild);
                    //recursively reheapup
                    reMinHeapUp (indexOfParent);
                }
             }
        }

        //Description: Reheap MIN heap post removal   
        //Precondition: index given must not be a leaf.
        //Postcondition: Binary Heap ordered.
        void reMinHeapDown (unsigned const int indexOfParent) {
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
            if (indexOfParent<=lastNotLeaf) {
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
                if (BHeap[indexOfMinChild]<BHeap[indexOfParent]) {
                    swapElements (indexOfParent,indexOfMinChild);        
                    //recursively reheap until leaf.
                    reMinHeapDown (indexOfMinChild);
                }
            }
        }

        //Description: prints the heap structure
        void printHeap () {
            cout<<"printing heap:"<<endl;
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
                cout<<i<<" ";
            }
            cout<<endl<<"printing arrayElements: "<<endl;
            for (int i=0;i<elementCount;i++) {
                cout<<BHeap[i]<<" ";
            }
            cout<<endl<<endl;
        }

        //Description: swaps heap elements of provided indices.
        void swapElements (unsigned const int &index1, unsigned const int &index2) {
            ElementType temp = BHeap[index1];
            BHeap[index1]=BHeap[index2];
            BHeap[index2]=temp;
        }

        //Description: resizes anArray based on the original size and the multipler factor. 
        void resizeArray(ElementType *&anArray, int size, float multiplier){
            int newSize=(int)size*multiplier;
            int *resized = new int [newSize];
            for (int i=0;i< elementCount;i++){
                resized[i]=anArray[i];
            }

            delete[]anArray;
            anArray=resized;
        }

    public:

        //Description: Basic constructor.
        BinaryHeap () {
            // indexOfRoot = 0;
            indexOfBottom = 0;
            indexOfParent = 0;
            elementCount = 0;
        }

        //Description: Basic destructor.
        ~BinaryHeap () {
            delete[]BHeap;    
        }

    /******* Binary Heap Public Interface - START - *******/
    // Class Invariant:  Min Binary Heap
    // Description: Returns "true" is this Binary Heap is empty, otherwise "false".
    // Postcondition:  The Binary Heap is unchanged by this operation.
    // Time Efficiency: O(1)
    bool isEmpty() const {
        if (elementCount==0) {
            return true;
        }
        else return false;
    }

    // Description: Inserts newElement in this Binary Heap and 
    //              returns "true" if successful, otherwise "false".
    // Time Efficiency: O(log2 n)
    bool insert(ElementType& newElement) {
        if (elementCount>(capacity-1)){
            int multiplier = 2;
            resizeArray(BHeap,capacity,multiplier);
            capacity=capacity*multiplier;
        }

        else {
            indexOfBottom=elementCount;
            BHeap[indexOfBottom] = newElement;
            elementCount++;
            reMinHeapUp(indexOfBottom);
            printArray();
            printHeap();
        }
    }

    // Description: Removes (but does not return) the element located at the root.
    // Precondition: This Binary Heap is not empty.
    // Exception: Throws EmptyDataCollectionException if Binary Heap is empty.
    // Time Efficiency: O(log2 n)
    void remove() { //throw(EmptyDataCollectionException);
        indexOfBottom = elementCount-1;
        //enforce check on precondition
        if (!isEmpty()){
            swapElements(indexOfBottom,indexOfRoot);
            elementCount--;
            reMinHeapDown(indexOfRoot);
            //exclude removed element from heap by decrementing elementCount.
            printHeap();
        }
        else {
            cout<<"error: attempting to remove from an empty binary heap."<<endl;        
        }
    }
    
    // Description: Returns (but does not remove) the element located at the root.
    // Precondition: This Binary Heap is not empty.   
    // Exception: Throws EmptyDataCollectionException if Binary Heap is empty.
    // Time Efficiency: O(1)
    ElementType& retrieve() { //throw(EmptyDataCollectionException);
        //enforce check on precondition
        if (!isEmpty()){
            return BHeap[indexOfRoot];
        }
        else cout<<"error: attempting to retrieve from an empty binary heap."<<endl;
    }
    /******* Binary Heap Public Interface - END - *******/

};
//end of BinaryHeap.h