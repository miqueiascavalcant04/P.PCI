#define LED_1   D1
#define LED_2   D2

void setup()
{
  // Configura pinos como saída
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}

void loop()
{
  // Pisca os LEDs de forma intercalada a cada 1 segundo
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, LOW);
  delay(1000);

  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, HIGH);
  delay(1000);
}