#include <ArduinoJson.h>

long int t0 = 0;
long int t1 = 0;
long int contador = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  t0= millis();

}

void loop() {
  // put your main code here, to run repeatedly:
  t1 = millis();
  if(t1>(t0+1000)){
    t0 = millis();
    contador++;
    //ocurrio 1 segundo
    int valorADC = analogRead(A0);
    Serial.print("{\"adc0\":\"");
    Serial.print(valorADC);
    Serial.print("\"}");
    }

}
