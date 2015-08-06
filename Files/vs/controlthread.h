#ifndef CONTROLTHREAD_H
#define CONTROLTHREAD_H
#include "threadd.h"
class controlThread: public QThread
{
public:
    controlThread();
    void control(threadd &a, bool &is);
    void run();
    threadd *a;
    bool *is;
};

#endif // CONTROLTHREAD_H
