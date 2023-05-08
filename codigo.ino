#include <LiquidCrystal.h>

// Configuración del LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Configuración del sensor de humedad de suelo
const int sensorHumedad = A0;
int lectura = 0;
int humedad = 0;

// Configuración de la alarma
const int alarma = 7;

// Imágenes de la gota de agua
byte charSeco[8] = {
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110
};
byte charMedio[8] = {
  B00100,
 B01010,
 B01010,
 B10001,
 B11111,
 B11111,
 B01110
};
byte charMojado[8] = {
  B00100,
  B01110,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110
};

void setup() {
  // Inicializar el LCD
  lcd.begin(16, 2);
  // Crear los caracteres personalizados
  lcd.createChar(0, (uint8_t*)charSeco);
  lcd.createChar(1, (uint8_t*)charMedio);
  lcd.createChar(2, (uint8_t*)charMojado);
  
  // Inicializar la alarma
  pinMode(alarma, OUTPUT);

  // Configurar la velocidad de comunicación serie
  Serial.begin(9600);
}

void loop() {
 // Leer el valor del sensor de humedad
 lectura = analogRead(sensorHumedad);

 // Convertir el valor leído en un porcentaje de humedad
 humedad = map(lectura, 0, 880, 0, 100);

 // Activar la alarma si el suelo está seco
 if (humedad < 11) {
   digitalWrite(alarma, HIGH);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Suelo seco");
   lcd.setCursor(0, 1);
   lcd.print("Humedad: ");
   lcd.print(humedad);
   lcd.print("% ");
   lcd.write((byte)0); // Mostrar la gota vacía
 } else if (humedad >= 11 && humedad <= 75) {
   digitalWrite(alarma, LOW);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Suelo humedo");
   lcd.setCursor(0, 1);
   lcd.print("Humedad: ");
   lcd.print(humedad);
   lcd.print("% ");
   lcd.write((byte)1); // Mostrar la gota parcialmente llena
 } else {
   digitalWrite(alarma, LOW);
   delay(250);
   digitalWrite(alarma, HIGH);
   delay(250);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Suelo mojado");
   lcd.setCursor(0, 1);
   lcd.print("Humedad: ");
   lcd.print(humedad);
   lcd.print("% ");
   lcd.write((byte)2); // Mostrar la gota llena
 }
 
 // Imprimir los valores leídos en la consola serie
 Serial.print("Lectura ADC = ");
 Serial.print(lectura);
 Serial.print(". Humedad = ");
 Serial.print(humedad);
 Serial.println(" %");

 delay(2000);
}
