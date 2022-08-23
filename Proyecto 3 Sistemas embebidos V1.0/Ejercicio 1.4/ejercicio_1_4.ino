// declaro variables
int led=3;
int i;

void setup() {
Serial.begin(9600); // Establezco velocidad de puerto serie en bps
Serial.println("Bienvenido al Ejercicio 4A del TP !! ");
Serial.println();
pinMode(led, OUTPUT);

}

void loop() {
  Serial.println("Por favor, ingrese un numero entero, entre 0 y 255:");  
    
  while (!Serial.available() > 0); // Espero disponibilidad puerto serie
  i = Serial.parseInt();
  Serial.print("El valor introducido es: ");
  Serial.println(i);
  if ((i >= 0) and (i <=255)) {
    analogWrite(led,i);  // Envio valor a puerto PWM, el cual 
                         // en base al valor sera la intensidad del led  
    delay(500);  // Pausa de 1/2 segundo
  } else i = 0; // Si envian valor fuera de rango, dejo en 0
  
}