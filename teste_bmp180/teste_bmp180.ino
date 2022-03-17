#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Servo.h>

#define pinServo 9
#define buzzer 8

Adafruit_BMP085 bmp180;

Servo servo;

float alt0 = 0.0, alt1 = 0.0, alt2 = 0.0, alt3 = 0.0; //Valores de referencia de altura
float media_alt = 0.0, percent;
float alt_anterior = 0.0, maior_alt = 0.0, alt_atual = 0.0, alt_inicial = 0.0;

int cont = 0;

bool condicao = false;

void setup() {
  Serial.begin(9600);
  if(!bmp180.begin()) 
  {
    Serial.println("Sensor nao encontrado !!");
    while(1){}
  }

  Serial.println("Sensor iniciado !!");
  
  pinMode(buzzer, OUTPUT);
  servo.attach(pinServo);

  //Condição de teste do servo (pode retirar depois)
  servo.write(60);
  delay(200);
  servo.write(142);
  delay(200);
  servo.write(60);

  //Testa o buzzer
  tone(buzzer,261); //Dó  
  delay(200); 
  tone(buzzer,293); // Ré         
  delay(200);    
  noTone(buzzer); //Desativa buzzer
}

void loop() {
  Serial.print("Altitude : ");
  Serial.print(alt_atual);
  Serial.println(" m");
  
  servo.write(60);

  coleta(); 
  delay(500);

  condicao = altimetro(alt_inicial, alt1, alt2, alt3);

  if(condicao == true)
  {
    servo.write(142);
    Serial.print("DEU CERTO");

    //Avisa que o servo acionou
    tone(buzzer,261); //Dó  
    delay(500);     
    noTone(buzzer);

    exit(0); //teste para parar execução do programa (se der errado, tirar depois)
  }
  Serial.println("");
}

//Calibração do sensor
float calibracao_alt() {
  float alt0 = 0, alt1 = 0, alt2 = 0, alt3 = 0, media_alt, percent = 0.05;
  alt0 = bmp180.readAltitude();
  delay(30);
  alt1 = bmp180.readAltitude();
  delay(30);
  alt2 = bmp180.readAltitude();
  delay(30);
  alt3 = bmp180.readAltitude();
  media_alt = (alt1 + alt2 + alt3) / 3;
  if (alt0 >= (media_alt + (media_alt * percent)) || alt0 <= (media_alt - (media_alt * percent))) { // verifica se o valor coletado está dentro do intervalo gerado pela média
    return media_alt;
  } 
  else {
    return alt0;
  }
}

// Coleta das altitudes
void coleta()
{
  alt0 = bmp180.readAltitude(); //Valor de referencia (altura inicial)
  delay(100);
  alt1 = bmp180.readAltitude();
  delay(100);
  alt2 = bmp180.readAltitude();
  delay(100);
  alt3 = bmp180.readAltitude();

  alt_inicial = calibracao_alt();

//=============================================================================================================================================================================
  percent = 0.001;

  if (alt0 >= (media_alt + (media_alt * percent)) || alt0 <= (media_alt - (media_alt * percent))) { // verifica se o valor coletado está dentro do intervalo gerado pela média
    alt_atual = media_alt - alt_inicial;
  } 
  else {
    alt_atual = alt0 - alt_inicial;
  }
//=============================================================================================================================================================================
}

bool altimetro(float altura, float alt1, float alt2, float alt3)
{
  alt_anterior = alt_inicial;
  if(alt_inicial >= 1.5)
  { 
    // Medias das altitudes
    media_alt = (alt1 + alt2 + alt3)/3;


    // Checa se a media das altitudes eh maior que a altitude coletada
    if(media_alt > alt_anterior)
    {
      maior_alt = media_alt;
    }

    // Incrementa quando a maior altitude eh maior que a media 
    if(maior_alt > media_alt)
    {
      cont++;
    }

    Serial.print("MAIOR altura = ");
    Serial.println(maior_alt);
    delay(100);


    if(cont == 3)
    {
      cont = 0;
      return true;
    }
  }
  return false;
}
 
