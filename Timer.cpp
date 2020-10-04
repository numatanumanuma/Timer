/*
 * getTime()を呼ばないと基本的に時間が更新されない
*/

#include "Timer.h"
#include "Arduino.h"

Timer::Timer() {
  isON = false;
  isOver = false;
  isStop = false;
  setMillis_ = 20 * 1000;
  leftMillis = 20 * 1000;
}

void Timer::set(long _millis) {
  setMillis_ = _millis;
  leftMillis = _millis;
}

void Timer::start() {
  startMillis_ = millis();
  leftMillis = setMillis_;
  isON = true;
  isOver = false;
  isStop = false;
}

void Timer::reset() {
  leftMillis = setMillis_;
  isON = false;
  isOver = false;
  isStop = true;
}

void Timer::stop(){
  getTime();
  if(!isStop)
    stopMillis_ = millis();
  isON = false;
  isStop = true;
}

void Timer::restart(){
  startMillis_ += (millis() - stopMillis_);
  isON = true;
  isStop = false;
}

void Timer::getTime() {
  if (!isON){
    sprintf(times, "%00d", setMillis_/1000);
    return;
  }
  if (!isStop){
    leftMillis = setMillis_ - (millis() - startMillis_);
  }
  if (leftMillis >= 0) {
    // 残り時間があるなら
    // ちょっと表示の数字が少ないので1を足す
    sprintf(times, "%00d", leftMillis / 1000 + 1);
  } else {
    // 時間切れなら 0でタイマーオフ 時間切れフラグを立てる
    sprintf(times, "0");
    leftMillis = 0;
    isON = false;
    isOver = true;
  }
}
