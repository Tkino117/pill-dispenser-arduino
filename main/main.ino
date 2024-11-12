#include "main.h"
#include "Servo.h"
Servo servoA;
Servo servoB;
Servo servoC;

const int Light_sencer_Pin = 5; /*光センサーPIN　5番ピン*/
const int SvPin_A = 9, SvPin_B = 10, SvPin_C = 11; /*サーボモータのPIN番号設定　A-9 B-10 C-11*/
const int LED_Pin = 3, Buz_Pin = 4; /*追加　LEDPIN3番ピン　ブザーPIN4番ピン*/
int Light_sencer, millis_buf;

const int servoA_360 = 780;
const int servoB_360 = 800;
const int servoC_360 = 795;

LedMatrixController led;
WiFiController wifi;
WiFiClient client;

void setup() {
  Serial.begin(115200);

  pinMode(Light_sencer_Pin, INPUT);
  pinMode(LED_Pin, OUTPUT); /*追加*/

  servoA.attach(SvPin_A);  /*サーボ設定*/
  servoB.attach(SvPin_B);
  servoC.attach(SvPin_C);

  led.init();
  wifi.connect();
  Serial.print("try to connect to : ");
  Serial.print(host);
  Serial.print(" ");
  Serial.println(port);
  while (!client.connect(host, port)) {
    Serial.print("Connection failed. time : ");
    Serial.println(millis());
    delay(1000);
  }
  Serial.println("connected to the server!");
  Serial.println("arduino will start.");
}

void loop(){
  // led.drawChar("hello!", true);

  // message from server
    if (client.available()) {
      String line = client.readStringUntil('\r');
      line.trim();  // delete \r \n
      if (line.length() > 0) {
        Serial.print("received from server : ");
        Serial.println(line);
        execute(line);
      }
    }

  // message to server
  String s = needsToSendData();
  if (s != "0") {
    Serial.print("send message to server : ");
    Serial.println(s);
    client.println(s);
  }
  
  // if disconnected
  if (!client.connected()) {
    Serial.println("disconnected from the server.");
    reconnect();
  }
  delay(1000);
}

void execute(String cmd) {
  bool err = false;
  String words[10];
  int wordCount = 0;
  int lastSpace = -1;
  int nextSpace;

  // cmd to words[] (devided by ' ')
  while ((nextSpace = cmd.indexOf(' ', lastSpace + 1)) != -1) {
      if (lastSpace + 1 == nextSpace) {
        lastSpace++;
        continue;
      }
      words[wordCount] = cmd.substring(lastSpace + 1, nextSpace);
      wordCount++;
      lastSpace = nextSpace;
  }
  words[wordCount] = cmd.substring(lastSpace + 1);
  wordCount++;

  // command dis
  if (words[0] == "dispense" && wordCount == 3) {
    int id, count;
    id = words[1].toInt();
    count = words[2].toInt();
    if (id == 0 && words[1] != "0" || count == 0 && words[2] != "0") {
      err = true;
    }
    if (!err) {
      Serial.print("executing cmd : dispense ");
      Serial.print(id);
      Serial.print(" ");
      Serial.print(count);
      Serial.println();
      dispense(id, count);
    }
  }
  else if (words[0] == "servo" && wordCount == 3) {
    int id, deg;
    id = words[1].toInt();
    deg = words[2].toInt();
    if (id == 0 && words[1] != "0" || deg == 0 && words[2] != "0") {
      err = true;
    }
    if (!err) {
      Serial.print("executing cmd : servo ");
      Serial.print(id);
      Serial.print(" ");
      Serial.print(deg);
      Serial.println();
      adjustServo(id, deg);
    }
  }
  else {
    err = true;
  }

  if (err) {
    Serial.println("ERROR : cmd executing error. word is invalid.");
  }
}

void dispense(int id, int count) {
  // dispense pill here!
  if(id == 1){
    for(int i = 0; i < count; i++){
      millis_buf = millis();
      while(millis() - millis_buf < servoA_360){
        servoA.write(0);
      }
      servoA.write(90);
    }
  }
  else if(id == 2){
    for(int i = 0; i < count; i++){
      millis_buf = millis();
      while(millis() - millis_buf < servoB_360){
        servoB.write(0);
      }
      servoB.write(90);
    }
  }
  else if(id == 3){
    for(int i = 0; i < count; i++){
      millis_buf = millis();
      while(millis() - millis_buf < servoC_360){
        servoC.write(0);
      }
      servoC.write(90);
    }
  }
  digitalWrite(LED_Pin, HIGH);/*追加　薬排出時LED点灯*/
  tone(Buz_Pin,440);
}


int tmp = 0;
int Old;
String needsToSendData() {
  String res = "0";
  /*追加　排出後かつ光センサー反応時　LEDを消灯*/
  int Light_Sensor = digitalRead(Light_sencer_Pin);
  // Serial.println(Light_Sensor);
  // delay(100);
  if(Old == 1 && Light_Sensor == 0){
    digitalWrite(LED_Pin, LOW);
    noTone(Buz_Pin);
    res = "take pill";
    Serial.println("here2");
  }
  Old = Light_Sensor;
  return res;
}

void adjustServo(int id, int deg) {
  int tmp = millis();
  int write;
  if (deg >= 0) write = 0;
  else {
    deg = -deg;
    write = 180;
  }

  if (id == 1) {
    while(millis() - tmp < servoA_360 * deg / 360){
      servoA.write(write);
    }
    servoA.write(90);
  }
  else if (id == 2) {
    while(millis() - tmp < servoB_360 * deg / 360){
      servoB.write(write);
    }
    servoB.write(90);
  }
  else if (id == 3) {
    while(millis() - tmp < servoC_360 * deg / 360){
      servoC.write(write);
    }
    servoC.write(90);
  }
}

void reconnect() {
    Serial.println("reconnecting..");
    while (!client.connect(host, port)) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("reconnected!");
}