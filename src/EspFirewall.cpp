/*
  EspFirewall.cpp
  copyright by lutzion.de
*/

#include "EspFirewall.h" 

EspFirewall::EspFirewall()
{
  // default: allow everything, log nothing
  _ip = 0 ;
  _mask = 0 ;
  _logLvl = none ;
}

bool EspFirewall::setLogLevel(LogLvl lvl)
{
  _logLvl = lvl;
  return true ;
}
LogLvl EspFirewall::getLogLevel()
{
  return _logLvl ;
}

bool EspFirewall::setIpRange(String cIPR) 
{
  int ip[9] ;
  int bits ;

  // for ip4 so far
  sscanf(cIPR.c_str(), "%d.%d.%d.%d/%d", &ip[0], &ip[1], &ip[2], &ip[3], &bits) ;

  _ip = (ip[0] << 24) + 
        (ip[1] << 16) + 
        (ip[2] <<  8) + 
         ip[3] ;
  _mask = 0xFFFFFFFF << (32 - bits) ;

  if (_logLvl <= debug)
  {
    Serial.printf("EspFirewall::setIpRange(%s) -> %08X / %08X\n", cIPR.c_str(), _ip, _mask);
  }

  return true ;
}

bool EspFirewall::IPisAllowed(IPAddress ip) 
{
  uint32_t ipIn ;
  bool ok = true ;

  if (_ip == 0 &&
      _mask == 0)
  {
    // no CIDR set -> always true 
    return true ;
  }
  
  // convert IPAdress to uint32_t (only v4 so far)
  ipIn = (ip[0] << 24) + 
         (ip[1] << 16) + 
         (ip[2] <<  8) + 
          ip[3] ;

  ok = ((_ip & _mask) == (ipIn & _mask)) ;

  if (!ok && (_logLvl <= block))
  {
    String sIP = ip.toString();
    Serial.printf("EspFirewall::IPisAllowed(%s) blocked (%08X & %08X != %08X & %08X)\n", 
                   sIP.c_str(), _ip, _mask, ipIn, _mask);
  }

  return ok ;
}