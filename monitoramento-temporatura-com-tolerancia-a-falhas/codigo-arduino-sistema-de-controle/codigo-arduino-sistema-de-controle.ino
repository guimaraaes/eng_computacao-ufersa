//----------------------------------------------------
//---------------SISTEMA TOLERANTE À FALHAS - HARDWARE 
//----------------------------------------------------
//---------------DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress ds18b20;

//---------------KY-013
#include <math.h>
#define ky013 A5

double funcKY013(int analogValor) {
  double Temp;
  Temp = log(10000.0 * ((1024.0 / analogValor - 1)));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;
  return Temp;
}

//--------------LM35
#define lm35i A0


//-------------CHAVES
#define chaveky013 9
#define chaveLM35i 10
#define chaveDS18B20 12

void setup(void) {
  Serial.begin(9600);
  digitalWrite(chaveDS18B20, HIGH);
  delay(5000);
  sensors.begin();
  if (!sensors.getAddress(ds18b20, 0)) {
    Serial.println("Sensores DS18B20 nao encontrados !");
  }
}


double tempLM35i, tempDS18B20, tempKY013;
void lerLM35i() {
  digitalWrite(chaveLM35i, HIGH);
  tempLM35i = (float(analogRead(lm35i)) * 5 / (1023)) / 0.01;
  digitalWrite(chaveLM35i, LOW);
}


void lerDS18B20() {
  digitalWrite(chaveDS18B20, HIGH);
  sensors.requestTemperatures();
  tempDS18B20 = sensors.getTempC(ds18b20);
  digitalWrite(chaveDS18B20, LOW);
}

void lerKY013() {
  digitalWrite(chaveky013, HIGH);
  tempKY013 =  funcKY013(analogRead(ky013));
  digitalWrite(chaveky013, LOW);

}

int comparar(double sensor1, double sensor2, double referencia) {
  Serial.println("Fora do limite");
  int desativar = 0;
  if (abs(sensor1 - referencia) > abs(sensor2 - referencia)) {
    desativar = 1;
  } else {
    desativar = 2;
  }
  return desativar;
}

int long tempoUltimaAmostra, tempoAtual;

void parearKY013LMi() {
  Serial.println("NOVO PAREAMENTO parearKY013LMi() ");
  int k;
  k = 1;
  while (k == 1) {
    lerLM35i();
    Serial.print("lmi ");
    Serial.println(tempLM35i);
    tempoAtual = millis();
    if (tempoAtual - tempoUltimaAmostra >= 5000) {
      lerKY013();
      Serial.print("ky ");
      Serial.println(tempKY013);
      if ((tempKY013 > tempLM35i + tempLM35i * 0.15) || (tempKY013 < tempLM35i - tempLM35i * 0.15)) {
        Serial.print("exit(1) - sensores com falha ");
        while (k == 1)
          digitalWrite(13, HIGH);
      }
      tempoUltimaAmostra = millis();
    }
  }
}


void parearKY013DS18B20() {
  Serial.println("NOVO PAREAMENTO parearKY013DS18B20() ");
  int k;
  k = 1;
  while (k == 1) {
    lerKY013();
    Serial.print("ky ");
    Serial.println(tempKY013);
    tempoAtual = millis();
    if (tempoAtual - tempoUltimaAmostra >= 5000) {
      lerDS18B20();
      Serial.print("ds ");
      Serial.println(tempDS18B20);
      if ((tempKY013 > tempDS18B20 + tempDS18B20 * 0.15) || (tempKY013 < tempDS18B20 - tempDS18B20 * 0.15)) {
        Serial.print("exit(1) - sensores com falha ");
        while (k == 1)
          digitalWrite(13, HIGH);
      }
      tempoUltimaAmostra = millis();
    }
  }
}



void loop() {
  lerLM35i();
  Serial.print("lmi ");
  Serial.println(tempLM35i);
  tempoAtual = millis();
  if (tempoAtual - tempoUltimaAmostra >= 5000) {
    lerDS18B20();
    Serial.print("db ");
    Serial.println(tempDS18B20);
    if ((tempDS18B20 > tempLM35i + tempLM35i * 0.15) || (tempDS18B20 < tempLM35i - tempLM35i * 0.15)) {
      lerKY013();
      Serial.print("ky ");
      Serial.println(tempKY013);
      int compLMiKY = comparar (tempLM35i, tempDS18B20, tempKY013);
      if (compLMiKY == 2) {
        parearKY013LMi();
      } else {
        parearKY013DS18B20();
      }
    }
    tempoUltimaAmostra = millis();
  }
}
