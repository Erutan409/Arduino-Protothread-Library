#ifndef PROTOTHREAD_H
#define PROTOTHREAD_H

#include <StandardCplusplus.h>
#include <vector>
#include <Arduino.h>
#include <PThread.h>

class PThread; // forward declare

typedef std::vector<PThread> PThread_vector;

class Protothread {

    public:
        Protothread(void);
        PThread *createThread(void (*func)(void));
    
    private:
        PThread_vector *_threads;

};

#endif