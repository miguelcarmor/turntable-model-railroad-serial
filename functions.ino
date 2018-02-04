void calibrate() {
  stepper.moveTo(5000);
  stepper.run();

  sensorStatus = digitalRead(sensorPin);
  if (sensorStatus == LOW) {
    digitalWrite(ledPin, HIGH);
    stepper.setCurrentPosition(0);
    Serial.print("Sensor found and position reset to: ");
    Serial.println(stepper.currentPosition());
    initialStatus = 1;
    Serial.print("Estado inicial: ");
    Serial.println(initialStatus);
    Serial.print("Posição inicial: ");
    Serial.println(position0Status);
  }
}

void releaseCoil() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

}

