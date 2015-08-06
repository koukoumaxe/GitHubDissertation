#include "controlthread.h"

controlThread::controlThread()
{
is=false;
}

void controlThread::control(threadd &a, bool &is){
this->a=&a;
this->is=&is;


}

void controlThread::run(){
    while(is){
        a->sleep(10);
        cout<<"zzz"<<endl;
    }
}
