#include <SoftwareSerial.h>
#include <SimpleDHT.h>

const int dht = 2, vent = 3, led = 4, grijanje = 5;
const String d_temp = "|", d_vla = "-", d_ven = "/", d_ras = "#", d_grijanje = "%";

String input_rasv = "0", output_rasv = "";
String stanje_vent = "", stanje_grijanja = "";
String output_msg = "";  

int temperatura, vlaga;
int TH_vent_t = 25, TH_heat_t = 18;
  
SoftwareSerial MEGA(11,10);
SimpleDHT11 dht11(dht);

void setup() {
  Serial.begin(9600);
  MEGA.begin(4800);
  pinMode(vent, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(grijanje, OUTPUT);
}

void loop() {
  String msg_name = "";
  
  while(MEGA.available() > 0){
    if(MEGA.overflow()){
      Serial.println("Owerflov podataka!");
    }else{
      msg_name = MEGA.readStringUntil('|');        
      Serial.println(msg_name);
      
      if(msg_name == "FIRST"){
        TH_heat_t = MEGA.readStringUntil('%').toInt();
        TH_vent_t = MEGA.readStringUntil('/').toInt();
        input_rasv = MEGA.readStringUntil('#');         
      }else if (msg_name == "LIGHT"){
        if(input_rasv == "0"){
          input_rasv ="1";
        }else if(input_rasv == "1"){
          input_rasv = "0";
        }
      }else if(msg_name == "VENT"){          
        TH_vent_t =  MEGA.readStringUntil('/').toInt();
      }else if (msg_name == "HEAT"){          
        TH_heat_t =  MEGA.readStringUntil('/').toInt();
      }     
    }      
  }  
  
  DHT_podaci();
  stanje_vent = Ventilator();
  stanje_grijanja = Grijanje(); 
  output_rasv = Rasvjeta(); 
  
  output_msg = temperatura + d_temp + vlaga + d_vla + stanje_vent + d_ven + output_rasv + d_ras + stanje_grijanja + d_grijanje;

  Serial.print("Odlaz: ");
  Serial.println(output_msg);
  MEGA.print(output_msg);
  delay(3500);
}

void DHT_podaci(){
  byte t = 0, v = 0;
  dht11.read(&t, &v, NULL);
  temperatura = (int)t;
  vlaga = (int)v;          
}

String Ventilator(){
  String text = "";
  if (temperatura >= TH_vent_t){
    text = "1";
    digitalWrite(vent,HIGH);
  }else{
    text = "0";  
    digitalWrite(vent,LOW);
  }
  return text;  
}

String Rasvjeta(){
    String text = "";
    if (input_rasv == "1"){
      text = "1";
      digitalWrite(led,HIGH);
    }else if (input_rasv == "0"){
      text = "0";
      digitalWrite(led,LOW);       
    }
    return text;
}

String Grijanje(){
    String text = "";
    if (temperatura <= TH_heat_t){
      text = "1"; 
      digitalWrite(grijanje, HIGH); 
    }else{
      text = "0"; 
      digitalWrite(grijanje, LOW); 
    }
    return text;
}
