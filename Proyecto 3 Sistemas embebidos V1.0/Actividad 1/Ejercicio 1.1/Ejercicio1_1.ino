int num1,num2; // Declaro variables

void setup() {
Serial.begin(9600); // Establezco velocidad de puerto serie en bps
Serial.println("Bienvenido al Ejercicio 1A del TP !! ");
Serial.println();
}
void loop() {

Serial.println("Ingrese 1er nro:");
while (!Serial.available() > 0); // Verifico disponibilidad
num1 = Serial.parseInt(); // Asigno numero entero a variable

Serial.println("Ingrese 2do nro:");
while (!Serial.available() > 0); // Verifico disponibilidad
num2 = Serial.parseInt(); // Asigno numero entero a variable

// ----- Bloque de informacion de datos:
Serial.print("Los numeros ingresados son: ");
Serial.print(num1);
Serial.print(" y ");
Serial.println(num2);
Serial.print("La suma de los nros es: ");
Serial.println(num1+num2);
// ------
}