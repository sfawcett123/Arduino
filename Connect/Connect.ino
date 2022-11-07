#include <SPI.h>
#include <WiFiNINA.h>

class FlightSim
{
   private:
    int status = WL_IDLE_STATUS;
    char *secret_ssid = "BT-93AF3W";
    char *secret_pass = "FDbMTrepcU4rLq";

   public: 
    void Status()
    {
        digitalWrite( LED_BUILTIN, LOW ); 
        if ( status != WL_CONNECTED) {
          Serial.println("Couldn't get a WiFi connection");
        }
        else
        {
          Serial.println("WiFi connected");
        }
        digitalWrite( LED_BUILTIN, HIGH ); 

    }

    FlightSim()  
    {
        pinMode( LED_BUILTIN, OUTPUT );
        digitalWrite( LED_BUILTIN, HIGH ); 
        status = WiFi.begin(secret_ssid, secret_pass);
    }
 
};


/**** MAIN BODY ******/


FlightSim sim() ;
WiFiClient client;

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial Connected 77");
  sim.Status();
}
 

void loop()
{
      //sim.Status();
      delay(1000);
}
