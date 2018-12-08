
/* 
 * File:   jdehay_dsa_final_project.cpp
 * Author: Jeremy DeHay
 * Class:  Data Structures and Algorithms
 * Due on December 14, 2018
 */

//Queue.cpp
//demonstrates queue
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

/**
 * Queue class retrieved from:
 * D'Souza, J (2018) Week 13: Lecture 6 - Code [Online Lecture] Retrieved
 *      from https://champlain.instructure.com/courses/1026917/pages/week-4-
 *      lecture-9-queue-code?module_item_id=20864417
 */
//////////////////////////////////////////////////////////////

class Queue {
private:
    int maxSize;
    vector<int> queVect;
    int front;
    int rear;
    int nItems;
public:
    //------------------------------------------------------------
    //constructor

    Queue(int s) : maxSize(s), front(0), rear(-1), nItems(0) {
        queVect.resize(maxSize);
    }
    //------------------------------------------------------------

    void insert(int j) //put item at rear of queue
    {
        if (rear == maxSize - 1) //deal with wraparound
            rear = -1;
        queVect[++rear] = j; //increment rear and insert
        nItems++; //one more item
    }
    //------------------------------------------------------------

    int remove() //take item from front of queue
    {
        int temp = queVect[front++]; //get value and incr front
        if (front == maxSize) //deal with wraparound
            front = 0;
        nItems--; //one less item
        return temp;
    }
    //------------------------------------------------------------

    int peekFront() //peek at front of queue
    {
        return queVect[front];
    }
    //------------------------------------------------------------

    bool isEmpty() //true if queue is empty
    {
        return (nItems == 0);
    }
    //------------------------------------------------------------

    bool isFull() //true if queue is full
    {
        return (nItems == maxSize);
    }
    //------------------------------------------------------------

    int size() //number of items in queue
    {
        return nItems;
    }
    //------------------------------------------------------------
    
}; //end class Queue
//////////////////////////////////////////////////////////////


//prototypes
string cashier_display(int s);
void ClearScreen()  // System agnostic attempt from http://www.cplusplus.com/articles/4z18T05o/
    {
    cout << string( 100, '\n' );
    }

/*
 * Scenario: A supermarket has 9 cashiers. Customers arrive and leave at random 
 * time intervals. Use 0-5 seconds for this project. Make sure the customers 
 * arrive faster than they depart so that the queues fill up. The goal of the 
 * program is to put the next arriving customer in the shortest queue out of 
 * the 9 cashier queues. Your program will need to loop infinitely to simulate 
 * the passing of a certain amount of time. I suggest looping the program every 
 * second and clearing the screen and displaying all queues. Use a simple "for 
 * loop" as a delay. Also use an asterisk (*) to represent customers.
 */
int main(int argc, char** argv) {
    int incomingTimer = -1;  // sentinel value for generating customers
    int outgoingTimer = -1;  // sentinel value for removing customers
    int incomingCounter = 0;
    int outgoingCounter = 0;
    int customer = 0;
    
    // Make cashiers
    Queue* cashier1 = new Queue(20);
    Queue* cashier2 = new Queue(20);
    Queue* cashier3 = new Queue(20);
    Queue* cashier4 = new Queue(20);
    Queue* cashier5 = new Queue(20);
    Queue* cashier6 = new Queue(20);
    Queue* cashier7 = new Queue(20);
    Queue* cashier8 = new Queue(20);
    Queue* cashier9 = new Queue(20);
    Queue* queueArray[] = {cashier1, cashier2, cashier3, cashier4, 
                        cashier5, cashier6, cashier7, cashier8, cashier9};
        

    while (true) { // Program loop
        
        // random number for adding customers (up to every 4 seconds)
        if (incomingTimer == -1) {
            incomingTimer = rand() % 3;  // time value to add customers
        }
        
        // random number for removing customers (up to every 6 seconds)
        if (outgoingTimer == -1) {
            outgoingTimer = rand() % 5;  // time value to remove customers
        }
        
        // Create customers at random intervals
        if (incomingTimer == incomingCounter) {
            incomingCounter = -1;
            incomingTimer = -1;
            
            // first bubble sort the queues 
            bool swap;
            Queue* temp = new Queue(20);
            do {
                swap = false;
                for (int i = 0; i < 8; i++) {
                    
                    if (queueArray[i]->size() > queueArray[i + 1]->size()) {
                        temp = queueArray[i];
                        queueArray[i] = queueArray[i + 1];
                        queueArray[i + 1] = temp;
                        swap = true;
                    } 
                }
            } while (swap);
            
            // insert newest customer into the smallest queue
            queueArray[0]->insert(++customer);
        }
        
        // Remove a random customer
        if (outgoingTimer == outgoingCounter) {
            outgoingTimer = -1;
            outgoingCounter = -1;
            int randomCustomer = rand() % 8;
            queueArray[randomCustomer]->remove();
        }

        // Display cashiers
        cout << "|--------------------------------" << endl;
        cout << "|1| " << cashier_display(cashier1->size()) << endl;
        cout << "|--------------------------------" << endl;
        cout << "|2| " << cashier_display(cashier2->size()) << endl;
        cout << "|--------------------------------" << endl;
        cout << "|3| " << cashier_display(cashier3->size()) << endl;
        cout << "|--------------------------------" << endl;
        cout << "|4| " << cashier_display(cashier4->size()) << endl;
        cout << "|--------------------------------" << endl;
        cout << "|5| " << cashier_display(cashier5->size()) << endl;
        cout << "|--------------------------------" << endl;
        cout << "|6| " << cashier_display(cashier6->size()) << endl;
        cout << "|--------------------------------" << endl;
        cout << "|7| " << cashier_display(cashier7->size()) << endl;
        cout << "|--------------------------------" << endl;
        cout << "|8| " << cashier_display(cashier8->size()) << endl;
        cout << "|--------------------------------" << endl;
        cout << "|9| " << cashier_display(cashier9->size()) << endl;
        cout << "|--------------------------------" << endl;
        cout << "NOW SERVING CUSTOMER NUMBER " << customer << endl;
        // wait, clear the screen, and update
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        ClearScreen();
        
        // increment loop counters
        incomingCounter++;
        outgoingCounter++;
    }
    return 0;
}

// return asterisks to print the customers
string cashier_display(int s) {
    string result = "";
    for (int i = 0; i < s; i++) {
        result += "* ";
    }
    return result;
}

/*
 (                         *     
 )\ )                    (  `    
(()/(  (   (   (  (  (   )\))(   
 /(_)) )\  )\  )\ )\ )\ ((_)()\  
(_))_ ((_)((_)((_|(_|(_)(_()((_) 
 |   \| __\ \ / / | | __|  \/  | 
 | |) | _| \ V / || | _|| |\/| | 
 |___/|___| \_/ \__/|___|_|  |_| 
      https://is.gd/RGR0UQ                  
 */