#include <Servo.h>
Servo servo1;

#define pinS0 8
#define pinS1 9
#define pinS2 12
#define pinS3 11
#define pinOut 10
#define pinLED 7

//Pinos dos LEDs
#define pinoLedVerm 2
#define pinoLedVerd 3
#define pinoLedAzul 4

unsigned int valorVermelho = 0;
unsigned int valorVerde = 0;
unsigned int valorAzul = 0;
unsigned int valorBranco = 0;

void detectaCor();

void setup()
{
  servo1.attach (7);
  pinMode(pinS0, OUTPUT);
  pinMode(pinS1, OUTPUT);
  pinMode(pinS2, OUTPUT);
  pinMode(pinS3, OUTPUT);
  pinMode(pinLED, OUTPUT);
  pinMode(pinOut, INPUT);


//vermelho: s2 low e s3 low
//branco/sem filtro: s2 low
//azul: s2 low e s3 high
//verde: s2 high

  Serial.begin(9600);
  digitalWrite(pinS0, HIGH);
  digitalWrite(pinS1, LOW);

  delay(2000);


}

void loop()
{
 
  detectaCor();
  
  delay(1000);
  Serial.print("Vermelho :");
  Serial.print(valorVermelho);

  Serial.print(" Verde : ");
  Serial.print(valorVerde);

  Serial.print(" Azul : ");
  Serial.print(valorAzul);

  Serial.print(" Branco : ");
  Serial.print(valorBranco);
  Serial.println();
  

  //Verifica se a cor vermelha foi detectada
  if ((valorVermelho < valorAzul) &&
      (valorVermelho < valorVerde) &&
      (valorBranco < 1000)) {
    Serial.println("Vermelho");
    Serial.println("O Vermelho foi o mais usado");
    servo1.write(0);

  } else if ((valorAzul < valorVermelho) &&  //Verifica se a cor azul foi detectada
             (valorAzul < valorVerde) &&
             (valorBranco < 1000)) {
    Serial.println("Azul");
    Serial.println("O Azul foi o mais usado");
    servo1.write(90);
   
  } else if ((valorVerde < valorVermelho) &&  //Verifica se a cor verde foi detectada
             (valorVerde < valorAzul) &&
             (valorBranco < 1000)) {
    Serial.println("Verde");
     Serial.println("O Verde foi o mais usado");
     servo1.write(180);

     
  Serial.println();
             }
}
// *********** Leitura do sensor de cor ********************
void detectaCor() {
  //Vermelho
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, LOW);
  valorVermelho = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);
  
  //Sem filtro
  digitalWrite(pinS2, HIGH);
  valorBranco = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  //Azul
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, HIGH);
  valorAzul = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  //Verde
  digitalWrite(pinS2, HIGH);
  valorVerde = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);
}
