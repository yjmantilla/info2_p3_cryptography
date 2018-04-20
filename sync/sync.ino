// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

char msg[] = "que es lo que es vladimir?";
// the loop function runs over and over again forever
void loop() 
{
  if(Serial.available()>0)
  {
    char ByteLlegando = Serial.read(); 
    if(ByteLlegando == '{')
    {
      digitalWrite(13, HIGH);
      Serial.print(msg); // wait for a second
      delay(1000);
      //Serial.print("}");
      digitalWrite(13, LOW);
    }
  }
}
