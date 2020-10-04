#include <Arduino.h>
#include "Timer.h"

int lightValue = 0;
bool waitprint = false;

/*タイマー関連*/
bool watching;
Timer timer;

/* ブザーのピン番号　*/
#define BUZZER_PIN 5
/* LEDのピン番号　*/
#define LED_PIN 4
/*ひねるやつのピン番号*/
#define ROTARY_PIN A0
/*ボタンのピン番号*/
#define BUTTON_PIN 6
/* ライトセンサーのピン番号*/
#define LIGHT_PIN A6

/*タイマーの時間をここでセット (秒) * 1000 */
#define TIMER_MILLIS 15 * 1000
#define DILAY_MILLIS 100

// センサーの状態を取得
bool getStateSensor(){
  lightValue = analogRead(LIGHT_PIN);
  if(lightValue < 200)
    return true;
  else
    return false;
}
void setup() { 
  Serial.begin(115200);
  pinMode(ROTARY_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LIGHT_PIN, INPUT);

  watching = false;

  // 時間設定
  timer.set(TIMER_MILLIS);
  timer.start();

  digitalWrite(LED_PIN, LOW);

}

void loop() {
  if(watching){
    /* 見守り中 */
    digitalWrite(LED_PIN, HIGH);
    if(getStateSensor()){
      /* 手洗い中 */
      if (timer.isStop) {
        /* 一時停止なら再開 */
        timer.restart();
        Serial.println("restart");
      }
      // タイマーの残り時間取得
      timer.getTime();
      if (timer.isOver){
        /* 時間切れ */
        Serial.println("good!!!!!!!!!!");
      }else {
        Serial.println(timer.times);
      }
    }else{
      /* 手を洗っていない */
      timer.getTime();
      if (timer.isOver){
        /* 手洗い完了してるなら */
        watching = false;
        timer.reset();
      }else{
        /* サボっているなら指導*/
        if (!timer.isStop){
          Serial.println("bad!!!!!!!!!!");
          timer.stop();
        }
      }
    }
  }else{
    // 待機中
    digitalWrite(LED_PIN, LOW);
    if (getStateSensor()){
      /* 手洗い開始 */
      watching = true;
      waitprint = false;
      Serial.println("start watching");
      // タイマースタート
      timer.start();
    }else{
      // waitprintのフラグでもうwaitingを出力したかを確認
      // 一度のみにしておきたいため
      if (!waitprint){
        Serial.println("waiting");
        waitprint = true;
      }
    }
  }
  delay(DILAY_MILLIS);
}
