#include <Protothread.h>

Protothread::Protothread(void) {}

PThread *Protothread::createThread(void (*func)(void), unsigned int whenToExecute) {

    //[](){}
    PThread newThread(func, this);
    this->_threads.push_back(&newThread);
    return &newThread;

}