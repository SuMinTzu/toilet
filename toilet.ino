#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define Senpin A0
int Senval=0;
Servo myservo; // 建立Servo物件，控制伺服馬達
#define fsr_pin A0
#define MAX_BTCMDLEN 128
SoftwareSerial BTSerial(8,9); // Arduino RX/TX
int ModaIn = 3;
byte cmd[MAX_BTCMDLEN]; // received 128 bytes from an Android system
int len = 0; // received command length
int aa=1;
void setup() 
{ 
  myservo.attach(10); // 連接數位腳位10，伺服馬達的訊號線
  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(ModaIn, OUTPUT);
} 

void loop() 
{
  Senval=analogRead(Senpin);
    Serial.print("Analog reading = ");
    Serial.println(Senval);
    if(Senval>15 && Senval<30){
        Serial.println("#Using#");
        
        //bluetooth
         char str[MAX_BTCMDLEN];
         int insize, ii;  
         int tick=0;
         while ( tick<MAX_BTCMDLEN ) { // 因為包率同為9600, Android送過來的字元可能被切成數份
          if ( (insize=(BTSerial.available()))>0 ){ // 讀取藍牙訊息
            
            for ( ii=0; ii<insize; ii++ ){
                cmd[(len++)%MAX_BTCMDLEN]=char(BTSerial.read());
                aa = 0 - aa;
                Serial.println(aa) ;             
                if(aa > 0){ModaIn=1;}
                else {ModaIn=0;}
            }
          } else {tick++;}
         }
         if ( len ) { // 用串列埠顯示從Android手 機傳過來的訊息
          sprintf(str,"%s",cmd);
          
          Serial.print("o&c= ") ;
          Serial.println(str) ;
          if(str=="O"){
            Serial.println("OPEN") ;}
          cmd[0] = '\0';
         }
          len = 0;

      }
    else{
        Serial.println("empty");
        ModaIn=1;}
        
  delay(1000);
  int potpin = ModaIn;
  int i = 0;
  int z = 0;
  //int val = 0;
  //val = analogRead(potpin);
  Serial.println(potpin);
  if(potpin == 0){
    
    z=0;
    if(z==0){
      for(i = 0; i <= 180; i+=1){
        myservo.write(i); // 使用write，傳入角度，從0度轉到180度
        delay(20);
      }
      z=1;
    }
    if(z==1)
    {
      for(i = 180; i <= 0; i-=1){
        myservo.write(i); // 使用write，傳入角度，從0度轉到180度
        delay(20);
      }
    }
    potpin = 1;
  }
  else{
    //for(int i = 0; i <= 180; i+=1){
      myservo.write(i); // 使用write，傳入角度，從0度轉到180度
      delay(20);
    //}

  }
}

