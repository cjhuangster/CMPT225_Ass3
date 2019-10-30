/* 
 * BankSimApp.cpp
 *
 * Description: Bank Simulation Application
 * Class Invariant: ...  FIFO based on Priority Queue
 *
 * Author: Cheng Jie Huang
 * Date: October 28, 2019
 */

 #include "PriorityQueue.h"
 #include "Queue.h"
 #include "Event.h"
 #include <iostream>
 #include <sstream>
 #include <math.h>
 #include <string>

 using namespace std;

 class BankSim {
     private:
        unsigned int totalWaitTime;
        unsigned int inBankLine;
        unsigned int customerNumber;
        unsigned int currentTime;
        unsigned int totalTeller;
        unsigned int totalCustomersProcessed;
        bool tellerAvailable;
        bool dayIsOver;
        PriorityQueue <Event>*eventPriorityQueue = new PriorityQueue<Event>;
        Queue <Event>*bankLine = new Queue<Event>;
    
     public:

        BankSim () {
            customerNumber=0;
            totalWaitTime=0;
            currentTime=0;
            inBankLine=0;
            totalCustomersProcessed=0;
            //default to 1 teller available in the bank
            totalTeller=1;
            tellerAvailable=true;
            dayIsOver=false;
        }

        //Description: Simulation of the bank day
        void typicalBankDaySimulation () {
            //get day's event specifications.
            getEvents();

            cout<<"Simulation Begins"<<endl;

            //event loop
            while (!dayIsOver) {
                Event newEvent=eventPriorityQueue->peek();
                //get current time
                currentTime=currentTime+newEvent.getTime();

                //process the event as an arrival or departure event
                if (newEvent.isArrival()) {

                    processArrival(newEvent, eventPriorityQueue, bankLine);
                    printEvent(newEvent);
                }

                else {
                    processDeparture(newEvent, eventPriorityQueue, bankLine);
                    printEvent(newEvent);
                }
            bool dayIsOver = (eventPriorityQueue->isEmpty())&&(bankLine->isEmpty());
            }
            endScene();
        }

        //Description: Processes an arrival event
        void processArrival (Event&arrivalEvent, PriorityQueue<Event>*eventProrityQueue, Queue<Event>*bankLine) {
            eventPriorityQueue->dequeue();

            //if no one is in the bankline and the teller is available, process the arrival right away and send in a departure event
            if (bankLine->isEmpty()&&tellerAvailable) {
                cout<<"bankline is empty, teller is available."<<endl;
                int departureTime = currentTime+arrivalEvent.getLength();
                //if the customer is processed right away, enqueue his departure time.
                Event newDepartureEvent = Event('D', departureTime);
                eventPriorityQueue->enqueue(newDepartureEvent);
                cout<<"teller now unavailable."<<endl;
                tellerAvailable = false;
            }

            //if the bankline has a queue, send arrival to the back of the queue.
            else {
                cout<<"bankline is empty, teller is not available, customer sent to back."<<endl;
                bankLine->enqueue(arrivalEvent);
                inBankLine++;
            }
        }
        
        //Description: Processes a departure event
        void processDeparture (Event&departureEvent, PriorityQueue<Event>*eventProrityQueue, Queue<Event>*bankLine) {
            //take out current event
            eventPriorityQueue->dequeue();
            //if bankline is not empty, 
            if (!bankLine->isEmpty()) {
                cout<<"bankline is not empty: "<<endl;
                //Customer at front of line begins transaction
                Event customer = bankLine->peek();
                bankLine->dequeue();
                totalCustomersProcessed++;
                inBankLine--;
                totalWaitTime+=inBankLine*customer.getLength();
                //set departure time for customer thats currently in process.
                int departureTime = currentTime+customer.getLength();
                Event newDepartureEvent = Event('D', departureTime);
                eventPriorityQueue->enqueue(newDepartureEvent);
            }
            
            else {
                cout<<"teller now available"<<endl;
                tellerAvailable = true;
            } 
        }

        //Description: gets customer event description from input.
        void getEvents() {
            int input;
            int arrivalTime;
            int transactionLength;
            customerNumber=1;
            //while neither inputs are enter keys, keep inputting customer specifications
            while (1) {
                cout<<"input customer"<<customerNumber<<"'s arrival time:"<<endl;
                cin>>input;
                arrivalTime=input;
                if (arrivalTime==69) {
                    break;
                }
                cout<<"customer"<<customerNumber<<"'s arrival time is: \t"<<arrivalTime<<endl;
                cout<<"input customer"<<customerNumber<<"'s transaction length:"<<endl;
                cin>>input;
                transactionLength=input;
                cout<<"customer"<<customerNumber<<"'s transaction length is: \t"<<transactionLength<<endl;
                customerNumber++;
                Event currentCustomer= Event('A', arrivalTime, transactionLength);
                eventPriorityQueue->enqueue(currentCustomer);
                
            }

            while (!eventPriorityQueue->isEmpty()) {
                Event enqueued = eventPriorityQueue->peek(); 
                cout<<"time, type, length"<<enqueued.getTime()<<" "<<enqueued.getType()<<" "<<enqueued.getLength()<<endl;                ;
                eventPriorityQueue->dequeue();
            }             
        }

        //Description: Prints the activity completed at a certain time->
        void printEvent (Event&anEvent) {
            if (anEvent.isArrival()) {
                cout<<"Processing an arrival event at time: \t"<<anEvent.getTime()<<endl;
            }
            else {
                cout<<"Processing a departure event at time: \t"<<anEvent.getTime()<<endl;
            }
        }

        // Description: after simulation displays
        void endScene() {    
            float avgWaitTime = totalWaitTime/totalCustomersProcessed;        
            cout<<"Simulation Ends"<<endl<<endl
                <<"Final Statistics:"<<endl<<endl
                <<"\t\t Total number of people processed: "<<totalCustomersProcessed<<endl
                <<"\t\t Average amount of time spent waiting: "<<avgWaitTime<<endl;
        }
 
 };


  int main () {
    BankSim myBank=BankSim();
    myBank.typicalBankDaySimulation();
    return 0;
 }