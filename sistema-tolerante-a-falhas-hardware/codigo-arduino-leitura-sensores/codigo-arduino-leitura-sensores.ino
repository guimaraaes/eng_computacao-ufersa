#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress ds18b20;

#include <math.h>
#define ky013 A5


double funcKY013(int analogValor) {
  double Temp;
  Temp = log(10000.0 * ((1024.0 / analogValor - 1)));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;
  return Temp;
}

#define lm35i A0
#define lm35ii A1
void setup() {
  Serial.begin(9600);
  sensors.begin();

  if (!sensors.getAddress(ds18b20, 0))
    Serial.println("Sensores DS18B20 nao encontrados !");
}

void loop() {
  double tempLM35i, tempLM35ii, tempDS18B20, tempKY013;

  tempLM35i = (float(analogRead(lm35i)) * 5 / (1023)) / 0.01;
  Serial.println("lm");
  Serial.println(tempLM35i);


  sensors.requestTemperatures();
  tempDS18B20 = sensors.getTempC(ds18b20);
  Serial.println("ds");
  Serial.println(tempDS18B20);

  tempKY013 =  funcKY013(analogRead(ky013));
  Serial.println("ky");
  Serial.println(tempKY013);

  delay (2000);
}
