// declaro variables
byte rele=2;
String contrasena;

boolean cerradura(String clave){ //Funcion booleana
  if (clave == "2147483648"){ // Verifico clave ingresada
    digitalWrite(rele,HIGH); // Si es correcta
    return true;
  }else return false;  // No es correcta
}

void setup() {
  Serial.begin(9600); // Establezco velocidad de puerto serial
  Serial.println("Bienvenido al Ejercicio 1.6 del TP !! ");
  pinMode (rele, OUTPUT); // Preparo pin para salida
  digitalWrite(rele,LOW); // Incializo en 0 el valor del pin
  
}

void loop()
{
  Serial.println("Ingrese Clave de Cerradura:");
  while (!Serial.available() > 0); // Espero disponibilidad puerto serial
  contrasena = Serial.readStringUntil('\n');
  if (not cerradura(contrasena))
     Serial.println("Cerradura Cerrada!!");
  else 
    Serial.println("Cerradura Abierta!!");
}

