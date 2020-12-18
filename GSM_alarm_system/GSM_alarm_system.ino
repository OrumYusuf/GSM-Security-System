// Yusuf ÖRÜM
// for like this codes please visit my youtube channel -----> (Yusuf ÖRÜM)

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); //SIM800L Tx & Rx is connected to Arduino #3 & #2                                 
int value;                          
int light;
int lazer = 4;
int gas;
int ldr;
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(lazer,OUTPUT);
  Serial.println("Initializing...");

  delay(1000);
}

void loop()
{
  digitalWrite(lazer,HIGH);
  light = analogRead(A0); // gets value from lazer sensor
  value = analogRead(A1); // gets value from gas sensor
    Serial.println(light);
    Serial.println(value);

  delay(50);


  if(value>=300){
  gas = 1;
  }
  else {gas = 0;}

    if(light<=900){
  ldr = 1;
  }
  else {ldr = 0;}

  Serial.println(gas);
    Serial.println(ldr);

  while(ldr){ 
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"############\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("Thief Alarm!!!"); //text content
  updateSerial();
  mySerial.write(26);
  ldr = 0;
  }
  updateSerial();

  while(gas){ 
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+############\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("Fire Alarm!!!"); //text content
  updateSerial();
  mySerial.write(26);
  gas = 0;
  }
delay (10000);
  
updateSerial();
  

 
}

void updateSerial()
{
  delay(3000);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
