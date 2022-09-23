#include "Arduino.h"
#include "IRrecv.h"  // Libreria para Sensor IR
#include <WiFi.h>  //Libreria para conexion wifi
#include <PubSubClient.h> // Libreria para mqtt
#include <DHT.h> // Libreria sensor DHT22

// ---- Parametros DHT22 ------------------
#define D5 17 //GPIO17 - VSPI SS
const byte  Obj_DHT22 = D5; //Pin digital 17 para el ht22
#define DHTPIN Obj_DHT22     // Pin conectado a DHT22
#define DHTTYPE DHT22   // Defino sensor DHT22
DHT Obj_DHT(DHTPIN, DHTTYPE);
// ----------------------------------------

//------------ Establezco parametros de control IR ------
uint16_t RECV_PIN = 4; // Pin control IR
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long int value = 0;
int tecla;
//-------------------------------------------------------

// ------   Establezco parametros para sensor ultrasonico
const int trigPin = 5;
const int echoPin = 18;
#define SOUND_SPEED 0.034 // velocidad sonido en cm/uS
long duration;
float distanceCm;
char bufferd1[5];
//------------------------------------------------------

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

// ---------- Establezo parametros wifi ---------------
const char* ssid = "tecnica";
const char* password = "tecnica2018";
WiFiClient espClient;
// ----------------------------------------------------

//-------Establezco  Parametros MQTT ------------------
const char *mqtt_server = "siot.infovd.com.ar";
const int mqtt_port = 1883;
const char *mqtt_user = "esp32_pedro";
const char *mqtt_pass = "1876987";
const char* topico1 = "auto/temperatura";
const char* topico2 = "auto/humedad";
const char* topico3 = "auto/distanciao";
PubSubClient client(espClient);
//-----------------------------------------------------

long lastMsg = 0;
char msg[25];
String mg1="";

void setup_wifi(){  // Funcion para conectarnos al WIFI --------
  delay(10);
  // Nos conectamos a nuestra red Wifi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado a red WiFi!");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}
// -----------------------------------------------------------
//-------------- Funcion callback para mqtt----------------
void callback(char* topic, byte* payload, unsigned int length){
  String incoming = "";
  for (int i = 0; i < length; i++) {
    incoming += (char)payload[i];
  }
  incoming.trim();
  int orden = String(incoming).toInt();
  ledcWrite(pwmChannel, dutyCycle);
  switch (orden) {    // 
       case 2 : Serial.println("Adelanteeeeeeeee"); // Motores hacia adelante
                digitalWrite(motor1Pin1, LOW);
                digitalWrite(motor1Pin2, HIGH);
                digitalWrite(motor2Pin1, LOW);
                digitalWrite(motor2Pin2, HIGH);  
                delay(800);
                digitalWrite(motor1Pin1, LOW);
                digitalWrite(motor1Pin2, LOW);
                digitalWrite(motor2Pin1, LOW);
                digitalWrite(motor2Pin2, LOW);
       break;  
       case 8 : Serial.println("Atras");  // Motores hacia atras
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
       case 6 : Serial.println("Derecha");  // Girar a derecha
                digitalWrite(motor1Pin1, LOW);
                digitalWrite(motor1Pin2, HIGH);
                delay(400);
                digitalWrite(motor1Pin1, LOW);
                digitalWrite(motor1Pin2, LOW);
       break;
       case 4 : Serial.println("Izquierda"); // Girar a izquierda
                digitalWrite(motor2Pin1, LOW);
                digitalWrite(motor2Pin2, HIGH);
                delay(400);
                digitalWrite(motor2Pin1, LOW);
                digitalWrite(motor2Pin2, LOW);
       break;
       case 0 : Serial.println("Apagar Led1"); / Apago LED1
                digitalWrite (23, LOW);
       break;         
       case 1 : Serial.println("Encender Led1"); Enciendo LED1
                digitalWrite (23, HIGH);         
       break;
       case 200: humtemp(); // envio datos humedad y temperatura
       break;      
  }
  
}
//------------------------------------------------------------
//---------------- Funcion para restablecer coneccion MQTT -----
void reconnect() {

  while (!client.connected()) {
    Serial.print("Intentando conexión Mqtt...");
    // Creamos un cliente ID
    String clientId = "esp32_Auto_G8";
    
    // Intentamos conectar
    if (client.connect(clientId.c_str(),mqtt_user,mqtt_pass)) {
      Serial.println("Conectado!");
      // Nos suscribimos a los topicos
       client.subscribe("auto/adelante");
       client.subscribe("auto/atras");
       client.subscribe("auto/derecha");
       client.subscribe("auto/izquierda");
       client.subscribe("auto/envioth"); // topico para switch de envio temperatura y humedad
       client.subscribe("auto/led1");
     
    } else {
      Serial.print("falló :( con error -> ");
      Serial.print(client.state());
      Serial.println(" Intentamos de nuevo en 5 segundos");

      delay(5000);
    }
  }
}
//--------------------------------------------------------------

// Funcion para medir humedad y temperatura -----------------
void humtemp(){
  float h = Obj_DHT.readHumidity(); //Lee la humedad
    float t = Obj_DHT.readTemperature();//Lee la temperatura en grados centigrados (Valor por defecto)
    char buffert1[10];
    char buffert2[10];
    dtostrf(t,0, 2, buffert1); // Convierte a *char para poder enviar por mqtt
    dtostrf(h,0, 2, buffert2);
    // verifica si alguna lectura ha fallado
  //  if (isnan(h) || isnan(t)) {
  //    Serial.println("Existe un error en la lectura del sensor DHT22!");
  //    return;
  //  }
    
    Serial.print("Humedad: ");Serial.print(h);Serial.println(" %");
    Serial.print("Temperatura: ");Serial.print(t);Serial.println(" *C");
    client.publish(topico1,buffert1); / Publica en topicos
    client.publish(topico2,buffert2);
}

void setup() {
  setup_wifi(); // Inicializamos WIFI
  pinMode(trigPin, OUTPUT); // Seteo pin Trigger Sensor ultrasonico
  pinMode(echoPin, INPUT); // Seteo pin Echo Sensor ultrasonico
  pinMode(23, OUTPUT); // Seteo pin 
  client.setServer(mqtt_server, mqtt_port); // Conectamos a broker
  client.setCallback(callback); // Dejamos en escucha las subscripciones
  
  // Seteamos pines de salida para motores:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  irrecv.enableIRIn(); // Activamos IR

  Obj_DHT.begin(); // Iniciamos sensor DHT22
  Serial.println("Ingresando a la lectura del sensor Obj_DHT22...");
  
  // Funcionalidades PWM para motores
  ledcSetup(pwmChannel, freq, resolution);
  
  // Adjuntamos canal GPIO a ser controlado en motores
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcAttachPin(enable2Pin, pwmChannel);

  Serial.begin(115200); // Seteamos velocidad puerto serial
}

void loop() {
    
    if (!client.connected()) { // si se corta conexion mqtt
       reconnect();
    }
    client.loop();
   
    // Activo y envio mediciones de sensor ultrasonico-------------------
     
    digitalWrite(trigPin, LOW); // inicializo en 0 el trigger
    delayMicroseconds(2);
    
    digitalWrite(trigPin, HIGH); // Seteo en 1 el estado, por 10 microsegundos
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH); // Lee el echo Pin, devuelve el tiempo de viaje de la onda de sonido en microsegundos
  
    distanceCm = duration * SOUND_SPEED/2; // Calculo la distancia
    
    dtostrf(distanceCm,0, 2, bufferd1);
    if (distanceCm > 9 && distanceCm <= 100) { // Defino 9 cm como rango minimo y 100 cm como rango maximo de alcanze
       Serial.print("Distance (cm): ");
       Serial.println(distanceCm);
       
       client.publish(topico3,bufferd1); // Publico distancia a topico
       delay(400);   
     } else { 
          Serial.println("Fuera de rango ...");
          // client.publish(topico3,"101");
         // delay(1000);
       }
      
    // Bloque de control sensor IR  ---------------------------------------------- 
    if (irrecv.decode(&results)) { // Recivo valor sensor IR
           
      tecla = (uint32_t) (results.value & 0xFFFFFFFF);
      // Serial.println(tecla);
      ledcWrite(pwmChannel, dutyCycle);
      switch (tecla){
        case 16738455 : Serial.println("Tecla 0");
               Serial.println("Encender Led1");
               digitalWrite (23, !digitalRead(23));
        break;

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
        default: humtemp(); // Si pulsamos otro boton en control remoto, envia data de Temp. y Humedad
      }
      irrecv.resume();  // Recibir valor siguiente
    delay(100);
    }
    
}