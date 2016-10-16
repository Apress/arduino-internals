#include "EtherShield.h"

EtherShield es; // the EtherShield "object"

// please change these numbers!
byte mac_address[] = { 0x04, 0x07, 0x01, 0x09, 0x06, 0x03 };
byte ip_address[] = { 192, 168, 0, 99 };

#define BUFFER_SIZE 1000 // make it 500 for '168-based Arduinos
byte page_buffer[BUFFER_SIZE];

const char webpage_contents[] PROGMEM =
"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"
"<html><head><title>Arduino EN28J60 Web Server</title></head><body>"
"<h1>Arduino EN28J60 Web Server</h1>"
"<p>Yup, it works.</p>"
"<p>Simply amazing!</p>"
"<hr />"
"</body></html>"; // The End.  This line must have a semicolon ";" at the end of it

void setup() {
  es = EtherShield(); // create the EtherShield 'object'
  es.ES_enc28j60Init(mac_address); // initialize EN28J60
  es.ES_init_ip_arp_udp_tcp(mac_address, ip_address, 80); // use port 80
}

void loop() {
  if(es.ES_packetloop_icmp_tcp(page_buffer, es.ES_enc28j60PacketReceive(BUFFER_SIZE, page_buffer))) {
    // send web page contents if HTTP request received
    es.ES_www_server_reply(page_buffer, es.ES_fill_tcp_data_p(page_buffer, 0, webpage_contents));
  }
}
