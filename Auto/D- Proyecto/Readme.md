## INFORMACIÓN DE CONECTIVIDAD PROVISTA AL PROYECTO:
El vehiculo posee dos metodos principales de control: 
   * Por control remoto directo, usando sensor IR
   * Por control remoto indirecto, via wifi, usando protocolo mqtt.
                                                 
### Datos de coneccion y acceso mqtt:
El broker se encuentra instalado en un vps propio, de acceso público, lo que facilita 
el control de los integrantes del grupo que se encuentran en diferentes provincias, permitiéndoles
realizar pruebas de control y monitoreo del vehículo.

**Broker**: siot.infovd.com.ar
**Puerto** tcp : 1883  
**Usuario:** (oculto)  
**Password:** (oculto)

**Topicos para Publicación:**
auto/adelante  : 2  |  auto/atras: 8  |   auto/derecha : 6

auto/izquierda : 4  |  auto/led1 : 0 1 |  auto/envioth : 200

**Topicos para Suscripción:**

auto/temperatura  |  auto/humedad  |  auto/distanciao  

Se adjunta app, para la instalación en dispositivos android: <a href='https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/iot-mqtt-panel.apk' target='_blank'>iot-mqtt-panel.apk</a>

  La misma es de uso libre, y esta disponible en la tienda de Google.  Permite armar y configurar el dashboard del vehiculo.
  
  Capturas de un dashboard en teléfono móvil:
[![TSTEM.png](https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/panel1.jpeg)[![TSTEM.png](https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/panel1a.jpeg)[![TSTEM.png](https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/panel1b.jpeg)


 

### 📹 Videos del proyecto ...
<a href='https://youtu.be/_-yfnlz7STw' target='_blank'>
<img width='30%' src='https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/semana1.png' alt='Semana 1' />
</a>
<a href='https://youtu.be/GcXVVOA9xXE' target='_blank'>
<img width='30%' src='https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/semana2.png' alt='Semana 2' />
</a>
<a href='' target='_blank'>
<img width='30%' src='https://github.com/ISPC-TST-Electronica-Microcontrolada/Grupo8/blob/main/Auto/D-%20Proyecto/semana3.png' alt='Semana 3' />
</a>
