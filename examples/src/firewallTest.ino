/*
   firewallTest.ino
   copyright by lutzion.de
*/

#include <ESP8266WiFi.h>

#include "../../include/EspFirewall.h"


#define LED   LED_BUILTIN 

bool toggle = false ;

EspFirewall firewall ;

void setup()
{
    pinMode(LED, OUTPUT);
    digitalWrite(LED, toggle);  
    
    Serial.begin(115200);
    
    delay(500);

    Serial.println("=== FIREWALL TEST ===");
    firewall.setLogLevel(debug);
    firewall.setIpRange("192.168.1.0/24");
    Serial.println("LogLvl: " + String(firewall.getLogLevel())) ;
}

void loop()
{
    int x = random(1,3) ;
    int y = random(100,150);
    IPAddress  ia = IPAddress(192, 168, x, y) ;

    Serial.println("Checking " + ia.toString() + " ...") ;
    Serial.println(firewall.IPisAllowed(ia) ? "OK" : "blocked") ;
    delay(500);
}

