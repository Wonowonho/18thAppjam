#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "solar2.firebaseio.com"
#define FIREBASE_AUTH "6wMZgw3ozcT9ZmGa2yTMj9NlaBdt1wLGWYIYMKaZ"
#define WIFI_SSID "GDIP"
#define WIFI_PASSWORD ""


void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.print("recieve");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  //Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  String barcode = "";
  String firebarcode1 = Firebase.getString("/users/jiyoon1234/barcode");
  String firebarcode2 = Firebase.getString("/users/wonho1234/barcode");
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    while (Serial.available()) {
      char c = Serial.read();
      barcode += c;
    }
  }
  //Serial.println("파이어베이스의 데이터 : " + firebarcode1 + ",  읽은 바코드 값 : " + barcode);
  if (firebarcode1 != "" && firebarcode1.toInt() == barcode.toInt())  {
    String age1 = Firebase.getString("/users/jiyoon1234/age");
    //Serial.println("데이터 값이 같을 떄 --파이어베이스의 데이터 : " + firebarcode1 + ",  읽은 바코드 값 : " + barcode);
    //Serial.println("신용정보 조회 성공");
    Firebase.set("/users/jiyoon1234/check", "1");
    if (age1.toInt() <= 19) {
      Firebase.set("/users/jiyoon1234/check2", "1");
      Serial.println("1");
    }
    else if(age1.toInt() > 19) {
      Firebase.set("/users/jiyoon1234/check2","2");
      Serial.println("2");
    }
    delay(8000);
    Firebase.set("/users/jiyoon1234/check", "0");
  }
  if (firebarcode2 != "" && firebarcode2.toInt() == barcode.toInt())  {
    String age2 = Firebase.getString("/users/wonho1234/age");
    //Serial.println("데이터 값이 같을 떄 --파이어베이스의 데이터 : " + firebarcode1 + ",  읽은 바코드 값 : " + barcode);
    //Serial.println("신용정보 조회 성공");
    Firebase.set("/users/wonho1234/check", "1");
    if (age2.toInt() <= 19) {
      Firebase.set("/users/wonho1234/check2", "1");
      Serial.println("1");
    }
    else if(age2.toInt() > 19) {
      Firebase.set("/users/wonho1234/check2","2");
      Serial.println("2");
    }
    delay(8000);
    Firebase.set("/users/wonho1234/check", "0");
  }
  delay(100);
}
