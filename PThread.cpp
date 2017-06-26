#include <PThread.h>

PThread::PThread(void (*func)(void), Protothread *inst) {

    this->_func = func;
    this->_inst = inst;

}

void PThread::exec(void) {
    this->execute();
}

void PThread::execute(void) {
    this->_func();
}