// declaro variables
int leds;

void setup() {
  Serial.begin(9600); // Establezco velocidad de puerto serie en bps
  Serial.println("Bienvenido al Ejercicio 1.5 del TP !! ");
  for ( leds =2; leds <10;leds++){ // 
     pinMode (leds, OUTPUT); // declaro pines de salida (2 a 9)
     digitalWrite (leds, LOW); // inicializo en 0 los pines  
  }
   
}

void loop() {

  for ( leds =2; leds <10; leds++){ // inicio secuencia ascendente
   Serial.println(leds); // imprimo el pin correspondiente 
   digitalWrite (leds, HIGH); // enciendo led
   delay (500);
   Serial. print("    PIN = "); 
   digitalWrite (leds, LOW); // apago led
   delay (500);
   Serial. print(" + "); 
  }
}