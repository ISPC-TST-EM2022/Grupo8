#include "IRrecv.h"  // Libreria para Sensor IR

//------------ Establezco parametros de control IR ------
uint16_t RECV_PIN = 4; // Pin control IR
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long int value = 0;
int tecla;
//-------------------------------------------------------

// ---------- Establezo parametros de motores -----------
// Motor Der
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

// Motor Izq
int motor2Pin1 = 32; 
int motor2Pin2 = 33; 
int enable2Pin = 12; 

// Establezco propiedades PWM 
const int freq = 30000;
const int pwmChannel = 1;
const int resolution = 8;
int dutyCycle = 200;
//-----------------------------------------------------


void setup() {
  // Seteamos pines de salida para motores:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  irrecv.enableIRIn(); // Activamos IR
  
  // Funcionalidades PWM
  ledcSetup(pwmChannel, freq, resolution);
  
  // Adjuntamos canal GPIO a ser controlado
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcAttachPin(enable2Pin, pwmChannel);

  Serial.begin(115200);
}


void loop() {
    
    if (irrecv.decode(&results)) { // Recivo valor sensor IR
           
      tecla = (uint32_t) (results.value & 0xFFFFFFFF);
      ledcWrite(pwmChannel, dutyCycle);
      switch (tecla){
        case 16718055 : Serial.println("Tecla 2");
            Serial.println("Avanzar de frente");
            // ledcWrite(pwmChannel, dutyCycle);
            digitalWrite(motor1Pin1, LOW);
            digitalWrite(motor1Pin2, HIGH);
            digitalWrite(motor2Pin1, LOW);
            digitalWrite(motor2Pin2, HIGH);  
            delay(800);
            digitalWrite(motor1Pin1, LOW);
            digitalWrite(motor1Pin2, LOW);
            digitalWrite(motor2Pin1, LOW);
            digitalWrite(motor2Pin2, LOW);
            Serial.println("Detener avanze");
        break;
        case 16726215 : Serial.println("Tecla 5"); // DETENER MOTORES 
            digitalWrite(motor1Pin1, LOW);
            digitalWrite(motor1Pin2, LOW);
            digitalWrite(motor2Pin1, LOW);
            digitalWrite(motor2Pin2, LOW);
        break;
        case 16716015 : Serial.println("Tecla 4"); // GIRAR A LA IZQUIERDA
            digitalWrite(motor2Pin1, LOW);
            digitalWrite(motor2Pin2, HIGH);
            delay(400);
            digitalWrite(motor2Pin1, LOW);
            digitalWrite(motor2Pin2, LOW);
        break;
        case 16734885: Serial.println("Tecla 6"); //GIRAR A DERECHA
            digitalWrite(motor1Pin1, LOW);
            digitalWrite(motor1Pin2, HIGH);
            delay(400);
            digitalWrite(motor1Pin1, LOW);
            digitalWrite(motor1Pin2, LOW);
        break;
        case 16730805 : Serial.println("Tecla 8");  // RETROCEDER
            digitalWrite(motor1Pin1, HIGH);
            digitalWrite(motor1Pin2, LOW);
            digitalWrite(motor2Pin1, HIGH);
            digitalWrite(motor2Pin2, LOW); 
            delay(800);
            digitalWrite(motor1Pin1, LOW);
            digitalWrite(motor1Pin2, LOW);
            digitalWrite(motor2Pin1, LOW);
            digitalWrite(motor2Pin2, LOW);
        break;
      }
      irrecv.resume();  // Recibir valor siguiente
    delay(200);
    }
 
}
