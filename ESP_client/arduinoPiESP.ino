#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
SoftwareSerial Comunication_ESP(D2,D3); //Rx,Tx

const char* ssid = "ISKONOVAC-0D7B15";
const char* password = "MUPTARGE4UQX";

const char* host = "192.168.5.152";
const int port = 8080;

WiFiClient client;
bool toggleLed = false;

void setup()
{
  Serial.begin(9600);

  //arduino komunikacija
  Comunication_ESP.begin(4800);
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);

  //pi komunikacija
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}

void loop(){
  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, port)){
    Serial.println("connected]");
    
    while (client.connected()){
      if (client.available()){
        String msg = client.readStringUntil('\n');
        Comunication_ESP.print(msg);    
      }
      
      if(Comunication_ESP.available() > 0){        
        if(Comunication_ESP.overflow()){
          Serial.println("Owerflov podataka!");
        }else{
          String msg = Comunication_ESP.readStringUntil('\n');          
          Serial.print("Dolaz od MEGA-e: ");
          Serial.println(msg);
          Serial.println("\n");
          
          send_data(msg);
        }
      }
      delay(1750);    
    }   
    client.stop();
    Serial.println("\n[Disconnected]");
  }else{
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(5000);
}

void send_data(String msg){    
    client.print(msg);

    Serial.print("Odlaz na Server: ");
    Serial.println(msg);
    Serial.println("\n");
}
