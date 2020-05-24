// Kadir GULTEKIN - 2023174
// EE441 DATA STRUCTURES - HW1 - PROCESSOR SIMULATOR

#include <iostream>
#include <fstream>
#include "Process.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

int main() {
    Queue<Process> Q1; // queue for priority 1
    Queue<Process> Q2; // queue for priority 2
    Queue<Process> Q3; // queue for priority 3

    Stack<Process> S1;

    int pID, priority, arrTime, runTime;
    int t = 0; // System clock initialization

    ifstream infile; // input file stream
    ofstream outfile; // output file stream
    ofstream latency; // latency file stream

    infile.open("input.txt"); // input file is input.txt
    outfile.open("output.txt"); // output file is output.txt
    latency.open("latency.txt"); // latency file is latency.txt

    // Read input.txt and get the number of processes
    int totalProcess = 0;
    while(!infile.eof()){
        infile >> pID >> priority >> arrTime >> runTime;
        totalProcess++; // Increase totalProcess by 1 for each process
    }
    infile.close();

    // Create a dynamic array whose length is the number of processes in the input.txt
    Process *processArray = new Process[totalProcess];

    // Fill the dynamic array with the content of input.txt
    // At the end of this while loop, the dynamic array will contain all the processes written in input.txt
    infile.open("input.txt");
    int i = 0;
    while(!infile.eof()) {
        infile >> pID >> priority >> arrTime >> runTime;
        Process p;
        p.id = pID;
        p.priority = priority;
        p.arrivalTime = arrTime;
        p.runtime = runTime;
        processArray[i] = p; // Insert process into dynamic array
        i++; // Increase i to insert next process into dynamic array
    }

    infile.close(); // Close the file

    Process Running_Process;
    Running_Process = processArray[0]; // Initialize first process
    outfile << "At t=" << t << " Process " << Running_Process.id << " arrives and starts execution with priority " << Running_Process.priority << " and runtime " << Running_Process.runtime << endl;

    while(true) {
        Running_Process.Execute(); // Decrease runtime by 1
        t++; // Increase system clock
        for(int i=0; i<totalProcess; i++) {
            // Check if new process arrived
            if(processArray[i].arrivalTime == t) { // If the new process arrived
                if(processArray[i].priority < Running_Process.priority) { // If the new process has the higher priority
                    S1.Push(Running_Process); // Push the current process into stack
                    outfile << "At t="  << t << " Process " << Running_Process.id << " is pushed to stack with priority " << Running_Process.priority << " and runtime " << Running_Process.runtime << endl;
                    Running_Process = processArray[i]; // Update running process
                    outfile << "At t=" << t << " Process " << Running_Process.id << " arrives and starts execution with priority " << Running_Process.priority << " and runtime " << Running_Process.runtime << endl;
                    break; // No need to iterate more
                }
                else { // If the new process has the lower or equal priority
                    switch(processArray[i].priority) {
                        case 1: // If the new process has priority 1
                            Q1.Insert(processArray[i]); // If the id of the new process is 1, insert it in Q1.
                            outfile << "At t=" << t << " Process " << processArray[i].id << " is inserted into Q1 with priority " << processArray[i].priority << " and runtime " << processArray[i].runtime << endl;
                            break;
                        case 2: // If the new process has priority 2
                            Q2.Insert(processArray[i]); // If the id of the new process is 2, insert it in Q2.
                            outfile << "At t=" << t << " Process " << processArray[i].id << " is inserted into Q2 with priority " << processArray[i].priority << " and runtime " << processArray[i].runtime << endl;
                            break;
                        case 3: // If the new process has priority 3
                            Q3.Insert(processArray[i]); // If the id of the new process is 3, insert it in Q3.
                            outfile << "At t=" << t << " Process " << processArray[i].id << " is inserted into Q3 with priority " << processArray[i].priority << " and runtime " << processArray[i].runtime << endl;
                            break;
                        default: // If any ambiguous priority occurs
                            cerr << "Invalid case!" << endl;
                    }
                }
            }
            // After running process is finished, check all queues and the stack.
            // Compare their priorities and assign new running process.
            // If there is not any process in the queues and the stack, we are done.
            if(Running_Process.runtime == 0) {
                // First record the information of completed processes and all the latency information
                if(Running_Process.id != -1) {
                    outfile << "At t=" << t << " Process " << Running_Process.id << " is completed with priority " << Running_Process.priority << " and runtime " << Running_Process.runtime << endl;
                    latency << "Latency for Process " << Running_Process.id << " is " << t-Running_Process.arrivalTime << endl;
                }
                // Case for only stack is not empty
                if(Q1.QueueEmpty() && Q2.QueueEmpty() && Q3.QueueEmpty() && !S1.StackEmpty()) {
                    Running_Process = S1.Pop(); // Update running process
                    outfile << "At t=" << t << " Process " << Running_Process.id << " is popped from stack with priority " << Running_Process.priority << " and runtime " << Running_Process.runtime << endl;
                }
                // Case for Q1 is not empty. If Q1 is not empty, it will automatically be the running process
                // since stack cannot contain a process whose priority is 1.
                // It can contain at most 2 processes with priority 2 and 3.
                else if(!Q1.QueueEmpty()) {
                    Running_Process = Q1.Delete();
                    outfile << "At t=" << t << " Process " << Running_Process.id << " is dequeued from Q1 with priority " << Running_Process.priority << " and runtime " << Running_Process.runtime << endl;
                    }
                // Case for Q2 is not empty
                else if(!Q2.QueueEmpty()){ //
                    Process p1 = Q2.QFront(); // No modification on queue
                    if(!S1.StackEmpty()) { // If stack is not empty, compare priorities
                        Process p2 = S1.Peek();
                        if(p1.priority < p2.priority) { // If the process in Queue has higher priority
                            Running_Process = Q2.Delete();
                            outfile << "At t=" << t << " Process " << Running_Process.id << " is dequeued from Q2 with priority " << Running_Process.priority << " and runtime " << Running_Process.runtime << endl;
                        }
                        else { // If the process in Stack has higher priority
                            Running_Process = S1.Pop();
                            outfile << "At t=" << t << " Process " << Running_Process.id << " is popped from stack with priority " << Running_Process.priority << " and runtime " << Running_Process.runtime << endl;
                        }
                    }
                    else { // If stack is empty, then p1 is automatically will be the running process
                        Running_Process = Q1.Delete();
                        outfile << "At t=" << t << " Process " << Running_Process.id << " is dequeued from Q2 with priority " << Running_Process.priority << " and runtime " << Running_Process.runtime << endl;
                    }
                }
                // Case for Q3 is not empty
                else if(!Q3.QueueEmpty()) {
                    Process p1 = Q3.QFront();
                    if(!S1.StackEmpty()) { // If stack is not empty, compare priorities
                        Process p2 = S1.Peek();
                        if(p1.priority < p2.priority) { // If the process in Queue has higher priority
                            Running_Process = Q3.Delete();
                            outfile << "At t=" << t << " Process " << p1.id << " is dequeued from Q3 with priority " << Running_Process.priority << " and runtime " << Running_Process.runtime << endl;
                        }
                        else { // If the process in Stack has higher priority
                            Running_Process = S1.Pop();
                            outfile << "At t=" << t << " Process " << p2.id << " is popped from stack with priority " << Running_Process.priority << " and runtime " << Running_Process.runtime << endl;
                        }
                    }
                    else { // If stack is empty, then p1 is automatically will be the running process
                        Running_Process = Q3.Delete();
                        outfile << "At t=" << t << " Process " << p1.id << " is dequeued from Q3 with priority " << Running_Process.priority << " and runtime " << Running_Process.runtime << endl;
                    }

                }
                // If the running process is finished along with the stack and all the queues are empty, then we are done
                else {
                    Running_Process.id = -1;
                }
            }
        }

        // Stopping condition
        if(Running_Process.id == -1){
            break;
        }

    }

    outfile << "\nAll processes are done!" << endl;
    outfile.close();

    delete []processArray; // Return memory

    cout << "All the processes are done" << endl;
    cout << "Results are in output.txt" << endl;
    cout << "Latencies are in latency.txt" << endl;

    return 0;
}
