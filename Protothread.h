#ifndef PROTOTHREAD_H
#define PROTOTHREAD_H

#include <StandardCplusplus.h>
#include <vector>
#include <Arduino.h>

typedef void (*callback_func)(void);
typedef std::vector<struct PThread> PThread_vector;
class Protothread; // forward declare

struct PThread {
    volatile Protothread *inst;
    volatile callback_func func;
    unsigned int whenToExecute;
};

enum TIME_P {
    SECOND_P = 1000
    ,MINUTE_P = SECOND_P * 60
    ,HOUR_P = MINUTE_P * 60
    ,DAY_P = HOUR_P * 24
    ,WEEK_P = DAY_P * 7
};

class Protothread {

    public:
        Protothread(void);
        void createThread(void (*func)(void), unsigned int whenToExecute);
        void processThreads(void);
    
    private:
        const unsigned int _rollover = 4294967296;
        PThread_vector _threads;

};

#endif