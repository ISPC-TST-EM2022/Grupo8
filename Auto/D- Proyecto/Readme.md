## INFORMACIÓN DE CONECTIVIDAD PROVISTA AL PROYECTO:
El vehiculo posee dos metodos principales de control: 
   * Por control remoto directo, usando sensor IR
   * Por control remoto indirecto, via WIFI, usando protocolo mqtt.

### Control remoto Infrarojo:
Se utilizó un sensor Vs1838B, el cual recibe y decodifica al transmisor IR.
Se programaron las funcionalidades de control de motores, encendido de Led y envio de info de temperatura y humedad desde el DHT22.

### Datos de coneccion WIFI y acceso mqtt:
Para esta funcionalidad, se utilizó la placa wifi que posee el esp32 y se instaló un broker mqtt en VPS propio, con acceso público, lo que facilita 
el control de los integrantes del grupo que se encuentran en diferentes provincias, permitiéndoles realizar pruebas de control y monitoreo del vehículo.

**Broker**: siot.infovd.com.ar
**Puerto** tcp : 1883  
**Usuario:** (oculto)  
**Password:** (oculto)

**Topicos para Publicación:**
auto/adelante  : 2  |  auto/atras: 8  |   auto/derecha : 6

auto/izquierda : 4  |  auto/led1 : 0 1 |  auto/envioth : 200

**Topicos para Suscripción:**

auto/temperatura  |  auto/humedad  |  auto/distanciao  

Se utilizó una app genérica de uso libre disponible en Google Play. Permite armar y configurar el dashboard del vehiculo.
Se adjunta app, para la instalación en dispositivos android: <a href='https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/iot-mqtt-panel.apk' target='_blank'>iot-mqtt-panel.apk</a>
  
  Capturas de un dashboard en teléfono móvil:
  
![image](https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/panel1.jpeg) ![image](https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/panel1a.jpeg)

Para el broker se instaló en el vps: Debian 11 y la version gratuita de EMQX, el cual es un broker de altas prestaciones y uso profesional. 
Capturas del broker:
![image](https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/login_broker.jpg)
![image](https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/dashboard_broker.jpg)
![image](https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/conecciones_broker.jpg)

 ### 📹 Videos del proyecto ...
<a href='https://youtu.be/_-yfnlz7STw' target='_blank'>
<img width='30%' src='https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/presentacion.jpg' alt='Semana 1' />
</a>
<a href='https://youtu.be/GcXVVOA9xXE' target='_blank'>
<img width='30%' src='https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/semana%202.jpg' alt='Semana 2' />
</a>
<a href='' target='_blank'>
<img width='30%' src='https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/meetG8.jpg' alt='Meet' />
</a>
<a href='https://youtu.be/HIrCWpLWWqA' target='_blank'>
<img width='30%' src='https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/semana%203.jpg' alt='Semana 3' />
</a>
