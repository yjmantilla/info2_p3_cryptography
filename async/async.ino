// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

//char msg[]="00101000001100010010100100110010-";
char msg[] = "Ama tu ritmo y ritma tus acciones\nbajo su ley, asi como tus versos;\neres un universo de universos\ny tu alma una fuente de canciones.\nLa celeste unidad que presupones\nhara brotar en ti mundos diversos,\ny al resonar tus numeros dispersos\npitagoriza en tus constelaciones.\n-";
// the loop function runs over and over again forever
void loop() 
{
  Serial.print("{");
  delay(100);
  int i = 0;
  while(msg[i]!='-')
    {
      Serial.print(msg[i]);
      i++;
      delay(100);
    }
  Serial.print("}");
  delay(100);
}
