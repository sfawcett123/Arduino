#include <SPI.h>
#include <WiFiNINA.h>
#include "FlightSimulator.h"
#include <LiquidCrystal_I2C.h>

#include "C:\Users\steve\source\secrets\secrets.h"

int status = WL_IDLE_STATUS;
int ListenPort = 0;

String RequiredOutputs[1] = {"PLANE ALTITUDE"};
DynamicJsonDocument SimulatorData(100) ;

WiFiClient wifi;
FlightSimulator fsclient = FlightSimulator( wifi , HOST_NAME , HOST_PORT );
LiquidCrystal_I2C lcd(0x27,20,4);


void setup() {
 
  lcd.init();  
  lcd.backlight();
 
  Serial.begin(9600);
}

void loop() {

  if( status == WL_CONNECTED )
  {   
    if( !fsclient.connected())
    {
      Serial.println( "Registering");
      ListenPort = fsclient.Register( RequiredOutputs );
      if( ListenPort > 0 )
      {
        wifi.connect(  HOST_NAME , ListenPort );
        Serial.println( "Connected to host");
      }
    }

    if( fsclient.connected())
    {
      fsclient.Read(&SimulatorData) ;
      fsclient.Write(&SimulatorData) ;
    }

    String Altitude = SimulatorData["PLANE ALTITUDE"];
    lcd.setCursor(0,0);
    lcd.print( "Alt:");
    lcd.print( Altitude );
  }
  else
  {
    delay(5000);
    status = WiFi.begin(ssid, pass);
    Serial.println( status);
  } 
  delay(1000);
}