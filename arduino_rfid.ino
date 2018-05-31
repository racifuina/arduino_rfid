#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9  //Pin 9 para el reset del RC522
#define SS_PIN    10 //Pin 10 para el SS (SDA) del RC522

MFRC522 mfrc522(SS_PIN, RST_PIN); // Creacion de la instancia del lector MFRC522 
MFRC522::MIFARE_Key key;

int incomingByte = 2;  //Variable para almacenar el comando de acceso.

void setup() {
  pinMode(3, OUTPUT);   //pin LED rojo
  pinMode(5, OUTPUT);   //pin LED verde
  pinMode(6, OUTPUT);   //pin LED azul
  encenderLed(1, 200);  //Encendemos el LED rojo
  encenderLed(2, 200);  //Encendemos el LED verde
  encenderLed(3, 200);  //Encendemos el LED azul
  encenderLed(0, 200);  //Encendemos el LED blanco (RGB completo)
  Serial.begin(9600);   //Iniciamos la comunicación  serial
  SPI.begin();          //Iniciamos el Bus SPI
  mfrc522.PCD_Init();   // Iniciamos  el MFRC522
}

void loop() {
  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) {
    //Seleccionamos una tarjeta
    if (mfrc522.PICC_ReadCardSerial()) {
      //Encendemos el LED blanco para indicar que se leyó la tarjeta.
      encenderLed(0, 200);
      // Enviamos el UID por el puerto Serial
      Serial.print("{\"dec\":\"");
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i], DEC);  //valores Decimales 
      }
      Serial.print("\",\"hex\":\"");
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i], HEX);  //valores Hexadecimales 
      }
      Serial.print("\"}");
      //Finalización del envío de cadena de datos
      Serial.println();
      // Terminamos la lectura de la tarjeta  actual
      mfrc522.PICC_HaltA();
       //Lectura del comando de acceso
      while(incomingByte == 2) {
        if (Serial.available()){
          incomingByte = Serial.read();
          if (incomingByte == '1') {
            //Encendemos el LED verde para indicar acceso correcto.
            encenderLed(2, 1000);
          } else {
             //Encendemos el LED rojo para para indicar que no hay acceso.
            encenderLed(1, 1000);
          }
        }
      }
      incomingByte = 2; //Reset del comando de acceso
    }
  } 
  //Limpieza de Buffer para evitar comandos erroneos a la hora de esperar el comando de acceso
  while(Serial.available()){
     Serial.read();
  }
}

void encenderLed(int color, int duracion){
  switch (color) {
    case 1: //Encender LED rojo
      digitalWrite(3, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    break;
    case 2: //Encender LED verde
      digitalWrite(3, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
    break;
    case 3: //Encender LED azul
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
    break;
    default:  //Encender LED blanco (RGB completo)
      digitalWrite(3, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    break;
  }
  delay(duracion);        //Mantener encendido el LED por la duración ingresada
  digitalWrite(3, LOW);   //Apagar el LED
  digitalWrite(5, LOW);   //Apagar el LED
  digitalWrite(6, LOW);   //Apagar el LED
}

