/*
  firewall.h
  copyright by lutzion.de
*/

#ifndef EspFirewall_h
#define EspFirewall_h

#include "Arduino.h"
#include <ESP8266WiFi.h> 

class EspFirewall
{
  private:
    uint32_t _ip, _mask, _dbgLvl ;

	public:
		EspFirewall();
    void setDebugLevel(int lvl);
    bool setCIDR(String cCIDR) ;
		bool IPisAllowed(IPAddress ip);
};

#endif