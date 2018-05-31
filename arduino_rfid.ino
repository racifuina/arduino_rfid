#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9     // Configurable, see typical pin layout above
#define SS_PIN    10    // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;

int incomingByte = 2; 

void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  encenderLed(1, 200);
  encenderLed(2, 200);
  encenderLed(3, 200);
  encenderLed(0, 200);
  Serial.begin(9600); 
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card  
}

//void loop() {
//  // Revisamos si hay nuevas tarjetas  presentes
//  if ( mfrc522.PICC_IsNewCardPresent()) {
//    //Seleccionamos una tarjeta
//    if (mfrc522.PICC_ReadCardSerial()) {
//      //Encendemos el LED blanco para indicar que se leyó la tarjeta.
//      encenderLed(0, 200);
//      // Enviamos serialemente su UID
//      Serial.print("{\"dec\":\"");
//      for (byte i = 0; i < mfrc522.uid.size; i++) {
//        Serial.print(mfrc522.uid.uidByte[i], DEC);   
//      }
//      Serial.print("\",\"hex\":\"");
//      for (byte i = 0; i < mfrc522.uid.size; i++) {
//        Serial.print(mfrc522.uid.uidByte[i], HEX);   
//      }
//      Serial.print("\"}");
//      Serial.println();
//      // Terminamos la lectura de la tarjeta  actual
//      mfrc522.PICC_HaltA();
//       
//      while(incomingByte == 2) {
//        if (Serial.available()){
//          incomingByte = Serial.read();
//          if (incomingByte == '1') {
//            //Encendemos LED verde.
//            encenderLed(2, 1000);
//          } else {
//             //Encendemos LED Rojo.
//            encenderLed(1, 1000);
//          }
//        }
//      }
//      incomingByte = 2;
//    }
//  } 
//  //LIMPIEZA DE BUFFER
//  while(Serial.available()){
//     Serial.read();
//  }
//
//}

void loop() {
  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) {
    //Seleccionamos una tarjeta
    if (mfrc522.PICC_ReadCardSerial()) {
      //Encendemos el LED blanco para indicar que se leyó la tarjeta.
      encenderLed(0, 200);
      // Enviamos serialemente su UID
      Serial.print("{\"dec\":\"");
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i], DEC);   
      }
      Serial.print("\",\"hex\":\"");
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i], HEX);   
      }
      Serial.print("\"}");
      Serial.println();
      // Terminamos la lectura de la tarjeta  actual
      mfrc522.PICC_HaltA();
       
      while(incomingByte == 2) {
        if (Serial.available()){
          incomingByte = Serial.read();
          if (incomingByte == '1') {
            //Encendemos LED verde.
            encenderLed(2, 1000);
          } else {
             //Encendemos LED Rojo.
            encenderLed(1, 1000);
          }
        }
      }
      incomingByte = 2;
    }
  } 
  //LIMPIEZA DE BUFFER
  while(Serial.available()){
     Serial.read();
  }

}

void encenderLed(int color, int duracion){
  switch (color) {
    case 1:
      digitalWrite(3, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    break;
    case 2:
      digitalWrite(3, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
    break;
    case 3:
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
    break;
    default:
      digitalWrite(3, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    break;
  }
  delay(duracion);
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

