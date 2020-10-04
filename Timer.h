#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"

class Timer {
  public:
    Timer();
    void start();
    void set(long _millis);
    void getTime();
    void reset();
    void stop();
    void restart();

    char times[4];
    long leftMillis;

    bool isON;
    bool isOver;
    bool isStop;
  private:
    long startMillis_;
    long setMillis_;
    long stopMillis_;
//    bool isON_;
//    bool isOver_;
     
};
#endif
