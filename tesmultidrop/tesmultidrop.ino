/*
  SerialPassthrough sketch

  Some boards, like the Arduino 101, the MKR1000, Zero, or the Micro, have one
  hardware serial port attached to Digital pins 0-1, and a separate USB serial
  port attached to the IDE Serial Monitor. This means that the "serial
  passthrough" which is possible with the Arduino UNO (commonly used to interact
  with devices/shields that require configuration via serial AT commands) will
  not work by default.

  This sketch allows you to emulate the serial passthrough behaviour. Any text
  you type in the IDE Serial monitor will be written out to the serial port on
  Digital pins 0 and 1, and vice-versa.

  On the 101, MKR1000, Zero, and Micro, "Serial" refers to the USB Serial port
  attached to the Serial Monitor, and "Serial1" refers to the hardware serial
  port attached to pins 0 and 1. This sketch will emulate Serial passthrough
  using those two Serial ports on the boards mentioned above, but you can change
  these names to connect any two serial ports on a board that has multiple ports.

  created 23 May 2016
  by Erik Nyquist
*/

void setup() {
  Serial.begin(19200);
  Serial2.begin(19200, SERIAL_8N1, 16, 17);

  pinMode(4, OUTPUT);
  //  pinMode(26, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(4, LOW);
  //  digitalWrite(26, LOW);
  digitalWrite(5, LOW);
}

void loop() {
  if (Serial.available()) {      // If anything comes in Serial (USB),
    char Inchar = (char)Serial.read();
    Serial2.write(Inchar);   // read it and send it out Serial1 (pins 0 & 1)
    Serial.print(Inchar);
  }

  if (Serial2.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    char Inchar = (char)Serial2.read();
    Serial.print(Inchar);   // read it and send it out Serial (USB)
  }
}
