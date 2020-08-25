//NOTE:
//Program ini merupakan program utama ESP Wroom-02.
//Data yang dikirimkan oleh ATMega328 akan disimpan pada SD Card melalui protokol komunikasi SPI.
//Data yang diterima oleh ESP02 akan dikirim ke Cloud menggunakan WiFI (IEEE 802.11)
//Pastikan tombol Boot ditekan pada saat melakukan flashing


//Address yang didapatkan program scanning, dimasukan pada variabel addATMega dan addSDCard.

#include <SD.h>
#include <SPI.h>
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>


File myFile;
int pinCS = 15; // GPIO15 pada ESP WROOM -02 (Pin 6) - SS SPI

int dtATMega = 0;
String dtSDCard = "";

char ssid[] = "WISTA";   //Nama Wifi
char pass[] = "99912999";    //Password Wifi
unsigned long myChannelNumber = 1;  // Disesuaikan dengan channel pada thingspeak.
const char * myWriteAPIKey = "X22WNHD2EH72L54K";    // ThingSpeak Write API Key.
//------------------------------------------------------------------

WiFiClient  client;

void setup()
{
  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  rtc.begin();

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}


void loop()
{
  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  getDataATMega():
  saveDataSDCard():
  thingSpeak();
  
  }


  /
