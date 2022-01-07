/*
  firewall.cpp
  copyright by lutzion.de
*/

#include "EspFirewall.h" 

EspFirewall::EspFirewall()
{
  // default: allow everything
  _ip = 0 ;
  _mask = 0 ;
  _dbgLvl = 0 ;
}

void EspFirewall::setDebugLevel(int lvl)
{
  _dbgLvl = lvl;
}

bool EspFirewall::setCIDR(String cCIDR) 
{
  int ip[4] ;
  int bits ;

  // for ip4 so far
  sscanf(cCIDR.c_str(), "%d.%d.%d.%d/%d", &ip[0], &ip[1], &ip[2], &ip[3], &bits) ;

  _ip = (ip[0] << 24) + 
        (ip[1] << 16) + 
        (ip[2] <<  8) + 
         ip[3] ;
  _mask = 0xFFFFFFFF << (32 - bits) ;

  if (_dbgLvl > 0)
  {
    Serial.printf("EspFirewall::setCIDR(%s) -> %08X / %08X\n", cCIDR.c_str(), _ip, _mask);
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

  if (!ok && (_dbgLvl > 0))
  {
    String sIP = ip.toString();
    Serial.printf("EspFirewall::IPisAllowed(%s) blocked (%08X & %08X != %08X & %08X)\n", 
                   sIP.c_str(), _ip, _mask, ipIn, _mask);
  }

  return ok ;
}