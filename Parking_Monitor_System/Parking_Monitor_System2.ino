#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "VIVO Y32L";
const char* password = "kerokero"; //wifi connection stuff


WiFiServer server(80); //setup the board as a server on port 80 (html)


//begin sensor section
int sensor1 = D5;
int spot = 50;
int currentState=0;
int prevState1=0;
int prevState2=0;
int entrySensor;
int outSensor;



void setup() {

  Serial.begin(115200);

  
   // Begin WiFi Section
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("Name");
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot

  //part to verify connection to wifi by printing to serial
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());

  server.begin();         //very important to start the server


  pinMode(sensor1,INPUT);



}

 //the web page that will be displayed 
    String prepareHtmlPage()
    { 
      String htmlPage =
      String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 5\r\n" +       // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "<h1>" +
            "Parking Spot Left:  " + String(spot) +
            "</h1>" +
            "</html>" +
            "\r\n";
  return htmlPage;
}

void loop() {
   // THE MONITOR PART


   entrySensor= digitalRead(sensor1);
    if (entrySensor == HIGH )
    {
    currentState=1;
    }
   else 
    {
    currentState=0;
    }  

   if (currentState != prevState1) 
    { 
      if (currentState == 1 )
      {
        spot=spot-1;
        Serial.println(spot);
      }
    }

    prevState1=currentState;


      //THE WEBSERVER PART
     WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client)
  {
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
          client.println(prepareHtmlPage());
          break;
      }
    }
  }


}
