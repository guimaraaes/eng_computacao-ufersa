#define motor 3 //Base do transistor (motor) 
#define solenoide 11 //Base do transistor (solenoide) 
#define acionarmotor 7 //Botão de acionar o motor
#define acionarsolenoide 12 //Botão de acionamento do solenoide
#define cancelaracionamento 13 //Botão de cancelar acionamento do motor
int contsolenoide = 0; //Contator de vazão para solenoide

void setup() {
  pinMode (motor, OUTPUT);
  pinMode (solenoide, OUTPUT);
  pinMode (acionarsolenoide, INPUT);
  pinMode (acionarmotor, INPUT);
  pinMode (cancelaracionamento, INPUT);
}

void loop() {
  if (digitalRead(acionarsolenoide) == HIGH) { //Se o botão for pressionado
    if (digitalRead (cancelaracionamento) == LOW) { //Se o botão não estiver pressionado
      delay(3000);
      contsolenoide = contsolenoide + 1;
      switch (contsolenoide) {
        case '1' :
          digitalWrite (solenoide, HIGH);
          delay(20000); // Solenoide abre por 20s
          digitalWrite (solenoide, LOW);
          break;
        case '2' :
          digitalWrite (solenoide, HIGH);
          delay(32000); // Solenoide abre por 32s
          digitalWrite (solenoide, LOW);
          break;
        case '3' :
          digitalWrite (solenoide, HIGH);
          delay(400000); // Solenoide abre por 40s
          digitalWrite (solenoide, LOW);
          break;
      }
    }
  }
  if (digitalRead(acionarmotor) == HIGH) { //Se o botão for pressionado
    if (digitalRead (cancelaracionamento) == LOW) { //Se o botão não estiver pressionado
      delay(3000);
      digitalWrite (motor, HIGH);
      delay(200); // Motor trabalha por 0,2s
      digitalWrite (motor, LOW);
    }
  }
}
