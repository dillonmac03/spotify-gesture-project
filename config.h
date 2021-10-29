#ifndef __CONFIG_H
#define __CONFIG_H

// Enter your WiFi settings here 
char ap_ssid[] = "NETGEAR";
char ap_key[] = "spanky.1";

// NTP pool to use
char ntp_pool[] = "us.pool.ntp.org";

// AWS endpoint.. should look something like this:
// {random characters}.iot.{service zone}.amazonaws.com
// for example: abcd1234.iot.eu-west-1.amazonaws.com
char aws_endpoint[] = "agipwedf1y619.iot.us-west-1.amazonaws.com";



#endif
