#ifndef PROTOTHREAD_H
#define PROTOTHREAD_H

#include <StandardCplusplus.h>
#include <vector>
#include <Arduino.h>

typedef void (*callback_func)(void);
typedef std::vector<struct PThread> PThread_vector;
class Protothread; // forward declare

enum MILLIS_P {
    SECOND_P    = 0x3E8 // 1000
    ,MINUTE_P   = SECOND_P * 60 // 60000
    ,HOUR_P     = MINUTE_P * 60 // 3600000
    ,DAY_P      = HOUR_P * 24 // 86400000
    ,WEEK_P     = DAY_P * 7 // 604800000
};

enum DELAY_P {
    MILLIS_DELAY_P    = 0x01
    ,MICROS_DELAY_P   = 0x02
};

struct PThread {

    public:
        PThread &setFunc(callback_func func) {this->_func = func; return *this;}
        PThread &whenToExecute(unsigned int whenToExecute) {this->_whenToExecute = whenToExecute; return *this;}
        unsigned int *whenToExecute(void) {return &this->_whenToExecute;}
        PThread &delayType(DELAY_P dt) {this->_delayType = dt; return *this;}
        DELAY_P *delayType(void) {return &this->_delayType;}
        void exec(void) {this->_func();}

        void terminate(bool flag) {this->_active = !flag;};
        bool terminate(void) {return !this->_active;};

    private:
        bool _active = true;
        volatile callback_func _func;
        unsigned int _whenToExecute;
        DELAY_P _delayType;

};

class Protothread {

    public:
        static Protothread *getInst(void);
        PThread *createThread(void (*func)(void), unsigned int whenToExecute);
        PThread *createThread(void (*func)(void), unsigned int whenToExecute, DELAY_P delayType);
        void processThreads(void);
    
    private:
        Protothread(void);
        static Protothread *_inst;
        const unsigned int _rollover = 0xFFFFFFFF; // 4294967295
        PThread_vector _threads;

};

#endif