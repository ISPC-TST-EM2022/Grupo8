#include <WiFi.h>  //Libreria para conexion wifi
#include <PubSubClient.h> // Libreria para mqtt

// ------   Establezco parametros para sensor ultrasonico
const int trigPin = 5;
const int echoPin = 18;
#define SOUND_SPEED 0.034 // velocidad sonido en cm/uS
long duration;
float distanceCm;
char bufferd1[5];
//------------------------------------------------------


// ---------- Establezo parametros wifi ---------------
const char* ssid = "tecnica";
const char* password = "tecnica2022";
WiFiClient espClient;
// ----------------------------------------------------

//-------Establezco  Parametros MQTT ------------------
const char *mqtt_server = "siot.infovd.com.ar";
const int mqtt_port = 1883;
const char *mqtt_user = "usuario";
const char *mqtt_pass = "contraseña";
const char* topico1 = "planta/nivela1";
const char* topico2 = "planta/nivela2";
const char* topico3 = "planta/sensor1";
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
  
  Serial.println("");
  for (int i = 0; i < length; i++) {
    incoming += (char)payload[i];
  }
  incoming.trim();

  int orden = String(incoming).toInt();
  
  switch (orden) {
    
       case 0 : Serial.println("Apagar Motor1");
                digitalWrite (23, LOW);
       break;         
       case 1 : Serial.println("Apagar Motor2");
                digitalWrite (23, HIGH);         
       
       break;
       
  }
  
}
//------------------------------------------------------------
//---------------- Funcion para restablecer coneccion MQTT -----
void reconnect() {

  while (!client.connected()) {
    Serial.print("Intentando conexión Mqtt...");
    // Creamos un cliente ID
    String clientId = "esp32_planta1";
    
    // Intentamos conectar
    if (client.connect(clientId.c_str(),mqtt_user,mqtt_pass)) {
      Serial.println("Conectado!");
      // Nos suscribimos a los topicos
       client.subscribe("planta/nivela1");
       client.subscribe("planta/nivela2");
       client.subscribe("planta/sensor1");

    } else {
      Serial.print("falló :( con error -> ");
      Serial.print(client.state());
      Serial.println(" Intentamos de nuevo en 5 segundos");

      delay(5000);
    }
  }
}
//--------------------------------------------------------------


void setup() {
  setup_wifi();
  pinMode(trigPin, OUTPUT); // Seteo pin Trigger Sensor ultrasonico
  pinMode(echoPin, INPUT); // Seteo pin Echo Sensor ultrasonico
  pinMode(23, OUTPUT);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  Serial.begin(115200);
}

void loop() {
    
    if (!client.connected()) {
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
   
       }
      
    // ------------------------------------------------------------------- 
      
    delay(100);
    
    
}
