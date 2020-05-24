#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
#include "Stack.h"
using namespace std;


class Process
{
    public:
        Process();
        int id;
        int priority;
        int arrivalTime;
        int runtime; // Number of cycles of the remaining execution time of the processes
        void Execute();
        int PrintProcess();
};

Process::Process() {
    id = -1;
    priority = 0;
    arrivalTime = 0;
    runtime = 0;
}

void Process::Execute() {
    runtime--; // Decrease runtime
}

#endif // PROCESS_H
