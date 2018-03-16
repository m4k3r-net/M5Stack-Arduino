  /**************************************************************
 * Local Time Stamp with ESP32
 * Developed by Marcelo Rovai - 8 September 2017
 **************************************************************/
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include <WiFiMulti.h>
#include <M5Stack.h>

#include "m5_internet_time.h"


#define NTP_OFFSET  -7  * 60 * 60 // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "europe.pool.ntp.org"
//#define NTP_ADDRESS  "0.north-america.pool.ntp.org"
//#define NTP_ADDRESS  "us.pool.ntp.org"

WiFiMulti WiFiMulti;
WiFiClient  client;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

m5_internet_time  internet_time(TFT_YELLOW , TFT_BLACK , 20 , 4);

void setup()
{
  // M5 platform
  M5.begin();
  delay(1000); 
  M5.Lcd.fillScreen(TFT_BLACK); 
  M5.Lcd.drawRect(0,0,319,239,TFT_WHITE); 

  // Wifi
  WiFiMulti.addAP("SSID", "PASSWORD__");
  delay(5000);

  // NTP Client
  if(WiFiMulti.run() == WL_CONNECTED){
      timeClient.begin();  
  }  
    
}

void loop() 
{  
  timeClient.update();    
  internet_time.update(timeClient.getEpochTime());   
  internet_time.display();   
 
  delay(1000);
}
