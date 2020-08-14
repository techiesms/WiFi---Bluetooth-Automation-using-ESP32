/*
  This is the code for the project called

  WiFi & Bluetooth controlled Home Automation using ESP32

  This code is written by Sachin Soni on 14.08.2020

  The tutorial Video for the project is uploaded on 
  our YouTube channel called "techiesms"

  Channel Link - https://www.youtube.com/techiesms


          techiesms
  explore | learn | share 
*/

#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h> // https://github.com/blynkkk/blynk-library
#include "BluetoothSerial.h" // https://github.com/espressif/arduino-esp32/tree/master/libraries/BluetoothSerial


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run
`make menuconfig` to and enable it
#endif


BluetoothSerial SerialBT;


int bluedata; // variable for storing bluetooth data 

int relay1 = 15;
int relay2 = 2;
int relay3 = 4;
int relay4 = 22;

char auth[] = "AUTH_TOKEN";
char ssid[] = "SSID";
char pass[] = "PASS";

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(relay1, !pinValue);
  // process received value
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable
  digitalWrite(relay2, !pinValue);
  // process received value
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V3 to a variable
  digitalWrite(relay3, !pinValue);
  // process received value
}

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V4 to a variable
  digitalWrite(relay4, !pinValue);
  // process received value
}



void setup() 
{
  Serial.begin(115200);
  
  btStart();  Serial.println("Bluetooth On");
  
  SerialBT.begin("ESP32_Bluetooth"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  delay(10000);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);

  Serial.println("Connecting to Internet");
  delay(2000);

  WiFi.begin(ssid, pass); Serial.println("WiFi On");
  Blynk.config(auth);
  
  delay(2000);

}
void loop() 
{

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Not Connected");
  }
  else
  {
    Serial.println(" Connected");
    Blynk.run();
  }

  if (SerialBT.available())
  {

    Bluetooth_handle();

  }

}

void Bluetooth_handle()
{
  //char bluedata;
  bluedata = SerialBT.parseInt();
  //Serial.println(bluedata);
  delay(20);
  if (1 == bluedata) {
    digitalWrite(relay1, LOW);
    Blynk.virtualWrite(V1, 1);
    SerialBT.println("relay1 on");
    Serial.print("relay1 on\n");
  }
  else if (2 == bluedata) {
    digitalWrite(relay1, HIGH);
    Blynk.virtualWrite(V1, 0);
    SerialBT.println("relay1 off");
    Serial.print("relay1 off\n");
  }
  else if (3 == bluedata) {
    digitalWrite(relay2, LOW);
    Blynk.virtualWrite(V2, 1);
    SerialBT.println("relay2 on");
    Serial.print("relay2 on\n");
  }
  else if (4 == bluedata) {
    digitalWrite(relay2, HIGH);
    Blynk.virtualWrite(V2, 0);
    SerialBT.println("relay2 off");
    Serial.print("relay2 off\n");
  }
  else if (5 == bluedata) {
    digitalWrite(relay3, LOW);
    Blynk.virtualWrite(V3, 1);
    SerialBT.println("relay3 on");
    Serial.print("relay3 on\n");
  }
  else if (6 == bluedata) {
    digitalWrite(relay3, HIGH);
    Blynk.virtualWrite(V3, 0);
    SerialBT.println("relay3 off\n");
    Serial.print("relay3 off\n");
  }
  else if (7 == bluedata) {
    digitalWrite(relay4, LOW);
    Blynk.virtualWrite(V4, 1);
    SerialBT.println("relay4 on\n");
    Serial.print("relay4 on\n");
  }
  else if (bluedata == 8) {
    digitalWrite(relay4, HIGH);
    Blynk.virtualWrite(V4, 0);
    SerialBT.println("relay4 off");
    Serial.print("relay4 off\n");
  }
  else
  {
  }
}
