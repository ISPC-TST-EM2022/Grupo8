// Declaro variables
float reales=1, suma=0;
int n=0;

void setup() {
   Serial.begin(9600); // Establezco velocidad de puerto serie en bps
   Serial.println("Bienvenido al Ejercicio 3A del TP !! ");
   Serial.println();
   Serial.println("Por Favor Ingrese un nro:");
}
void loop() {

// ------ Bloque de Carga de Datos:

if (Serial.available() >0)
  {
    if (reales != 0)
     {
       Serial.println("Ingrese un numero, para finalizar ingrese 2 veces seguidas 0:");
       reales = Serial.parseFloat();
       Serial.println(reales);
       n++;
       suma = suma + reales;
      } else {
     // -----------------------------------
     // ----- Bloque de informacion de datos:
         Serial.println("-----------------------------------");
         Serial.print("La cantidad de valores ingresados es: ");
         Serial.println(n-1);
         Serial.print("La suma de los valores ingresados es: ");
         Serial.println(suma);
         Serial.print("La media de los valores ingresados es: ");
         Serial.println(suma/(n-1));
         while (!Serial.available() > 0);
         reales = Serial.parseFloat();
         Serial.println("-----------------------------------");
     // ------------------------------------
      }

    }
}