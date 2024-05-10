
#include <WiFi.h>


const char* ssid = "Mr";
const char* password = "8765432100";


WiFiServer server(80);


String header;


String output26State = "off";
String output27State = "off";
String output2State = "off";
String output4State = "off";
String input15state="LOW";
String input5state="LOW";
String input18state="LOW";
String input19state="LOW";

const int output2 = 2;
const int output4 = 4;
const int output26 = 26;
const int output27 = 27;
const int input15=15;
const int input5=5;
const int input18=18;
const int input19=19;


unsigned long currentTime = millis();

unsigned long previousTime = 0; 

const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
 
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output4, OUTPUT);
  //-----------------------
  pinMode(input15,INPUT);
   pinMode(input5,INPUT);
    pinMode(input18,INPUT);
     pinMode(input19,INPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
    digitalWrite(output2, LOW);
  digitalWrite(output4, LOW);
  


  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  input15state=digitalRead(input15) ? "HIGH" : "LOW";
  input5state=digitalRead(input5) ? "HIGH" : "LOW";
  input18state=digitalRead(input18) ? "HIGH" : "LOW";
  input19state=digitalRead(input19) ? "HIGH" : "LOW";
  
  WiFiClient client = server.available();   

  if (client) {                          
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");         
    String currentLine = "";                
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  
      currentTime = millis();
      if (client.available()) {            
        char c = client.read();         
        Serial.write(c);                    
        header += c;
        if (c == '\n') {               
         
       
          if (currentLine.length() == 0) {
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            

            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              output27State = "on";
              digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
            }//for led2
            else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            }
             else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta http-equiv=\"refresh\" content=\"3\">"); 
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
         
            client.println("<p>GPIO 26 - State " + output26State + "</p>");
            
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               

            client.println("<p>GPIO 27 - State " + output27State + "</p>");
           
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            // displaying state of led2
            client.println("<p>GPIO 2 - State " + output2State + "</p>");
            
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //------

            client.println("<p>GPIO 4 - State " + output4State + "</p>");
     
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            //
            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 15 - State: ");
            client.print(input15state);
            client.println("</p>");
            client.println("</body></html>");

            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 5 - State: ");
            client.print(input5state);
            client.println("</p>");
            client.println("</body></html>");

            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 18 - State: ");
            client.print(input18state);
            client.println("</p>");
            client.println("</body></html>");
            
            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"></head><body>");
            client.print("<p>Input Pin 19 - State: ");
            client.print(input19state);
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
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
