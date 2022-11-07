#include <SPI.h>
#include <WiFiNINA.h>
#include "FlightSimulator.h"
#include <LiquidCrystal_I2C.h>

#include "C:\Users\steve\source\secrets\secrets.h"

int status = WL_IDLE_STATUS;
int ListenPort = 0;

String RequiredOutputs[1] = {"PLANE ALTITUDE"};
DynamicJsonDocument SimulatorData(100) ;

WiFiClient wifi;//HttpClient client = HttpClient( wifi , HOST_NAME , HOST_PORT);
FlightSimulator fsclient = FlightSimulator( wifi , HOST_NAME , HOST_PORT );
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  lcd.init();  
  lcd.backlight();
 

  Serial.begin(9600);

  while ( status != WL_CONNECTED) {
    Serial.print("Connecting to WiFi ");
    Serial.println( ssid );
    status = WiFi.begin(ssid, pass);
  }

  ListenPort = fsclient.Register( RequiredOutputs );

  if( ListenPort > 0 )
      if( wifi.connect(  HOST_NAME , ListenPort ) )
      {
        Serial.print( "Connected to ");
        Serial.print(HOST_NAME);
        Serial.print(" port " );
        Serial.println(ListenPort);
      }
}

void loop() {

  fsclient.ReadFSData(&SimulatorData) ;
  String Altitude = SimulatorData["PLANE ALTITUDE"];
  lcd.setCursor(0,0);
  lcd.print( "Alt: ");
  lcd.print( Altitude );

  delay(1000);

  // if the server's disconnected, stop the client:
  if (!wifi.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    wifi.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}