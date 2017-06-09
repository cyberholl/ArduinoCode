/* Variaveis globais*/
int linhas; // Numero de pontos
String inputString; //string recebida
int transformacao[4][4]; // matriz de transformações geométricas
int recebeu_matriz; //
int recebeu_coordenadas; //
int vector[320][2];

void setup() {
  // put your setup code here, to run once:
  /* Colocar frequencia pinos em maximo*/
  setPwmFrequencyUNO(11, 1); // Pino 11
  setPwmFrequencyUNO(3, 1); // Pino 3
  setPwmFrequencyUNO(10, 1); // Pino 10
  setPwmFrequencyUNO(9, 1); // Pino 9
  pinMode(12, OUTPUT); //laser
  digitalWrite(12, LOW); //laser
  recebeu_matriz = 0;
  recebeu_coordenadas = 0;
  linhas = 0;
   digitalWrite(12, LOW);
  // Abrir porta série
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available() > 0)
  {
   
    inputString = Serial.readStringUntil(':'); //Read until receive : ( Inicio da Mensagem)
    /* Primeira Parte - Numero de pontos e as respectivas coordenadas*/
    inputString = Serial.readStringUntil(';');
    int    booleana = inputString.toInt();
    if (booleana > 0) {
     if(booleana==1){
      digitalWrite(12, HIGH);
      }else if(booleana==2){
    digitalWrite(12, LOW);
    
    }
      inputString = Serial.readStringUntil(';');
      linhas = inputString.toInt();
      int contador = 0; // contador = 0 para cenas
      do
      {
        recebeu_coordenadas = 1;
        int numero = contador + 1;
        inputString = Serial.readStringUntil(';');
        vector[numero][1] = inputString.toInt();
        inputString = Serial.readStringUntil(';');
        vector[numero][2] = inputString.toInt();
        contador = contador + 1;
      } while (contador < linhas);
    }
  }
  /*
      Colocar o ponteiro laser no respectivo local
  */

  if (recebeu_coordenadas != 0)
  {
    Ler_vetor();
  }
}

void Ler_vetor() {
  int x;
  int y;
  for (int i = 1; i <= linhas; i++) {
    x = vector[i][1];
    y = vector[i][2];
    Desenhar_coordenadas(x, y);
    delay(1);
  }
}

void Desenhar_coordenadas(int x, int y) {
  int anguloy = abs(y) * 255 / 20;
  int angulox = abs(x) * 255 / 20;
  if (x >= 0) {
    analogWrite(11, angulox);
    analogWrite(3, 0);
  }
  else if (x < 0) {
    analogWrite(3, angulox);
    analogWrite(11, 0);
  }
  if (y >= 0) {
    analogWrite(10, anguloy);
    analogWrite(9, 0);
  }
  else if (y < 0) {
    analogWrite(9, anguloy);
    analogWrite(10, 0);
  }
}


/* Colocar arduino na frequencia maxima */
void setPwmFrequencyUNO(int pin, int divisor) {
  byte mode;
  if (pin == 9 || pin == 10) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      default: return;
    }
    TCCR1B = TCCR1B & 0b11111000 | mode;
  } else if (pin == 3 || pin == 11) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
