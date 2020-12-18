/*
* ESP8266_NeoPixel.ino - Simple sketch to listen for E1.31 data on an ESP8266
*                        and drive WS2811 LEDs using the NeoPixel Library
*
* == Requires Adafruit_NeoPixel - http://github.com/adafruit/Adafruit_NeoPixel                        
*
* Project: E131 - E.131 (sACN) library for Arduino
* Copyright (c) 2015 Shelby Merrick
* http://www.forkineye.com
*
*  This program is provided free for you to use in any way that you wish,
*  subject to the laws and regulations where you are using it.  Due diligence
*  is strongly suggested before using this code.  Please give credit where due.
*
*  The Author makes no warranty of any kind, express or implied, with regard
*  to this program or the documentation contained in this document.  The
*  Author shall not be liable in any event for incidental or consequential
*  damages in connection with, or arising out of, the furnishing, performance
*  or use of these programs.
*
*/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <E131.h>
#include <Adafruit_NeoPixel.h>

#define LOG_PORT        Serial  /* Serial port for console logging */
#define CONNECT_TIMEOUT 15000   /* 15 seconds */

#define NUM_OUTPUTS_A 170  /* Number of pixels */
#define UNIVERSE_A 1      /* Universe to listen for */
#define CHANNEL_START_A 1 /* Channel to start listening at */

#define NUM_OUTPUTS_B 130  /* Number of pixels */
#define UNIVERSE_B 2      /* Universe to listen for */
#define CHANNEL_START_B 1 /* Channel to start listening at */

#define NUM_OUTPUTS_C 170  /* Number of pixels */
#define UNIVERSE_C 3      /* Universe to listen for */
#define CHANNEL_START_C 1 /* Channel to start listening at */

#define NUM_OUTPUTS_D 130  /* Number of pixels */
#define UNIVERSE_D 4      /* Universe to listen for */
#define CHANNEL_START_D 1 /* Channel to start listening at */

#define NUM_OUTPUTS_E 50  /* Number of pixels */
#define UNIVERSE_E 5      /* Universe to listen for */
#define CHANNEL_START_E 1 /* Channel to start listening at */

//Neopixel configurations ----------------------------------------------

#define NUM_PIXELS_A 300  /* Number of pixels */
#define NUM_PIXELS_B 300  /* Number of pixels */
#define NUM_PIXELS_C 50  /* Number of pixels */

#define DATA_PIN_A 14      /* Pixel output - GPIO14 / nodeMCU D5 */
#define DATA_PIN_B 12      /* Pixel output - GPIO12 / nodeMCU D6 */
#define DATA_PIN_C 13      /* Pixel output - GPIO13 / nodeMCU D7 */

const char ssid[] = "DLwireless";         /* Replace with your SSID */
const char passphrase[] = "22342234";   /* Replace with your WPA2 passphrase */

E131 e131;
ESP8266WebServer server ( 80 );

Adafruit_NeoPixel pixels_a = Adafruit_NeoPixel(NUM_PIXELS_A, DATA_PIN_A, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixels_b = Adafruit_NeoPixel(NUM_PIXELS_B, DATA_PIN_B, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixels_c = Adafruit_NeoPixel(NUM_PIXELS_C, DATA_PIN_C, NEO_RGB + NEO_KHZ800);

int initWifi() {
    /* Switch to station mode and disconnect just in case */
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(secureRandom(100,500));


    LOG_PORT.println("");
    LOG_PORT.print(F("Connecting to "));
    LOG_PORT.println(ssid);

    WiFi.begin(ssid, passphrase);


    uint32_t timeout = millis();
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        LOG_PORT.print(".");
        if (millis() - timeout > CONNECT_TIMEOUT) {
            LOG_PORT.println("");
            LOG_PORT.println(F("*** Failed to connect ***"));
            break;
        }
    }

    if (WiFi.status() == WL_CONNECTED) {
        LOG_PORT.println("");
        LOG_PORT.print(F("Connected with IP: "));
        LOG_PORT.println(WiFi.localIP());

        e131.begin(E131_MULTICAST, UNIVERSE_A, UNIVERSE_E - UNIVERSE_A + 1);

        digitalWrite(D4, LOW);  //indicate connected
    }

    return WiFi.status();
}

String getPage(){
  String page = "<html><head><meta http-equiv='refresh' content='120' name='viewport' content='width=device-width, initial-scale=1'/>";
  page += "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script><script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>";
  page += "<title>BunnyPixel E1.31 Controller</title></head><body>";
  page += "<div class='container-fluid'>";
  page +=   "<div class='row'>";
  page +=     "<div class='col-md-12'>";
  page +=       "<h1>BunnyPixel E1.31 Controller</h1>";
  page +=       "<h3>Status Panel</h3>";
  page +=       "<table class='table'>";
  page +=         "<thead><tr><th>Status</th><th>Value</th></tr></thead>";
  page +=         "<tbody>";
  page +=           "<tr><td>IP Address</td><td>";
  page +=           WiFi.localIP().toString();
  page +=           "</td></tr>";
  page +=           "<tr><td>MCU Voltage</td><td>";
  float vccVolt = ((float)ESP.getVcc())/1024;
  page +=           vccVolt;
  page +=           " V</td></tr>";
  page +=           "<tr><td>Memory Usage</td><td>";
  page +=           ESP.getFreeHeap();
  page +=           " / ";
  page +=           ESP.getFlashChipSize();
  page +=           "</td></tr>";
  page +=       "</tbody></table>";
  page +=       "<h3>Pixel Test</h3>";
  page +=       "<div class='row'>";
  page +=         "<div class='col-md-6'><h4 class ='text-left'>Universe 1 ";
  page +=           "<span class='badge'>";
  page +=           String(NUM_PIXELS_A);
  page +=         " pixels</span></h4></div>";
  page +=         "<div class='col-md-6'><form action='/' method='POST'><button type='button submit' name='D5' value='1' class='btn btn-success btn-lg'>Run Test</button></form></div>";
  page +=         "<div class='col-md-6'><h4 class ='text-left'>Universe 2 ";
  page +=           "<span class='badge'>";
  page +=           String(NUM_PIXELS_B);
  page +=         " pixels</span></h4></div>";
  page +=         "<div class='col-md-6'><form action='/' method='POST'><button type='button submit' name='D6' value='1' class='btn btn-success btn-lg'>Run Test</button></form></div>";
  page +=         "<div class='col-md-6'><h4 class ='text-left'>Universe 3 ";
  page +=           "<span class='badge'>";
  page +=           String(NUM_PIXELS_C);
  page +=         " pixels</span></h4></div>";
  page +=         "<div class='col-md-6'><form action='/' method='POST'><button type='button submit' name='D7' value='1' class='btn btn-success btn-lg'>Run Test</button></form></div>";
  page +=       "</div>";
  page +=     "<br><p>Written by Dominick Lee.</p>";
  page += "</div></div></div>";
  page += "</body></html>";
  return page;
}

void handleRoot(){ 
  if ( server.hasArg("D5") ) {
      theaterChaseA(50);
  } else if ( server.hasArg("D6") ) {
      theaterChaseB(50);
  } else if ( server.hasArg("D7") ) {
      theaterChaseC(50);
  }
  else {
    server.send ( 200, "text/html", getPage() );
  }  
}

void theaterChaseA(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < pixels_a.numPixels(); i=i+3) {
        pixels_a.setPixelColor(i+q, WheelA( (i+j) % 200));    //turn every third pixel on
      }
      pixels_a.show();
      delay(wait);
      for (uint16_t i=0; i < pixels_a.numPixels(); i=i+3) {
        pixels_a.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t WheelA(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels_a.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels_a.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels_a.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void theaterChaseB(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < pixels_b.numPixels(); i=i+3) {
        pixels_b.setPixelColor(i+q, WheelB( (i+j) % 200));    //turn every third pixel on
      }
      pixels_b.show();
      delay(wait);
      for (uint16_t i=0; i < pixels_b.numPixels(); i=i+3) {
        pixels_b.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t WheelB(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels_b.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels_b.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels_b.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void theaterChaseC(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < pixels_c.numPixels(); i=i+3) {
        pixels_c.setPixelColor(i+q, WheelC( (i+j) % 200));    //turn every third pixel on
      }
      pixels_c.show();
      delay(wait);
      for (uint16_t i=0; i < pixels_c.numPixels(); i=i+3) {
        pixels_c.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t WheelC(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels_c.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels_c.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels_c.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

ADC_MODE(ADC_VCC);

void setup() {
    LOG_PORT.begin(115200);
    delay(10);
    pinMode(D4, OUTPUT);
    digitalWrite(D4, HIGH);
      
    /* Choose one to begin listening for E1.31 data */
    e131.begin(ssid, passphrase);                       /* via Unicast on the default port */
    //e131_a.beginMulticast(ssid, passphrase, UNIVERSE_A);  /* via Multicast for Universe 1 */
    initWifi();
    
    /* Initialize output */
    pixels_a.begin();
    pixels_a.show();
    pixels_b.begin();
    pixels_b.show();
    pixels_c.begin();
    pixels_c.show();

    if (!MDNS.begin("bunnypixel")) {
      Serial.println("Error setting up MDNS responder!");
      while(1) { 
        delay(1000);
      }
    }
    Serial.println("mDNS responder started");

    server.on ( "/", handleRoot );
    server.begin();
}

void loop() {
    server.handleClient();
    /* Parse a packet and update pixels */
    if(e131.parsePacket())
    {
        if (e131.universe == UNIVERSE_A) {
            //Serial.print("Univ A \t");
            for (int i = 0; i < NUM_OUTPUTS_A; i++) {
                int j = i * 3 + (CHANNEL_START_A - 1);
                pixels_a.setPixelColor(i, e131.data[j], e131.data[j+1], e131.data[j+2]);
                /*
                Serial.print(e131.data[j]);
                Serial.print("\t");
                Serial.print(e131.data[j+1]);
                Serial.print("\t");
                Serial.println(e131.data[j+2]);
                */
            }
            //pixels_a.show();
        }
        if (e131.universe == UNIVERSE_B) {
            //Serial.print("Univ B \t");
            for (int i = 0; i < NUM_OUTPUTS_B; i++) {
                int j = i * 3 + (CHANNEL_START_B - 1);
                pixels_a.setPixelColor(i + NUM_OUTPUTS_A, e131.data[j], e131.data[j+1], e131.data[j+2]);
                /*
                Serial.print(e131.data[j]);
                Serial.print("\t");
                Serial.print(e131.data[j+1]);
                Serial.print("\t");
                Serial.println(e131.data[j+2]);
                */
            }
            pixels_a.show();
        }
        if (e131.universe == UNIVERSE_C) {
            //Serial.print("Univ C \t");
            for (int i = 0; i < NUM_OUTPUTS_C; i++) {
                int j = i * 3 + (CHANNEL_START_C - 1);
                pixels_b.setPixelColor(i, e131.data[j], e131.data[j+1], e131.data[j+2]);
                /*
                Serial.print(e131.data[j]);
                Serial.print("\t");
                Serial.print(e131.data[j+1]);
                Serial.print("\t");
                Serial.println(e131.data[j+2]);
                */
            }
            //pixels_b.show();
        }
        if (e131.universe == UNIVERSE_D) {
            //Serial.print("Univ D \t");
            for (int i = 0; i < NUM_OUTPUTS_D; i++) {
                int j = i * 3 + (CHANNEL_START_D - 1);
                pixels_b.setPixelColor(i + NUM_OUTPUTS_C, e131.data[j], e131.data[j+1], e131.data[j+2]);
                /*
                Serial.print(e131.data[j]);
                Serial.print("\t");
                Serial.print(e131.data[j+1]);
                Serial.print("\t");
                Serial.println(e131.data[j+2]);
                */
            }
            pixels_b.show();
        }
        if (e131.universe == UNIVERSE_E) {
            //Serial.print("Univ E \t");
            for (int i = 0; i < NUM_OUTPUTS_E; i++) {
                int j = i * 3 + (CHANNEL_START_E - 1);
                pixels_c.setPixelColor(i, e131.data[j], e131.data[j+1], e131.data[j+2]);
                /*
                Serial.print(e131.data[j]);
                Serial.print("\t");
                Serial.print(e131.data[j+1]);
                Serial.print("\t");
                Serial.println(e131.data[j+2]);
                */
            }
            pixels_c.show();
        }
    }
}
