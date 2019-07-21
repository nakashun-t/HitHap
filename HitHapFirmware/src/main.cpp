#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <Servo.h>

char ssid[] = "*********";          //your network SSID
char pass[] = "*********";          //your network password

WiFiUDP Udp;
const IPAddress outIp(10,40,10,105);
const unsigned int outPort = 9999;
const unsigned int localPort = 8888;

static const int servoPin = 13;
Servo servo1;

OSCErrorCode error;
unsigned int servoPos;

void setup() {
  Serial.begin(115200);
  servo1.attach(servoPin);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
#ifdef ESP32
  Serial.println(localPort);
#else
  Serial.println(Udp.localPort());
#endif

}

void servo(OSCMessage &msg) {
  servoPos = msg.getInt(0);
  servoPos = -servoPos + 84;
  servo1.write(servoPos);
  Serial.print("/servoPos: ");
  Serial.println(servoPos);
}

void loop() {
  OSCMessage message;
  int size = Udp.parsePacket();

  if (size > 0) {
    while (size--) {
      message.fill(Udp.read());
    }
    if(!message.hasError()){
      message.dispatch("/servo", servo);
    } else {
      error = message.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}
