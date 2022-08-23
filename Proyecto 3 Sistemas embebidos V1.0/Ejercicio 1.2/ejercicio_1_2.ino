// Declaro variables
String nombre;
String apellido;
String dni;
String celular;

void setup() {
Serial.begin(9600); // Establezco velocidad de puerto serie en bps
Serial.println("Bienvenido al Ejercicio 2A del TP !! ");
Serial.println("Por favor, luego de ingresar el dato solicitado, presione la tecla ENTER");
Serial.println();
}
void loop() {

// ------ Bloque de Carga de Datos:
Serial.println("Ingrese Nombre: ");
while (!Serial.available() > 0); // Verifico disponibilidad
nombre = Serial.readStringUntil('\n'); // Leer cadena ingresada hasta el salto de linea (tecla enter pulsada)

Serial.println("Ingrese Apellido: ");
while (!Serial.available() > 0);
apellido = Serial.readStringUntil('\n');

Serial.println("Ingrese DNI(sin puntos): ");
while (!Serial.available() > 0);
dni = Serial.readStringUntil('\n');

Serial.println("Ingrese Nro. Celular: ");
while (!Serial.available() > 0);
celular = Serial.readStringUntil('\n');
// -----------------------------------

// ----- Bloque de informacion de datos:
Serial.println("------------------------------");
Serial.println("Los datos ingresados son: ");
Serial.println("Nombre y apellido: " + nombre + " " + apellido);
Serial.println("Dni Nro:           " + dni);
Serial.println("Celular Nro:       " + celular);
Serial.println("------------------------------");
// ------
}