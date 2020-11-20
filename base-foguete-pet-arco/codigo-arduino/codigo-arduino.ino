const int ledvermelho = 1; //Led vermelho conectado ao terminal 13 do arduino
const int ledverde = 2; //Led verde conectado ao terminal 9 do arduino
const int acionar = 4; //Botão 1 conectado ao terminal 4 do arduino
const int cancelaracionamento = 3; //Botão 2 conectado ao terminal 3 do arduino
const int motor = 5; //Base do transistor (motor) conectado ao terminal 2 do arduino
void setup() {//Definição se os terminais recebem o sinal (input) ou transmitem um sinal (output)
  pinMode (acionar, INPUT);
  pinMode (motor, OUTPUT);
  pinMode (ledvermelho, OUTPUT);
  pinMode (ledverde, OUTPUT);
  pinMode (cancelaracionamento, INPUT);
}
void loop() {
  if (digitalRead(acionar) == HIGH) { //Se o botão 1 for pressionado
    digitalWrite(ledvermelho, HIGH);
    delay(5000);//Led vermelho aceso por 5s
    digitalWrite (ledverde, HIGH);
    delay(2000);//Led verde aceso por 2s
    if (digitalRead (cancelaracionamento) == HIGH) { //Se o botão 2 estiver pressionado
      digitalWrite (ledvermelho, LOW);//Apaga led vermelho
      digitalWrite (ledverde, LOW);
    }//Apaga led verde
    else { //Caso contrário
      digitalWrite (ledvermelho, LOW);//Led vermelho desligado
      digitalWrite (motor, HIGH);
      delay(200);// Motor trabalha por 0,2s
      digitalWrite (motor, LOW);//Motor desligado
      digitalWrite (ledverde, LOW);
    }//Led verde desligado
  }
}
