#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include "Arduino.h"
#include "Audio.h"


#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu=0;
#else 
static const BaseType_t app_cpu=1;
#endif

static TaskHandle_t task_Speaker_Handle= NULL ;
static TaskHandle_t task_Web_Handle= NULL ;


#define I2S_DOUT  27
#define I2S_BCLK  26
#define I2S_LRC   25

Audio audio;

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "Mr";
const char* password = "8765432100";


WiFiServer server(80);

String header;

String output23State = "off";
String output1State = "off";
String output3State = "off";
String output19State = "off";
String output18State = "off";
String output5State = "off";
String output17State = "off";
String output16State = "off";
String output2State = "off";
String output4State = "off";
String output15State = "off";

String input36state="LOW";
String input39state="LOW";
String input34state="LOW";
String input35state="LOW";
String input32state="LOW";
String input33state="LOW";
String input14state="LOW";
String input12state="LOW";
String input13state="LOW";



const int output23 = 23;
const int output1  = 1;
const int output3  = 3;
const int output19 = 19;
const int output18 = 18;
const int output5 = 5;
const int output17 = 17;
const int output16 = 16;
const int output4  = 4;
const int output2  = 2;
const int output15  = 15;

const int input36=36;
const int input39=39;
const int input34=34;
const int input35=35;
const int input32=32;
const int input33=33;
const int input14=14;
const int input12=12;
const int input13=13;


unsigned long currentTime = millis();

unsigned long previousTime = 0; 

const long timeoutTime = 2000;

void task_Speaker(void *parameter){
  
 while(1){                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
//audio
  audio.loop();
  }
}

void task_Web(void *parameter){
  
 while(1){
vTaskDelay( 1000/ portTICK_PERIOD_MS);
  
  input36state=digitalRead(input36) ? "HIGH" : "LOW";
  input39state=digitalRead(input39) ? "HIGH" : "LOW";
  input34state=digitalRead(input34) ? "HIGH" : "LOW";
  input35state=digitalRead(input35) ? "HIGH" : "LOW";
  input32state=digitalRead(input32) ? "HIGH" : "LOW";
  input33state=digitalRead(input33) ? "HIGH" : "LOW";
  input14state=digitalRead(input14) ? "HIGH" : "LOW";
  input12state=digitalRead(input12) ? "HIGH" : "LOW";
  input13state=digitalRead(input13) ? "HIGH" : "LOW";
  
  WiFiClient client = server.available();   

  if (client) {                          
    currentTime = millis();
    previousTime = currentTime;
    Serial.println(F("New Client."));         
    String currentLine = "";                
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  
      currentTime = millis();
      if (client.available()) {            
        char c = client.read();         
        Serial.write(c);                    
        header += c;
        if (c == '\n') {               
         
       
          if (currentLine.length() == 0) {
            
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-type:text/html"));
            client.println(F("Connection: close"));
            client.println();

          

            if (header.indexOf("GET /23/on") >= 0) {
           
            
              output23State = "on";
              digitalWrite(output23, HIGH);
            }
            
             else if (header.indexOf("GET /23/off") >= 0) {
         
            
              output23State = "off";
              digitalWrite(output23, LOW); 
             }
              else if (header.indexOf("GET /2/on") >= 0) {
         
          display.clearDisplay();
          display.setCursor(0, 10);
          display.println(F("GPIO 2 on"));
          display.display();
    
              output2State = "on";
              digitalWrite(output2, HIGH);
            }
                else if (header.indexOf("GET /2/off") >= 0) {
         
          display.clearDisplay();
          display.setCursor(0, 10);
          display.println(F("GPIO 2 off"));
          display.display();
          output2State = "off";
          digitalWrite(output2, LOW);
               
          
            }
            else if (header.indexOf("GET /1/on") >= 0) {
        
              output1State = "on";
              digitalWrite(output3, HIGH);
            } 
              else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println(F("GPIO  off"));
              output1State = "off";
              digitalWrite(output1, LOW);
              }
             
              else if (header.indexOf("GET /3/on") >= 0) {
        
              output3State = "on";
              digitalWrite(output3, HIGH);
            } 
              else if (header.indexOf("GET /3/off") >= 0) {
      
              output3State = "off";
              digitalWrite(output3, LOW);
              }
              else if (header.indexOf("GET /19/on") >= 0) {
        
              output19State = "on";
              digitalWrite(output19, HIGH);
            }
              
              else if (header.indexOf("GET /19/off") >= 0) {
       
              output19State = "off";
              digitalWrite(output19, LOW);
            }
              else if (header.indexOf("GET /18/on") >= 0) {
         
              output18State = "on";
              digitalWrite(output18, HIGH);
            }
              else if (header.indexOf("GET /18/off") >= 0) {
      
              output18State = "off";
              digitalWrite(output18, LOW);
            }
              else if (header.indexOf("GET /5/on") >= 0) {
    
              output5State = "on";
              digitalWrite(output5, HIGH);
            }
             
             else if (header.indexOf("GET /5/off") >= 0) {
  
              output5State = "off";
              digitalWrite(output5, LOW);
            }
             else if (header.indexOf("GET /17/on") >= 0) {
     
              output17State = "on";
              digitalWrite(output17, HIGH);
             
            } else if (header.indexOf("GET /17/off") >= 0) {
   
              output17State = "off";
              digitalWrite(output17, LOW);
            }
              else if (header.indexOf("GET /16/on") >= 0) {
  
              output16State = "on";
              digitalWrite(output16, HIGH);
             
            } else if (header.indexOf("GET /16/off") >= 0) {

              output16State = "off";
              digitalWrite(output16, LOW);
            }
              else if (header.indexOf("GET /4/on") >= 0) {
   
              output4State = "on";
              digitalWrite(output4, HIGH);
             
            } else if (header.indexOf("GET /4/off") >= 0) {
    
              output4State = "off";
              digitalWrite(output4, LOW);
            }
              else if (header.indexOf("GET /15/on") >= 0) {
   
              output15State = "on";
              digitalWrite(output15, HIGH);
             
            } else if (header.indexOf("GET /15/off") >= 0) {

              output15State = "off";
              digitalWrite(output15, LOW);
            }
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta http-equiv=\"refresh\" content=\"7\">"); 
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            
            client.println("<body><h1>ESP32 Web Server</h1>");
                 //2 displaying state of led2
            client.println("<p>GPIO 2 - State " + output2State + "</p>");
            
            if (output2State=="off") {
            client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
            client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
        
            client.println("<p>GPIO 23 - State " + output23State + "</p>");
            
            if (output23State=="off") {
            client.println("<p><a href=\"/23/on\"><button class=\"button\">ON</button></a></p>");
            } else {
            client.println("<p><a href=\"/23/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
        
            client.println("<p>GPIO 1 - State " + output1State + "</p>");
            
            if (output1State=="off") {
            client.println("<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>");
            } else {
            client.println("<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
        
            client.println("<p>GPIO 3 - State " + output3State + "</p>");
            
            if (output3State=="off") {
            client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            } else {
            client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("<p>GPIO 19 - State " + output19State + "</p>");
            
            if (output19State=="off") {
            client.println("<p><a href=\"/19/on\"><button class=\"button\">ON</button></a></p>");
            } else {
            client.println("<p><a href=\"/19/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
          
            client.println("<p>GPIO 18 - State " + output18State + "</p>");
            
            if (output18State=="off") {
            client.println("<p><a href=\"/18/on\"><button class=\"button\">ON</button></a></p>");
            } else {
            client.println("<p><a href=\"/18/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            client.println("<p>GPIO 5 - State " + output5State + "</p>");
            
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
         

               client.println("<p>GPIO 17 - State " + output17State + "</p>");
            
            if (output17State=="off") {
              client.println("<p><a href=\"/17/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/17/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
           

               client.println("<p>GPIO 16 - State " + output16State + "</p>");
            
            if (output16State=="off") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

        

            client.println("<p>GPIO 4 - State " + output4State + "</p>");
     
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

       

           

            client.println("<p>GPIO 15 - State " + output15State + "</p>");
     
            if (output15State=="off") {
              client.println("<p><a href=\"/15/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/15/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            
            
            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 36 - State: ");
            client.print(input36state);
            client.println("</p>");
            client.println("</body></html>");

            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 39 - State: ");
            client.print(input39state);
            client.println("</p>");
            client.println("</body></html>");

            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 34 - State: ");
            client.print(input34state);
            client.println("</p>");
            client.println("</body></html>");
            
            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 35 - State: ");
            client.print(input35state);
            client.println("</p>");
            client.println("</body></html>");

            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 32 - State: ");
            client.print(input32state);
            client.println("</p>");
            client.println("</body></html>");
            
            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 33 - State: ");
            client.print(input33state);
            client.println("</p>");
            client.println("</body></html>");

            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 14 - State: ");
            client.print(input14state);
            client.println("</p>");
            client.println("</body></html>");

            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 12 - State: ");
            client.print(input12state);
            client.println("</p>");
            client.println("</body></html>");

            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 13 - State: ");
            client.print(input13state);
            client.println("</p>");
            client.println("</body></html>");
 
            client.println();
 
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') { 
          currentLine += c;      
        }
      }
  }  
  
    header = "";

    client.stop();
    //Serial.println(F("Client disconnected."));
    Serial.println("");
  }
 


  }
}


  

void setup() {
  
    Serial.begin(1000000);
    Serial.print(F("Connecting to "));
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay( 1000/ portTICK_PERIOD_MS);
    Serial.print(".");
  }
  //pin config i2s
   audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
   audio.setVolume(90);

   //connect to internet
  //audio.connecttohost("http://vis.media-ice.musicradio.com/CapitalMP3");
  //audio.connecttohost("mediaserv30.live-nect MAX98357 I2S Amplifier Module
  //audio.connecttohost("www.surfmusic.de/m3u/100-5-das-hitradio,4529.m3u");
  //audio.connecttohost("stream.1a-webradio.de/deutsch/mp3-128/vtuner-1a");
  //audio.connecttohost("www.antenne.de/webradio/antenne.m3u");
  audio.connecttohost("0n-80s.radionetz.de:8000/0n-70s.mp3");
  //audio.connecttohost("https://www.youtube.com/watch?v=95yUbClyf3E&list=PLXyB2ILBXW5FLc7j2hLcX6sAGbmH0JxX8&index=3");

   
 

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  vTaskDelay( 2000/ portTICK_PERIOD_MS);
  
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);

   

     
   //wifi conn
  Serial.println("");
  Serial.println(F("WiFi connected."));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());
  server.begin();

  
    
    pinMode(output23, OUTPUT);
    pinMode(output1, OUTPUT);
    pinMode(output3, OUTPUT);
    pinMode(output19, OUTPUT);
    pinMode(output18, OUTPUT);
    pinMode(output5, OUTPUT);
    pinMode(output17, OUTPUT);
    pinMode(output16, OUTPUT);
    pinMode(output4, OUTPUT);
    pinMode(output2, OUTPUT);
    pinMode(output15, OUTPUT);

 
   pinMode(input36,INPUT);
   pinMode(input39,INPUT);
   pinMode(input34,INPUT);
   pinMode(input35,INPUT);
   pinMode(input32,INPUT);
   pinMode(input33,INPUT);
   pinMode(input14,INPUT);
   pinMode(input12,INPUT);
   pinMode(input13,INPUT);

xTaskCreatePinnedToCore( task_Speaker,
                              "Connect Speaker",
                              2000,
                              NULL,
                              2,
                              &task_Speaker_Handle,
                              app_cpu);
xTaskCreatePinnedToCore( task_Web,
                              "Control_Web",
                              2000,
                              NULL,
                              2,
                              &task_Web_Handle,
                              app_cpu);

}

void loop(){

}
