#ifndef PTHREAD_H
#define PTHREAD_H

#include <Protothread.h>

typedef void (*callback_func)(void);

class Protothread; // forward delcare

class PThread {

    public:
        PThread(void (*func)(void), Protothread *inst);
        void exec(void); // alias
        void execute(void);
    
    private:
        volatile Protothread *_inst;
        volatile callback_func _func;

};

#endif