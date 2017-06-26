#ifndef PROTOTHREAD_H
#define PROTOTHREAD_H

#include <StandardCplusplus.h>
#include <vector>
#include <Arduino.h>

typedef void (*callback_func)(void);
typedef std::vector<struct PThread> PThread_vector;
class Protothread; // forward declare

struct PThread {

    public:
        volatile Protothread *inst;
        volatile callback_func func;
        unsigned int whenToExecute;

        void terminate(bool flag) {this->_active = flag;};
        bool terminate(void) {return this->_active;};

    private:
        bool _active = true;

};

enum TIME_P {
    SECOND_P    = 0x3E8 // 1000
    ,MINUTE_P   = SECOND_P * 60 // 60000
    ,HOUR_P     = MINUTE_P * 60 // 3600000
    ,DAY_P      = HOUR_P * 24 // 86400000
    ,WEEK_P     = DAY_P * 7 // 604800000
};

class Protothread {

    public:
        Protothread(void);
        PThread *createThread(void (*func)(void), unsigned int whenToExecute);
        void processThreads(void);
    
    private:
        const unsigned int _rollover = 0xFFFFFFFF; // 4294967295
        PThread_vector _threads;

};

#endif