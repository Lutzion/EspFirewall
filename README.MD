# EspFirewall

like descriped in the title of this project, this is a minimal firewall for ESP devices like ESP8266 or ESP32.
  
--- 
# Functions
## getLogLevel()

get the actual log level. Levels can be
- debug: log everything that is coded
- block: log ips that are detected to block and warnings
- warn: log warnings
- none: log nothing  
  
## setLogLevel(LogLvl lvl)

set the level  
  
## setIpRange(String cCIDR)

set ip and mask for firewall in format a.b.c.d/r for example 192.168.1.0/24  
  
## IPisAllowed(IPAddress ip)

function for checking if ip-address has to be blocked.
   
you have to code consequences of blocked ip:
- don't let client connect if ip-address is not allowed for tcp connections
- don't process udp data if ip-address is not allowed
- ...  
  
  
--- 
# Log of firewallTest (the example)
```
21:31:27.177 > EspFirewall::setIpRange(192.168.1.0/24) -> C0A80100 / FFFFFF00
21:31:27.183 > LogLvl: 0
21:31:27.185 > Checking 192.168.2.145 ...
21:31:27.185 > EspFirewall::IPisAllowed(192.168.2.145) blocked (C0A80100 & FFFFFF00 != C0A80291 & FFFFFF00)
21:31:27.194 > blocked
21:31:29.189 > Checking 192.168.1.111 ...
21:31:29.190 > OK
...
```