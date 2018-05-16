    #include<SoftwareSerial.h>
    #include <Wire.h> 
    #include <SPI.h>
    #include <MFRC522.h>
    #define SS_PIN 10 // RFID-RC522 SDA
    #define RST_PIN 9 // RFID-RC522 RST
    #define relay1 7
    #define relay2 6
    #define switch_sensor 5
    SoftwareSerial ArduinoSerial(3, 2); // RX, TX
    MFRC522 mfrc522(SS_PIN, RST_PIN);  // instance of class  
    long cardUserID[] = { 2521080, 933350, 1210690 ,970490,1217390}; // ID Set Up 
    byte CardCount = 5; 
    boolean Status = false;
    int count = 0;
void setup() {
      Serial.begin(115200);
      ArduinoSerial.begin(4800);
      SPI.begin();
      pinMode(relay1,OUTPUT);
      pinMode(relay2,OUTPUT);  
      pinMode(switch_sensor,INPUT);  
      mfrc522.PCD_Init();   
}
void loop() {  
     input_data(); 
      if ( ! mfrc522.PICC_IsNewCardPresent()) {  
        return;
      }    
      if ( ! mfrc522.PICC_ReadCardSerial()) { 
        return;
      }
     
      
      sent_data();    
      long code=0;    
      for (byte i = 0; i < mfrc522.uid.size; i++) {
         code=((code+mfrc522.uid.uidByte[i])*10);
      }    
      Serial.print(F("Enter Card is:"));
      Serial.println(code);     
      if(CardReader(code) == true) {
        Serial.println(F(" [Correct]"));               
                 digitalWrite(relay1,HIGH);
                 digitalWrite(relay2,LOW);
                      delay(900);
                 digitalWrite(relay1,LOW);
                 digitalWrite(relay2,LOW);
                      delay(4000); 
                 digitalWrite(relay1,LOW);
                 digitalWrite(relay2,HIGH);   
                      delay(908); 
                digitalWrite(relay1,LOW);
                digitalWrite(relay2,LOW);         
      }
      else {
        Serial.println(F(" [Incorrect]"));
      } 
     delay(200); 
    } 
    boolean CardReader(long cardUUID) {
      boolean id = false;   
      for(int i=0; i < CardCount; i++) {
        if(cardUserID[i] == cardUUID) { 
          id = true; 
        }
      }
      return id;  
    }
 int sent_data(){ 
      long code=0;      
      for (byte i = 0; i < mfrc522.uid.size; i++) {// Reader card and show in serial
         code=((code+mfrc522.uid.uidByte[i])*10);
      }     
      Serial.print(F("Enter Card:"));
      Serial.println(code);
      int code_id = code;
      Serial.println(code_id);   
      if (code_id == 31042) {
        ArduinoSerial.print(code_id);
        ArduinoSerial.print("\n");        
        Serial.println("sent 1");
      }
      if (code_id == 30712){
        ArduinoSerial.print(code_id);
        ArduinoSerial.print("\n");
        Serial.println("sent 2");;
      }
      if (code_id == 15846 ){
        ArduinoSerial.print(code_id);
        ArduinoSerial.print("\n");
        Serial.println("sent 3");
      }
       if (code_id == -12550 ){
        ArduinoSerial.print(code_id);
        ArduinoSerial.print("\n");
        Serial.println("sent 4");
      }
      if (code_id == -27794 ){
        ArduinoSerial.print(code_id);
        ArduinoSerial.print("\n");
        Serial.println("sent 5");
      }
       else {
        int code_defuat = 8888;
         ArduinoSerial.print(code_defuat);
         ArduinoSerial.print("\n");
         Serial.println(" Not User in program");
       }
      Serial.println("hello");
  }
  void input_data(){
          while (ArduinoSerial.available() > 0) {
      int val = ArduinoSerial.parseInt();
          if (ArduinoSerial.read() == '\n') {
              Serial.println(val);
              if (val == 10){
                Serial.println("hello arduino");
                   digitalWrite(relay1,HIGH);
                  digitalWrite(relay2,LOW);
                     delay(900);
                  digitalWrite(relay1,LOW);
                  digitalWrite(relay2,LOW);
                     delay(4000); 
                 digitalWrite(relay1,LOW);
                 digitalWrite(relay2,HIGH);         
                    delay(908);
                      digitalWrite(relay1,LOW);
                  digitalWrite(relay2,LOW);
                                      
              }
              
          }
      }
  }


