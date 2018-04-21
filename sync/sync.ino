// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}
//char msg[]="00101000001100010010100100110010";
char msg[] = "Ama tu ritmo y ritma tus acciones\nbajo su ley, asi como tus versos;\neres un universo de universos\ny tu alma una fuente de canciones.\nLa celeste unidad que presupones\nhara brotar en ti mundos diversos,\ny al resonar tus numeros dispersos\npitagoriza en tus constelaciones.\n";
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
