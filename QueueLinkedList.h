/* 
 * QueueLinkedList.h
 *
 * Description: Queue data collection ADT class.
 *              Implementation of an int sequence with enqueue/dequeue ...
 * Class Invariant: ... in FIFO order
 *
 * Author: Michael Huang
 * Date: 2019/10/18
 */
#include <iostream>
#include <ostream>
#include <string>
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

    public:


        // Description: Constructor
        // Postcondition: Queue is empty
        Queue(){
		    //initialize variables to NULL;
          head=NULL;
          tail=NULL;
        };


        // Description: Destructor 
        // Postcondition: All memory released
        ~Queue(){
		    //release memory associated with variables
                while (head!=NULL){
                elementType toPop=dequeue();
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

        // Description: Inserts newElement at the back (O(1))  
        void enqueue(elementType newElement){
          QueueNode *temp = new QueueNode;
		  			//input element to current node, iterate
					temp->data = newElement;
					temp->next = NULL;

					//Check if stack is empty, if empty then the first element will become temp
					if(head==NULL){
						head=temp;
						tail=temp;
						temp=NULL;
					}

					//Else simply stack newElement as the next element.
					else{
						tail->next=temp;
						tail=temp;
						tail->next=NULL;
					}
        }

        // Description: Removes the frontmost element (O(1))
        // Precondition: Queue not empty
         void dequeue(){
					//initializing new StackNodes
						QueueNode *toPop=new QueueNode;
                        QueueNode *newHead= new QueueNode;

					//checks if stack is empty
					if (head==NULL){
									cout<<"error: stack is empty!"<<endl;
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


        // Description: Returns a copy of the frontmost element (O(1))
        // Precondition: Queue not empty
         elementType peek() const{
				//check if head is allocated memory, if yes then stack has at least one element, if not then stack is empty
				if (head==NULL){
					cout<<"error: stack is empty!"<<endl;
				return 0;
				}

				else return head->data;       
        }


        // Description: Returns true if and only if queue empty (O(1))
        bool isEmpty() const {
					//check if head is allocated memory, if yes then stack has at least one element, if not then stack is empty
					if (head==NULL)	{
						return true;
					}
					else return false;
        }
};

