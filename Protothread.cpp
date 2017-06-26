#include <Protothread.h>
#include <algorithm>

Protothread::Protothread(void) {}

PThread *Protothread::createThread(void (*func)(void), unsigned int whenToExecute) {

    unsigned int current = millis();
    unsigned int diff = this->_rollover - current;

    struct PThread newThread;
    newThread.inst = this;
    newThread.func = func;
    newThread.whenToExecute = diff >= whenToExecute? current + whenToExecute : whenToExecute - diff;
    this->_threads.push_back(newThread);

    return &newThread;

}

void Protothread::processThreads(void) {

    unsigned int current = millis();

    for (int i = 0; i < this->_threads.size(); i++) {
        
        struct PThread &t = this->_threads.at(i);

        if (t.terminate()) {goto removeVector;}
        if (t.whenToExecute > current) {continue;}

        t.func();

        removeVector:
        this->_threads.erase(i);
        i--; // reset back one

    }

}