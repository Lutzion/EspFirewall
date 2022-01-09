/*
  EspFirewall.h
  copyright by lutzion.de
*/

#ifndef EspFirewall_h
#define EspFirewall_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

enum LogLvl
{
  debug,
  block,
  warn,
  none
};

class EspFirewall
{
  private:
    uint32_t _ip, _mask ;
    LogLvl _logLvl ;

  public:
    EspFirewall();
    LogLvl getLogLevel();
    bool setLogLevel(LogLvl lvl);
    bool setIpRange(String cIPR) ;
    bool IPisAllowed(IPAddress ip);
};

#endif