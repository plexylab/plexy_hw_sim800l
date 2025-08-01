/*
  ================================================================
  AVISO DE RESPONSABILIDAD / DISCLAIMER

  [ESPAÑOL]
  Este código es un ejemplo básico del uso del módulo SIM800L con Arduino Uno
  para enviar mensajes SMS. Se proporciona únicamente con fines educativos y
  de prueba. No se garantiza su funcionamiento en todas las configuraciones ni
  su idoneidad para aplicaciones críticas o comerciales.

  El uso, modificación e implementación de este código es responsabilidad total
  del usuario. El autor no se hace responsable por daños al hardware, pérdida de
  datos, costos asociados al uso de la red GSM, ni cualquier otro efecto derivado
  del uso de este software.

  Utilícelo bajo su propio riesgo.

  [ENGLISH]
  This code is a basic example of using the SIM800L module with Arduino Uno
  to send SMS messages. It is provided for educational and testing purposes only.
  Its operation is not guaranteed in all configurations, nor is it suitable for
  critical or commercial applications.

  Use, modification, and implementation of this code are entirely the user's
  responsibility. The author assumes no liability for hardware damage, data loss,
  GSM network usage charges, or any other consequences arising from the use of
  this software.

  Use at your own risk.
  ================================================================
*/

#include <SoftwareSerial.h>

// RX del SIM800L al pin 10, TX del SIM800L al pin 11
SoftwareSerial sim800l(10, 11);

void setup() {
  Serial.begin(9600);        // Para depuración desde el monitor serial
  sim800l.begin(9600);       // Velocidad por defecto del SIM800L

  delay(1000);
  Serial.println("Iniciando SIM800L...");

  // Comandos de inicialización
  sim800l.println("AT");
  delay(1000);

  sim800l.println("AT+CMGF=1"); // Configura modo texto
  delay(1000);

  sim800l.println("AT+CMGS=\"+593XXXXXXXXX\""); // Reemplaza por número real
  delay(1000);

  sim800l.print("Hola mundo"); // Mensaje SMS

  // Enviar Ctrl+Z para finalizar el mensaje
  sim800l.write(26); // Código ASCII de Ctrl+Z
  delay(1000);

  Serial.println("Mensaje enviado.");
}

void loop() {
  updateSerial(); // Reenvía datos entre el SIM800L y el monitor serial
}

// Función para reenviar datos entre Serial y SIM800L
void updateSerial() {
  delay(500); // Pequeña pausa para estabilidad

  while (Serial.available()) {
    sim800l.write(Serial.read()); // Datos del monitor serial al SIM800L
  }

  while (sim800l.available()) {
    Serial.write(sim800l.read()); // Datos del SIM800L al monitor serial
  }
}
