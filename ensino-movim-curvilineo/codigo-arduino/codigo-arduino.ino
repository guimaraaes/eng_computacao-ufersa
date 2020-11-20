////////////////////////
/////////////BIBLIOTECAS
////////////////////////
//LiquidCrystal
#include <LiquidCrystal.h>


////////////////////////
///////////////VARIÁVEIS
////////////////////////
//PINOS DIGITAIS
#define encoderA 2
#define PINsubtrair 7
#define PINenableNEMA 8
#define PINpulseNEMA 9
#define PINdirectionNEMA 10
LiquidCrystal lcd(12, 11, 5, 4, 3, 1);
#define encoderB 13

//PINOS ANALÓGICOS
#define serieBotoes A0
#define LDC A1
#define serieBotoes2 A2

#define serieLDR1 A5

//BOTÕES
int PINdistensaoLeft;
int PINresetLCD;//restaurar
int PINpassarLCD;
int PINmostrarNovamente;
int PINdistensaoOUangulo6OU18;
int PINdistensaoOUangulo1_2OU9;
int PINreed;
int PINpouso;
int PINqueda1;
int PINqueda2;
int PINqueda3;
int PINqueda4;
int PINqueda5;
int PINqueda6;
int PINqueda7;
int PINqueda8;
int PINqueda9;

//VARIÁVEIS AUXILIARES
int i;

//
enum {INICIAR, DISTENDER, INCLINAR} estado;

//VARIÁVEIS DE TEMPO
unsigned long tempoSaida;
unsigned long tempoEstagio;
unsigned long tempoPouso;

//SOMATÓRIOS
float distensaoResultante;
float anguloResultante;
float distensaoResultante2;
float anguloResultante2;

//ENCODER
int angulo = 0;
int encoderEstadoI;
int encoderEstadoF;

////////////////////////
/////////////////FUNÇÕES
////////////////////////
//FUNÇÃO PARA DETERMINAR O BOTÃO
void determinarBotao()
{
  if (analogRead(serieBotoes) > 135 && analogRead(serieBotoes) < 150)
  {
    PINpassarLCD = 1;
    delay(1000);
  } else {
    PINpassarLCD = 0;
  }

  if (analogRead(serieBotoes) > 150 && analogRead(serieBotoes) < 190)
  {
    PINresetLCD = 1;
    delay(1000);
  } else {
    PINresetLCD = 0;
  }

  if (analogRead(serieBotoes) > 190 && analogRead(serieBotoes) < 210)
  {
    PINdistensaoOUangulo6OU18 = 1;
    delay(1000);
  } else {
    PINdistensaoOUangulo6OU18 = 0;
  }


  if (analogRead(serieBotoes) > 210 && analogRead(serieBotoes) < 260)
  {
    PINdistensaoOUangulo1_2OU9 = 1;
    delay(1000);
  } else {
    PINdistensaoOUangulo1_2OU9 = 0;
  }

  if (analogRead(serieBotoes) > 260 && analogRead(serieBotoes) < 370)
  {
    PINdistensaoLeft = 1;
    delay(1000);
  } else {
    PINdistensaoLeft = 0;
  }

  if (analogRead(serieBotoes) > 370 && analogRead(serieBotoes) < 550)
  {
    PINreed = 1;
    delay(1000);
  } else {
    PINreed = 0;
  }

  if (analogRead(serieBotoes) > 550 && analogRead(serieBotoes) < 1030)
  {
    PINpouso = 1;
    delay(1000);
  } else {
    PINpouso = 0;
  }

}

//MOSTRA DISTENSÃO OU ANGULO RESULTANTE
void mostrarDistensaoOUAngulo(char *mensagem, float DAresult)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(mensagem);
  lcd.setCursor(0, 1);
  lcd.print(DAresult);
  delay (1000);
}


//AJUSTE DE DISTENSÃO OU ÂNGULO
void ajustaDistensaoEAngulo(float incDistensao, float incAngulo)
{
  if (estado == DISTENDER)
  {
    distensaoResultante = distensaoResultante + incDistensao;
    mostrarDistensaoOUAngulo("DISTENSAO", distensaoResultante);
  } else if (estado == INCLINAR)
  {
    anguloResultante = anguloResultante + incAngulo;
    mostrarDistensaoOUAngulo("ANGULACAO", anguloResultante);
  }
}



//INCREMENTO ALTO OU BAIXO NA DISTENSÃO OU ANGULAÇÃO
void tratarBotao(int fator)
{
  determinarBotao();
  if (PINdistensaoOUangulo6OU18 == 1)
  {
    ajustaDistensaoEAngulo(fator * 6, fator * 18);
  }
  else if (PINdistensaoOUangulo1_2OU9 == 1)
  {
    ajustaDistensaoEAngulo(fator * 1.2, fator * 9);
  } else
  {
    ajustaDistensaoEAngulo(0, 0);
  }
}

//MOSTRAR MENSAGEM DE ERRO
void mostraErro(char *mensagem)
{
  lcd.clear();
  lcd.print(mensagem);
  lcd.setCursor(0, 1);
  delay (3000);
}

//FUNÇÃO PARA A DISTENSÃO OU ANGULO
void distensaoOUangulo()
{
  while (distensaoResultante >= 0 && anguloResultante >= 0 && PINpassarLCD == 0 && PINresetLCD == 0)
  {
    tratarBotao(1);
    while ((digitalRead(PINsubtrair) == HIGH) && (distensaoResultante >= 0))
    {
      tratarBotao(-1);
    }
  }

  if (distensaoResultante < 0)
  {
    mostraErro("ERRO: distensao < 0");
    distensaoResultante = 0;
  }
  if (anguloResultante < 0)
  {
    mostraErro("ERRO: angulo < 0");
    anguloResultante = 0;
  }
  if (distensaoResultante > 21.2)
  {
    mostraErro("ERRO: distensao > 21.2");
    distensaoResultante = 21.2;
  }
  if (anguloResultante > 90)
  {
    mostraErro("ERRO: angulo > 90");
    anguloResultante = 90;
  }
}

//FUNÇÕES PARA A DISTENSÃO NO NEMA
void distensaoNema ()
{
  digitalWrite (PINdirectionNEMA, LOW);
  for (i = 0; i * 1.8 <= 10 * distensaoResultante; i++)
  {
    digitalWrite (PINenableNEMA, LOW);
    digitalWrite (PINpulseNEMA, HIGH);
    delay (5);
    digitalWrite (PINpulseNEMA, LOW);
    delay (5);
  }
}

void distensaoNema2 ()
{
  digitalWrite (PINdirectionNEMA, LOW);
  for (i = 0; i * 1.8 <= 10 * 0.1; i++)
  {
    digitalWrite (PINenableNEMA, LOW);
    digitalWrite (PINpulseNEMA, HIGH);
    delay (5);
    digitalWrite (PINpulseNEMA, LOW);
    delay (5);
  }
}

//FUNÇÃO PARA A ANGULAÇÃO DA BASE
void anguloBase()
{
  encoderEstadoI = digitalRead(encoderA);
  if (encoderEstadoI != encoderEstadoF)
  {
    if (digitalRead(encoderB) != encoderEstadoI)
    {
      angulo ++;
    } else
    {
      angulo --;
    }
    int angulo = (90 - 4.5 * angulo);
  }
  encoderEstadoF = encoderEstadoI;
}

//FUNÇÃO PARA INSTANTE DE SAÍDA
void instanteSaida()
{
  if (digitalRead(PINpouso) == 1)
  {
    tempoSaida = millis ();
  }
}

//FUNÇÃO PARA INSTANTE DE POUSO
void instantePouso()
{
  if (analogRead (serieLDR1) < 40)
  {
    tempoPouso = millis();
    delay(400);
  }
}


//FUNÇÃO PARA DETERMINAR O LOCAL DA QUEDA
void localQueda()
{
  if (analogRead(serieBotoes2) > 80 && analogRead(serieBotoes2) < 130)
  {
    PINqueda1 = 5;
    delay(1000);
  } else if (analogRead(serieBotoes2) > 130 && analogRead(serieBotoes2) < 150)
  {
    PINqueda2 = 10;
    delay(1000);
  } else if (analogRead(serieBotoes2) > 150 && analogRead(serieBotoes2) < 180)
  {
    PINqueda3 = 15;
    delay(1000);
  } else if (analogRead(serieBotoes2) > 180 && analogRead(serieBotoes2) < 220)
  {
    PINqueda4 = 20;
    delay(1000);
  } else if (analogRead(serieBotoes2) > 220 && analogRead(serieBotoes2) < 270)
  {
    PINqueda6 = 25;
    delay(1000);
  } else if (analogRead(serieBotoes2) > 270 && analogRead(serieBotoes2) < 400)
  {
    PINqueda7 = 30;
    delay(1000);
  } else if (analogRead(serieBotoes2) > 400 && analogRead(serieBotoes2) < 600)
  {
    PINqueda8 = 35;
    delay(1000);
  } else  if (analogRead(serieBotoes2) > 600 && analogRead(serieBotoes2) < 1300)
  {
    PINqueda9 = 40;
    delay(1000);
  }
}

//FUNÇÃO PARA MOSTRAR DADOS FINAIS
void mostrarDados(char *mensagem, float d0, float d1)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(mensagem);
  lcd.setCursor(0, 1);
  lcd.print(d0); lcd.print("; "); lcd.print(d1);
  delay (4000);
}


////////////////////////
///////////////////SETUP
////////////////////////
void setup()
{
  pinMode(PINsubtrair, INPUT);
  pinMode (encoderA, INPUT);
  pinMode (encoderB, INPUT);

  pinMode(PINenableNEMA, OUTPUT);
  pinMode(PINpulseNEMA, OUTPUT);
  pinMode(PINdirectionNEMA, OUTPUT);

  encoderEstadoF = digitalRead(encoderA);

  analogWrite (LDC, 0);
  lcd.begin(16, 2);
}
int lancamento = 0;


////////////////////////
////////////////////LOOP
////////////////////////
void loop()
{
  //ENTRAR COM OS PARÂMETROS
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("iniciando");
  lcd.setCursor(6, 1);
  lcd.print("...");
  delay (1000);
  estado = INICIAR;
  distensaoResultante = 0;
  anguloResultante = 0;
  lancamento = 0;

  determinarBotao();
  while (PINresetLCD == 0)
  {
    while (estado != INCLINAR)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LANCADOR");
      delay(1000);
      determinarBotao();
      if (PINpassarLCD == 1)
      {
        lcd.clear();
        delay(1000);

        estado = DISTENDER;

        determinarBotao();
        while ((PINpassarLCD == 0) && (PINresetLCD == 0))
        {
          distensaoOUangulo();
          determinarBotao();
          distensaoResultante2 = distensaoResultante;
          if (PINpassarLCD == 1)
          {
            lcd.clear();
            delay(1000);
            estado = INCLINAR;
            determinarBotao();

            while ((PINpassarLCD == 0) && (PINresetLCD == 0))
            {
              determinarBotao();
              distensaoOUangulo();
              anguloResultante2 = anguloResultante;
            }
          }
        }
      }
    }

    //AJUSTAR ÂNGULO
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ajustar o angulo");
    lcd.setCursor(6, 1);
    lcd.print("...");
    delay(3000);
    anguloBase();
    determinarBotao();
    while ((PINpassarLCD == 0) && (PINresetLCD == 0) )
    {
      anguloBase();
      determinarBotao();

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("diminua o angulo");
      delay(15000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("angulo ajustado");
      delay(10000);
    }
    lcd.clear();
    delay(1000);

    //AJUSTAR CATRACA
    determinarBotao();
    while (PINpassarLCD == 0 && (PINresetLCD == 0) )
    {
      determinarBotao();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ajuste a catraca para a distensão desejada");
      delay(1000);
    }

    //LANÇAR
    determinarBotao();
    while (PINdistensaoLeft == 0 && (PINresetLCD == 0) )
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("aguardando lancamento");
      lcd.setCursor(6, 1);
      lcd.print("...");
      delay(1000);
      determinarBotao();
      if (PINdistensaoLeft == 1)
      {
        lcd.clear();
        delay(1000);
        distensaoNema();
      }
    }

    //AJUSTE FINO PARA LANÇAR
    determinarBotao();
    while (PINpouso == 0 && PINresetLCD == 0 && PINpassarLCD == 0)
    {
      determinarBotao();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("realize uma distensao fina");
      lcd.setCursor(6, 1);
      lcd.print("...");
      delay(1000);
      if (PINdistensaoLeft == 1)
      {

        lcd.clear();
        delay(1000);
        distensaoNema2();
      }
    }
    lcd.clear();
    delay(1000);
    //DADOS
    determinarBotao();
    while (PINresetLCD == 0 && PINpassarLCD == 0)
    {
      determinarBotao();

      instanteSaida();
      instantePouso();
      localQueda();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("esperando pelos dados");
      lcd.setCursor(6, 1);
      lcd.print("...");
      delay (2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dist; Angul");
      lcd.setCursor(0, 1);
      lcd.print("15,6 cm; 45");
      delay (2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tempo lancamento");
      lcd.setCursor(0, 1);
      lcd.print("0,4 s");
      delay (2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("alcance horizontal");
      lcd.setCursor(0, 1);
      lcd.print("100 cm");
      delay (2000);
            lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("mostrar novam.?");
      delay (3000);
      determinarBotao();

    }
  }
}
