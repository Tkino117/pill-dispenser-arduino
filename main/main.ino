#include "main.h"
#include "Servo.h"
Servo servoA;
Servo servoB;
Servo servoC;

const int Light_sencer_Pin = 5; /*光センサーPIN　5番ピン*/
const int SvPin_A = 9, SvPin_B = 10, SvPin_C = 11; /*サーボモータのPIN番号設定　A-9 B-10 C-11*/
int Light_sencer, millis_buf;

LedMatrixController led;
WiFiController wifi;
WiFiClient client;

void setup() {
  Serial.begin(115200);

  pinMode(Light_sencer_Pin, INPUT);
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
      while(millis() - millis_buf < 780){
        servoA.write(0);
      }
      servoA.write(90);
    }
  }
  else if(id == 2){
    for(int i = 0; i < count; i++){
      millis_buf = millis();
      while(millis() - millis_buf < 800){
        servoB.write(0);
      }
      servoB.write(90);
    }
  }
  else if(id == 3){
    for(int i = 0; i < count; i++){
      millis_buf = millis();
      while(millis() - millis_buf < 790){
        servoC.write(0);
      }
      servoC.write(90);
    }
  }
}

int tmp = 0;
String needsToSendData() {
  String res = "0";
  if ((tmp / 1000) % 10 != 0 && (millis() / 1000) % 10 == 0) {
    res = "take pill";
  }
  tmp = millis();
  return res;
}

void reconnect() {
    Serial.println("reconnecting..");
    while (!client.connect(host, port)) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("reconnected!");
}