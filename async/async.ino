// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

// the loop function runs over and over again forever
void loop() 
{
  if(Serial.available()>0)
  {
    char ByteLlegando = Serial.read(); 
    if(ByteLlegando == 'k')
    {
      digitalWrite(13, HIGH);
      Serial.print("Descomponerte,Descomponerte.\nDesentrelazarte el alma.\nDesvestirte hasta el pasado.\nDesvestirte hasta los sueños.\nMorir en tu pecho.\nTransformarte en lagrima.\nDevolverte al cielo.\nDonde perteneces.\nConvertirte en sueño.\nDevorarte el alma."); // wait for a second
      delay(1000);
      Serial.print("k");
      digitalWrite(13, LOW);
    }
  }
}
