#include <iostream>
#include <ostream>
#include <sstream> d
#include <string>
#include <typeinfo>
#include "EmptyDataCollectionException.h"

using namespace std;

template <class elementType>
class Queue {
    private:
        // Description: Nodes for a singly-linked list
        class QueueNode {
            public:
                elementType data;
                QueueNode * next;
        };
        

        // Description: head = ptr to the first QueueNode (NULL if empty)
        //              tail = ptr to the last QueueNode (NULL if empty)
        QueueNode * head;
        QueueNode * tail;

        // int checkType (elementType newVariable) {
        //     string myString; int myInt; char myChar;
        //     return 0;
        // }

    public:
            
        // Description: Constructor
        // Postcondition: Queue is empty
        Queue(){
		    //initialize variables to NULL;
          head=NULL;
          tail=NULL;

          //switch()
        };

            // Description: Destructor 
        // Postcondition: All memory released
        ~Queue(){
		    //release memory associated with variables
            while (head!=NULL){
                dequeue();
                // QueueNode*temp = new QueueNode;
                // temp=head;
                // head=head->next;
                // temp=NULL;
                // delete temp; 
            }
            head=NULL;
            tail=NULL;
            delete head;
            delete tail;
        }
        /******* Queue Public Interface - START - *******/
        // Class Invariant:  FIFO or LILO order

        // Description: Returns "true" is this Queue is empty, otherwise "false".
        // Time Efficiency: O(1)
        bool isEmpty() const {
					//check if head is allocated memory, if yes then stack has at least one element, if not then stack is empty
					if (head==NULL)	{
						return true;
					}
					else return false;
        }
        
        // Description: Inserts newElement at the "back" of this Queue 
        //              (not necessarily the "back" of its data structure) and 
        //              returns "true" if successful, otherwise "false".
        // Time Efficiency: O(1)
        bool enqueue(elementType& newElement) {
            QueueNode *temp = new QueueNode;
            //input element to current node, iterate
            temp->data = newElement;
            temp->next = NULL;

            //Check if stack is empty, if empty then the first element will become temp
            if(head==NULL){
                head=temp;
                tail=temp;
                temp=NULL;
                return true;
            }
            //Else simply stack newElement as the next element.
            else{
                tail->next=temp;
                tail=temp;
                tail->next=NULL;
                return true;
            }
        }
        
        // Description: Removes (but does not return) the element at the "front" of this Queue 
        //              (not necessarily the "front" of its data structure).
        // Precondition: This Queue is not empty.
        // Exception: Throws EmptyDataCollectionException if this Queue is empty.   
        // Time Efficiency: O(1)
        void dequeue() throw(EmptyDataCollectionException) {
        //initializing new StackNodes
            QueueNode *toPop=new QueueNode;
            QueueNode *newHead= new QueueNode;

        //Enforcing precondition
            if (isEmpty()) {
                cout<<"error: stack is empty!"<<endl;
                throw EmptyDataCollectionException("dequeue() called with empty queue.");
            }
             
            //Starting from head, iterate until the next is NULL, set tail to the previous element, then dereference the current element. Repeat until the 2nd element is NULL
            else {
                //set head as the next out of queue
                toPop=head;
                //set the next head
                newHead=head->next;
                head=NULL;
                head=newHead;
            }
        }
        
        // Description: Returns (but does not remove) the element at the "front" of this Queue
        //              (not necessarily the "front" of its data structure).
        // Precondition: This Queue is not empty.
        // Exception: Throws EmptyDataCollectionException if this Queue is empty.
        // Time Efficiency: O(1)
        elementType& peek() throw(EmptyDataCollectionException) {
            //Enforcing precondition
            if (isEmpty()){
                cout<<"error: stack is empty!"<<endl;
            //    throw EmptyDataCollectionException("peek() called with empty queue.");
            }

            //else 
            else return head->data;       
        }
    };
        /******* Queue Public Interface - END - *******/