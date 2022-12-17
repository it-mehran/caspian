#include <SoftwareSerial.h>
//*********************************************Config Uart_PIN
const int PIN_RXD = 2;
const int PIN_TXT = 3;
SoftwareSerial WIFI(PIN_RXD, PIN_TXT); // RX, TX
//*********************************************Config PIN_RLY
const int PIN_RLY1 = 4;
const int PIN_RLY2 = 5;
const int PIN_RLY3 = 6;
const int PIN_RLY4 = 7;
const int PIN_LED = 13;
//*********************************************Config WIFI
const String IP_SERVER = "192.168.4.1";
const String wifi_name = "caspiannoor";
const String wifi_pass = "1234test";
const long interval = 500;
//*********************************************Create Value
unsigned long previousMillis = 0;
int start_search = 0;
int ledState = HIGH;
String input_data;
String Message;
//*********************************************Subprogram setup()
void setup() {
  pinMode(PIN_RLY1, OUTPUT);
  pinMode(PIN_RLY2, OUTPUT);
  pinMode(PIN_RLY3, OUTPUT);
  pinMode(PIN_RLY4, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_RLY1, LOW);
  digitalWrite(PIN_RLY2, LOW);
  digitalWrite(PIN_RLY3, LOW);
  digitalWrite(PIN_RLY4, LOW);
  digitalWrite(PIN_LED, HIGH);
  WIFI.begin(115200);
  set_ESP8266_server();
  set_ip_wifi();
  set_pass_wifi();
}
//*********************************************Subprogram loop()
void loop() {
  if (WIFI.available()) {
    digitalWrite(PIN_LED, HIGH);
    read_input_data();
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(PIN_LED, ledState);
  }
}
//*********************************************Subprogram read_input_data()
void read_input_data() {
  input_data = WIFI.readString();
  input_data.trim();
  start_search = input_data.indexOf(":");
  start_search++;
  input_data = input_data.substring(start_search);
  Run_command();
}
//*********************************************Subprogram Run_command()
void Run_command() {
  Message = "";
  if (input_data == "R1on" || input_data == "r1on" || input_data == "R1ON" || input_data == "r1On" || input_data == "r1ON" || input_data == "r1oN") {
    digitalWrite(PIN_RLY1, HIGH);
    Message = "Relay 1 ON";
  } else if (input_data == "R1of" || input_data == "r1of" || input_data == "R1OF" || input_data == "r1Of" || input_data == "r1OF" || input_data == "r1oF") {
    digitalWrite(PIN_RLY1, LOW);
    Message = "Relay 1 OFF";
  } else if (input_data == "R2on" || input_data == "r2on" || input_data == "R2ON" || input_data == "r2On" || input_data == "r2ON" || input_data == "r2oN") {
    digitalWrite(PIN_RLY2, HIGH);
    Message = "Relay 2 ON";
  } else if (input_data == "R2of" || input_data == "r2of" || input_data == "R2OF" || input_data == "r2Of" || input_data == "r2OF" || input_data == "r2oF") {
    digitalWrite(PIN_RLY2, LOW);
    Message = "Relay 2 OFF";
  } else if (input_data == "R3on" || input_data == "r3on" || input_data == "R3ON" || input_data == "r3On" || input_data == "r3ON" || input_data == "r3oN") {
    digitalWrite(PIN_RLY3, HIGH);
    Message = "Relay 3 ON";
  } else if (input_data == "R3of" || input_data == "r3of" || input_data == "R3OF" || input_data == "r3Of" || input_data == "r3OF" || input_data == "r3oF") {
    digitalWrite(PIN_RLY3, LOW);
    Message = "Relay 3 OFF";
  } else if (input_data == "R4on" || input_data == "r4on" || input_data == "R4ON" || input_data == "r4On" || input_data == "r4ON" || input_data == "r4oN") {
    digitalWrite(PIN_RLY4, HIGH);
    Message = "Relay 4 ON";
  } else if (input_data == "R4of" || input_data == "r4of" || input_data == "R4OF" || input_data == "r4Of" || input_data == "r4OF" || input_data == "r4oF") {
    digitalWrite(PIN_RLY4, LOW);
    Message = "Relay 4 OFF";
  } else if (input_data == "on" || input_data == "ON" || input_data == "On") {
    digitalWrite(PIN_RLY1, HIGH);
    digitalWrite(PIN_RLY2, HIGH);
    digitalWrite(PIN_RLY3, HIGH);
    digitalWrite(PIN_RLY4, HIGH);
    Message = "All relays are turned ON";
  } else if (input_data == "off" || input_data == "OFF" || input_data == "Off") {
    digitalWrite(PIN_RLY1, LOW);
    digitalWrite(PIN_RLY2, LOW);
    digitalWrite(PIN_RLY3, LOW);
    digitalWrite(PIN_RLY4, LOW);
    Message = "All relays are turned OFF";
  }
  if (Message != "") {
    Message = Message + " | ";
    WIFI.print("AT+CIPSEND=0,");
    WIFI.println(Message.length());
    delay (1000);
    WIFI.println(Message);
  }
}
//*********************************************Subprogram set_ESP8266_server()
void set_ESP8266_server() {
  WIFI.println("AT");
  delay (1000);
  WIFI.println("AT+RST");
  delay (3000);
  WIFI.println("AT+CIPMUX=1");
  delay (2000);
  WIFI.println("AT+CIPSERVER=1,8888");
  delay (3000);
}
//*********************************************Subprogram set_ip_wifi()
void set_ip_wifi() {
  WIFI.print("AT+CIPAP=\"");
  WIFI.print(IP_SERVER);
  WIFI.println("\"");
  delay (2000);
}
//*********************************************Subprogram set_pass_wifi()
void set_pass_wifi() {
  WIFI.print("AT+CWSAP=\"");
  WIFI.print(wifi_name);
  WIFI.print("\",\"");
  WIFI.print(wifi_pass);
  WIFI.println("\",1,3");
  delay (3000);
}
