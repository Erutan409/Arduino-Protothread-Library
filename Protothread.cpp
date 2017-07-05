#include <Protothread.h>

Protothread::Protothread(void) {}
//define static properties
Protothread *Protothread::_inst;

Protothread *Protothread::getInst(void) {

    if (Protothread::_inst == nullptr) {Protothread::_inst = new Protothread();}
    return Protothread::_inst;

}

// default to millis
PThread *Protothread::createThread(callback_func func, unsigned int whenToExecute) {
    return createThread(func, whenToExecute, MILLIS_DELAY_P);
}

PThread *Protothread::createThread(callback_func func, unsigned int whenToExecute, DELAY_P delayType) {

    unsigned int current = delayType == MICROS_DELAY_P? micros() : millis();
    unsigned int diff = this->_rollover - current;

    PThread newThread;
    newThread.setFunc(func)
            .whenToExecute(diff >= whenToExecute? current + whenToExecute : whenToExecute - diff)
            .delayType(delayType);
    this->_threads.push_back(newThread);

    return &this->_threads.at(this->_threads.size() - 1);

}

void Protothread::processThreads(void) {

    for (int i = 0; i < this->_threads.size(); i++) {
        
        PThread &t = this->_threads.at(i);

        unsigned int current = *t.delayType() == MICROS_DELAY_P? micros() : millis();

        if (t.terminate()) {goto removeVector;}
        if (*t.whenToExecute() > current) {continue;}

        t.exec();

        removeVector:
        this->_threads.erase(this->_threads.begin() + i);
        i--; // reset back one

    }

}