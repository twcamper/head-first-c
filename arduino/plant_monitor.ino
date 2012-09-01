const short LED_PIN    = 13;
const short THRESHHOLD = 550;
const short INTERVAL   = 10000;
const short SERIAL_BAUD_RATE = 9600;

boolean needs_water() {  
  short a = analogRead(A0);
  Serial.print(a);
  Serial.print(":\t");
  if (a < THRESHHOLD)
    return true;
  else
    return false; 
}
void indicate_dry()
{
  digitalWrite(LED_PIN, HIGH);
  Serial.println("Feed Me!"); 
}
void indicate_moist()
{
  digitalWrite(LED_PIN, LOW);
  Serial.println("Thank You, Seymour!"); 
}
void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  if (needs_water())
    indicate_dry();
  else
    indicate_moist();


  delay(INTERVAL);
}
